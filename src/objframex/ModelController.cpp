#include "ModelController.h"

#include <osg/LightSource>

#include "WorldSettings.h"

bool ModelController::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:
		switch (ea.getKey())
		{
        case 'e':
			osg::ref_ptr<osg::LightSource> source = WorldSettings::getInstance().lightSource();

			osg::Vec4 pos = source->getLight()->getPosition();
			
			osg::Vec3 pos3(pos.x(), pos.y(), pos.z());

			osg::Quat q;
			q.makeRotate(osg::PI/360.0f, osg::Z_AXIS);
		
			pos3 = q*pos3;

			source->getLight()->setPosition(osg::Vec4(pos3.x(), pos3.y(), pos3.z(), 0.0));
			break;
		}
	}
	return false;
}
