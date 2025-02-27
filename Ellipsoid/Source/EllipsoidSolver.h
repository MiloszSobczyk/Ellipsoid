#pragma once
#include <Ellipsoid.h>
#include <Point.h>

class EllipsoidSolver
{
private:
	Ellipsoid ellipsoid;
	Point** points;
	int width, height;
public:
	EllipsoidSolver(Ellipsoid ellipsoid, int width, int height);
	~EllipsoidSolver();
	void Solve();
	Point** getPoints() const { return points; }
};