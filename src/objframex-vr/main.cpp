#include <cstdlib> 
#include <ctime> 
#include <iostream>

#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/TexGen>
#include <osg/LineWidth>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/UFOManipulator>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <osgShadow/SoftShadowMap>
#include <osgShadow/ShadowVolume>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/Tessellator>
#include "SkyBox.h"

#include "WorldSettings.h"
#include "PositionalObject.h"
#include "GeomPoint.h"
#include "GeomLine.h" 
#include "GeomPoints.h"
#include "GeomLines.h"
#include "ModelController.h"
#include "BasicFrameFactory.h"
#include "PickHandler.h"
#include "KeyboardFpsManipulator.h"
#include "Grid.h"

#include "oculusviewer.h"
#include "oculuseventhandler.h"

#include <osgGA/GUIEventHandler>

#include "KeyboardFpsManipulator.h"


double randomValue(double minVal, double maxVal)
{
	double range = maxVal - minVal;
	return minVal + range*((double)rand() / (double)RAND_MAX);
}

SkyBox* createSkyBox(const osg::Group* root)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(), root->getBound().radius())));
	geode->setCullingActive(false);

    osg::ref_ptr<osg::Image> posx = osgDB::readImageFile("images/sposx.png");
    osg::ref_ptr<osg::Image> negx = osgDB::readImageFile("images/snegx.png");
    osg::ref_ptr<osg::Image> posy = osgDB::readImageFile("images/sposz.png");
    osg::ref_ptr<osg::Image> negy = osgDB::readImageFile("images/snegz.png");
    osg::ref_ptr<osg::Image> posz = osgDB::readImageFile("images/snegy.png");
    osg::ref_ptr<osg::Image> negz = osgDB::readImageFile("images/sposy.png");

	osg::ref_ptr<SkyBox> skybox = new SkyBox;
	skybox->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::TexGen);
	skybox->setEnvironmentMap(0, posx, negx, posy, negy, posz, negz);
	skybox->addChild(geode.get());

	return skybox.release();
}

using namespace std;

int main(int argc, char** argv) 
{
    //osg::setNotifyLevel(osg::INFO);

    std::cout << "Test" << std::endl;
    //osg::notify(osg::NOTICE) << "TESTING-------" << std::endl;

	srand((unsigned)time(0));

	osg::ArgumentParser arguments(&argc, argv);
	osg::DisplaySettings::instance()->setNumMultiSamples(4);

	// ----- Setup oculus ----------------------------------------------------

	// Open the HMD
	float nearClip = 0.01f;
	float farClip = 10000.0f;
	float pixelsPerDisplayPixel = 1.0;
	float worldUnitsPerMetre = 1.0f;
	int samples = 4;
	osg::ref_ptr<OculusDevice> oculusDevice = new OculusDevice(nearClip, farClip, pixelsPerDisplayPixel, worldUnitsPerMetre, samples);

	// Exit if we do not have a valid HMD present
	if (!oculusDevice->hmdPresent())
	{
		osg::notify(osg::FATAL) << "Error: No valid HMD present!" << std::endl;
		return 1;
	}

	//const osg::BoundingSphere& bs = loadedModel->getBound();

	// Get the suggested context traits
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = oculusDevice->graphicsContextTraits();
	traits->windowName = "OsgOculusViewerExample";

	// ----- Shadowed scene---------------------------------------------------

	osg::ref_ptr<osgShadow::ShadowMap> sm = new osgShadow::ShadowMap;
	sm->setLight(WorldSettings::getInstance().lightSource());
	sm->setTextureSize(osg::Vec2s(4096, 4096));
	sm->setTextureUnit(1);
	sm->setAmbientBias(osg::Vec2(0.8, 0.2));

	osg::ref_ptr<osgShadow::ShadowedScene> ssRoot = new osgShadow::ShadowedScene;
	ssRoot->setShadowTechnique(sm.get());
	ssRoot->setReceivesShadowTraversalMask(rcvShadowMask);
	ssRoot->setCastsShadowTraversalMask(castShadowMask);

	// ----- Setup shadowed scene --------------------------------------------

	WorldSettings::getInstance().setNodeRadius(0.15);
	WorldSettings::getInstance().setLineRadius(0.075);

	osg::ref_ptr<BasicFrameFactory> frameFactory = new BasicFrameFactory;
    frameFactory->setSize(10, 5, 5);
	frameFactory->generate();

 	ssRoot->addChild(frameFactory->points());
	ssRoot->addChild(frameFactory->lines());
	ssRoot->addChild(WorldSettings::getInstance().lightSource());

	osg::ref_ptr<osg::ShapeDrawable> plane = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0, 0.0, -0.01), 100.0, 100.0, 0.01));
	plane->setColor(osg::Vec4(153.0 / 255.0, 189.0 / 255.0, 144.0 / 255.0, 1.0f));
	plane->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	plane->setNodeMask(rcvShadowMask);

	//osg::ref_ptr<osg::Geode> grid = createGrid(100.0, 100.0, 100, 100);
	//grid->setNodeMask(rcvShadowMask);

	osg::ref_ptr<Grid> grid = new Grid();

	ssRoot->addChild(plane.get());
	//ssRoot->addChild(grid.get());

	// ----- Add Sky box, shadow scene to root--------------------------------

	osg::ref_ptr<SkyBox> skybox = createSkyBox(ssRoot.get());

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(skybox.get());
	root->addChild(grid.get());
	root->addChild(ssRoot.get());

	const osg::BoundingSphere& bs = ssRoot->getBound();

	// ----- Setup viewer ----------------------------------------------------

	// Create a graphic context based on our desired traits
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

	if (!gc)
	{
		osg::notify(osg::NOTICE) << "Error, GraphicsWindow has not been created successfully" << std::endl;
		return 1;
	}

	if (gc.valid())
	{
		gc->setClearColor(osg::Vec4(0.2f, 0.2f, 0.4f, 1.0f));
		gc->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	osgViewer::Viewer viewer;

	viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	viewer.getCamera()->setGraphicsContext(gc.get());
	viewer.getCamera()->setViewport(0, 0, traits->width, traits->height);

	// Disable automatic computation of near and far plane
	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
	osg::ref_ptr<KeyboardFpsManipulator> cameraManipulator = new KeyboardFpsManipulator(oculusDevice.get(), &viewer);
	if (bs.valid())
	{
		// Adjust view to object view
		osg::Vec3 modelCenter = bs.center();
		osg::Vec3 eyePos = bs.center() + osg::Vec3(0, bs.radius(), 0);
		cameraManipulator->setHomePosition(eyePos, modelCenter, osg::Vec3(0, 0, 1));
	}
	viewer.setCameraManipulator(cameraManipulator.get());

	// Things to do when viewer is realized
	osg::ref_ptr<OculusRealizeOperation> oculusRealizeOperation = new OculusRealizeOperation(oculusDevice);
	viewer.setRealizeOperation(oculusRealizeOperation.get());

	osg::ref_ptr<OculusViewer> oculusViewer = new OculusViewer(&viewer, oculusDevice, oculusRealizeOperation);
	oculusViewer->addChild(root.get());
	viewer.setSceneData(oculusViewer.get());

	// Add statistics handler
	viewer.addEventHandler(new osgViewer::StatsHandler);

	viewer.addEventHandler(new OculusEventHandler(oculusDevice));

	viewer.run();

	return 0;
}
