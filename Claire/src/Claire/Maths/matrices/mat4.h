#pragma once

#include "Claire/Maths/vectors/tvec4.h"

namespace ClaireMath
{
	struct mat4
	{
		union
		{
			float data[4 * 4];
			vec4 rows[4];
		};

		mat4();
		mat4(float identity);
		mat4(const mat4& other);
		mat4(float* data);
		mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3);

		static mat4 Identity();

		mat4& Multiply(const mat4& other);

		friend mat4 operator*(mat4 left, const mat4& right);
		mat4& operator*=(const mat4& other);

		mat4& Invert();

		vec4 GetColumn(int index);
		void SetColumn(uint32_t index, const vec4& column);
	};
}