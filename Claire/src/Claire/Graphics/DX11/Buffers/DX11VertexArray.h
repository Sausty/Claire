#pragma once

#include "DX11VertexBuffer.h"
#include "DX11IndexBuffer.h"
#include <vector>

class VertexArray
{
public:
	VertexArray() = default;
	void Release();

	void AddVertexBuffer(VertexBuffer* buffer);
	void SetIndexBuffer(IndexBuffer* buffer);

	void DrawArrays();
	void DrawElements();
private:
	IndexBuffer* ib;
	std::vector<VertexBuffer*> m_VertexBuffers;
};