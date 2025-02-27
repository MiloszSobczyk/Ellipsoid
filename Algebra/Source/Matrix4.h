#pragma once
#include "Vector4.h"

namespace Algebra
{
	class Matrix4
	{
	public:
		Vector4 rows[4];

		Matrix4();
		Matrix4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);

		Vector4& operator[](int index);
		const Vector4& operator[](int index) const;

		float& operator()(int row, int col);
		const float& operator()(int row, int col) const;

		Matrix4 operator+(const Matrix4& other) const;
		Matrix4 operator-(const Matrix4& other) const;
		Matrix4 operator*(float scalar) const;
		Matrix4 operator*(const Matrix4& other) const;
		Vector4 operator*(const Vector4& vec) const;

		Matrix4 Transpose() const;
	};

	Vector4 operator*(const Vector4& vec, const Matrix4& mat);
}
