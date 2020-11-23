#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>

namespace ClaireMath
{
	template<typename T>
	struct tvec2
	{
		T x, y;

		tvec2<T>();
		tvec2<T>(const T& x, const T& y);
		tvec2<T>(const tvec2<T>& other);

		tvec2<T>& Add(const tvec2<T>& other);
		tvec2<T>& Substract(const tvec2<T>& other);
		tvec2<T>& Multiply(const tvec2<T>& other);
		tvec2<T>& Divide(const tvec2<T>& other);

		// OPERATORS
		friend tvec2<T> operator+(tvec2<T> left, const tvec2<T>& right);
		friend tvec2<T> operator-(tvec2<T> left, const tvec2<T>& right);
		friend tvec2<T> operator*(tvec2<T> left, const tvec2<T>& right);
		friend tvec2<T> operator/(tvec2<T> left, const tvec2<T>& right);

		tvec2<T>& operator+=(const tvec2<T>& other);
		tvec2<T>& operator-=(const tvec2<T>& other);
		tvec2<T>& operator*=(const tvec2<T>& other);
		tvec2<T>& operator/=(const tvec2<T>& other);

		bool operator==(const tvec2<T>& other);
		bool operator!=(const tvec2<T>& other);

		const std::string& ToString() const;

		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const tvec2<T>& vector);
	};

	template<typename T>
	tvec2<T>::tvec2()
	{
		x = 0;
		y = 0;
	}
	template<typename T>
	tvec2<T>::tvec2(const T& x, const T& y)
		: x(x), y(y)
	{
	}
	template<typename T>
	tvec2<T>::tvec2(const tvec2<T>& other)
	{
		*this = other;
	}
	template<typename T>
	tvec2<T>& tvec2<T>::Add(const tvec2<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	template<typename T>
	tvec2<T>& tvec2<T>::Substract(const tvec2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	template<typename T>
	tvec2<T>& tvec2<T>::Multiply(const tvec2<T>& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	template<typename T>
	tvec2<T>& tvec2<T>::Divide(const tvec2<T>& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	template<typename T>
	bool tvec2<T>::operator==(const tvec2<T>& other)
	{
		return (x == other.x && y == other.y);
	}
	template<typename T>
	bool tvec2<T>::operator!=(const tvec2<T>& other)
	{
		return !(*this == other);
	}
	template<typename T>
	const std::string& tvec2<T>::ToString() const
	{
		std::stringstream ss;
		ss << "tvec2" << std::endl << "type size: " << sizeof(x) << std::endl << "x: " << x << std::endl << "y: " << y << std::endl;
		return ss.str();
	}

	template<typename T>
	tvec2<T> operator+(tvec2<T> left, const tvec2<T>& right)
	{
		return left.Add(right);
	}
	template<typename T>
	tvec2<T> operator-(tvec2<T> left, const tvec2<T>& right)
	{
		return left.Substract(right);
	}
	template<typename T>
	tvec2<T> operator*(tvec2<T> left, const tvec2<T>& right)
	{
		return left.Multiply(right);
	}
	template<typename T>
	tvec2<T> operator/(tvec2<T> left, const tvec2<T>& right)
	{
		return left.Divide(right);
	}
	template<typename T>
	tvec2<T>& tvec2<T>::operator+=(const tvec2<T>& other)
	{
		return Add(other);
	}
	template<typename T>
	tvec2<T>& tvec2<T>::operator-=(const tvec2<T>& other)
	{
		return Substract(other);
	}
	template<typename T>
	tvec2<T>& tvec2<T>::operator*=(const tvec2<T>& other)
	{
		return Multiply(other);
	}
	template<typename T>
	tvec2<T>& tvec2<T>::operator/=(const tvec2<T>& other)
	{
		return Divide(other);
	}
	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const tvec2<T>& vector)
	{
		stream << "tvec2" << std::endl << "type size: " << sizeof(vector.x) << std::endl << "x: " << vector.x << std::endl << "y: " << vector.y << std::endl;
		return stream;
	}

	using fvec2 = tvec2<float>;
	using vec2 = fvec2;
	using ivec2 = tvec2<int>;
	using uvec2 = tvec2<uint32_t>;
}