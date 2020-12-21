#include "Window.h"
#include "Claire/Core/Input/InputManager.h"
#include "Claire/Core/Input/MouseCodes.h"
#include <imgui.h>

#include <examples/imgui_impl_win32.h>

#include "DX11/View/DX11Viewport.h"
#include "DX11/DX11Context.h"
#include "DX12/View/DX12Viewport.h"
#include "DX12/DX12Context.h"
#include <examples/imgui_impl_dx11.h>
#include <examples/imgui_impl_dx12.h>

Window* WindowPointer = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_CREATE:
	{
		auto* const params = reinterpret_cast<LPCREATESTRUCT>(lParam);
		auto* const window =
			reinterpret_cast<Window* const>(params->lpCreateParams);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		break;
	}

	case WM_DESTROY:
	{
		auto* const window =
			reinterpret_cast<Window* const>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		window->Shutdown();
		PostQuitMessage(0);
		break;
	}

	case WM_LBUTTONDOWN:
	{
		ClaireInput::InputManager::GetMouseHandle().buttons[ClaireInput::MouseButtons::ButtonLeft] = true;
		break;
	}

	case WM_LBUTTONUP:
	{
		ClaireInput::InputManager::GetMouseHandle().buttons[ClaireInput::MouseButtons::ButtonLeft] = false;
		break;
	}

	case WM_RBUTTONDOWN:
	{
		ClaireInput::InputManager::GetMouseHandle().buttons[ClaireInput::MouseButtons::ButtonRight] = true;
		break;
	}

	case WM_RBUTTONUP:
	{
		ClaireInput::InputManager::GetMouseHandle().buttons[ClaireInput::MouseButtons::ButtonRight] = false;
		break;
	}

	case WM_MBUTTONDOWN:
	{
		ClaireInput::InputManager::GetMouseHandle().buttons[ClaireInput::MouseButtons::ButtonMiddle] = true;
		break;
	}

	case WM_MBUTTONUP:
	{
		ClaireInput::InputManager::GetMouseHandle().buttons[ClaireInput::MouseButtons::ButtonMiddle] = false;
		break;
	}

	case WM_DPICHANGED: {
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
		{
			const RECT* suggested_rect = (RECT*)lParam;
			::SetWindowPos(hwnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return NULL;
}

Window::Window(uint32_t width, uint32_t height, LPCWSTR title, API api)
	: m_Width(width), m_Height(height), m_Title(title)
{
	curApi = api;

	if (!Create())
		__debugbreak();

	switch (curApi)
	{
	case API::DirectX11:
		DX11Context::Get().Init(*this);
		break;
	case API::DirectX12:
		DX12Context::Get().Init(m_Handle);
		break;
	}
}

Window::~Window()
{
	switch (curApi)
	{
	case API::DirectX11:
		DX11Context::Get().Shutdown();
		break;
	case API::DirectX12:
		DX12Context::Get().Shutdown();
		break;
	}

	DestroyWindow(m_Handle);
}

void Window::Update()
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
}

RECT Window::GetWindowFramebufferSize()
{
	RECT result;
	GetClientRect(WindowPointer->GetNativeWindow(), &result);
	return result;
}

void Window::Clear()
{
	switch (curApi)
	{
	case API::DirectX11:
		DX11Context::Get().GetRendererSwapChain()->Present();
		break;
	}
}

void Window::ClearColor(float r, float g, float b, float a)
{
	switch (curApi)
	{
	case API::DirectX11:
		DX11Context::Get().ClearColor(r, g, b, a);
		break;
	}
}

void Window::StartImGui()
{
	switch (curApi)
	{
	case API::DirectX11:
		ImGui_ImplDX11_NewFrame();
		break;
	}
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Window::StopImGui()
{
	if (IsOpen())
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.DisplaySize = ImVec2((float)m_Width, (float)m_Height);

		ImGui::Render();

		switch (curApi)
		{
		case API::DirectX11:
			DX11Context::Get().GetRendererSwapChain()->RecreateRenderTargetView(m_Width, m_Height);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			break;
		}

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}

bool Window::Create()
{
	DWORD dwStyle = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU;
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	WNDCLASSEX wndClass{};
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.lpszClassName = m_Title;
	wndClass.lpfnWndProc = &WindowCallback;

	if (!RegisterClassEx(&wndClass))
		return false;

	RECT rect = { 0, 0, m_Width, m_Height };
	AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);

	const auto width = rect.right - rect.left;
	const auto height = rect.bottom - rect.top;

	m_Handle = CreateWindowEx(
		dwExStyle,
		wndClass.lpszClassName,
		wndClass.lpszClassName,
		dwStyle |                           // Defined Window Style
		WS_CLIPSIBLINGS |                   // Required Window Style
		WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		nullptr,
		this);

	if (!m_Handle)
		return false;

	ShowWindow(m_Handle, SW_SHOW);
	
	return true;
}

bool Window::Shutdown()
{
	m_IsRunning = false;

	return true;
}
