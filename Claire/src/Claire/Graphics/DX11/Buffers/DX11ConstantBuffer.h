#pragma once

#include <d3d11.h>
#include <cstdint>

#include "Claire/Graphics/DX11/Shaders/DX11Shader.h"

#include <any>

class ConstantBuffer
{
public:
	ConstantBuffer(std::any data);
	void Release();

	void BindForShader(Shader* shader);
	void Update();

	ID3D11Buffer* GetBufferHandle() const { return m_BufferHandle; }
private:
	std::any m_Data;
	ID3D11Buffer* m_BufferHandle = nullptr;
};