#pragma once

#include <osg/Group>
#include <osg/Array>

class NodeSet : public osg::Group {
protected:
	osg::ref_ptr<osg::Vec3dArray> m_coords;
public:
	NodeSet();

	NodeSet(const NodeSet& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
		: osg::Group(copy, copyop) {}

	void setSize(int size);
	int size();

	void setCoord(int idx, double x, double y, double z);

	META_Node(osg, NodeSet);

protected:
	virtual ~NodeSet() {};
};

