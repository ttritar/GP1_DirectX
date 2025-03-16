#pragma once

//includes
#include "math.h"
#include "Effect.h"
#include "EffectPartialCoverage.h"
#include "EffectDefault.h"
#include <cassert>

namespace dae {

	struct Vertex
	{
		Vector3 position{};
		//Vector3 worldPosition{};
		Vector2 uv{};
		Vector3 normal{}; 
		Vector3 tangent{};
		//Vector3 viewDirection{}; 
	};

	struct Vertex_In
	{
		Vector3 position{};
		Vector2 uv{};
		Vector3 normal{};
		Vector3 tangent{};
		//Vector3 viewDirection{};
	};

	class Mesh 
	{
	public:
		Mesh( ID3D11Device* pDevice, const std::vector<Vertex_In>& vertices, const std::vector<uint32_t>& indices,  bool isPartialCoverage );
		~Mesh();

		Mesh(const Mesh&) = delete;
		Mesh(Mesh&&) noexcept = delete;
		Mesh& operator=(const Mesh&) = delete;
		Mesh& operator=(Mesh&&) noexcept = delete;

		virtual void Render(ID3D11DeviceContext* pDeviceContext, const Matrix& worldMatrix, const Matrix& worldViewProjectionMatrix, const Vector3& cameraPos, const FilteringMethod& filteringMethod);
		
	private:
		const bool m_IsPartialCoverage;

		Effect* m_pEffect = nullptr;
		ID3DX11EffectTechnique* m_pTechnique = nullptr;
		FilteringMethod m_FilteringMethod{}; 

		ID3D11InputLayout* m_pInputLayout = nullptr;
		ID3D11Buffer* m_pVertexBuffer = nullptr;
		ID3D11Buffer* m_pIndexBuffer = nullptr;

		uint32_t m_NumIndices{};

		Texture* m_pDiffuseTexture;
		Texture* m_pNormalTexture;
		Texture* m_pSpecularTexture;
		Texture* m_pGlossinessTexture;
	};
}