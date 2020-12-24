#include "DX12SwapChain.h"
#include "DX12Context.h"

void DX12SwapChain::Init(HWND hwnd, unsigned int width, unsigned int height)
{
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Width = width;
    swapChainDesc.Height = height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.Stereo = FALSE;
    swapChainDesc.SampleDesc = { 1, 0 };
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    swapChainDesc.Flags = 0;

    IDXGISwapChain1* swapChain1;
    HRESULT res = DX12Context::Get().GetDXGIFactory()->CreateSwapChainForHwnd(DX12Context::Get().GetCommandQueue()->GetCommandQueue(), hwnd, &swapChainDesc, nullptr, nullptr, &swapChain1);
    if (FAILED(res))
        __debugbreak();

    m_Handle = (IDXGISwapChain4*)swapChain1;
}

void DX12SwapChain::Release()
{
    if (m_Handle)
        m_Handle->Release();

    if (this)
    {
        delete this;
    }
}
