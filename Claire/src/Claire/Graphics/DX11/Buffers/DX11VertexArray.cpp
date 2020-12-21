#include "DX11VertexArray.h"
#include "Claire/Graphics/DX11/DX11Context.h"

void DX11VertexArray::Release()
{
	for (auto i : m_VertexBuffers)
	{
		i->Release();
	}

	ib->Release();
}

void DX11VertexArray::AddVertexBuffer(DX11VertexBuffer* buffer)
{
	m_VertexBuffers.push_back(buffer);
}

void DX11VertexArray::SetIndexBuffer(DX11IndexBuffer* buffer)
{
	ib = buffer;
}

void DX11VertexArray::DrawArrays()
{
	for (auto i : m_VertexBuffers)
	{
		DX11Context::Get().DrawArrays(i->GetVerticesSize(), 0, DrawMode::TriangleStrip);
	}
}

void DX11VertexArray::DrawElements()
{
	for (auto i : m_VertexBuffers)
		i->Bind();
	ib->Bind();
	DX11Context::Get().DrawIndexed(ib->GetCount());
}
