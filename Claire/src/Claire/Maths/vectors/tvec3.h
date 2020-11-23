#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>

#include "tvec2.h"

namespace ClaireMath
{
	template<typename T>
	struct tvec3
	{
		T x, y, z;

		tvec3<T>();
		tvec3<T>(const T& x, const T& y, const T& z);
		tvec3<T>(T scalar);
		tvec3<T>(const tvec3<T>& other);
		tvec3<T>(const tvec2<T>& other);

		static tvec3<T> Up() { return tvec3<T>(0, 1, 0); }
		static tvec3<T> Down() { return tvec3<T>(0, -1, 0); }
		static tvec3<T> Left() { return tvec3<T>(-1, 0, 0); }
		static tvec3<T> Right() { return tvec3<T>(1, 0, 0); }
		static tvec3<T> Forward() { return tvec3<T>(0, 0, 1); }
		static tvec3<T> Backward() { return tvec3<T>(0, 0, -1); }
		static tvec3<T> Zero() { return tvec3<T>(0, 0, 0); }

		tvec3<T>& Add(const tvec3<T>& other);
		tvec3<T>& Substract(const tvec3<T>& other);
		tvec3<T>& Multiply(const tvec3<T>& other);
		tvec3<T>& Divide(const tvec3<T>& other);

		// OPERATORS
		friend tvec3<T> operator+(tvec3<T> left, const tvec3<T>& right);
		friend tvec3<T> operator-(tvec3<T> left, const tvec3<T>& right);
		friend tvec3<T> operator*(tvec3<T> left, const tvec3<T>& right);
		friend tvec3<T> operator/(tvec3<T> left, const tvec3<T>& right);

		tvec3<T>& operator+=(const tvec3<T>& other);
		tvec3<T>& operator-=(const tvec3<T>& other);
		tvec3<T>& operator*=(const tvec3<T>& other);
		tvec3<T>& operator/=(const tvec3<T>& other);

		bool operator==(const tvec3<T>& other);
		bool operator!=(const tvec3<T>& other);

		tvec3<T> Cross(const tvec3<T>& other);
		float Dot(const tvec3<T>& other);
		float Magnitude();
		tvec3<T> Normalise() const;
		float Distance(const tvec3<T>& other);

		const std::string& ToString() const;

		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const tvec3<T>& vector);
	};

	template<typename T>
	tvec3<T>::tvec3()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	template<typename T>
	tvec3<T>::tvec3(const T& x, const T& y, const T& z)
		: x(x), y(y), z(z)
	{
	}
	template<typename T>
	tvec3<T>::tvec3(T scalar)
		: x(scalar), y(scalar), z(scalar)
	{
	}
	template<typename T>
	tvec3<T>::tvec3(const tvec3<T>& other)
	{
		*this = other;
	}
	template<typename T>
	tvec3<T>::tvec3(const tvec2<T>& other)
		: x(other.x), y(other.y), z(0)
	{
	}
	template<typename T>
	tvec3<T>& tvec3<T>::Add(const tvec3<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	template<typename T>
	tvec3<T>& tvec3<T>::Substract(const tvec3<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	template<typename T>
	tvec3<T>& tvec3<T>::Multiply(const tvec3<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	template<typename T>
	tvec3<T>& tvec3<T>::Divide(const tvec3<T>& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	template<typename T>
	bool tvec3<T>::operator==(const tvec3<T>& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}
	template<typename T>
	bool tvec3<T>::operator!=(const tvec3<T>& other)
	{
		return !(*this == other);
	}
	template<typename T>
	tvec3<T> tvec3<T>::Cross(const tvec3<T>& other)
	{
		return tvec3<T>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}
	template<typename T>
	float tvec3<T>::Dot(const tvec3<T>& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}
	template<typename T>
	float tvec3<T>::Magnitude()
	{
		return sqrt(x * x + y * y + z * z);
	}
	template<typename T>
	tvec3<T> tvec3<T>::Normalise() const
	{
		float length = Magnitude();
		return tvec3<T>(x / length, y / length, z / length);
	}
	template<typename T>
	float tvec3<T>::Distance(const tvec3<T>& other)
	{
		float a = x - other.x;
		float b = y - other.y;
		float c = z - other.z;
		return sqrt(a * a + b * b + c * c);
	}
	template<typename T>
	const std::string& tvec3<T>::ToString() const
	{
		std::stringstream ss;
		ss << "tvec3" << std::endl << "type size: " << sizeof(x) << std::endl << "x: " << x << std::endl << "y: " << y << std::endl << "z: " << z << std::endl;
		return ss.str();
	}

	template<typename T>
	tvec3<T> operator+(tvec3<T> left, const tvec3<T>& right)
	{
		return left.Add(right);
	}
	template<typename T>
	tvec3<T> operator-(tvec3<T> left, const tvec3<T>& right)
	{
		return left.Substract(right);
	}
	template<typename T>
	tvec3<T> operator*(tvec3<T> left, const tvec3<T>& right)
	{
		return left.Multiply(right);
	}
	template<typename T>
	tvec3<T> operator/(tvec3<T> left, const tvec3<T>& right)
	{
		return left.Divide(right);
	}
	template<typename T>
	tvec3<T>& tvec3<T>::operator+=(const tvec3<T>& other)
	{
		return Add(other);
	}
	template<typename T>
	tvec3<T>& tvec3<T>::operator-=(const tvec3<T>& other)
	{
		return Substract(other);
	}
	template<typename T>
	tvec3<T>& tvec3<T>::operator*=(const tvec3<T>& other)
	{
		return Multiply(other);
	}
	template<typename T>
	tvec3<T>& tvec3<T>::operator/=(const tvec3<T>& other)
	{
		return Divide(other);
	}
	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const tvec3<T>& vector)
	{
		stream << "tvec3" << std::endl << "type size: " << sizeof(x) << std::endl << "x: " << x << std::endl << "y: " << y << std::endl << "z: " << z << std::endl;
		return stream;
	}

	using fvec3 = tvec3<float>;
	using vec3 = fvec3;
	using ivec3 = tvec3<int>;
	using uvec3 = tvec3<uint32_t>;
}