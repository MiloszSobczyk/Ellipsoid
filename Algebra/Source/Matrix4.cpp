#pragma once

#include "Matrix4.h"
#include <stdexcept>

namespace Algebra
{
	Matrix4::Matrix4()
	{
		for (int i = 0; i < 4; ++i)
			rows[i] = Vector4();
	}

	Matrix4::Matrix4(const Vector4& diagonal)
		: Matrix4()
	{
		for (int i = 0; i < 4; ++i)
			rows[i][i] = diagonal[i];
	}

	Matrix4::Matrix4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3)
	{
		rows[0] = row0;
		rows[1] = row1;
		rows[2] = row2;
		rows[3] = row3;
	}

	float Matrix4::Sum() const
	{
		float sum = 0.0f;
		for (int i = 0; i < 4; ++i)
			sum += rows[i].Sum();
		
		return sum;
	}

	Matrix4 Matrix4::Transpose()
	{
		return Matrix4(Column(0), Column(1), Column(2), Column(3));
	}

	Vector4 Matrix4::Column(int index) const
	{
		return Vector4(rows[0][index], rows[1][index], rows[2][index], rows[3][index]);
	}

	Vector4& Matrix4::operator[](int index)
	{
		return rows[index];
	}

	const Vector4& Matrix4::operator[](int index) const
	{
		return rows[index];
	}

	const Matrix4 Matrix4::operator+(const Matrix4& other) const
	{
		return Matrix4(rows[0] + other[0], rows[1] + other[1], rows[2] + other[2], rows[3] + other[3]);
	}

	const Matrix4 Matrix4::operator-(const Matrix4& other) const
	{
		return Matrix4(rows[0] - other[0], rows[1] - other[1], rows[2] - other[2], rows[3] - other[3]);
	}

	const Matrix4 Matrix4::operator*(const Matrix4& rightMatrix) const
	{
		Matrix4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result[i][j] = (*this)[i] * rightMatrix.Column(j);
			}
		}
		return result;
	}

	Matrix4 operator*(const Matrix4& matrix, const float& scalar)
	{
		return Matrix4(matrix[0] * scalar, matrix[1] * scalar, matrix[2] * scalar, matrix[3] * scalar);
	}

	Matrix4 operator*(const float& scalar, const Matrix4& matrix)
	{
		return matrix * scalar;
	}

	Matrix4 operator/(const Matrix4& matrix, const float& scalar)
	{
		if (scalar == 0)
		{
			throw std::runtime_error("Scalar cannot be zero");
		}

		return matrix * (1.f / scalar);
	}

	Matrix4 Matrix4::Identity()
	{
		return Matrix4(Vector4(1, 1, 1, 1));
	}

	Matrix4 Matrix4::Translation(float x, float y, float z)
	{
		Matrix4 temp = Matrix4::Identity();
		temp[0][3] = x;
		temp[1][3] = y;
		temp[2][3] = z;
		return temp;
	}

	Matrix4 Matrix4::RotationX(float angle)
	{
		Matrix4 temp = Matrix4::Identity();
		float angleCos = cosf(angle);
		float angleSin = sinf(angle);
		temp[1][1] = angleCos;
		temp[1][2] = -angleSin;
		temp[2][1] = angleSin;
		temp[2][2] = angleCos;

		return temp;
	}

	Matrix4 Matrix4::RotationY(float angle)
	{
		Matrix4 temp = Matrix4::Identity();
		float angleCos = cosf(angle);
		float angleSin = sinf(angle);
		temp[0][0] = angleCos;
		temp[0][2] = angleSin;
		temp[2][0] = -angleSin;
		temp[2][2] = angleCos;

		return temp;
	}

	Matrix4 Matrix4::RotationZ(float angle)
	{
		Matrix4 temp = Matrix4::Identity();
		float angleCos = cosf(angle);
		float angleSin = sinf(angle);
		temp[0][0] = angleCos;
		temp[0][1] = -angleSin;
		temp[1][0] = angleSin;
		temp[1][1] = angleCos;

		return temp;
	}

	Matrix4 Matrix4::Rotation(float x, float y, float z)
	{
		return RotationX(x) * RotationY(y) * RotationZ(z);
	}

	Matrix4 Matrix4::RotationXDegree(float angle)
	{
		return RotationX(Algebra::DegreeToRadians(angle));
	}

	Matrix4 Matrix4::RotationYDegree(float angle)
	{
		return RotationY(Algebra::DegreeToRadians(angle));
	}

	Matrix4 Matrix4::RotationZDegree(float angle)
	{
		return RotationZ(Algebra::DegreeToRadians(angle));
	}

	Matrix4 Matrix4::RotationDegree(float x, float y, float z)
	{
		return RotationXDegree(x) * RotationYDegree(y) * RotationZDegree(z);
	}

	Matrix4 Matrix4::DiagonalScaling(float x, float y, float z, float w)
	{
		return Matrix4();
	}
}