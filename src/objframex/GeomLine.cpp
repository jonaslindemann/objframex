#include "GeomLine.h"

#include "WorldSettings.h"

/*
osg::Geode* createCylinder(osg::Vec3 StartPoint, osg::Vec3 EndPoint, float radius, osg::Vec4 CylinderColor)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::Vec3 center;
	float height;
	osg::ref_ptr<osg::Cylinder> cylinder;
	osg::ref_ptr<osg::Drawable> cylinderDrawable;
	osg::ref_ptr<osg::Material> pMaterial;

	height = (StartPoint - EndPoint).length();
	center = osg::Vec3((StartPoint.x() + EndPoint.x()) / 2, (StartPoint.y() + EndPoint.y()) / 2, (StartPoint.z() + EndPoint.z()) / 2);

	// This is the default direction for the cylinders to face in OpenGL
	osg::Vec3 z = osg::Vec3(0, 0, 1);

	// Get diff between two points you want cylinder along
	osg::Vec3 p = (StartPoint - EndPoint);

	// Get CROSS product (the axis of rotation)
	osg::Vec3 t = z ^ p;

	// Get angle. length is magnitude of the vector
	double angle = acos((z * p) / p.length());

	// Create a cylinder between the two points with the given radius
	cylinder = new osg::Cylinder(center, radius, height);
	cylinder->setRotation(osg::Quat(angle, osg::Vec3(t.x(), t.y(), t.z())));

	cylinderDrawable = new osg::ShapeDrawable(cylinder);
	geode->addDrawable(cylinderDrawable);

	// Set the color of the cylinder that extends between the two points.
	pMaterial = new osg::Material;
	pMaterial->setDiffuse(osg::Material::FRONT, CylinderColor);
	geode->getOrCreateStateSet()->setAttribute(pMaterial, osg::StateAttribute::OVERRIDE);

	// Add the cylinder between the two points to an existing group
	return geode.release();
}
*/

void GeomLine::createCylinder()
{
	osg::Vec3 center;
	float height;
	osg::ref_ptr<osg::Cylinder> cylinder;
	osg::ref_ptr<osg::ShapeDrawable> cylinderDrawable;

	osg::Vec3 startPoint(m_point0->x(), m_point0->y(), m_point0->z());
	osg::Vec3 endPoint(m_point1->x(), m_point1->y(), m_point1->z());

	height = (startPoint - endPoint).length();
	center = osg::Vec3((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2, (startPoint.z() + endPoint.z()) / 2);

	// This is the default direction for the cylinders to face in OpenGL
	osg::Vec3 z = osg::Vec3(0, 0, 1);

	// Get diff between two points you want cylinder along
	osg::Vec3 p = (startPoint - endPoint);

	// Get CROSS product (the axis of rotation)
	osg::Vec3 t = z ^ p;

	// Get angle. length is magnitude of the vector
	double angle = acos((z * p) / p.length());

	// Create a cylinder between the two points with the given radius
	cylinder = new osg::Cylinder(center, WorldSettings::getInstance().lineRadius(), height);
	cylinder->setRotation(osg::Quat(angle, osg::Vec3(t.x(), t.y(), t.z())));

	cylinderDrawable = new osg::ShapeDrawable(cylinder);
  	cylinderDrawable->setTessellationHints(WorldSettings::getInstance().tesselationHints());

	cylinderDrawable->setUserValue("Owner", std::string("GeomLine"));
	cylinderDrawable->setUserValue("OwnerRef", reinterpret_cast<std::uintptr_t>(this));

	m_geode->removeDrawables(0);
	m_geode->addDrawable(cylinderDrawable);

	// Set the color of the cylinder that extends between the two points.
	m_geode->getOrCreateStateSet()->setAttribute(WorldSettings::getInstance().lineMaterial(), osg::StateAttribute::OVERRIDE);
}

GeomLine::GeomLine()
{
	m_geode = new osg::Geode;
	this->addChild(m_geode);
	this->setUserValue("Owner", std::string("GeomLine"));
	this->setUserValue("OwnerRef", reinterpret_cast<std::uintptr_t>(this));
	m_geode->setUserValue("Owner", std::string("GeomLine"));
	m_geode->setUserValue("OwnerRef", reinterpret_cast<std::uintptr_t>(this));
}

void GeomLine::setPoints(GeomPoint * p0, GeomPoint * p1)
{
	m_point0 = p0;
	m_point1 = p1;
	this->createCylinder();
}

GeomPoint * GeomLine::p0()
{
	return m_point0.get();
}

GeomPoint * GeomLine::p1()
{
	return m_point1.get();
}

GeomLine::~GeomLine()
{
}
