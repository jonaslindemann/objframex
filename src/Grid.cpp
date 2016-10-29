#include "Grid.h"

#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/LineWidth>

#include "WorldSettings.h"

void Grid::createGrid()
{
	double dx = m_width / m_xDiv;
	double dy = m_height / m_yDiv;

	double dx2 = m_width / m_xSubDiv;
	double dy2 = m_height / m_ySubDiv;

	osg::Vec4 gridColor(153.0 / 255.0, 189.0 / 255.0, 144.0 / 255.0, 0.5f);
	gridColor *= 0.8;
	osg::Vec4 gridColor2(153.0 / 255.0, 189.0 / 255.0, 144.0 / 255.0, 0.5f);
	gridColor2 *= 0.8;

	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;

	for (int i = 0; i < m_yDiv + 1; i++)
	{
		vertices->push_back(osg::Vec3(-m_width / 2.0, -m_height / 2.0 + dy * i, 0.0f));
		vertices->push_back(osg::Vec3(m_width / 2.0, -m_height / 2.0 + dy * i, 0.0f));
		colors->push_back(gridColor);
		colors->push_back(gridColor);
	}

	for (int i = 0; i < m_xDiv + 1; i++)
	{
		vertices->push_back(osg::Vec3(-m_width / 2.0 + dx * i, -m_height / 2.0, 0.0f));
		vertices->push_back(osg::Vec3(-m_width / 2.0 + dx * i, m_height / 2.0, 0.0f));
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

	osg::ref_ptr<osg::Vec3Array> vertices2 = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> colors2 = new osg::Vec4Array;
	osg::ref_ptr<osg::Vec3Array> normals2 = new osg::Vec3Array;

	for (int i = 0; i < m_ySubDiv + 1; i++)
	{
		vertices2->push_back(osg::Vec3(-m_width / 2.0, -m_height / 2.0 + dy2 * i, 0.0f));
		vertices2->push_back(osg::Vec3(m_width / 2.0, -m_height / 2.0 + dy2 * i, 0.0f));
		colors2->push_back(gridColor2);
		colors2->push_back(gridColor2);
	}

	for (int i = 0; i < m_xSubDiv + 1; i++)
	{
		vertices2->push_back(osg::Vec3(-m_width / 2.0 + dx2 * i, -m_height / 2.0, 0.0f));
		vertices2->push_back(osg::Vec3(-m_width / 2.0 + dx2 * i, m_height / 2.0, 0.0f));
		colors2->push_back(gridColor);
		colors2->push_back(gridColor);
	}

	normals2->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	osg::ref_ptr<osg::Geometry> quad2 = new osg::Geometry;
	quad2->setVertexArray(vertices2.get());
	quad2->setNormalArray(normals2.get());
	quad2->setNormalBinding(osg::Geometry::BIND_OVERALL);
	quad2->setColorArray(colors2.get());
	quad2->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	quad2->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, vertices2->getNumElements()));

	m_gMain->removeDrawables(0);
	m_gSub->removeDrawable(0);

	m_gMain->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	m_gMain->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(2.0f), osg::StateAttribute::ON);
	m_gMain->addDrawable(quad.get());
	m_gSub->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	m_gSub->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(1.0f), osg::StateAttribute::ON);
	m_gSub->addDrawable(quad2.get());
}

Grid::Grid()
{
	m_gMain = new osg::Geode;
	m_gSub= new osg::Geode;
	this->addChild(m_gMain);
	this->addChild(m_gSub);
	m_width = 50.0;
	m_height = 50.0;
	m_xDiv = 50;
	m_yDiv = 50;
	m_xSubDiv = 250;
	m_ySubDiv = 250;
	this->createGrid();
}

double Grid::width()
{
	return m_width;
}

double Grid::height()
{
	return m_height;
}

int Grid::xDiv()
{
	return m_xDiv;
}

int Grid::yDiv()
{
	return m_yDiv;
}

int Grid::xSubDiv()
{
	return m_xSubDiv;
}

int Grid::ySubDiv()
{
	return m_ySubDiv;
}

void Grid::setWidth(double width)
{
	m_width = width;
}

void Grid::setHeight(double height)
{
	m_height = height;
}

void Grid::setXDiv(int division)
{
	m_xDiv = division;
}

void Grid::setYDiv(int division)
{
	m_yDiv = division;
}

void Grid::setXSubDiv(int division)
{
	m_xSubDiv = division;
}

void Grid::setYSubDiv(int division)
{
	m_ySubDiv = division;
}

Grid::~Grid()
{
}
