#include "DX11ConstantBuffer.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"

#include <iostream>

ConstantBuffer::ConstantBuffer(void* data, uint32_t size)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = data;


	GraphicsAssert(Context::Get().GetDevice()->CreateBuffer(&buff_desc, &init_data, &m_BufferHandle))
}

void ConstantBuffer::Release()
{
	m_BufferHandle->Release();
	delete this;
}

void ConstantBuffer::BindForShader(int bufferIndex)
{
	Context::Get().GetDeviceContext()->VSSetConstantBuffers(bufferIndex, 1, &m_BufferHandle);
	Context::Get().GetDeviceContext()->PSSetConstantBuffers(bufferIndex, 1, &m_BufferHandle);
}

void ConstantBuffer::Unbind()
{
	Context::Get().GetDeviceContext()->VSSetConstantBuffers(0, 1, nullptr);
	Context::Get().GetDeviceContext()->PSSetConstantBuffers(0, 1, nullptr);
}

void ConstantBuffer::Update(void* data)
{
	Context::Get().GetDeviceContext()->UpdateSubresource(m_BufferHandle, NULL, NULL, data, NULL, NULL);
}
