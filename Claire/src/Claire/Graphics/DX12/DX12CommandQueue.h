#pragma once

#include <d3d12.h>

class DX12CommandQueue
{
public:
	void Init();
	void Release();

	ID3D12CommandQueue* GetCommandQueue() { return m_CmdQueue; }
private:
	ID3D12CommandQueue* m_CmdQueue;
};