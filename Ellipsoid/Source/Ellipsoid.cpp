#pragma once

#include "Ellipsoid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "UserInterface.h"


Ellipsoid::Ellipsoid()
	: a(1.f), b(1.f), c(1.f)
{
	InitTransformations();
}

Ellipsoid::Ellipsoid(float a, float b, float c)
	: a(a), b(b), c(c)
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

	Matrix4 inverseRotation =
		Matrix4::RotationX(values.rotationX).Transpose() *
		Matrix4::RotationY(values.rotationY).Transpose() *
		Matrix4::RotationZ(values.rotationZ).Transpose();

	Matrix4 inverseScaling = Matrix4(Vector4(1 / values.scale, 1 / values.scale, 1 / values.scale, 1));

	Matrix4 inverseTransform = inverseScaling * inverseRotation * inverseTranslation;
	return inverseTransform;
}

Matrix4 Ellipsoid::CalculateTransformations()
{
	UIValues values = UserInterface::values;
	Matrix4 translation = Matrix4::Translation(
		values.translationX,
		values.translationY,
		values.translationZ
	);

	Matrix4 rotation =
		Matrix4::RotationXByDegree(rotations[0]).Transpose() *
		Matrix4::RotationYByDegree(rotations[1]).Transpose() *
		Matrix4::RotationZByDegree(rotations[2]).Transpose();

	Matrix4 scaling = Matrix4(Vector4(values.scale, values.scale, values.scale, 1));

	Matrix4 transform = scaling * rotation * translation;

	return transform;
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


