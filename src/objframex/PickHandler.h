#pragma once

#include <osg/Node>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>

class PickHandler : public osgGA::GUIEventHandler {
private:
protected:
    osg::ref_ptr<osg::MatrixTransform> m_selectionBox;
public:
    osg::MatrixTransform* getOrCreateSelectionBox();

    PickHandler();

    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
};
