#include "DX11Shader.h"
#include "Claire/Graphics/DX11/DX11Context.h"

#include <fstream>
#include <d3dcompiler.h>
#include <iostream>

const Shader* Shader::s_CurrentlyBound = nullptr;

Shader::Shader(const std::string& source)
{
	Load(source);
}

void Shader::Release()
{
	for (int i = 0; i < m_Buffers.size(); i++)
		m_Buffers[i]->Release();

	m_Data.VertexShader->Release();
	m_Data.FragmentShader->Release();
}

void Shader::Bind()
{
	s_CurrentlyBound = this;

	Context::Get().GetDeviceContext()->VSSetShader(m_Data.VertexShader, NULL, 0);
	Context::Get().GetDeviceContext()->PSSetShader(m_Data.FragmentShader, NULL, 0);

	for (int i = 0; i < m_Buffers.size(); i++)
		m_Buffers[i]->BindForShader(i);
}

void Shader::UpdateUniforms() const
{
	for (int i = 0; i < m_Buffers.size(); i++)
		m_Buffers[i]->Update();
}

void Shader::Unbind() const
{
	s_CurrentlyBound = nullptr;

	Context::Get().GetDeviceContext()->VSSetShader(nullptr, NULL, 0);
	Context::Get().GetDeviceContext()->PSSetShader(nullptr, NULL, 0);
}

void Shader::AddConstantBuffer(ConstantBuffer* buff)
{
	m_Buffers.push_back(buff);
	m_ExpectedSize++;
}

ID3DBlob* Shader::Compile(const std::string& source, const std::string& profile, const std::string& main, ShaderErrorInfo& info)
{
	ID3DBlob* shaderBlob;
	ID3DBlob* errorBlob;
	HRESULT status = D3DCompile(source.c_str(), source.size(), NULL, NULL, NULL, main.c_str(), profile.c_str(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
	if (status != S_OK)
		info.Message = "Unable to compile shader from source\n";
	if (errorBlob)
	{
		info.Profile += profile + "\n";
		if (errorBlob->GetBufferSize())
			std::cout << "Shader Compile Errors" << std::endl << (const char*)errorBlob->GetBufferPointer() << std::endl;
		errorBlob->Release();
	}
	if (status == S_OK)
		return shaderBlob;
	return nullptr;
}

void Shader::Load(const std::string& source)
{
	ShaderErrorInfo info;
	m_Data.VertexBlob = Compile(source, "vs_5_0", "VSMain", info);
	m_Data.FragmentBlob = Compile(source, "ps_5_0", "PSMain", info);
	Context::Get().GetDevice()->CreateVertexShader(m_Data.VertexBlob->GetBufferPointer(), m_Data.VertexBlob->GetBufferSize(), NULL, &m_Data.VertexShader);
	Context::Get().GetDevice()->CreatePixelShader(m_Data.FragmentBlob->GetBufferPointer(), m_Data.FragmentBlob->GetBufferSize(), NULL, &m_Data.FragmentShader);
}

std::string Shader::RemoveComments(const std::string& source)
{
	return std::string();
}

bool Shader::TryCompile(const std::string& source, std::string& error)
{
	ShaderErrorInfo info;

	if (!Compile(source, "vs_5_0", "VSMain", info))
	{
		error += info.Message;
		return false;
	}

	if (!Compile(source, "ps_5_0", "PSMain", info))
	{
		error += info.Message;
		return false;
	}
	return true;
}

bool Shader::TryCompileFromFile(const std::string& filepath, std::string& error)
{
	std::string source = ReadFile(filepath);
	return TryCompile(source, error);
}
