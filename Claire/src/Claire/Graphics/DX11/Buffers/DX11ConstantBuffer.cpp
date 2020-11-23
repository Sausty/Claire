#include "DX11ConstantBuffer.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"

#include <iostream>

ConstantBuffer::ConstantBuffer(std::any data)
	: m_Data(data)
{
	D3D11_BUFFER_DESC buff_desc;
	ZeroMemory(&buff_desc, sizeof(D3D11_BUFFER_DESC));
	buff_desc.ByteWidth = sizeof(data);
	buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = &data;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

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

void ConstantBuffer::Update()
{
	Context::Get().GetDeviceContext()->UpdateSubresource(m_BufferHandle, NULL, NULL, &m_Data, NULL, NULL);
}
