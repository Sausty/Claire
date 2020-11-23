#pragma once

#include <d3d11.h>
#include <string>
#include <fstream>
#include <vector>

#include "Claire/Graphics/DX11/Buffers/DX11ConstantBuffer.h"

struct ShaderErrorInfo
{
	std::string Profile;
	std::string Message;
};

static std::string ReadFile(const std::string& filepath)
{
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
	if (in)
	{
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size != -1)
		{
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
		}
		else
		{
			__debugbreak();
		}
	}
	else
	{
		__debugbreak();
	}

	return result;
}

class Shader
{
private:
	static const Shader* s_CurrentlyBound;

	struct Data
	{
		ID3D11VertexShader* VertexShader;
		ID3D11PixelShader* FragmentShader;
		ID3DBlob* VertexBlob;
		ID3DBlob* FragmentBlob;
	};
	
	std::string m_FilePath;
	mutable Data m_Data;

public:
	Shader(const std::string& source);
	void Release();

	inline Data& GetData() const { return m_Data; }

	void Bind();
	void UpdateUniforms() const;
	void Unbind() const;

	void AddConstantBuffer(ConstantBuffer* buff);
private:
	static ID3DBlob* Compile(const std::string& source, const std::string& profile, const std::string& main, ShaderErrorInfo& info);
	void Load(const std::string& source);

	std::string RemoveComments(const std::string& source);

	std::vector<ConstantBuffer*> m_Buffers;
	int m_ExpectedSize = 0;
public:
	static bool TryCompile(const std::string& source, std::string& error);
	static bool TryCompileFromFile(const std::string& filepath, std::string& error);
	
	static const Shader* CurrentlyBound() { return s_CurrentlyBound; }
};