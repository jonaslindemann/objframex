#include <cstdlib> 
#include <ctime> 
#include <iostream>

#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/TexGen>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
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

osg::Geode* createGrid(double width, double depth, int xDiv, int yDiv)
{
	double dx = width / xDiv;
	double dy = depth / yDiv;

	osg::Vec4 gridColor(153.0 / 255.0, 189.0 / 255.0, 144.0 / 255.0, 1.0f);
	gridColor *= 0.8;

	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;

	for (int i = 0; i < yDiv + 1; i++)
	{
		vertices->push_back(osg::Vec3(-width / 2.0, -depth / 2.0 + dy * i, 0.0f));
		vertices->push_back(osg::Vec3(width / 2.0, -depth / 2.0 + dy * i, 0.0f));
		colors->push_back(gridColor);
		colors->push_back(gridColor);
	}

	for (int i = 0; i < xDiv + 1; i++)
	{
		vertices->push_back(osg::Vec3(-width / 2.0 + dx * i, -depth / 2.0, 0.0f));
		vertices->push_back(osg::Vec3(-width / 2.0 + dx * i, depth / 2.0, 0.0f));
		colors->push_back(gridColor);
		colors->push_back(gridColor);
	}

	normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
	quad->setVertexArray(vertices.get());
	quad->setNormalArray(normals.get());
	quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
	quad->setColorArray(colors.get());
	quad->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	quad->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, vertices->getNumElements()));

	osg::ref_ptr<osg::Geode> grid = new osg::Geode;
	grid->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	grid->addDrawable(quad.get());

	return grid.release();
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
	srand((unsigned)time(0));

	osg::ArgumentParser arguments(&argc, argv);

	osg::DisplaySettings::instance()->setNumMultiSamples(4);

	osg::ref_ptr<osg::ShapeDrawable> plane = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0, 0.0, -0.02), 100.0, 100.0, 0.01));
	plane->setColor(osg::Vec4(153.0 / 255.0, 189.0 / 255.0, 144.0 / 255.0, 1.0f));
	plane->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	plane->setNodeMask(rcvShadowMask);

	osg::ref_ptr<osg::Geode> grid = createGrid(100.0, 100.0, 100, 100);
	grid->setNodeMask(rcvShadowMask);

	osg::ref_ptr<osg::LightSource> source = new osg::LightSource;
	source->getLight()->setPosition(osg::Vec4(5.0, 10.0, 20.0, 0.0));
	source->getLight()->setAmbient(osg::Vec4(0.4, 0.4, 0.4, 1.0));
	source->getLight()->setDiffuse(osg::Vec4(0.8, 0.8, 0.8, 1.0));
	source->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

	osg::ref_ptr<osgShadow::ShadowMap> sm = new osgShadow::ShadowMap;
	sm->setLight(source.get());
	sm->setTextureSize(osg::Vec2s(4096, 4096));
	sm->setTextureUnit(1);
	sm->setAmbientBias(osg::Vec2(0.8, 0.2));

	osg::ref_ptr<osgShadow::ShadowedScene> ssRoot = new osgShadow::ShadowedScene;
	ssRoot->setShadowTechnique(sm.get());
	ssRoot->setReceivesShadowTraversalMask(rcvShadowMask);
	ssRoot->setCastsShadowTraversalMask(castShadowMask);

	osg::ref_ptr<SkyBox> skybox = createSkyBox(ssRoot.get());

	ssRoot->addChild(plane.get());
	ssRoot->addChild(grid.get());

	WorldSettings::getInstance().setNodeRadius(0.15);
	WorldSettings::getInstance().setLineRadius(0.075);

	osg::ref_ptr<GeomPoints> points = new GeomPoints;

	int nFloors = 10;
	int nCols = 4;
	int nRows = 4;

	for (int i = 0; i < nFloors; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			for (int k = 0; k < nRows; k++)
			{
				points->add(2.0*j, 2.0*k, 2.0*i);
			}
		}
	}

	osg::ref_ptr<GeomLines> lines = new GeomLines(points);

	for (int i = 0; i < nFloors-1; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			for (int k = 0; k < nRows; k++)
			{
				int idx0 = i * (nRows * nCols) + j*nCols + k;
				int idx1 = (i + 1) * (nRows * nCols) + j*nCols + k;
				lines->add(idx0, idx1);
			}
		}
	}

	for (int i = 1; i < nFloors; i++)
	{
		for (int k = 0; k < nRows; k++)
		{
			for (int j = 0; j < nCols-1; j++)
			{
				int idx0 = i * (nRows * nCols) + j*nCols + k;
				int idx1 = i * (nRows * nCols) + (j+1)*nCols + k;
				lines->add(idx0, idx1);
			}
		}
	}

	for (int i = 1; i < nFloors; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			for (int k = 0; k < nRows - 1; k++)
		    {
				int idx0 = i * (nRows * nCols) + j*nCols + k;
				int idx1 = i * (nRows * nCols) + j*nCols + k + 1;
				lines->add(idx0, idx1);
			}
		}
	}

 	ssRoot->addChild(points);
	ssRoot->addChild(lines);

	ssRoot->addChild(source.get());

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(skybox.get());
	root->addChild(ssRoot.get());

	osgViewer::Viewer viewer;

	osgViewer::StatsHandler* statsHandler = new osgViewer::StatsHandler;
	viewer.addEventHandler(statsHandler);

	osg::ref_ptr<osgGA::TrackballManipulator> manip = new osgGA::TrackballManipulator;
	viewer.setCameraManipulator(manip.get());

	viewer.setUpViewOnSingleScreen();
	viewer.setSceneData(root.get());
	viewer.getCameraManipulator()->setAutoComputeHomePosition(false);
	viewer.getCameraManipulator()->setHomePosition(osg::Vec3(0.0, 40.0, 10.0), osg::Vec3(0, 0, 0), osg::Vec3(0, 0, 1));
	viewer.home();

	return viewer.run();
}