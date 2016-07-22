#pragma once

#include <osg/Referenced>

#include "GeomPoint.h"
#include "GeomLine.h"
#include "GeomPoints.h"
#include "GeomLines.h"

class BasicFrameFactory : public osg::Referenced {
private:
	int m_floors = 10;
	int m_cols = 4;
	int m_rows = 4;

	double m_floorSpacing;
	double m_colSpacing;
	double m_rowSpacing;

	osg::ref_ptr<GeomPoints> m_points;
	osg::ref_ptr<GeomLines> m_lines;

public:
	BasicFrameFactory();

	void generate();

	GeomPoints* points();
	GeomLines* lines();

	void setFloors(int floors);
	int floors();

	void setColumns(int cols);
	int columns();

	void setRows(int rows);
	int rows();

	void setSize(int floors, int rows, int cols);
	
	void setFloorSpacing(double spacing);
	double floorSpacing();

	void setColSpacing(double spacing);
	double colSpacing();

	void setRowSpacing(double spacing);
	double rowSpacing();

};