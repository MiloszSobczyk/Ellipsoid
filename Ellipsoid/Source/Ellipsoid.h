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
	std::vector<Point> visiblePoints;
	Vector4 rotations;
	Vector4 scaling;
	Vector4 translations;

	unsigned int VAO;
	unsigned int VBO;
	Shader shader;

	float vertices[9];

public:
	Ellipsoid();
	Ellipsoid(float a, float b, float c);

	void InitBuffers();

	Matrix4 CalculateInverseTransformations();

	void CalculatePoints(float xLeft, float xRight, float yUp, float yDown,
		int xPoints, int yPoints);

	void Render();
};