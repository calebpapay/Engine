//2024. Caleb Papay

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_SkinLightTexture.h"
#include "CameraMan.h"
#include "GameMan.h"
#include "TexNodeMan.h"
#include "DirectXDeviceMan.h"
#include "ComputeRSVBuffer.h"
#include "ShaderMappings.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_SkinLightTexture::GraphicsObject_SkinLightTexture(Mesh::Name meshName,
																   ShaderObject::Name shaderName,
																   TextureObject::Name textName,
																   Mixer *_pMixer,
																   WorldCompute *_pWorldCompute, Vec3 &LightColor,
																	 Vec3 &LightPos)
		: GraphicsObject(meshName, shaderName),
		pTex{ nullptr },
		pMixer{ _pMixer },
		pWorldCompute{ _pWorldCompute }
	{
		poLightColor = new Vec3(LightColor);
		poLightPos = new Vec3(LightPos);


		this->pTex = TexNodeMan::Find(textName);
		assert(pTex);
		assert(pMixer);
		assert(pWorldCompute);
	}		//delete poLightColor;
		//delete poLightPos;
	GraphicsObject_SkinLightTexture::~GraphicsObject_SkinLightTexture()
	{
		// Future - settings to directX
		// say make it wireframe or change culling mode
		delete poLightColor;
		delete poLightPos;
	}
	void GraphicsObject_SkinLightTexture::SetState()
	{
		// Future - settings to directX
		// say make it wireframe or change culling mode
		this->pTex->ActivateTexture();
	}

	void GraphicsObject_SkinLightTexture::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);


		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightColor, 0, nullptr, poLightColor, 0, 0);
		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightPos, 0, nullptr, poLightPos, 0, 0);

		// Set the BoneWorld to Vertex shader
		assert(pWorldCompute->poVsBoneWorld);
		pWorldCompute->poVsBoneWorld->BindVertex(ShaderResourceBufferSlot::BoneWorldIn);
	}

	void GraphicsObject_SkinLightTexture::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_SkinLightTexture::RestoreState()
	{
		Game *pGame = GameMan::GetGame();
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		UINT sampleMask = 0xffffffff;
		pGame->g_d3dDeviceContext->OMSetBlendState(pGame->g_d3eBlendStateOff, blendFactor, sampleMask);
	}

}

// --- End of File ---
