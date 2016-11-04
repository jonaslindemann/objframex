#pragma once

#include <osg/MatrixTransform>
#include <osg/Array>

class PositionalObject : public osg::MatrixTransform {
protected:
	double m_pos[3];
	osg::ref_ptr<osg::Node> m_node;
public:
	PositionalObject();

	PositionalObject(const PositionalObject& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
		: osg::MatrixTransform(copy, copyop) {}

	void setNode(osg::Node* node);
	osg::Node* node();

	void setPosition(double x, double y, double z);

	double x();
	double y();
	double z();

	META_Node(osg, PositionalObject);

protected:
	virtual ~PositionalObject() {};
};

