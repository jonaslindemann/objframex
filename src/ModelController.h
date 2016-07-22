#pragma once

#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>

class ModelController : public osgGA::GUIEventHandler {
private:
public:
	ModelController() { };

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
};