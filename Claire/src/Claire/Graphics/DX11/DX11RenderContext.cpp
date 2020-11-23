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
	m_DeviceContext->ClearDepthStencilView(swapChain->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_DeviceContext->OMSetRenderTargets(1, &swapChain->m_RenderTargetView, swapChain->m_DepthStencilView);
	m_DeviceContext->RSSetState(swapChain->m_RasterizerState);
	m_DeviceContext->OMSetDepthStencilState(swapChain->GetDepthStencilState(), 0);
}

void RenderContext::Release()
{
	m_DeviceContext->Release();
	delete this;
}
