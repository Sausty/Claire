#include <Claire/Claire.h>
#include <iostream>

using namespace ClaireMath;
using namespace ClaireInput;

struct vertex
{
	vec3 position;
	vec3 color;
};

struct CBO
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

int main()
{
	vertex list[] =
	{
		vec3(0.5f, 0.5f, 0.0f), vec3(1, 0, 0),
		vec3(0.5f,-0.5f, 0.0f), vec3(0, 1, 0),
		vec3(-0.5f,-0.5f, 0.0f),vec3(0, 0, 1),
		vec3(-0.5f, 0.5f, 0.0f),vec3(0, 1, 0)
	};
	uint32_t listSize = ARRAYSIZE(list);

	Viewport viewport(1280, 720);
	Window window(viewport, L"My Window");

	Shader* shader = new Shader(ReadFile("Shaders/HelloTriangle/HelloTriangle.hlsl"));
	shader->Bind();

	CBO data;

	data.modelMatrix = ClaireMath::Translation(ClaireMath::vec3(0, 0, 0));
	data.viewMatrix = ClaireMath::mat4::Identity();
	data.projectionMatrix = ClaireMath::Perspective(viewport.AspectRatio(), 70, 0.01, 10000);

	ConstantBuffer* constantBuffer = new ConstantBuffer(&data, sizeof(CBO));

	VertexArray vao;

	BufferLayout layout = {
		{ "POSITION", 0, LayoutType::Float3, 0 },
		{ "COLOR", 0, LayoutType::Float3, 0 }
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

	shader->Unbind();

	while (window.IsOpen())
	{
		window.Update();
		window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		Context::Get().GetRendererContext()->SetViewport(viewport);

		shader->Bind();
		constantBuffer->BindForShader(0);
		constantBuffer->Update(&data);

		vao.DrawElements();

		shader->Unbind();

		window.Clear();
	}

	shader->Release();
	vao.Release();
}