#include "mat4.h"

namespace ClaireMath
{
	mat4::mat4()
	{
		memset(data, 0, 4 * 4 * sizeof(float));
	}

	mat4::mat4(float identity)
	{
		memset(data, 0, 4 * 4 * sizeof(float));
		data[0 + 0 * 4] = identity;
		data[1 + 1 * 4] = identity;
		data[2 + 2 * 4] = identity;
		data[3 + 3 * 4] = identity;
	}

	mat4::mat4(const mat4& other)
	{
		memcpy(this->data, other.data, 4 * 4 * sizeof(float));
	}

	mat4::mat4(float* data)
	{
		memcpy(this->data, data, 4 * 4 * sizeof(float));
	}

	mat4::mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3)
	{
		rows[0] = row0;
		rows[1] = row1;
		rows[2] = row2;
		rows[3] = row3;
	}

	mat4 mat4::Identity()
	{
		return mat4(1.0f);
	}

	mat4& mat4::Multiply(const mat4& other)
	{
		float datar[16];
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += this->data[e + row * 4] * other.data[col + e * 4];
				}
				datar[col + row * 4] = sum;
			}
		}
		memcpy(this->data, datar, 4 * 4 * sizeof(float));
		return *this;
	}

	mat4& mat4::operator*=(const mat4& other)
	{
		return Multiply(other);
	}

	mat4& mat4::Invert()
	{
		float temp[16];

		temp[0] = data[5] * data[10] * data[15] -
			data[5] * data[11] * data[14] -
			data[9] * data[6] * data[15] +
			data[9] * data[7] * data[14] +
			data[13] * data[6] * data[11] -
			data[13] * data[7] * data[10];

		temp[4] = -data[4] * data[10] * data[15] +
			data[4] * data[11] * data[14] +
			data[8] * data[6] * data[15] -
			data[8] * data[7] * data[14] -
			data[12] * data[6] * data[11] +
			data[12] * data[7] * data[10];

		temp[8] = data[4] * data[9] * data[15] -
			data[4] * data[11] * data[13] -
			data[8] * data[5] * data[15] +
			data[8] * data[7] * data[13] +
			data[12] * data[5] * data[11] -
			data[12] * data[7] * data[9];

		temp[12] = -data[4] * data[9] * data[14] +
			data[4] * data[10] * data[13] +
			data[8] * data[5] * data[14] -
			data[8] * data[6] * data[13] -
			data[12] * data[5] * data[10] +
			data[12] * data[6] * data[9];

		temp[1] = -data[1] * data[10] * data[15] +
			data[1] * data[11] * data[14] +
			data[9] * data[2] * data[15] -
			data[9] * data[3] * data[14] -
			data[13] * data[2] * data[11] +
			data[13] * data[3] * data[10];

		temp[5] = data[0] * data[10] * data[15] -
			data[0] * data[11] * data[14] -
			data[8] * data[2] * data[15] +
			data[8] * data[3] * data[14] +
			data[12] * data[2] * data[11] -
			data[12] * data[3] * data[10];

		temp[9] = -data[0] * data[9] * data[15] +
			data[0] * data[11] * data[13] +
			data[8] * data[1] * data[15] -
			data[8] * data[3] * data[13] -
			data[12] * data[1] * data[11] +
			data[12] * data[3] * data[9];

		temp[13] = data[0] * data[9] * data[14] -
			data[0] * data[10] * data[13] -
			data[8] * data[1] * data[14] +
			data[8] * data[2] * data[13] +
			data[12] * data[1] * data[10] -
			data[12] * data[2] * data[9];

		temp[2] = data[1] * data[6] * data[15] -
			data[1] * data[7] * data[14] -
			data[5] * data[2] * data[15] +
			data[5] * data[3] * data[14] +
			data[13] * data[2] * data[7] -
			data[13] * data[3] * data[6];

		temp[6] = -data[0] * data[6] * data[15] +
			data[0] * data[7] * data[14] +
			data[4] * data[2] * data[15] -
			data[4] * data[3] * data[14] -
			data[12] * data[2] * data[7] +
			data[12] * data[3] * data[6];

		temp[10] = data[0] * data[5] * data[15] -
			data[0] * data[7] * data[13] -
			data[4] * data[1] * data[15] +
			data[4] * data[3] * data[13] +
			data[12] * data[1] * data[7] -
			data[12] * data[3] * data[5];

		temp[14] = -data[0] * data[5] * data[14] +
			data[0] * data[6] * data[13] +
			data[4] * data[1] * data[14] -
			data[4] * data[2] * data[13] -
			data[12] * data[1] * data[6] +
			data[12] * data[2] * data[5];

		temp[3] = -data[1] * data[6] * data[11] +
			data[1] * data[7] * data[10] +
			data[5] * data[2] * data[11] -
			data[5] * data[3] * data[10] -
			data[9] * data[2] * data[7] +
			data[9] * data[3] * data[6];

		temp[7] = data[0] * data[6] * data[11] -
			data[0] * data[7] * data[10] -
			data[4] * data[2] * data[11] +
			data[4] * data[3] * data[10] +
			data[8] * data[2] * data[7] -
			data[8] * data[3] * data[6];

		temp[11] = -data[0] * data[5] * data[11] +
			data[0] * data[7] * data[9] +
			data[4] * data[1] * data[11] -
			data[4] * data[3] * data[9] -
			data[8] * data[1] * data[7] +
			data[8] * data[3] * data[5];

		temp[15] = data[0] * data[5] * data[10] -
			data[0] * data[6] * data[9] -
			data[4] * data[1] * data[10] +
			data[4] * data[2] * data[9] +
			data[8] * data[1] * data[6] -
			data[8] * data[2] * data[5];

		float determinant = data[0] * temp[0] + data[1] * temp[4] + data[2] * temp[8] + data[3] * temp[12];
		determinant = 1.0f / determinant;

		for (int i = 0; i < 4 * 4; i++)
			data[i] = temp[i] * determinant;

		return *this;
	}

	vec4 mat4::GetColumn(int index)
	{
		return rows[index];
	}

	void mat4::SetColumn(uint32_t index, const vec4& column)
	{
		data[index + 0 * 4] = column.x;
		data[index + 1 * 4] = column.y;
		data[index + 2 * 4] = column.z;
		data[index + 3 * 4] = column.w;
	}

	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.Multiply(right);
	}
}