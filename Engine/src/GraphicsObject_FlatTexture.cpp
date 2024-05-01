//2024. Caleb Papay

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_FlatTexture.h"
#include "CameraMan.h"
#include "GameMan.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_FlatTexture::GraphicsObject_FlatTexture(Mesh *mesh,
														   TextureObject *_pTex)
		: GraphicsObject(mesh, ShaderObject::Name::FlatTexture),
		pTex(_pTex)
	{
		assert(pTex);
	}

	void GraphicsObject_FlatTexture::SetState()
	{
		//  settings to directX
		// enable alpha blending
		this->pTex->ActivateTexture();

		if(this->pTex->HasAlpha())
		{
			Game *pGame = GameMan::GetGame();
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			UINT sampleMask = 0xffffffff;
			pGame->g_d3dDeviceContext->OMSetBlendState(pGame->g_d3eBlendStateAlpha, blendFactor, sampleMask);

		}
	}

	void GraphicsObject_FlatTexture::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		assert(pCam);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);
	}

	void GraphicsObject_FlatTexture::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_FlatTexture::RestoreState()
	{
		//  settings to directX
		// disable alpha blending
		Game *pGame = GameMan::GetGame();
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		UINT sampleMask = 0xffffffff;
		pGame->g_d3dDeviceContext->OMSetBlendState(pGame->g_d3eBlendStateOff, blendFactor, sampleMask);
	}

}

// --- End of File ---
