#pragma once

#include "Claire/Maths/matrices/mat4.h"
#include "Claire/Maths/vectors/tvec3.h"

#undef near
#undef far

namespace ClaireMath
{
	static mat4 Translation(const vec3& vector)
	{
		mat4 result = mat4::Identity();

		result.data[3 + 0 * 4] = vector.x;
		result.data[3 + 1 * 4] = vector.y;
		result.data[3 + 2 * 4] = vector.z;

		return result;
	}

	static mat4 Rotate(const vec3& axis, float angle)
	{
		mat4 result = mat4::Identity();

		float r = angle * 3.14159 / 180;
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.data[0 + 0 * 4] = x * x * omc + c;
		result.data[0 + 1 * 4] = y * x * omc + z * s;
		result.data[0 + 2 * 4] = x * z * omc - y * s;

		result.data[1 + 0 * 4] = x * y * omc - z * s;
		result.data[1 + 1 * 4] = y * y * omc + c;
		result.data[1 + 2 * 4] = y * z * omc + x * s;

		result.data[2 + 0 * 4] = x * z * omc + y * s;
		result.data[2 + 1 * 4] = y * z * omc - x * s;
		result.data[2 + 2 * 4] = z * z * omc + c;

		return result;
	}

	static mat4 Scale(const vec3& scale)
	{
		mat4 result = mat4::Identity();

		result.data[0 + 0 * 4] = scale.x;
		result.data[1 + 1 * 4] = scale.y;
		result.data[2 + 2 * 4] = scale.z;

		return result;
	}

	static mat4 Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 result = mat4::Identity();

		result.data[0 + 0 * 4] = 2.0f / (right - left);

		result.data[1 + 1 * 4] = 2.0f / (top - bottom);

		result.data[2 + 2 * 4] = 2.0f / (near - far);

		result.data[3 + 0 * 4] = (left + right) / (left - right);
		result.data[3 + 1 * 4] = (bottom + top) / (bottom - top);
		result.data[3 + 2 * 4] = (far + near) / (far - near);

		return result;
	}

	static mat4 Perspective(float aspectRatio, float fov, float nearClip, float farClip)
	{
		mat4 result = mat4::Identity();

		float q = 1.0f / tan((0.5f * fov) * 3.14159 / 180);
		float a = q / aspectRatio;

		float b = (nearClip + farClip) / (nearClip - farClip);
		float c = (2.0f * nearClip * farClip) / (nearClip - farClip);

		result.data[0 + 0 * 4] = a;
		result.data[1 + 1 * 4] = q;
		result.data[2 + 2 * 4] = b;
		result.data[2 + 3 * 4] = -1.0f;
		result.data[3 + 2 * 4] = c;

		return result;
	}

	static mat4 LookAt(const vec3& cameraPos, const vec3& objectPos, const vec3& up)
	{
		mat4 result = mat4::Identity();

		vec3 f = (objectPos - cameraPos).Normalise();
		vec3 s = f.Cross(up.Normalise());
		vec3 u = s.Cross(f);

		result.data[0 + 0 * 4] = s.x;
		result.data[0 + 1 * 4] = s.y;
		result.data[0 + 2 * 4] = s.z;
		result.data[1 + 0 * 4] = u.x;
		result.data[1 + 1 * 4] = u.y;
		result.data[1 + 2 * 4] = u.z;
		result.data[2 + 0 * 4] = -f.x;
		result.data[2 + 1 * 4] = -f.y;
		result.data[2 + 2 * 4] = -f.z;

		return result * Translation(vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z));
	}
}