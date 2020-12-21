#include "DX12Context.h"
#include "Claire/Graphics/Window.h"

void DX12Context::Init(HWND hwnd)
{
	CreateDXGIFactory(IID_PPV_ARGS(&m_DXGIFactory));

	D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device));
}

void DX12Context::Shutdown()
{
	m_Device->Release();
	m_DXGIFactory->Release();
}

DX12Context& DX12Context::Get()
{
	static DX12Context ctx;
	return ctx;
}
