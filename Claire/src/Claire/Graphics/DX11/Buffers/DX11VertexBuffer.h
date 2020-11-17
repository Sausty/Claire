#pragma once

#include <d3d11.h>
#include <cstdint>
#include "DX11BufferLayout.h"

class VertexBuffer
{
public:
	VertexBuffer();
	void Release();

	void SetLayout(const BufferLayout& layout);
	void Create(void* vertices, uint32_t vertexSize, uint32_t listSize);

	uint32_t GetVertexSize() const { return m_VertexSize; }
	uint32_t GetVerticesSize() const { return m_VerticesSize; }

	void Bind();
	void Unbind();
private:
	uint32_t m_VertexSize;
	uint32_t m_VerticesSize;
private:
	ID3D11Buffer* m_Buffer;
	BufferLayout m_Layout;
private:
	friend class RenderContext;
};