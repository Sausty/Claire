#include "DX11IndexBuffer.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"

DX11IndexBuffer::DX11IndexBuffer(uint32_t* data, uint32_t count)
	: m_Count(count)
{
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(D3D11_BUFFER_DESC));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = count * sizeof(uint32_t);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA ibInitData;
	ibInitData.pSysMem = data;

	GraphicsAssert(DX11Context::Get().GetDevice()->CreateBuffer(&ibd, &ibInitData, &m_Handle));
}

void DX11IndexBuffer::Release()
{
	m_Handle->Release();
	delete this;
}

void DX11IndexBuffer::Bind() const
{
	DX11Context::Get().GetDeviceContext()->IASetIndexBuffer(m_Handle, DXGI_FORMAT_R32_UINT, 0);
}

void DX11IndexBuffer::Unbind() const
{
}

uint32_t DX11IndexBuffer::GetCount() const
{
	return m_Count;
}
