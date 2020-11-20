#include "DX11ConstantBuffer.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"

#include <iostream>

ConstantBuffer::ConstantBuffer(std::any data)
	: m_Data(data)
{
	D3D11_BUFFER_DESC buff_desc;
	std::cout << sizeof(data) << std::endl;
	buff_desc.ByteWidth = sizeof(data);
	buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = &data;

	GraphicsAssert(Context::Get().GetDevice()->CreateBuffer(&buff_desc, &init_data, &m_BufferHandle))
}

void ConstantBuffer::Release()
{
	m_BufferHandle->Release();
	delete this;
}

void ConstantBuffer::BindForShader(Shader* shader)
{
	Context::Get().GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_BufferHandle);
	Context::Get().GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_BufferHandle);
}

void ConstantBuffer::Update()
{
	Context::Get().GetDeviceContext()->UpdateSubresource(m_BufferHandle, NULL, NULL, &m_Data, NULL, NULL);
}
