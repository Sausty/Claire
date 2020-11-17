#include "DX11BufferLayout.h"

#include "Claire/Core/DX11Assert.h"
#include "Claire/Graphics/DX11/DX11Context.h"
#include "Claire/Graphics/DX11/Shaders/DX11Shader.h"

static DXGI_FORMAT ClaireToDXGI(LayoutType type)
{
	switch (type)
	{
		case LayoutType::Float: return DXGI_FORMAT_R32_FLOAT;
		case LayoutType::Float2: return DXGI_FORMAT_R32G32_FLOAT;
		case LayoutType::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
		case LayoutType::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case LayoutType::Int: return DXGI_FORMAT_R32_SINT;
		case LayoutType::Int2: return DXGI_FORMAT_R32G32_SINT;
		case LayoutType::Int3: return DXGI_FORMAT_R32G32B32_SINT;
		case LayoutType::Int4: return DXGI_FORMAT_R32G32B32A32_SINT;
	}
};

void BufferLayout::CalculateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC* desc = new D3D11_INPUT_ELEMENT_DESC[m_Layout.size()];
	for (auto i = 0; i < m_Layout.size(); i++)
	{
		const BufferElement& element = m_Layout[i];
		desc[i] = { element.Name.c_str(), element.SemanticIndex, ClaireToDXGI(element.Format), element.InputSlot, element.AlignedByteOffset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	const Shader* shader = Shader::CurrentlyBound();
	GraphicsAssert(Context::Get().GetDevice()->CreateInputLayout(desc, m_Layout.size(), shader->GetData().VertexBlob->GetBufferPointer(), shader->GetData().VertexBlob->GetBufferSize(), &m_InputLayout));
	delete desc;
}
