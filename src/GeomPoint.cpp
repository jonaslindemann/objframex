#include "GeomPoint.h"

#include <osg/ShapeDrawable>

#include "WorldSettings.h"

GeomPoint::GeomPoint()
{
	this->setNode(WorldSettings::getInstance().pointShape());
}

GeomPoint::~GeomPoint()
{
}
