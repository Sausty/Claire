#pragma once

#include <d3d11.h>
#include <cstdint>

class DX11IndexBuffer
{
public:
	DX11IndexBuffer(uint32_t* data, uint32_t count);
	void Release();

	void Bind() const;
	void Unbind() const;

	uint32_t GetCount() const;

private:
	ID3D11Buffer* m_Handle;
	uint32_t m_Count;
};