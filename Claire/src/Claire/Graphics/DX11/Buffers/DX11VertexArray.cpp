#include "DX11VertexArray.h"
#include "Claire/Graphics/DX11/DX11Context.h"

void VertexArray::Release()
{
	for (auto i : m_VertexBuffers)
	{
		i->Release();
	}
}

void VertexArray::AddVertexBuffer(VertexBuffer* buffer)
{
	m_VertexBuffers.push_back(buffer);
}

void VertexArray::DrawArrays()
{
	for (auto i : m_VertexBuffers)
	{
		Context::Get().DrawArrays(i->GetVerticesSize(), 0, DrawMode::TriangleStrip);
	}
}
