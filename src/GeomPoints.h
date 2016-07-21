#pragma once

#include <osg/Group>
#include "GeomPoint.h"

class GeomPoints : public osg::Group {
private:
public:
	GeomPoints();

	GeomPoints(const GeomPoints& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
		: osg::Group(copy, copyop) {}

	META_Node(osg, osg::Group);

	void add(double x, double y, double z);
	void get(int idx, double& x, double& y, double& z);
	GeomPoint* get(int idx);
	int indexOf(GeomPoint* point);
	void modify(int idx, double x, double y, double z);
	void clearPoints();

protected:
	~GeomPoints();
};

