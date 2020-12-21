#pragma once

#include <d3d12.h>
#include <dxgi.h>
#include <cstdint>

class DX12Context
{
public:
	void Init(HWND hwnd);
	void Shutdown();

	static DX12Context& Get();

	ID3D12Device* GetDevice() { return m_Device; }

	IDXGIFactory* GetDXGIFactory() const { return m_DXGIFactory; }
private:
	HWND m_WindowHandle;
	ID3D12Device* m_Device = nullptr;

	IDXGIFactory* m_DXGIFactory;
};