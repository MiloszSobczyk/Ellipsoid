#pragma once

class Ellipsoid
{
public:
	float a, b, c;
	Ellipsoid();
	Ellipsoid(float a, float b, float c);

	float GetZFromXY(float x, float y) const;
};