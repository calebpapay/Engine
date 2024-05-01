//2024. Caleb Papay

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_LightTexture.h"
#include "DirectXDeviceMan.h"
#include "CameraMan.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_LightTexture::GraphicsObject_LightTexture(Mesh *mesh,
															 TextureObject *_pTex,
															 Vec3 &LightColor,
															 Vec3 &LightPos)
		: GraphicsObject(mesh, ShaderObject::Name::LightTexture),
		pTex(_pTex),
		poLightColor(nullptr),
		poLightPos(nullptr)
	{
		assert(pTex);

		poLightColor = new Vec3(LightColor);
		poLightPos = new Vec3(LightPos);

		assert(poLightColor);
		assert(poLightPos);
	}

	GraphicsObject_LightTexture::~GraphicsObject_LightTexture()
	{
		delete poLightColor;
		delete poLightPos;
	}

	void GraphicsObject_LightTexture::SetState()
	{
		// Future - settings to directX
		// say make it wireframe or change culling mode
		this->pTex->ActivateTexture();
	}

	void GraphicsObject_LightTexture::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		Vec4 pos;// = this->poWorld->get(Row4::i3);
		//Vec3 objectPosition;
		pos[x] = poWorld->m12(); // or worldMatrix.m3() if using 0-based indexing
		pos[y] = poWorld->m13(); // or worldMatrix.m7() if using 0-based indexing
		pos[z] = poWorld->m14();
		pos[w] = 1.0f;
		//Vec4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		Vec3 test;
		pCam->GetScreenXY(test, &pos);
		assert(pCam);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);

		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightColor, 0, nullptr, poLightColor, 0, 0);
		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightPos, 0, nullptr, poLightPos, 0, 0);
	}

	void GraphicsObject_LightTexture::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_LightTexture::RestoreState()
	{
		// Future - Undo settings to directX
	}

}

// --- End of File ---
