#pragma once

#include <osgGA/GUIEventHandler>
#include <osgGA/StandardManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>

#include "oculusdevice.h"

class KeyboardFpsManipulator : public osgGA::FirstPersonManipulator {
private:
    bool m_moveForward;
	bool m_moveBackward;
	bool m_moveLeft;
	bool m_moveRight;

    double m_dt;
    double m_t0;

	osgViewer::Viewer* m_viewer;
	OculusDevice* m_oculusDevice;

	osgViewer::GraphicsWindow* m_window;
public:
    KeyboardFpsManipulator(OculusDevice* oculusDevice, osgViewer::Viewer* viewer);


    KeyboardFpsManipulator(const KeyboardFpsManipulator& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
        : osgGA::FirstPersonManipulator(copy, copyop) {}


    META_Object(osgGA, osgGA::FirstPersonManipulator)

    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);


	void setWindow(osgViewer::GraphicsWindow* window);
protected:
	virtual bool performMovement();

	void moveForward(const osg::Quat& rotation, const double distance);
};
