#include "DX11VertexBuffer.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"
#include "Claire/Graphics/DX11/Shaders/DX11Shader.h"

DX11VertexBuffer::DX11VertexBuffer()
{
	
}

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

void DX11VertexBuffer::Create(void* vertices, uint32_t vertexSize, uint32_t listSize)
{
	m_VertexSize = vertexSize; 
	m_VerticesSize = listSize;

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = m_VertexSize * m_VerticesSize;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	GraphicsAssert(DX11Context::Get().GetDevice()->CreateBuffer(&buff_desc, &init_data, &m_Buffer));
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
