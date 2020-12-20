#pragma once

#include <Claire/Claire.h>

using namespace ClaireInput;
using namespace ClaireMath;

class SandboxCamera
{
public:
	SandboxCamera(float left, float right, float bottom, float top);

	void SetProjection(float left, float right, float bottom, float top);

	const ClaireMath::vec3& GetPosition() const { return m_Position; }
	void SetPosition(const ClaireMath::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

	float GetRotation() const { return m_Rotation; }
	void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

	const ClaireMath::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const ClaireMath::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const ClaireMath::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	void Update();
private:
	void RecalculateViewMatrix();
private:
	ClaireMath::mat4 m_ProjectionMatrix;
	ClaireMath::mat4 m_ViewMatrix;
	ClaireMath::mat4 m_ViewProjectionMatrix;

	ClaireMath::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	float m_Rotation = 0.0f;
};