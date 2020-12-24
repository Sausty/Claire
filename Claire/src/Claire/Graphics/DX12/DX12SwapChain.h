#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>

class DX12SwapChain
{
public:
	void Init(HWND hwnd, unsigned int width, unsigned int height);
	void Release();

	IDXGISwapChain4* GetSwapChain() { return m_Handle; }
private:
	IDXGISwapChain4* m_Handle;

	friend class DX11RenderContext;
};