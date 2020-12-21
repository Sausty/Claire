#include "DX11ConstantBuffer.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"

#include <iostream>

DX11ConstantBuffer::DX11ConstantBuffer(void* data, uint32_t size)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = data;


	GraphicsAssert(DX11Context::Get().GetDevice()->CreateBuffer(&buff_desc, &init_data, &m_BufferHandle))
}

void DX11ConstantBuffer::Release()
{
	m_BufferHandle->Release();
	delete this;
}

void DX11ConstantBuffer::BindForShader(int bufferIndex)
{
	DX11Context::Get().GetDeviceContext()->VSSetConstantBuffers(bufferIndex, 1, &m_BufferHandle);
	DX11Context::Get().GetDeviceContext()->PSSetConstantBuffers(bufferIndex, 1, &m_BufferHandle);
}

void DX11ConstantBuffer::Unbind()
{
	DX11Context::Get().GetDeviceContext()->VSSetConstantBuffers(0, 1, nullptr);
	DX11Context::Get().GetDeviceContext()->PSSetConstantBuffers(0, 1, nullptr);
}

void DX11ConstantBuffer::Update(void* data)
{
	DX11Context::Get().GetDeviceContext()->UpdateSubresource(m_BufferHandle, NULL, NULL, data, NULL, NULL);
}
