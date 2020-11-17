#pragma once

#include <d3d11.h>
#include <cstdint>

class VertexBuffer
{
public:
	VertexBuffer(void* vertices, uint32_t vertexSize, uint32_t listSize);
	void Release();

	uint32_t GetVertexSize() const { return m_VertexSize; }
	uint32_t GetVerticesSize() const { return m_VerticesSize; }

	void Bind();
	void Unbind();
private:
	uint32_t m_VertexSize;
	uint32_t m_VerticesSize;
private:
	ID3D11Buffer* m_Buffer;
	ID3D11InputLayout* m_InputLayout;
private:
	friend class RenderContext;
};