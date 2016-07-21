#include "GeomPoints.h"

#include "GeomPoint.h"
#include "WorldSettings.h"

GeomPoints::GeomPoints()
{
}

void GeomPoints::add(double x, double y, double z)
{
	osg::ref_ptr<GeomPoint> point = new GeomPoint;
	point->setPosition(x, y, z);
	point->setNodeMask(castShadowMask);
	addChild(point.get());
}

void GeomPoints::get(int idx, double& x, double& y, double& z)
{
	osg::ref_ptr<GeomPoint> point = static_cast<GeomPoint*>(getChild(idx));
	x = point->x();
	y = point->y();
	z = point->z();
}

GeomPoint * GeomPoints::get(int idx)
{
	osg::ref_ptr<GeomPoint> point = static_cast<GeomPoint*>(getChild(idx));
	return point.get();
}

int GeomPoints::indexOf(GeomPoint * point)
{
	return this->getChildIndex(point);
}

void GeomPoints::modify(int idx, double x, double y, double z)
{
	osg::ref_ptr<GeomPoint> point = static_cast<GeomPoint*>(getChild(idx));
	point->setPosition(x, y, z);
}

void GeomPoints::clearPoints()
{
	this->removeChildren(0, this->getNumChildren()-1);
}

GeomPoints::~GeomPoints()
{
}
