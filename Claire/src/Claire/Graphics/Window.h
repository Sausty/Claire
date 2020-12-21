#pragma once

#include <Windows.h>
#include <cstdint>

enum class API
{
	DirectX11,
	DirectX12
};

static API curApi;

class Window
{
public:
	Window(uint32_t width, uint32_t height, LPCWSTR title, API api);
	~Window();

	bool Create();
	bool Shutdown();

	void Update();

	bool IsOpen() { return m_IsRunning; }

	HWND GetNativeWindow() const { return m_Handle; }

	RECT GetWindowFramebufferSize();

	uint32_t GetWidth() const { return m_Width; }
	uint32_t GetHeight() const { return m_Height; }

	void Clear();
	void ClearColor(float r, float g, float b, float a);

	void StartImGui(); 
	void StopImGui();
private:
	HWND m_Handle = nullptr;

	uint32_t m_Width;
	uint32_t m_Height;
	LPCWSTR m_Title;

	bool m_IsRunning = true;
};