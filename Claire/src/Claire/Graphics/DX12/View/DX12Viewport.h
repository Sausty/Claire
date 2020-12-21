#pragma once

#include <d3d12.h>

class DX12Viewport
{
public:
	DX12Viewport(UINT width, UINT height)
		: m_Width(width), m_Height(height)
	{
		m_Viewport.Width = m_Width;
		m_Viewport.Height = m_Height;
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;
	}

	void Recreate(UINT width, UINT height)
	{
		m_Width = width;
		m_Height = height;

		m_Viewport.Width = m_Width;
		m_Viewport.Height = m_Height;
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;
	}

	float AspectRatio()
	{
		return m_Width / m_Height;
	}

	D3D12_VIEWPORT GetViewport() const { return m_Viewport; }
private:
	UINT m_Width;
	UINT m_Height;
	D3D12_VIEWPORT m_Viewport = {};
}; 
