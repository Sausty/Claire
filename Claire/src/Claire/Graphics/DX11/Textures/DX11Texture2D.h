#pragma once

#include <d3d11.h>
#include <Claire/Graphics/DX11/Shaders/DX11Shader.h>

class DX11Texture2D
{
public:
	DX11Texture2D(const wchar_t* path);

	void Release();

	void Bind(int slot, DX11Shader* shader);
	void Unbind();
private:
	ID3D11Resource* m_Texture = nullptr;
	ID3D11ShaderResourceView* m_ShaderResView = nullptr;
};