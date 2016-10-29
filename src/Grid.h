#pragma once

#include "PositionalObject.h"

#include <osg/Geode>

class Grid : public PositionalObject {
private:
	osg::ref_ptr<osg::Geode> m_gMain;
	osg::ref_ptr<osg::Geode> m_gSub;
	double m_width;
	double m_height;
	int m_xDiv;
	int m_yDiv;
	int m_xSubDiv;
	int m_ySubDiv;

	void createGrid();
public:
	Grid();

	Grid(const Grid& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
		: PositionalObject(copy, copyop) {}

	double width();
	double height();
	int xDiv();
	int yDiv();
	int xSubDiv();
	int ySubDiv();

	void setWidth(double width);
	void setHeight(double height);
	void setXDiv(int division);
	void setYDiv(int division);
	void setXSubDiv(int division);
	void setYSubDiv(int division);

	META_Node(osg, Grid);

protected:
	~Grid();
};

