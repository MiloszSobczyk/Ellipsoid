#pragma once
#include <Point.h>
#include <vector>
#include <Matrix4.h>

using namespace Algebra;

class Ellipsoid
{
private:
	float a, b, c;
	std::vector<Point> visiblePoints;
	Vector4 rotations;
	Vector4 scaling;
	Vector4 translations;

public:
	Ellipsoid();
	Ellipsoid(float a, float b, float c);

	Matrix4 CalculateInverseTransformations();

	void CalculatePoints(float xLeft, float xRight, float yUp, float yDown,
		int xPoints, int yPoints);
};