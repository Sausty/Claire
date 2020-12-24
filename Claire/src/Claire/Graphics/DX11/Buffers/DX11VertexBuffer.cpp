#include "DX11VertexBuffer.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"
#include "Claire/Graphics/DX11/Shaders/DX11Shader.h"

void DX11VertexBuffer::Release()
{
	m_Buffer->Release();
	m_Layout.GetNativeInputLayout()->Release();
	delete this;
}

void DX11VertexBuffer::SetLayout(const DX11BufferLayout& layout)
{
	m_Layout = layout;
	m_Layout.CalculateInputLayout();
}

void DX11VertexBuffer::Create(uint32_t vertexSize)
{
	m_VertexSize = vertexSize;
	m_VerticesSize = 0;

	m_BufferDesc = {};
	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_BufferDesc.MiscFlags = 0;
}

void DX11VertexBuffer::Create(void* vertices, uint32_t vertexSize, uint32_t listSize)
{
	m_VertexSize = vertexSize; 
	m_VerticesSize = listSize;

	m_BufferDesc = {};
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.ByteWidth = m_VertexSize * m_VerticesSize;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = 0;
	m_BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	GraphicsAssert(DX11Context::Get().GetDevice()->CreateBuffer(&m_BufferDesc, &init_data, &m_Buffer));
}

void* DX11VertexBuffer::GetPointerInternal()
{
	DX11Context::Get().GetDeviceContext()->Map(m_Buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_MappedSubresource);
	return m_MappedSubresource.pData;
}

void DX11VertexBuffer::Resize(uint32_t size)
{
	m_VerticesSize = size;
	m_BufferDesc.ByteWidth = size;
	GraphicsAssert(DX11Context::Get().GetDevice()->CreateBuffer(&m_BufferDesc, NULL, &m_Buffer));
}

void DX11VertexBuffer::SetData(void* vertices, uint32_t listSize)
{
	if (m_VerticesSize < listSize)
		Resize(listSize);

	GetPointerInternal();
	memcpy(m_MappedSubresource.pData, vertices, listSize);
	DX11Context::Get().GetDeviceContext()->Unmap(m_Buffer, NULL);
}

void DX11VertexBuffer::Bind()
{
	UINT stride = m_VertexSize;
	UINT offset = 0;
	DX11Context::Get().GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);
	DX11Context::Get().GetDeviceContext()->IASetInputLayout(m_Layout.GetNativeInputLayout());
}

void DX11VertexBuffer::Unbind()
{

}
