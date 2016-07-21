#pragma once

#include "PositionalObject.h"

#include <osg/ShapeDrawable>

class GeomPoint : public PositionalObject {
private:
	osg::ref_ptr<osg::ShapeDrawable> m_shape;
public:
	GeomPoint();

	GeomPoint(const GeomPoint& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
		: PositionalObject(copy, copyop) {}

	META_Node(osg, GeomPoint);

protected:
	~GeomPoint();
};

