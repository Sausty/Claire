#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cstdint>
#include "DX12CommandQueue.h"
#include "DX12SwapChain.h"

class Window;

class DX12Context
{
public:
	void Init(const Window& window);
	void Shutdown();

	static DX12Context& Get();

	ID3D12Device* GetDevice() { return m_Device; }

	IDXGIFactory4* GetDXGIFactory() const { return m_DXGIFactory; }
	DX12CommandQueue* GetCommandQueue() const { return m_CommandQueue; }
	DX12SwapChain* GetSwapChain() const { return m_SwapChain; }
private:
	HWND m_WindowHandle;
	ID3D12Device* m_Device = nullptr;
	IDXGIFactory4* m_DXGIFactory;

	DX12CommandQueue* m_CommandQueue;
	DX12SwapChain* m_SwapChain;
};