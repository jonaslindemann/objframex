#include "BasicFrameFactory.h"

BasicFrameFactory::BasicFrameFactory()
{
	m_floors = 10;
	m_cols = 4;
	m_rows = 4;

	m_colSpacing = 2.0;
	m_rowSpacing = 2.0;
	m_floorSpacing = 2.0;
}

void BasicFrameFactory::generate()
{
	m_points = new GeomPoints;

	for (int i = 0; i < m_floors; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			for (int k = 0; k < m_rows; k++)
			{
				m_points->add(m_colSpacing*j - m_cols / 2.0, m_rowSpacing*k - m_rows / 2.0, m_floorSpacing*i);
			}
		}
	}

	m_lines = new GeomLines(m_points);

	for (int i = 0; i < m_floors - 1; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			for (int k = 0; k < m_rows; k++)
			{
				int idx0 = i * (m_rows * m_cols) + j*m_cols + k;
				int idx1 = (i + 1) * (m_rows * m_cols) + j*m_cols + k;
				m_lines->add(idx0, idx1);
			}
		}
	}

	for (int i = 1; i < m_floors; i++)
	{
		for (int k = 0; k < m_rows; k++)
		{
			for (int j = 0; j < m_cols - 1; j++)
			{
				int idx0 = i * (m_rows * m_cols) + j*m_cols + k;
				int idx1 = i * (m_rows * m_cols) + (j + 1)*m_cols + k;
				m_lines->add(idx0, idx1);
			}
		}
	}

	for (int i = 1; i < m_floors; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			for (int k = 0; k < m_rows - 1; k++)
			{
				int idx0 = i * (m_rows * m_cols) + j*m_cols + k;
				int idx1 = i * (m_rows * m_cols) + j*m_cols + k + 1;
				m_lines->add(idx0, idx1);
			}
		}
	}
}

GeomPoints * BasicFrameFactory::points()
{
	return m_points.get();
}

GeomLines * BasicFrameFactory::lines()
{
	return m_lines.get();
}

void BasicFrameFactory::setFloors(int floors)
{
	m_floors = floors;
}

int BasicFrameFactory::floors()
{
	return m_floors;
}

void BasicFrameFactory::setColumns(int cols)
{
	m_cols = cols;
}

int BasicFrameFactory::columns()
{
	return m_cols;
}

void BasicFrameFactory::setRows(int rows)
{
	m_rows = rows;
}

int BasicFrameFactory::rows()
{
	return m_rows;
}

void BasicFrameFactory::setSize(int floors, int rows, int cols)
{
	m_rows = rows;
	m_cols = cols;
	m_floors = floors;
}

void BasicFrameFactory::setFloorSpacing(double spacing)
{
	m_floorSpacing = spacing;
}

double BasicFrameFactory::floorSpacing()
{
	return m_floorSpacing;
}

void BasicFrameFactory::setColSpacing(double spacing)
{
	m_colSpacing = spacing;
}


double BasicFrameFactory::colSpacing()
{
	return m_colSpacing;
}

void BasicFrameFactory::setRowSpacing(double spacing)
{
	m_rowSpacing = spacing;
}

double BasicFrameFactory::rowSpacing()
{
	return m_rowSpacing;
}
