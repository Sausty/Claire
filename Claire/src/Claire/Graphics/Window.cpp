#include "Window.h"

Window* WindowPointer = nullptr;

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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
	
	case WM_SIZE:
	{
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return NULL;
}

Window::Window(const Viewport& viewport, LPCWSTR title)
	: m_Width(viewport.GetViewport().Width), m_Height(viewport.GetViewport().Height), m_Title(title)
{
	if (!Create())
		__debugbreak();

	Context::Get().Init(*this);
}

Window::Window(uint32_t width, uint32_t height, LPCWSTR title)
	: m_Width(width), m_Height(height), m_Title(title)
{
	if (!Create())
		__debugbreak();

	Context::Get().Init(*this);
}

Window::~Window()
{
	Context::Get().Shutdown();
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
	Context::Get().GetRendererSwapChain()->Present();
}

void Window::ClearColor(float r, float g, float b, float a)
{
	Context::Get().ClearColor(r, g, b, a);
}

bool Window::Create()
{
	WNDCLASSEX wndClass{};
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
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	const auto width = rect.right - rect.left;
	const auto height = rect.bottom - rect.top;

	m_Handle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		wndClass.lpszClassName,
		wndClass.lpszClassName,
		WS_OVERLAPPEDWINDOW,
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
