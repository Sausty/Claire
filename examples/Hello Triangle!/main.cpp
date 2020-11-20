#include <Claire/Claire.h>
#include <Claire/Graphics/DX11/Buffers/DX11VertexArray.h>
#include <Claire/Graphics/DX11/Buffers/DX11VertexBuffer.h>
#include <Claire/Graphics/DX11/Buffers/DX11ConstantBuffer.h>
#include <Claire/Graphics/DX11/Shaders/DX11Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

// Define constant buffer data in a struct

struct CUniform
{
	float r, g, b;
};

int main()
{
    // Quad vertices

	vertex list[] =
	{
		{  0.5f,  0.5f, 0.0f }, 
		{  0.5f, -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f,  0.5f, 0.0f },
	};
	uint32_t listSize = ARRAYSIZE(list);

    // Create the viewport and the window
	Viewport viewport(1280, 720);
	Window window(viewport, L"My Window");

    // Create the shader and bind it
	Shader* shader = new Shader(ReadFile("shaders/shader.hlsl"));
	shader->Bind();

    // VERTEX ARRAY, BUFFERS AND INDEX BUFFERS
	VertexArray vao;

    // NAME, SEMANTIC INDEX, TYPE, INPUT SLOT, ALIGNED BYTE OFFSET
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
	
    // CONSTANT BUFFER FOR SHADER UNIFORMS

	CUniform cb;
	cb.r = 0.0;
	cb.g = 1.0f;
	cb.b = 0.0f;

	ConstantBuffer* cbo = new ConstantBuffer(cb);

	while (window.IsOpen())
	{
        // Update and clears the window
		window.Update();
		window.ClearColor(0, 0.3f, 0.4f, 1);

        // Set the render viewport
		Context::Get().GetRendererContext()->SetViewport(viewport);
		
        // Draw
		cbo->BindForShader(shader);
		shader->Bind();
		cbo->Update();
		vao.DrawElements();

		window.Clear();
	}

    // Release the data
	vao.Release();
    cbo->Release();
	shader->Release();
}