#pragma once

#include "DX11VertexBuffer.h"
#include "DX11IndexBuffer.h"
#include <vector>

class DX11VertexArray
{
public:
	DX11VertexArray() = default;
	void Release();

	void AddVertexBuffer(DX11VertexBuffer* buffer);
	void SetIndexBuffer(DX11IndexBuffer* buffer);

	void DrawArrays();
	void DrawElements();
private:
	DX11IndexBuffer* ib;
	std::vector<DX11VertexBuffer*> m_VertexBuffers;
};