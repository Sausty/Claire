#include "DX11Context.h"

#include "Claire/Graphics/Window.h"
#include <Windows.h>
#include <DirectXTex.h>
#include <DirectXTex.inl>
#include <wrl.h>
#include <stdexcept>
#include <imgui.h>
#include <examples/imgui_impl_dx11.h>
#include <examples/imgui_impl_win32.h>

void DX11Context::Init(const Window& window)
{
	ImGui_ImplWin32_EnableDpiAwareness();

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

	m_RendererContext = new DX11RenderContext(m_Context);

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_DXGIDevice);
	m_DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_DXGIAdapter);
	m_DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_DXGIFactory);

	m_RendererSwapChain = new DX11SwapChain();
	m_RendererSwapChain->Create(m_WindowHandle, window.GetWidth(), window.GetHeight());

	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		throw std::runtime_error("COM Library is already initialized on this thread.");
	}

	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;        
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   
	io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; 

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(m_WindowHandle);
	ImGui_ImplDX11_Init(m_Device, m_Context);
}

void DX11Context::Shutdown()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	m_RendererSwapChain->Release();

	m_DXGIDevice->Release();
	m_DXGIAdapter->Release();
	m_DXGIFactory->Release();

	m_RendererContext->Release();
	m_Device->Release();
}

DX11Context& DX11Context::Get()
{
	static DX11Context context;
	return context;
}

void DX11Context::OnWindowResize(uint32_t width, uint32_t height)
{
	m_RendererSwapChain->RecreateRenderTargetView(width, height);
}

void DX11Context::ClearColor(float r, float g, float b, float a)
{
	m_RendererContext->SetClearColor(m_RendererSwapChain, r, g, b, a);
}

void DX11Context::DrawIndexed(UINT count)
{
	m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Context->DrawIndexed(count, 0, 0);
}

void DX11Context::DrawArrays(UINT vertexCount, UINT startVertexCount, DrawMode mode)
{
	m_Context->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)mode);
	m_Context->Draw(vertexCount, startVertexCount);
}
