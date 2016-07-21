#pragma once

#include <osg/Group>
#include "GeomPoint.h"
#include "GeomLine.h"
#include "GeomPoints.h"

class GeomLines : public osg::Group {
private:
	osg::ref_ptr<GeomPoints> m_points;
public:
	GeomLines(GeomPoints* points);

	GeomLines(const GeomLines& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
		: osg::Group(copy, copyop) {}

	META_Node(osg, osg::Group);

	void add(int i0, int i1);
	void get(int idx, int& i0, int& i1);
	GeomLine* get(int idx);
	void modify(int idx, int i0, int i1);
	void clearLines();

protected:
	~GeomLines();
};

