#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>

#include "tvec3.h"

namespace ClaireMath
{
	template<typename T>
	struct tvec4
	{
		T x, y, z, w;

		tvec4<T>();
		tvec4<T>(const T& x, const T& y, const T& z);
		tvec4<T>(T scalar);
		tvec4<T>(const tvec4<T>& other);
		tvec4<T>(const tvec3<T>& other);

		static tvec4<T> Up() { return tvec4<T>(0, 1, 0); }
		static tvec4<T> Down() { return tvec4<T>(0, -1, 0); }
		static tvec4<T> Left() { return tvec4<T>(-1, 0, 0); }
		static tvec4<T> Right() { return tvec4<T>(1, 0, 0); }
		static tvec4<T> Forward() { return tvec4<T>(0, 0, 1); }
		static tvec4<T> Backward() { return tvec4<T>(0, 0, -1); }
		static tvec4<T> Zero() { return tvec4<T>(0, 0, 0); }

		tvec4<T>& Add(const tvec4<T>& other);
		tvec4<T>& Substract(const tvec4<T>& other);
		tvec4<T>& Multiply(const tvec4<T>& other);
		tvec4<T>& Divide(const tvec4<T>& other);

		// OPERATORS
		friend tvec4<T> operator+(tvec4<T> left, const tvec4<T>& right);
		friend tvec4<T> operator-(tvec4<T> left, const tvec4<T>& right);
		friend tvec4<T> operator*(tvec4<T> left, const tvec4<T>& right);
		friend tvec4<T> operator/(tvec4<T> left, const tvec4<T>& right);

		tvec4<T>& operator+=(const tvec4<T>& other);
		tvec4<T>& operator-=(const tvec4<T>& other);
		tvec4<T>& operator*=(const tvec4<T>& other);
		tvec4<T>& operator/=(const tvec4<T>& other);

		bool operator==(const tvec4<T>& other);
		bool operator!=(const tvec4<T>& other);

		float Dot(const tvec4<T>& other);
		float Magnitude();
		tvec4<T> Normalise() const;
		float Distance(const tvec4<T>& other);

		const std::string& ToString() const;

		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const tvec4<T>& vector);
	};

	template<typename T>
	tvec4<T>::tvec4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	template<typename T>
	tvec4<T>::tvec4(const T& x, const T& y, const T& z)
		: x(x), y(y), z(z), w(w)
	{
	}
	template<typename T>
	tvec4<T>::tvec4(T scalar)
		: x(scalar), y(scalar), z(scalar), w(scalar)
	{
	}
	template<typename T>
	tvec4<T>::tvec4(const tvec4<T>& other)
	{
		*this = other;
	}
	template<typename T>
	tvec4<T>::tvec4(const tvec3<T>& other)
		: x(other.x), y(other.y), z(other.z), w(0)
	{
	}
	template<typename T>
	tvec4<T>& tvec4<T>::Add(const tvec4<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	template<typename T>
	tvec4<T>& tvec4<T>::Substract(const tvec4<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	template<typename T>
	tvec4<T>& tvec4<T>::Multiply(const tvec4<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}
	template<typename T>
	tvec4<T>& tvec4<T>::Divide(const tvec4<T>& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}
	template<typename T>
	bool tvec4<T>::operator==(const tvec4<T>& other)
	{
		return (x == other.x && y == other.y && z == other.z && w == other.w);
	}
	template<typename T>
	bool tvec4<T>::operator!=(const tvec4<T>& other)
	{
		return !(*this == other);
	}
	template<typename T>
	float tvec4<T>::Dot(const tvec4<T>& other)
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}
	template<typename T>
	float tvec4<T>::Magnitude()
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}
	template<typename T>
	tvec4<T> tvec4<T>::Normalise() const
	{
		float length = Magnitude();
		return tvec4<T>(x / length, y / length, z / length, w / length);
	}
	template<typename T>
	float tvec4<T>::Distance(const tvec4<T>& other)
	{
		float a = x - other.x;
		float b = y - other.y;
		float c = z - other.z;
		float d = w - other.w;
		return sqrt(a * a + b * b + c * c, d * d);
	}
	template<typename T>
	const std::string& tvec4<T>::ToString() const
	{
		std::stringstream ss;
		ss << "tvec4" << std::endl << "type size: " << sizeof(x) << std::endl << "x: " << x << std::endl << "y: " << y << std::endl << "z: " << z << std::endl << "w: " << w << std::endl;
		return ss.str();
	}

	template<typename T>
	tvec4<T> operator+(tvec4<T> left, const tvec4<T>& right)
	{
		return left.Add(right);
	}
	template<typename T>
	tvec4<T> operator-(tvec4<T> left, const tvec4<T>& right)
	{
		return left.Substract(right);
	}
	template<typename T>
	tvec4<T> operator*(tvec4<T> left, const tvec4<T>& right)
	{
		return left.Multiply(right);
	}
	template<typename T>
	tvec4<T> operator/(tvec4<T> left, const tvec4<T>& right)
	{
		return left.Divide(right);
	}
	template<typename T>
	tvec4<T>& tvec4<T>::operator+=(const tvec4<T>& other)
	{
		return Add(other);
	}
	template<typename T>
	tvec4<T>& tvec4<T>::operator-=(const tvec4<T>& other)
	{
		return Substract(other);
	}
	template<typename T>
	tvec4<T>& tvec4<T>::operator*=(const tvec4<T>& other)
	{
		return Multiply(other);
	}
	template<typename T>
	tvec4<T>& tvec4<T>::operator/=(const tvec4<T>& other)
	{
		return Divide(other);
	}
	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const tvec4<T>& vector)
	{
		stream << "tvec4" << std::endl << "type size: " << sizeof(x) << std::endl << "x: " << x << std::endl << "y: " << y << std::endl << "z: " << z << std::endl << "w: " << w << std::endl;
		return stream;
	}

	using fvec4 = tvec4<float>;
	using vec4 = fvec4;
	using ivec4 = tvec4<int>;
	using uvec4 = tvec4<uint32_t>;
}