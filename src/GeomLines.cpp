#include "GeomLines.h"

GeomLines::GeomLines(GeomPoints* points)
{
	m_points = points;
}

void GeomLines::add(int i0, int i1)
{
	osg::ref_ptr<GeomLine> line = new GeomLine;
	line->setPoints(m_points->get(i0), m_points->get(i1));
	addChild(line.get());
}

void GeomLines::get(int idx, int & i0, int & i1)
{
	osg::ref_ptr<GeomLine> line = static_cast<GeomLine*>(getChild(idx));
	i0 = m_points->indexOf(line->p0());
	i1 = m_points->indexOf(line->p1());
}

GeomLine * GeomLines::get(int idx)
{
	osg::ref_ptr<GeomLine> line = static_cast<GeomLine*>(getChild(idx));
	return line.get();
}

void GeomLines::modify(int idx, int i0, int i1)
{
	osg::ref_ptr<GeomLine> line = static_cast<GeomLine*>(getChild(idx));
	line->setPoints(m_points->get(i0), m_points->get(i1));
}

void GeomLines::clearLines()
{
	this->removeChildren(0, this->getNumChildren());
}

GeomLines::~GeomLines()
{
}
