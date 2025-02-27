#include "Matrix4.h"
#include <stdexcept>

namespace Algebra
{
	Matrix4::Matrix4()
		: rows{ Vector4(), Vector4(), Vector4(), Vector4() } {}

	Matrix4::Matrix4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3)
		: rows{ row0, row1, row2, row3 } {}

	Vector4& Matrix4::operator[](int index)
	{
		return rows[index];
	}

	const Vector4& Matrix4::operator[](int index) const
	{
		return rows[index];
	}

	float& Matrix4::operator()(int row, int col)
	{
		switch (col)
		{
		case 0: return rows[row].x;
		case 1: return rows[row].y;
		case 2: return rows[row].z;
		case 3: return rows[row].w;
		default: throw std::out_of_range("Column index out of range");
		}
	}

	const float& Matrix4::operator()(int row, int col) const
	{
		switch (col)
		{
		case 0: return rows[row].x;
		case 1: return rows[row].y;
		case 2: return rows[row].z;
		case 3: return rows[row].w;
		default: throw std::out_of_range("Column index out of range");
		}
	}

	Matrix4 Matrix4::operator+(const Matrix4& other) const
	{
		return Matrix4(
			rows[0] + other.rows[0],
			rows[1] + other.rows[1],
			rows[2] + other.rows[2],
			rows[3] + other.rows[3]
		);
	}

	Matrix4 Matrix4::operator-(const Matrix4& other) const
	{
		return Matrix4(
			rows[0] - other.rows[0],
			rows[1] - other.rows[1],
			rows[2] - other.rows[2],
			rows[3] - other.rows[3]
		);
	}

	Matrix4 Matrix4::operator*(float scalar) const
	{
		return Matrix4(
			rows[0] * scalar,
			rows[1] * scalar,
			rows[2] * scalar,
			rows[3] * scalar
		);
	}

	Matrix4 Matrix4::operator*(const Matrix4& other) const
	{
		Matrix4 transposedOther = other.Transpose();

		return Matrix4(
			Vector4(rows[0].Dot(transposedOther.rows[0]), rows[0].Dot(transposedOther.rows[1]), rows[0].Dot(transposedOther.rows[2]), rows[0].Dot(transposedOther.rows[3])),
			Vector4(rows[1].Dot(transposedOther.rows[0]), rows[1].Dot(transposedOther.rows[1]), rows[1].Dot(transposedOther.rows[2]), rows[1].Dot(transposedOther.rows[3])),
			Vector4(rows[2].Dot(transposedOther.rows[0]), rows[2].Dot(transposedOther.rows[1]), rows[2].Dot(transposedOther.rows[2]), rows[2].Dot(transposedOther.rows[3])),
			Vector4(rows[3].Dot(transposedOther.rows[0]), rows[3].Dot(transposedOther.rows[1]), rows[3].Dot(transposedOther.rows[2]), rows[3].Dot(transposedOther.rows[3]))
		);
	}

	Vector4 Matrix4::operator*(const Vector4& vec) const
	{
		return Vector4(
			rows[0].Dot(vec),
			rows[1].Dot(vec),
			rows[2].Dot(vec),
			rows[3].Dot(vec)
		);
	}

	Matrix4 Matrix4::Transpose() const
	{
		return Matrix4(
			Vector4(rows[0].x, rows[1].x, rows[2].x, rows[3].x),
			Vector4(rows[0].y, rows[1].y, rows[2].y, rows[3].y),
			Vector4(rows[0].z, rows[1].z, rows[2].z, rows[3].z),
			Vector4(rows[0].w, rows[1].w, rows[2].w, rows[3].w)
		);
	}

	Vector4 operator*(const Vector4& vec, const Matrix4& mat)
	{
		return Vector4(
			Vector4(mat.rows[0].x, mat.rows[1].x, mat.rows[2].x, mat.rows[3].x).Dot(vec),
			Vector4(mat.rows[0].y, mat.rows[1].y, mat.rows[2].y, mat.rows[3].y).Dot(vec),
			Vector4(mat.rows[0].z, mat.rows[1].z, mat.rows[2].z, mat.rows[3].z).Dot(vec),
			Vector4(mat.rows[0].w, mat.rows[1].w, mat.rows[2].w, mat.rows[3].w).Dot(vec)
		);
	}
}
