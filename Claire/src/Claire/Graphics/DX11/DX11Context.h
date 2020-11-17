#pragma once

#include <d3d11.h>
#include <cstdint>
#include <Windows.h>

#include "DX11SwapChain.h"
#include "DX11RenderContext.h"

#include <string>

class Window;

enum class DrawMode
{
	TriangleList = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	TriangleStrip = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
};

class Context
{
public:
	void Init(const Window& window);
	void Shutdown();

	static Context& Get();

	ID3D11Device* GetDevice() { return m_Device; }
	ID3D11DeviceContext* GetDeviceContext() { return m_Context; }

	IDXGIDevice* GetDXGIDevice() const { return m_DXGIDevice; }
	IDXGIAdapter* GetDXGIAdapter() const { return m_DXGIAdapter; }
	IDXGIFactory* GetDXGIFactory() const { return m_DXGIFactory; }

	void OnWindowResize(uint32_t width, uint32_t height);

	void RecreateSwapChain(HWND hwnd, uint32_t width, uint32_t height) { m_RendererSwapChain->Create(hwnd, width, height); }
	SwapChain* GetRendererSwapChain() { return m_RendererSwapChain; }
	RenderContext* GetRendererContext() const { return m_RendererContext; }

	void ClearColor(float r, float g, float b, float a);
	void DrawIndexed(UINT count);
	void DrawArrays(UINT vertexCount, UINT startVertexCount, DrawMode mode);
private:
	HWND m_WindowHandle;
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_Context;
	D3D_FEATURE_LEVEL m_FeatureLevel;

	IDXGIDevice* m_DXGIDevice;
	IDXGIAdapter* m_DXGIAdapter;
	IDXGIFactory* m_DXGIFactory;
private:
	SwapChain* m_RendererSwapChain;
	RenderContext* m_RendererContext;
private:
	friend class SwapChain;
};