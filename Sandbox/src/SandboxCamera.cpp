#include "SandboxCamera.h"
#include <iostream>

static float radians(float angle)
{
	return angle * 3.14159 / 180;
}

SandboxCamera::SandboxCamera(float left, float right, float bottom, float top)
	: m_ProjectionMatrix(Orthographic(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(mat4::Identity())
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void SandboxCamera::SetProjection(float left, float right, float bottom, float top)
{
	m_ProjectionMatrix = Orthographic(left, right, bottom, top, -1.0f, 1.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void SandboxCamera::Update()
{
	if (InputManager::IsKeyPressed(Key::Q))
	{
		m_Position.x += 0.01f;
	}
	if (InputManager::IsKeyPressed(Key::D))
	{
		m_Position.x -= 0.01f;
	}
	if (InputManager::IsKeyPressed(Key::S))
	{
		m_Position.y += 0.01f;
	}
	if (InputManager::IsKeyPressed(Key::Z))
	{
		m_Position.y -= 0.01f;
	}

	RecalculateViewMatrix();
}

void SandboxCamera::RecalculateViewMatrix()
{
	mat4 transform = Translation(m_Position) * Rotate(vec3(0, 0, 1), radians(m_Rotation));

	m_ViewMatrix = transform.Invert();
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
