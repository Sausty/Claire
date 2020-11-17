#include "DX11VertexBuffer.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"
#include "Claire/Graphics/DX11/Shaders/DX11Shader.h"

VertexBuffer::VertexBuffer(void* vertices, uint32_t vertexSize, uint32_t listSize)
	: m_VertexSize(vertexSize), m_VerticesSize(listSize)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = m_VertexSize * m_VerticesSize;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	GraphicsAssert(Context::Get().GetDevice()->CreateBuffer(&buff_desc, &init_data, &m_Buffer));

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	uint32_t sizeLayout = ARRAYSIZE(layout);

	const Shader* shader = Shader::CurrentlyBound();
	GraphicsAssert(Context::Get().GetDevice()->CreateInputLayout(layout, sizeLayout, shader->GetData().VertexBlob->GetBufferPointer(), shader->GetData().VertexBlob->GetBufferSize(), &m_InputLayout));
}

void VertexBuffer::Release()
{
	m_Buffer->Release();
	m_InputLayout->Release();
	delete this;
}

void VertexBuffer::Bind()
{
	UINT stride = m_VertexSize;
	UINT offset = 0;
	Context::Get().GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);
	Context::Get().GetDeviceContext()->IASetInputLayout(m_InputLayout);
}

void VertexBuffer::Unbind()
{

}
