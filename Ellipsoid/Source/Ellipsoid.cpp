#include "Ellipsoid.h"
#include <Matrix4.h>

using namespace Algebra;

Ellipsoid::Ellipsoid() 
	: a(1.0f), b(1.0f), c(1.0f) { }

Ellipsoid::Ellipsoid(float a, float b, float c)
	: a(a), b(b), c(c) { }

float Ellipsoid::GetZFromXY(float x, float y) const
{
	float rightHandSide = (1 - a * x * x - b * y * y) / c;
	return sqrt(rightHandSide > 0 ? rightHandSide : 0.0f);
}
