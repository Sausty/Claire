#include "DX11RenderContext.h"
#include "DX11SwapChain.h"

RenderContext::RenderContext(ID3D11DeviceContext* context)
	: m_DeviceContext(context)
{
}

void RenderContext::SetViewport(const Viewport& viewport)
{
	m_DeviceContext->RSSetViewports(1, &viewport.GetViewport());
}

void RenderContext::SetClearColor(SwapChain* swapChain, float r, float g, float b, float a)
{
	float ClearColorValues[] = { r, g, b, a };
	m_DeviceContext->ClearRenderTargetView(swapChain->GetRenderTargetView(), ClearColorValues);
	m_DeviceContext->OMSetRenderTargets(1, &swapChain->m_RenderTargetView, NULL);
}

void RenderContext::Release()
{
	m_DeviceContext->Release();
	delete this;
}
