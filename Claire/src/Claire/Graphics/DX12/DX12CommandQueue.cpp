#include "DX12CommandQueue.h"
#include "DX12Context.h"

void DX12CommandQueue::Init()
{
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.NodeMask = 0;

    HRESULT res = DX12Context::Get().GetDevice()->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_CmdQueue));
    if (FAILED(res))
        __debugbreak();
}

void DX12CommandQueue::Release()
{   
    if (m_CmdQueue)
    {
        m_CmdQueue->Release();
    }

    if (this)
    {
        delete this;
    }
}
