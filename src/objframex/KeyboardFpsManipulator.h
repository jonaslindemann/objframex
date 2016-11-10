#pragma once

#include <osgGA/GUIEventHandler>
#include <osgGA/StandardManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>

#ifdef WIN32
#include <Windows.h>
#include <XInput.h>
#endif

//#include "oculusdevice.h"

class KeyboardFpsManipulator : public osgGA::FirstPersonManipulator {
private:
    bool m_moveForward;
	bool m_moveBackward;
	bool m_moveLeft;
	bool m_moveRight;

    double m_dt;
    double m_t0;

#ifdef WIN32
	XINPUT_STATE m_ctrlState;
#endif

	osgViewer::Viewer* m_viewer;

	osgViewer::GraphicsWindow* m_window;
public:
    KeyboardFpsManipulator();


    KeyboardFpsManipulator(const KeyboardFpsManipulator& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
        : osgGA::FirstPersonManipulator(copy, copyop) {}


    META_Object(osgGA, osgGA::FirstPersonManipulator)

    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);


	void setWindow(osgViewer::GraphicsWindow* window);
protected:
	virtual bool performMovement();

	void moveForward(const osg::Quat& rotation, const double distance);
};
