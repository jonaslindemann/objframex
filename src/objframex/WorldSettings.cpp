#include "WorldSettings.h"

WorldSettings::WorldSettings()
{
	m_lineRadius = 0.125;
	m_nodeRadius = 0.25;

	m_pointShape = new osg::ShapeDrawable;
	m_tesselationHints = new osg::TessellationHints;
	m_tesselationHints->setDetailRatio(0.2);
	m_lightSource = new osg::LightSource;
	m_lightSource->getLight()->setPosition(osg::Vec4(5.0, 10.0, 20.0, 0.0));
	m_lightSource->getLight()->setAmbient(osg::Vec4(0.4, 0.4, 0.4, 1.0));
	m_lightSource->getLight()->setDiffuse(osg::Vec4(0.8, 0.8, 0.8, 1.0));
	m_lightSource->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

}

void WorldSettings::updateShapes()
{
	m_pointShape->setShape(new osg::Sphere(osg::Vec3(0.0, 0.0, 0.0), m_nodeRadius));
	m_pointShape->setTessellationHints(m_tesselationHints);

	m_selectionMaterial = new osg::Material;
	m_selectionMaterial->setDiffuse(osg::Material::FRONT, osg::Vec4(1.0, 1.0, 0.0, 0.5));
	m_selectionMaterial->setSpecular(osg::Material::FRONT, osg::Vec4(1.0, 1.0, 1.0, 0.5));
	m_selectionMaterial->setShininess(osg::Material::FRONT, 100.0);

	m_pointMaterial = new osg::Material;
	m_pointMaterial->setDiffuse(osg::Material::FRONT, osg::Vec4(1.0, 0.5, 0.5, 1.0));
	m_pointMaterial->setSpecular(osg::Material::FRONT, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	m_pointMaterial->setShininess(osg::Material::FRONT, 100.0);

	m_lineMaterial = new osg::Material;
	m_lineMaterial->setDiffuse(osg::Material::FRONT, osg::Vec4(0.5, 1.0, 0.5, 1.0));
	m_lineMaterial->setSpecular(osg::Material::FRONT, osg::Vec4(1.0, 1.0, 1.0, 1.0));
	m_lineMaterial->setShininess(osg::Material::FRONT, 100.0);

	m_pointShape->getOrCreateStateSet()->setAttribute(m_pointMaterial);
}

WorldSettings& WorldSettings::getInstance()
{
	static WorldSettings m_instance; // Guaranteed to be destroyed.

	return m_instance;
}

void WorldSettings::setPointShape(osg::ShapeDrawable* shape)
{
	this->m_pointShape = shape;
}

osg::ShapeDrawable* WorldSettings::pointShape()
{
	return m_pointShape.get();
}

void WorldSettings::setPointMaterial(osg::Material * material)
{
	m_pointMaterial = material;
	this->updateShapes();
}

osg::Material * WorldSettings::pointMaterial()
{
	return m_pointMaterial.get();
}

void WorldSettings::setLineMaterial(osg::Material * material)
{
	m_lineMaterial = material;
	this->updateShapes();
}

osg::Material * WorldSettings::lineMaterial()
{
	return m_lineMaterial.get();
}

void WorldSettings::setSelectionMaterial(osg::Material * material)
{
	m_selectionMaterial = material;
	this->updateShapes();
}

osg::Material * WorldSettings::selectionMaterial()
{
	return m_selectionMaterial.get();
}

void WorldSettings::setLineRadius(double radius)
{
	m_lineRadius = radius;
	this->updateShapes();
}

double WorldSettings::lineRadius()
{
	return m_lineRadius;;
}

void WorldSettings::setNodeRadius(double radius)
{
	m_nodeRadius = radius;
	this->updateShapes();
}

double WorldSettings::nodeRadius()
{
	return m_nodeRadius;
}

osg::TessellationHints * WorldSettings::tesselationHints()
{
	return m_tesselationHints.get();
}

osg::LightSource * WorldSettings::lightSource()
{
	return m_lightSource.get();
}
