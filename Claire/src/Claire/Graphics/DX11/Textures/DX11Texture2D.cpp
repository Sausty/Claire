#include "DX11Texture2D.h"
#include <DirectXTex.h>
#include <Claire/Graphics/DX11/DX11Context.h>
#include <Claire/Core/DX11Assert.h>
#include <wincodec.h>

Texture2D::Texture2D(const wchar_t* path)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(Context::Get().GetDevice(), image_data.GetImages(),
			image_data.GetImageCount(), image_data.GetMetadata(), &m_Texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsAssert(Context::Get().GetDevice()->CreateShaderResourceView(m_Texture, &desc, &m_ShaderResView));
	}
	else
	{
		__debugbreak();
	}
}

void Texture2D::Release()
{
	m_ShaderResView->Release();
	m_Texture->Release();
}

void Texture2D::Bind(int slot, Shader* shader)
{
	Context::Get().GetDeviceContext()->VSSetShaderResources(slot, 1, &m_ShaderResView);
	Context::Get().GetDeviceContext()->PSSetShaderResources(slot, 1, &m_ShaderResView);
}

void Texture2D::Unbind()
{
	
}
