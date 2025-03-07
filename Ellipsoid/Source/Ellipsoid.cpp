#pragma once

#include "Ellipsoid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "UserInterface.h"

Ellipsoid::Ellipsoid(float a, float b, float c)
	: a(a), b(b), c(c), inverseRotations(Vector4(1.f, 1.f, 1.f, 1.f))
{
	InitTransformations();
}

void Ellipsoid::InitTransformations()
{
	translations = Vector4(0.f, 0.f, 0.f, 0.f);
	scaling = Vector4(1.f, 1.f, 1.f, 1.f);
	rotations = Vector4(0.f, 0.f, 0.f, 0.f);
}

void Ellipsoid::Refresh()
{
	UIValues values = UserInterface::values;

	Matrix4 diag(Vector4(values.a, values.b, values.c, -1.f));
	Matrix4 inv = CalculateInverseTransformations();
	finalMatrix = inv.Transpose() * diag * inv;
}

Matrix4 Ellipsoid::CalculateInverseTransformations()
{
	UIValues values = UserInterface::values;

	Matrix4 inverseTranslation = Matrix4::Translation(
		-values.translationX, 
		-values.translationY, 
		-values.translationZ
	);

	AddRotation(values.rotationYChange);
	UserInterface::values.rotationYChange = 0.f;

	Matrix4 inverseScaling = Matrix4(Vector4(1 / values.scale, 1 / values.scale, 1 / values.scale, 1));
	
	Matrix4 inverseTransform = inverseScaling * inverseRotations * inverseTranslation;
	return inverseTransform;
}


void Ellipsoid::AddRotation(float angle)
{
	if (angle == 0.f)
		return;

	std::cout << angle << '\n';
	inverseRotations = inverseRotations * Matrix4::RotationByDegree(-angle, 0.f, 0.f);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << inverseRotations[i][j] << ' ';
		}
		std::cout << '\n';
	}

	std::cout << '\n';
}

std::pair<bool, float> Ellipsoid::CalculatePoint(float x, float y)
{
	float aZ = finalMatrix[2][2];
	// possible easier calculation of bZ
	float bZ = ((finalMatrix[0][2] + finalMatrix[2][0]) * x + (finalMatrix[1][2] + finalMatrix[2][1]) * y +
		finalMatrix[2][3] + finalMatrix[3][2]);
	float cZ = Vector4(x, y, 0.f, 1.f) * finalMatrix * Vector4(x, y, 0.f, 1.f);

	float delta = bZ * bZ - 4 * aZ * cZ;

	if (delta < 0)
	{
		return std::make_pair(false, 0.f);
	}

	float deltaSquared = sqrtf(delta);
	float z1 = (-bZ + deltaSquared) / (2.f * aZ);
	float z2 = (-bZ - deltaSquared) / (2.f * aZ);

	return std::make_pair(true, std::max(z1, z2));
}

Vector4 Ellipsoid::CalculateGradient(float x, float y, float z)
{
	float a = 2 * finalMatrix[0][0];
	float b = Vector4(0, y, z, 1) * finalMatrix * Vector4(1, 0, 0, 0) 
		+ Vector4(1, 0, 0, 0) * finalMatrix * Vector4(0, y, z, 1);
	float xGrad = a * x + b;

	a = 2 * finalMatrix[1][1];
	b = Vector4(x, 0, z, 1) * finalMatrix * Vector4(0, 1, 0, 0)
		+ Vector4(0, 1, 0, 0) * finalMatrix * Vector4(x, 0, z, 1);
	float yGrad = a * y + b;

	a = 2 * finalMatrix[2][2];
	b = Vector4(x, y, 0, 1) * finalMatrix * Vector4(0, 0, 1, 0)
		+ Vector4(0, 0, 1, 0) * finalMatrix * Vector4(x, y, 0, 1);
	float zGrad = a * z + b;

	return Vector4(xGrad, yGrad, zGrad, 0.f);
}


