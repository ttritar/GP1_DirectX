#pragma once
#include "Mesh.h"
#include "Camera.h"

struct SDL_Window;
struct SDL_Surface;

namespace dae
{
	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Update(const Timer* pTimer);
		void Render() const;

		void SwitchFilterMode()
		{
			switch (m_FilteringMethod)
			{
			case dae::FilteringMethod::Point:
				m_FilteringMethod = FilteringMethod::Linear;
				break;
			case dae::FilteringMethod::Linear:
				m_FilteringMethod = FilteringMethod::Anisotropic;
				break;
			case dae::FilteringMethod::Anisotropic:
				m_FilteringMethod = FilteringMethod::Point;
				break;
			default:
				m_FilteringMethod = FilteringMethod::Point;
				break;
			}
		};
		void ToggleRotation() { m_Rotating = !m_Rotating; };

	private:
		SDL_Window* m_pWindow{};

		int m_Width{};
		int m_Height{};

		bool m_IsInitialized{ false };

		FilteringMethod m_FilteringMethod{}; // 0 = point, 1 = linear, 2 = antisotrophic
		Mesh* m_pMeshVehicle;
		Mesh* m_pMeshFire;

		Matrix m_WorldMatrix{ {1,0,0,0},{0,1,0,0},{0,0,1,0} ,{0,0,0,1} };
		bool m_Rotating{};
		float m_Rotation{};

		Camera m_Camera{};
	


		//DIRECTX
		//======
		HRESULT InitializeDirectX();

		//Device & DeviceContent
		ID3D11Device* m_pDevice = nullptr;
		ID3D11DeviceContext* m_pDeviceContext = nullptr;

		//SwapChain
		IDXGISwapChain* m_pSwapChain = nullptr;
		
		//DepthStencil (DS) & DepthStencilView (DSV)
		ID3D11Texture2D* m_pDepthStencilBuffer = nullptr;
		ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

		//RenderTarget (RT) & RenderTargetView (RTV)
		ID3D11Resource* m_pRenderTargetBuffer = nullptr;
		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

			
	};
}
