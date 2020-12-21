#pragma once

#include <d3d11.h>
#include <cstdint>

class DX11ConstantBuffer
{
public:
	DX11ConstantBuffer(void* data, uint32_t size);
	void Release();

	void BindForShader(int bufferIndex);
	void Unbind();

	void Update(void* data);

	ID3D11Buffer* GetBufferHandle() const { return m_BufferHandle; }
private:
	ID3D11Buffer* m_BufferHandle = nullptr;
};