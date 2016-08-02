#pragma once

#include <osgGA/GUIEventHandler>
#include <osgGA/FirstPersonManipulator>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>

class KeyboardFpsManipulator : public osgGA::FirstPersonManipulator {
private:
    bool m_moving;
    double m_dt;
    double m_t0;
public:
    KeyboardFpsManipulator();

    KeyboardFpsManipulator(const KeyboardFpsManipulator& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
        : osgGA::FirstPersonManipulator(copy, copyop) {}


    META_Object(osgGA, osgGA::FirstPersonManipulator)

    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
};
