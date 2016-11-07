#include "GeomPoint.h"

#include <osg/ShapeDrawable>

#include "WorldSettings.h"

GeomPoint::GeomPoint()
{
	this->setNode(WorldSettings::getInstance().pointShape());
	this->setName("GeomPoint");
	this->setUserValue("GeomPoint", reinterpret_cast<std::uintptr_t>(this));
	this->node()->setName("GeomPoint");
	this->node()->setUserValue("Owner", std::string("GeomPoint"));
	this->node()->setUserValue("OwnerRef", reinterpret_cast<std::uintptr_t>(this));
}

GeomPoint::~GeomPoint()
{
}
