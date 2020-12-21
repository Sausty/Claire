#include <Claire/Claire.h>
#include <iostream>

#include "FPSCamera.h"
#include <imgui.h>

using namespace ClaireInput;

struct vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
};

int main()
{
	Camera camera(glm::vec3(0, 0, -3));

	vertex vertices[] = 
	{
		glm::vec3(0.5f, 0.5f, 0.0f),  glm::vec3(1, 0, 0), glm::vec2(0.0, 0.0),
		glm::vec3(0.5f,-0.5f, 0.0f),  glm::vec3(0, 1, 0), glm::vec2(0.0, 1.0),
		glm::vec3(-0.5f,-0.5f, 0.0f), glm::vec3(0, 0, 1), glm::vec2(1.0, 1.0),
		glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1, 1, 0), glm::vec2(1.0, 0.0)
	};
	uint32_t listSize = ARRAYSIZE(vertices);

	Window window(1280, 720, L"My Window", API::DirectX11);

	Shader* shader = new Shader(ReadFile("Shaders/HelloTriangle/HelloTriangle.hlsl"));
	shader->Bind();

	glm::mat4 cam = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)1280 / (float)720, 0.1f, 100.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
	glm::mat4 result = projection * cam * model;
	ConstantBuffer* constantBuffer = new ConstantBuffer(&cam, sizeof(glm::mat4));

	VertexArray vao;

	BufferLayout layout = {
		{ "POSITION", 0, LayoutType::Float3, 0 },
		{ "COLOR", 0, LayoutType::Float3, 0 },
		{ "TEXCOORD", 0, LayoutType::Float2, 0 }
	};

	VertexBuffer* buffer = new VertexBuffer();
	buffer->Create(vertices, sizeof(vertex), listSize);
	buffer->SetLayout(layout);

	uint32_t indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};
	IndexBuffer* ibo = new IndexBuffer(indices, sizeof(indices));

	vao.AddVertexBuffer(buffer);
	vao.SetIndexBuffer(ibo);

	shader->Unbind();

	Texture2D tex(L"res/textures/companion.jpg");

	while (window.IsOpen())
	{
		window.Update();
		window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Context::Get().GetRendererContext()->SetViewport(Viewport(1280, 720));

		{
			shader->Bind();
			tex.Bind(0, shader);

			constantBuffer->BindForShader(0);
			glm::mat4 cam = camera.GetViewMatrix();
			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)1280 / (float)720, 0.1f, 100.0f);
			glm::mat4 result = projection * cam * model;
			camera.Update();
			constantBuffer->Update(&cam);

			vao.DrawElements();

			tex.Unbind();
			shader->Unbind();
		}

		window.StartImGui();
		ImGui::ShowDemoWindow();
		window.StopImGui();

		window.Clear();
	}

	shader->Release();
	tex.Release();
	vao.Release();
}