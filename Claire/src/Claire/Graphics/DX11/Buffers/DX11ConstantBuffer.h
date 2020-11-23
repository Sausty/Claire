#pragma once

#include <d3d11.h>
#include <cstdint>

#include <any>

class ConstantBuffer
{
public:
	ConstantBuffer(std::any data);
	void Release();

	void BindForShader(int bufferIndex);
	void Unbind();

	void Update();

	ID3D11Buffer* GetBufferHandle() const { return m_BufferHandle; }
private:
	std::any m_Data;
	ID3D11Buffer* m_BufferHandle = nullptr;
};