#include "Vector4.h"
#include <stdexcept>

namespace Algebra
{
	Vector4::Vector4() : x(0), y(0), z(0), w(0) {}

	Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	float Vector4::Sum() const
	{
		return x + y + z + w;
	}

	float Vector4::Length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	Vector4 Vector4::Normalize() const
	{
		return *this / Length();
	}

	float& Vector4::operator[](int index)
	{
		switch (index)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw std::runtime_error("invalid vector4 index");
		}
	}

	const float& Algebra::Vector4::operator[](int index) const
	{
		switch (index)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw std::runtime_error("invalid vector4 index");
		}
	}

	Vector4 Vector4::operator+(const Vector4& other) const
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	Vector4 Vector4::operator-(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	//Vector4 Vector4::operator*(const Matrix4& matrix) const
	//{
	//	return Vector4();
	//}

	float Vector4::operator*(const Vector4& rightVector) const
	{
		return x * rightVector.x + y * rightVector.y + z * rightVector.z + w * rightVector.w;
	}

	Vector4 operator*(const Vector4& vector, const float& scalar)
	{
		return Vector4(vector.x * scalar, vector.y * scalar, vector.z * scalar, vector.w * scalar);
	}

	Vector4 operator*(const float& scalar, const Vector4& vector)
	{
		return vector * scalar;
	}

	Vector4 operator/(const Vector4& vector, const float& scalar)
	{
		if (scalar == 0)
		{
			throw std::runtime_error("Scale cannot be zero");
		}

		return vector * (1.f / scalar);
	}
}
