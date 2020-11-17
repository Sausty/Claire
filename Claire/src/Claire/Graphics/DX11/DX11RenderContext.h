#pragma once

#include <d3d11.h>
#include "View/DX11Viewport.h"

class SwapChain;

class RenderContext
{
public:
	RenderContext(ID3D11DeviceContext* context);

	void SetViewport(const Viewport& viewport);
	void SetClearColor(SwapChain* swapChain, float r, float g, float b, float a);

	void Release();

	ID3D11DeviceContext* GetDeviceContext() const { return m_DeviceContext; }
private:
	ID3D11DeviceContext* m_DeviceContext;
};