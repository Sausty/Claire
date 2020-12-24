#include "DX12Context.h"
#include "Claire/Graphics/Window.h"

void DX12Context::Init(const Window& window)
{
	CreateDXGIFactory2(0, IID_PPV_ARGS(&m_DXGIFactory));

	D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device));

	m_CommandQueue = new DX12CommandQueue();
	m_CommandQueue->Init();
	m_SwapChain = new DX12SwapChain();
	m_SwapChain->Init(window.GetNativeWindow(), window.GetWidth(), window.GetHeight());
}

void DX12Context::Shutdown()
{
	m_SwapChain->Release();
	m_CommandQueue->Release();
	m_Device->Release();
	m_DXGIFactory->Release();
}

DX12Context& DX12Context::Get()
{
	static DX12Context ctx;
	return ctx;
}
