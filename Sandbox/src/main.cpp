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
		{ -0.5f, -0.5f, 0.0f }, 
		{ -0.5f,  0.5f, 0.0f },
		{  0.5f, -0.5f, 0.0f },
		{  0.5f,  0.5f, 0.0f },
	};
	uint32_t listSize = ARRAYSIZE(list);

	Viewport viewport(1280, 720);
	Window window(viewport, L"My Window");

	Shader* shader = new Shader(ReadFile("Shaders/HelloTriangle/HelloTriangle.hlsl"));
	shader->Bind();

	VertexArray vao;

	VertexBuffer* buffer = new VertexBuffer(list, sizeof(vertex), listSize);
	vao.AddVertexBuffer(buffer);

	while (window.IsOpen())
	{
		window.Update();
		window.ClearColor(0, 0.3f, 0.4f, 1);

		Context::Get().GetRendererContext()->SetViewport(viewport);
		
		shader->Bind();
		buffer->Bind();
		vao.DrawArrays();

		window.Clear();
	}

	vao.Release();
	shader->Release();
}