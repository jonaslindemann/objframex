#include "KeyboardFpsManipulator.h"

#include <iostream>

#include <osgGA/GUIEventAdapter>

KeyboardFpsManipulator::KeyboardFpsManipulator():
    FirstPersonManipulator()
{
    m_moveForward = false;
	m_moveBackward = false;
	m_moveLeft = false;
	m_moveRight = false;
	m_dt = 0.0;
    m_t0 = 0.0;
	this->setAllowThrow(false);
}

/// Handles GUIEventAdapter::DRAG event.
bool KeyboardFpsManipulator::handleMouseMove(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	addMouseEvent(ea);

	if (performMovement())
		us.requestRedraw();

	us.requestContinuousUpdate(false);
	_thrown = false;

	return true;
}


void KeyboardFpsManipulator::setWindow(osgViewer::GraphicsWindow * window)
{
	m_window = window;
}

/// Make movement step of manipulator. Returns true if any movement was made.
bool KeyboardFpsManipulator::performMovement()
{
	using namespace osgGA;

	//std::cout << "performMovement" << std::endl;
	// return if less then two events have been added
	if (_ga_t0.get() == NULL || _ga_t1.get() == NULL)
		return false;

	// get delta time
	double eventTimeDelta = _ga_t0->getTime() - _ga_t1->getTime();
	if (eventTimeDelta < 0.)
	{
		OSG_WARN << "Manipulator warning: eventTimeDelta = " << eventTimeDelta << std::endl;
		eventTimeDelta = 0.;
	}

	// get deltaX and deltaY
	float dx = _ga_t0->getXnormalized() - _ga_t1->getXnormalized();
	float dy = _ga_t0->getYnormalized() - _ga_t1->getYnormalized();

	std::cout << dx << ", " << dy << std::endl;

	// return if there is no movement.
	if (dx == 0. && dy == 0.)
		return false;


	// call appropriate methods
	unsigned int buttonMask = _ga_t1->getButtonMask();
	if (buttonMask == GUIEventAdapter::LEFT_MOUSE_BUTTON)
	{
		return performMovementLeftMouseButton(eventTimeDelta, dx, dy);
	}
	else if (buttonMask == GUIEventAdapter::MIDDLE_MOUSE_BUTTON ||
		buttonMask == (GUIEventAdapter::LEFT_MOUSE_BUTTON | GUIEventAdapter::RIGHT_MOUSE_BUTTON))
	{
		return performMovementMiddleMouseButton(eventTimeDelta, dx, dy);
	}
	else if (buttonMask == GUIEventAdapter::RIGHT_MOUSE_BUTTON)
	{
		return performMovementRightMouseButton(eventTimeDelta, dx, dy);
	}

	return performMovementLeftMouseButton(eventTimeDelta, dx, dy);;
}

bool KeyboardFpsManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    bool result = FirstPersonManipulator::handle(ea, aa);

	bool moved = false;

	double t1;

    switch (ea.getEventType())
    {
    case osgGA::GUIEventAdapter::FRAME:
        //std::cout << "FRAME" << std::endl;
        t1 = ea.getTime();
        if( m_t0 == 0.0 )
        {
            m_t0 = ea.getTime();
            m_dt = 0.0;
        }
        else
        {
            m_dt = t1 - m_t0;
            m_t0 = t1;
        }
        if (m_moveForward)
            this->moveForward(m_dt*12.0);
		if (m_moveBackward)
			this->moveForward(-m_dt*12.0);
		if (m_moveLeft)
			this->moveRight(-m_dt*12.0);
		if (m_moveRight)
			this->moveRight(m_dt*12.0);

		return false;
        break;
    case osgGA::GUIEventAdapter::KEYDOWN:
        switch (ea.getKey())
        {
        case 'w':
			m_moveForward = true;
            return false;
            break;
		case 'a':
			m_moveLeft = true;
			return false;
			break;
		case 'd':
			m_moveRight = true;
			return false;
			break;
		case 's':
			m_moveBackward = true;
			return false;
			break;
		default:
			break;
        }
		this->flushMouseEventStack();
		break;
    case osgGA::GUIEventAdapter::KEYUP:
        switch (ea.getKey())
        {
        default:
			m_moveForward = false;
			m_moveBackward = false;
			m_moveLeft = false;
			m_moveRight = false;
			break;
        }
		this->flushMouseEventStack();
		break;
	case osgGA::GUIEventAdapter::MOVE:
		moved = true;
		break;
	}

	if (!moved)
	{
		int _mouseCenterX = (ea.getXmin() + ea.getXmax()) / 2.0f;
		int _mouseCenterY = (ea.getYmin() + ea.getYmax()) / 2.0f;
		aa.requestWarpPointer(_mouseCenterX, _mouseCenterY);
		this->flushMouseEventStack();
	}
    return result;
}