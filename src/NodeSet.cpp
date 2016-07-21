#include "NodeSet.h"

NodeSet::NodeSet()
{
}

void NodeSet::setSize(int size)
{
	m_coords->resize(size, osg::Vec3d(0.0, 0.0, 0.0));
}

int NodeSet::size()
{
	return m_coords->size();
}

void NodeSet::setCoord(int idx, double x, double y, double z)
{
	m_coords->at(idx) = osg::Vec3d(x, y, z);
}