#include "RayCaster.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Utils/Logger.h"
#include <iostream>

RayCaster::RayCaster() : shader("Resources/Shaders/Shader.glsl")
{
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glGenVertexArrays(1, &VAO));
}

void RayCaster::CalculatePoints(Ellipsoid shape, float xLeft, float xRight, 
	float yDown, float yUp, int xSegments, int ySegments)
{
	shape.Refresh();
	points.clear();

	for (int i = 0; i < xSegments; ++i)
	{
		for (int j = 0; j < ySegments; ++j)
		{
			float x = xLeft + (xRight - xLeft) / xSegments * i;
			float y = yDown + (yUp - yDown) / ySegments * j;

			auto result = shape.CalculatePoint(x, y);
			if (result.first)
			{
				Vector4 camera(0.f, 0.f, 100.f, 0.f);

				Vector4 v = (camera - Vector4(x, y, result.second, 0.f)).Normalize();
				Vector4 gradient = shape.CalculateGradient(x, y, result.second).Normalize();

				float intensity = std::pow(v * gradient, 9.0f); 
			
				points.push_back(RayCasterPoint{ 
					.point{ x, y, 0.f, 1.f }, 
					.color{ intensity, intensity, intensity, 1.0f } 
				});
			}
		}
	}

	Save();
}

void RayCaster::Save()
{
	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(RayCasterPoint), points.data(), GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(RayCasterPoint), (void*)offsetof(RayCasterPoint, point)));
	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(RayCasterPoint), (void*)offsetof(RayCasterPoint, color)));
	
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glBindVertexArray(0));
}

void RayCaster::Render()
{
	shader.Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, points.size());
	glBindVertexArray(0);

	shader.Unbind();
}
