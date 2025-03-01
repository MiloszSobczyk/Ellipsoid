#pragma once

#include "Ellipsoid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


Ellipsoid::Ellipsoid() 
	: a(1.f), b(1.f), c(1.f), visiblePoints(), shader("Resources/Shaders/Shader.glsl"),
		vertices { 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f }
{
	translations = Vector4(0.f, 0.f, 0.f, 0.f);
	scaling = Vector4(1.f, 1.f, 1.f, 1.f);
	rotations = Vector4(0.f, 0.f, 0.f, 0.f);

	InitBuffers();
}

Ellipsoid::Ellipsoid(float a, float b, float c)
	: a(a), b(b), c(c), visiblePoints(), shader("Resources/Shaders/Shader.glsl"),
		vertices{ 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f }
{
	translations = Vector4(0.f, 0.f, 0.f, 0.f);
	scaling = Vector4(1.f, 1.f, 1.f, 1.f);
	rotations = Vector4(0.f, 0.f, 0.f, 0.f);

	InitBuffers();
}

void Ellipsoid::InitBuffers()
{
	float vertices2[] = { 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f };

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Ellipsoid::Render()
{
	shader.Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	shader.Unbind();
}


Matrix4 Ellipsoid::CalculateInverseTransformations()
{
	Matrix4 inverseTranslation = Matrix4::Translation(-translations[0], -translations[1], -translations[2]);
	Matrix4 inverseRotation =
		Matrix4::RotationZByDegree(rotations[2]).Transpose() *
		Matrix4::RotationYByDegree(rotations[1]).Transpose() *
		Matrix4::RotationXByDegree(rotations[0]).Transpose();
	Matrix4 inverseScaling = Matrix4(Vector4(1 / scaling[0], 1 / scaling[1], 1 / scaling[2], 1));

	Matrix4 inverseTransform = inverseScaling * inverseRotation * inverseTranslation;
	return inverseTransform;
}

void Ellipsoid::CalculatePoints(float xLeft, float xRight, float yUp, float yDown, 
	int xPoints, int yPoints)
{
	Matrix4 diag(Vector4(a, b, c, -1.f));
	Matrix4 inv = CalculateInverseTransformations();
	Matrix4 finalMat = inv.Transpose() * diag * inv;
	
	for (int i = 0; i < xPoints; ++i)
	{
		for (int j = 0; j < yPoints; ++j)
		{
			float x = xLeft + (xRight - xLeft) / xPoints * i;
			float y = yDown + (yUp - yDown) / yPoints * j;

			float aZ = finalMat[2][2];
			// possible easier calculation of bZ
			float bZ = ((finalMat[0][2] + finalMat[2][0]) * x + (finalMat[1][2] + finalMat[2][1]) * y +
				finalMat[2][3] + finalMat[3][2]);
			float cZ = Vector4(x, y, 0.f, 1.f) * finalMat * Vector4(x, y, 0.f, 1.f);

			float delta = bZ * bZ - 4 * aZ * cZ;

			if (delta < 0)
			{
				continue;
			}

			float deltaSquared = sqrtf(delta);
			float z1 = (-bZ + deltaSquared) / (2.f * aZ);
			float z2 = (-bZ - deltaSquared) / (2.f * aZ);

			visiblePoints.push_back(Point(x, y, std::max(z1, z2)));
		}
	}
}


