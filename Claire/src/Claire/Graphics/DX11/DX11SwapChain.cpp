#include "DX11SwapChain.h"
#include "DX11Context.h"

#include "Claire/Graphics/Window.h"

void SwapChain::Create(HWND hwnd, uint32_t width, uint32_t height)
{
	auto device = Context::Get().GetDevice();

	DXGI_SWAP_CHAIN_DESC swapChainInfo;
	ZeroMemory(&swapChainInfo, sizeof(swapChainInfo));

	swapChainInfo.BufferCount = 1;
	swapChainInfo.BufferDesc.Width = width;
	swapChainInfo.BufferDesc.Height = height;
	swapChainInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainInfo.BufferDesc.RefreshRate.Numerator = 60; // TODO: Select refresh rate
	swapChainInfo.BufferDesc.RefreshRate.Denominator = 1;
	swapChainInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainInfo.OutputWindow = hwnd;
	swapChainInfo.SampleDesc.Count = 1;
	swapChainInfo.SampleDesc.Quality = 0;
	swapChainInfo.Windowed = TRUE;

	HRESULT result = Context::Get().GetDXGIFactory()->CreateSwapChain(device, &swapChainInfo, &m_Handle);

	if (FAILED(result))
	{
		__debugbreak();
	}

	ID3D11Texture2D* buffer = NULL;
	result = m_Handle->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(result))
	{
		__debugbreak();
	}

	result = device->CreateRenderTargetView(buffer, NULL, &m_RenderTargetView);
	buffer->Release();

	if (FAILED(result))
	{
		__debugbreak();
	}
}

void SwapChain::Release()
{
	m_Handle->Release();
	delete this;
}

void SwapChain::Present()
{
	m_Handle->Present(false, NULL);
}
