#pragma once

#include <d3d11.h>
#include <cstdint>
#include "DX11BufferLayout.h"

class DX11VertexBuffer
{
public:
	void Release();

	void SetLayout(const DX11BufferLayout& layout);
	void Create(uint32_t vertexSize);
	void Create(void* vertices, uint32_t vertexSize, uint32_t listSize);
	void SetData(void* vertices, uint32_t listSize);

	uint32_t GetVertexSize() const { return m_VertexSize; }
	uint32_t GetVerticesSize() const { return m_VerticesSize; }

	void Bind();
	void Unbind();
private:
	void Resize(uint32_t size);
	uint32_t m_VertexSize;
	uint32_t m_VerticesSize;
private:
	void* GetPointerInternal();
	ID3D11Buffer* m_Buffer;
	D3D11_BUFFER_DESC m_BufferDesc;
	D3D11_MAPPED_SUBRESOURCE m_MappedSubresource;
	DX11BufferLayout m_Layout;
private:
	friend class RenderContext;
};