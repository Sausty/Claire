#include <Claire/Claire.h>
#include <Claire/Graphics/DX11/Buffers/DX11VertexArray.h>
#include <Claire/Graphics/DX11/Buffers/DX11VertexBuffer.h>
#include <Claire/Graphics/DX11/Shaders/DX11Shader.h>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

int main()
{
	vertex list[] =
	{
		{  0.5f,  0.5f, 0.0f }, 
		{  0.5f, -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f,  0.5f, 0.0f },
	};

	uint32_t listSize = ARRAYSIZE(list);

	Viewport viewport(1280, 720);
	Window window(viewport, L"My Window");

	Shader* shader = new Shader(ReadFile("Shaders/HelloTriangle/HelloTriangle.hlsl"));
	shader->Bind();

	VertexArray vao;

	BufferLayout layout = {
		{ "POSITION", 0, LayoutType::Float3, 0, 0 }
	};

	VertexBuffer* buffer = new VertexBuffer();
	buffer->Create(list, sizeof(vertex), listSize);
	buffer->SetLayout(layout);

	uint32_t indices[] =
	{
		0,1,3, 
		1,2,3, 
	};
	IndexBuffer* ibo = new IndexBuffer(indices, sizeof(indices));

	vao.AddVertexBuffer(buffer);
	vao.SetIndexBuffer(ibo);

	while (window.IsOpen())
	{
		window.Update();
		window.ClearColor(0, 0.3f, 0.4f, 1);

		Context::Get().GetRendererContext()->SetViewport(viewport);
		
		shader->Bind();
		vao.DrawElements();

		window.Clear();
	}

	vao.Release();
	shader->Release();
}