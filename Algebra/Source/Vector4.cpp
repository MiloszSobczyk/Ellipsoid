#include "Vector4.h"
#include <stdexcept>

namespace Algebra
{
	Vector4::Vector4() : x(0), y(0), z(0), w(0) {}

	Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	float Vector4::operator[](int index) const
	{
		switch (index)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw std::out_of_range("Vector index out of range");
		}
	}

	float& Vector4::operator[](int index)
	{
		switch (index)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw std::out_of_range("Vector index out of range");
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

	Vector4 Vector4::operator*(float scalar) const
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	Vector4 Vector4::operator/(float scalar) const
	{
		if (scalar == 0)
			return Vector4();

		return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
	}

	Vector4 Vector4::operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	float Vector4::Dot(const Vector4& other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	float Vector4::Length() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	float Vector4::Sum() const
	{
		return x + y + z + w;
	}

	Vector4 Vector4::Normalize() const
	{
		float length = Length();
		return (length != 0) ? (*this / length) : Vector4();
	}
}
