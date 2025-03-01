#pragma once
#include <Point.h>
#include <vector>
#include <Matrix4.h>
#include <Utils/Shader.h>

using namespace Algebra;


class Ellipsoid
{
private:
	float a, b, c;
	Vector4 rotations;
	Vector4 scaling;
	Vector4 translations;
	Matrix4 finalMatrix;
public:
	Ellipsoid();
	Ellipsoid(float a, float b, float c);

	Matrix4 CalculateInverseTransformations();

	std::pair<bool, float> CalculatePoint(float x, float y);

	void Refresh();
};