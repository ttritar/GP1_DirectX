
//includes
#include "Texture.h"

namespace dae {

	Texture::Texture(ID3D11Device* pDevice,  SDL_Surface* pSurface)
	{

		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
		D3D11_TEXTURE2D_DESC desc{};
		desc.Width = pSurface->w;
		desc.Height = pSurface->h;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = pSurface->pixels;
		initData.SysMemPitch = static_cast<UINT>(pSurface->pitch);
		initData.SysMemSlicePitch = static_cast<UINT>(pSurface->h * pSurface->pitch);

		HRESULT hr = pDevice->CreateTexture2D(&desc, &initData, &m_pResource);
		if (FAILED(hr) || m_pResource == nullptr) // Check for failure or null resource
		{
			std::cerr << "Failed to create texture2D. HRESULT: " << hr << std::endl;
			SDL_FreeSurface(pSurface); // Free the SDL_Surface since the constructor failed
			pSurface = nullptr;
			return; // Early return on failure
		}


		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc{};
		SRVDesc.Format = format;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = 1;

		hr = pDevice->CreateShaderResourceView(m_pResource, &SRVDesc, &m_pSRV);
		if (FAILED(hr) || m_pSRV == nullptr) // Check for failure or null SRV
		{
			std::cerr << "Failed to create shader resource view. HRESULT: " << hr << std::endl;
			m_pResource->Release(); // Clean up the texture resource if the SRV creation fails
			m_pResource = nullptr;

			SDL_FreeSurface(pSurface);
			pSurface = nullptr;
			return; // Early return on failure
		}

		SDL_FreeSurface(pSurface);
		pSurface = nullptr;
	}

	Texture::~Texture()
	{
		if (m_pSRV)
			m_pSRV->Release();

		if (m_pResource)
			m_pResource->Release();
	}




	Texture* Texture::LoadFromFile(const std::string& path, ID3D11Device* pDevice)
	{
		//Load SDL_Surface using IMG_LOAD
		auto SDL_Surf = IMG_Load(path.c_str());
		Texture* pTex = new Texture( pDevice, SDL_Surf );

		return pTex;
	}


	ID3D11ShaderResourceView* Texture::GetSRV()
	{
		return m_pSRV;
	}
}