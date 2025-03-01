#pragma once
#include <Vector4.h>
#include <vector>
#include <Ellipsoid.h>

using namespace Algebra;

struct RayCasterPoint
{
	Vector4 point;
	Vector4 color;
};

class RayCaster
{
private:
	std::vector<RayCasterPoint> points;
	unsigned int VAO;
	unsigned int VBO;
	Shader shader;

public:
	RayCaster();
	void CalculatePoints(Ellipsoid shape, float xLeft, float xRight, float yDown, float yUp, int xSegments, int ySegments);
	void Render();
	void Save();
};