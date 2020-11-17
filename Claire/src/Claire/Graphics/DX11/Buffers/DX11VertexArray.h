#pragma once

#include "DX11VertexBuffer.h"
#include <vector>

class VertexArray
{
public:
	VertexArray() = default;
	void Release();

	void AddVertexBuffer(VertexBuffer* buffer);

	void DrawArrays();
private:
	std::vector<VertexBuffer*> m_VertexBuffers;
};