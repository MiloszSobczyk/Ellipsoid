#include "EllipsoidSolver.h"

EllipsoidSolver::EllipsoidSolver(Ellipsoid ellipsoid, int width, int height)
	: ellipsoid(ellipsoid), width(width), height(height)
{
	points = new Point* [height];
	for (int i = 0; i < height; ++i)
		points[i] = new Point[width];
}

EllipsoidSolver::~EllipsoidSolver()
{
	for (int i = 0; i < height; ++i)
		delete[] points[i];
	delete[] points;
}

void EllipsoidSolver::Solve()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			float x = (float)j / (width - 1) * 2 - 1;
			float y = (float)i / (height - 1) * 2 - 1;
			float z = ellipsoid.GetZFromXY(x, y);
			points[i][j] = Point(x, y, z);
		}
	}
}
