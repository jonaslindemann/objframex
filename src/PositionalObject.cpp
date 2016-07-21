#include "PositionalObject.h"

PositionalObject::PositionalObject()
{

}

void PositionalObject::setNode(osg::Node * node)
{
	if (m_node!=nullptr)
		this->removeChild(m_node);

	m_node = node;
	
	this->addChild(m_node);
}

osg::Node * PositionalObject::node()
{
	return m_node.get();
}

void PositionalObject::setPosition(double x, double y, double z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;

	this->setMatrix(osg::Matrix::translate(x, y, z));
}

double PositionalObject::x()
{
	return m_pos[0];
}

double PositionalObject::y()
{
	return m_pos[1];
}

double PositionalObject::z()
{
	return m_pos[2];
}
