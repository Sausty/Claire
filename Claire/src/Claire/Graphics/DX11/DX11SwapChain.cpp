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

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	result = device->CreateTexture2D(&depthStencilDesc, NULL, &m_DepthStencilBuffer);
	if (FAILED(result))
	{
		__debugbreak();
	}

	result = device->CreateDepthStencilView(m_DepthStencilBuffer, NULL, &m_DepthStencilView);
	if (FAILED(result))
	{
		__debugbreak();
	}

	D3D11_DEPTH_STENCIL_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	result = device->CreateDepthStencilState(&depthstencildesc, &m_DepthStencilState);
	if (FAILED(result))
	{
		__debugbreak();
	}

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	result = device->CreateRasterizerState(&rasterizerDesc, &m_RasterizerState);
	if (FAILED(result))
	{
		__debugbreak();
	}

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	result = device->CreateSamplerState(&sampDesc, &m_SamplerState); //Create sampler state
	if (FAILED(result))
	{
		__debugbreak();
	}

	Context::Get().GetDeviceContext()->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	Context::Get().GetDeviceContext()->RSSetViewports(1, &vp);
}

void SwapChain::Release()
{
	m_SamplerState->Release();
	m_RasterizerState->Release(); 
	m_DepthStencilState->Release();
	m_DepthStencilView->Release();
	m_DepthStencilBuffer->Release();
	m_RenderTargetView->Release();
	m_Handle->Release();
	delete this;
}

void SwapChain::Present()
{
	m_Handle->Present(1, 0);
}

void SwapChain::RecreateRenderTargetView(uint32_t width, uint32_t height)
{
	if (m_Handle != nullptr)
	{
		Context::Get().GetDeviceContext()->OMSetRenderTargets(0, 0, 0);
		m_RenderTargetView->Release();

		HRESULT hr;
		hr = m_Handle->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

		if (FAILED(hr))
			__debugbreak();

		ID3D11Texture2D* buffer = NULL;
		hr = m_Handle->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

		if (FAILED(hr))
		{
			__debugbreak();
		}

		hr = Context::Get().GetDevice()->CreateRenderTargetView(buffer, NULL, &m_RenderTargetView);
		buffer->Release();

		Context::Get().GetDeviceContext()->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

		D3D11_VIEWPORT vp;
		vp.Width = width;
		vp.Height = height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		Context::Get().GetDeviceContext()->RSSetViewports(1, &vp);
	}
}
