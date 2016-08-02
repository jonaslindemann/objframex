#include "KeyboardFpsManipulator.h"

#include <iostream>

KeyboardFpsManipulator::KeyboardFpsManipulator():
    FirstPersonManipulator()
{
    m_moving = false;
    m_dt = 0.0;
    m_t0 = 0.0;
}


bool KeyboardFpsManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    bool result = FirstPersonManipulator::handle(ea, aa);

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
        if (m_moving)
            this->moveForward(m_dt);
        return false;
        break;
    case osgGA::GUIEventAdapter::KEYDOWN:
        switch (ea.getKey())
        {
        case 'w':
            std::cout << "key down..." << ea.getEventType() << std::endl;
            m_moving = !m_moving;
            //aa.requestRedraw();
            return false;
            break;
        }
        break;
    case osgGA::GUIEventAdapter::KEYUP:
        switch (ea.getKey())
        {
        case 'w':
            //std::cout << "key up..." << std::endl;
            //m_moving = false;
            break;
        }
        break;
    }

    if (m_moving)
    {
        //std::cout << "moving..." << std::endl;
    }

    return result;
}
