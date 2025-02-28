#pragma once
#include "Vector4.h"

namespace Algebra
{
	class Matrix4
	{
	private:
		Vector4 rows[4];
	public:
		Matrix4();
		Matrix4(const Vector4& diagonal);
		Matrix4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4);

		float Sum() const;
		Matrix4 Transpose();

		Vector4 Column(int index) const;

		Vector4& operator[](int index);
		const Vector4& operator[](int index) const;
		const Matrix4 operator+(const Matrix4& other) const;
		const Matrix4 operator-(const Matrix4& other) const;

		const Matrix4 operator*(const Matrix4& rightMatrix) const;

		friend Matrix4 operator*(const Matrix4& matrix, const float& scalar);
		friend Matrix4 operator*(const float& scalar, const Matrix4& matrix);
		friend Matrix4 operator/(const Matrix4& matrix, const float& scalar);
	};
}