#pragma once

#include <string>
#include <vector>
#include <d3d11.h>

enum class LayoutType
{
	Float,
	Float2,
	Float3,
	Float4,
	Int,
	Int2,
	Int3,
	Int4
};

struct BufferElement
{
	std::string Name;
	uint32_t SemanticIndex;
	LayoutType Format;
	uint32_t InputSlot;

	uint32_t GetFormatSize() const
	{
		switch (Format)
		{
		case LayoutType::Float:	 return 4;
		case LayoutType::Float2: return 4 * 2;
		case LayoutType::Float3: return 4 * 3;
		case LayoutType::Float4: return 4 * 4;
		case LayoutType::Int:	 return 4;
		case LayoutType::Int2:   return 4 * 2;
		case LayoutType::Int3:   return 4 * 3;
		case LayoutType::Int4:   return 4 * 4;
		}
	}
};

class BufferLayout final
{
public:
	BufferLayout() {}

	BufferLayout(std::initializer_list<BufferElement> elements)
		: m_Layout(elements) {}

	void CalculateInputLayout();
	ID3D11InputLayout* GetNativeInputLayout() const { return m_InputLayout; }
private:
	ID3D11InputLayout* m_InputLayout;
	std::vector<D3D11_INPUT_ELEMENT_DESC> m_InputElementDescription;
	std::vector<BufferElement> m_Layout;
};