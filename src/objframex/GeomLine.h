#pragma once

#include <osg/MatrixTransform>
#include <osg/Geode>

#include "GeomPoint.h"

class GeomLine : public osg::MatrixTransform {
private:
	osg::ref_ptr<GeomPoint> m_point0;
	osg::ref_ptr<GeomPoint> m_point1;
	osg::ref_ptr<osg::Geode> m_geode;
	void createCylinder();
public:
	GeomLine();

	GeomLine(const GeomLine& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
		: osg::MatrixTransform(copy, copyop) {}

	META_Node(osg, osg::MatrixTransform);

	void setPoints(GeomPoint* p0, GeomPoint* p1);
	GeomPoint* p0();
	GeomPoint* p1();

protected:
	~GeomLine();
};

