#pragma once
#include <cmath>

namespace Algebra
{
	class Vector4
	{
	public:
		float x, y, z, w;

		Vector4();
		Vector4(float x, float y, float z, float w);

		float operator[](int index) const;

		Vector4 operator+(const Vector4& other) const;
		Vector4 operator-(const Vector4& other) const;
		Vector4 operator*(float scalar) const;
		Vector4 operator/(float scalar) const;
		Vector4 operator-() const;

		float Dot(const Vector4& other) const;
		float Length() const;
		Vector4 Normalize() const;
	};
}
