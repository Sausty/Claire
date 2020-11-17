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
	uint32_t AlignedByteOffset;
};

class BufferLayout
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