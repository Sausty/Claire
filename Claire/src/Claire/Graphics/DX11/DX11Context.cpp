#include "DX11Context.h"

#include "Claire/Graphics/Window.h"

void Context::Init(const Window& window)
{
	m_WindowHandle = window.GetNativeWindow();

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	uint32_t driverSize = ARRAYSIZE(driverTypes);
	
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	uint32_t levelSize = ARRAYSIZE(levels);
	HRESULT success = 0;
	
	for (int i = 0; i < driverSize;)
	{
		success = D3D11CreateDevice(NULL, driverTypes[i], NULL, NULL, levels, levelSize, D3D11_SDK_VERSION, &m_Device, &m_FeatureLevel, &m_Context);
	
		if (SUCCEEDED(success))
			break;
			++i;
	}

	if (FAILED(success))
	{
		__debugbreak();
	}

	m_RendererContext = new RenderContext(m_Context);

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_DXGIDevice);
	m_DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_DXGIAdapter);
	m_DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_DXGIFactory);

	m_RendererSwapChain = new SwapChain();
	m_RendererSwapChain->Create(m_WindowHandle, window.GetWidth(), window.GetHeight());
}

void Context::Shutdown()
{
	m_RendererSwapChain->Release();

	m_DXGIDevice->Release();
	m_DXGIAdapter->Release();
	m_DXGIFactory->Release();

	m_RendererContext->Release();
	m_Device->Release();
}

Context& Context::Get()
{
	static Context context;
	return context;
}

void Context::OnWindowResize(uint32_t width, uint32_t height)
{
	if (m_WindowHandle)
	{
		m_RendererSwapChain->Release();
		m_RendererSwapChain = new SwapChain();
		m_RendererSwapChain->Create(m_WindowHandle, width, height);
	}
}

void Context::ClearColor(float r, float g, float b, float a)
{
	m_RendererContext->SetClearColor(m_RendererSwapChain, r, g, b, a);
}

void Context::DrawIndexed(UINT count)
{
	m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Context->DrawIndexed(count, 0, 0);
}

void Context::DrawArrays(UINT vertexCount, UINT startVertexCount, DrawMode mode)
{
	m_Context->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)mode);
	m_Context->Draw(vertexCount, startVertexCount);
}
