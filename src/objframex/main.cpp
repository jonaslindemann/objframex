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

double randomValue(double minVal, double maxVal)
{
	double range = maxVal - minVal;
	return minVal + range*((double)rand() / (double)RAND_MAX);
}

osg::Geometry* createExtrusion(osg::Vec3Array* vertices, const osg::Vec3& direction, float length)
{
	osg::ref_ptr<osg::Vec3Array> newVertices = new osg::Vec3Array;
	newVertices->insert(newVertices->begin(), vertices->begin(), vertices->end());

	unsigned int numVertices = vertices->size();
	osg::Vec3 offset = direction * length;
	for (osg::Vec3Array::reverse_iterator ritr = vertices->rbegin();
	ritr != vertices->rend(); ++ritr)
	{
		newVertices->push_back((*ritr) + offset);
	}

	osg::ref_ptr<osg::Geometry> extrusion = new osg::Geometry;
	extrusion->setVertexArray(newVertices.get());
	extrusion->addPrimitiveSet(new osg::DrawArrays(GL_POLYGON, 0, numVertices));
	extrusion->addPrimitiveSet(new osg::DrawArrays(GL_POLYGON, numVertices, numVertices));

	osgUtil::Tessellator tessellator;
	tessellator.setTessellationType(osgUtil::Tessellator::TESS_TYPE_POLYGONS);
	tessellator.setWindingType(osgUtil::Tessellator::TESS_WINDING_ODD);
	tessellator.retessellatePolygons(*extrusion);

	osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt(GL_QUAD_STRIP);
	for (unsigned int i = 0; i<numVertices; ++i)
	{
		sideIndices->push_back(i);
		sideIndices->push_back((numVertices - 1 - i) + numVertices);
	}
	sideIndices->push_back(0);
	sideIndices->push_back(numVertices * 2 - 1);
	extrusion->addPrimitiveSet(sideIndices.get());

	osgUtil::SmoothingVisitor::smooth(*extrusion);
	return extrusion.release();
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
    osg::setNotifyLevel(osg::INFO);

    std::cout << "Test" << std::endl;
    //osg::notify(osg::NOTICE) << "TESTING-------" << std::endl;

	srand((unsigned)time(0));

	osg::ArgumentParser arguments(&argc, argv);
	osg::DisplaySettings::instance()->setNumMultiSamples(4);

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

	// ----- Setup viewer ----------------------------------------------------

	osgViewer::Viewer viewer;

    osg::ref_ptr<PickHandler> pickHandler = new PickHandler;
    root->addChild(pickHandler->getOrCreateSelectionBox());
    viewer.addEventHandler(pickHandler);

	osg::ref_ptr<ModelController> controller = new ModelController;
	viewer.addEventHandler(controller.get());

	osgViewer::StatsHandler* statsHandler = new osgViewer::StatsHandler;
	statsHandler->setKeyEventTogglesOnScreenStats('i');
	viewer.addEventHandler(statsHandler);

    osg::ref_ptr<KeyboardFpsManipulator> fpsManip = new KeyboardFpsManipulator;
	osg::ref_ptr<osgGA::TrackballManipulator> manip = new osgGA::TrackballManipulator;
    osg::ref_ptr<osgGA::UFOManipulator> ufoManip = new osgGA::UFOManipulator;

    //viewer.setCameraManipulator(ufoManip.get());
    //viewer.setCameraManipulator(fpsManip.get());
    viewer.setCameraManipulator(manip.get());

    //viewer.setUpViewInWindow(50,50, 1024,768);
    viewer.setUpViewOnSingleScreen();
	viewer.setSceneData(root.get());
	viewer.getCameraManipulator()->setAutoComputeHomePosition(false);
	viewer.getCameraManipulator()->setHomePosition(osg::Vec3(0.0, 40.0, 10.0), osg::Vec3(0, 0, 0), osg::Vec3(0, 0, 1));
	viewer.home();

	std::vector<osgViewer::GraphicsWindow*> windows;

	viewer.getWindows(windows);
	windows[0]->useCursor(true);
	fpsManip->setWindow(windows[0]);

	return viewer.run();
}
