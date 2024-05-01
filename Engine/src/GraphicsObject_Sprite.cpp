//2024. Caleb Papay

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_Sprite.h"
#include "CameraMan.h"
#include "GameMan.h"
#include "MeshNodeMan.h"
#include "ImageMan.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_Sprite::GraphicsObject_Sprite(Image *_pImage, Rect rect)
		: GraphicsObject(MeshNodeMan::Find(Mesh::Name::SPRITE) , ShaderObject::Name::Sprite)
	{
		this->color.Set(1.0f, 1.0f, 1.0f, 1.0f);
		// w1(7)
		assert(_pImage);
		this->pImage = _pImage;

		this->origWidth = rect.width;
		this->origHeight = rect.height;

		this->origPosX = rect.x;
		this->origPosY = rect.y;

		// Create the UV matrix
		this->poMatrix_uv = new Mat4();

		float w = pImage->imageRect.width / (float)pImage->pText->width;
		float h = pImage->imageRect.height / (float)pImage->pText->height;
		float u = pImage->imageRect.x / (float)pImage->pText->width;
		float v = pImage->imageRect.y / (float)pImage->pText->height;
		Scale ScaleUV(w, h, 1.0f);
		Trans TransUV(u, v, 0.0f);
		*this->poMatrix_uv = ScaleUV *TransUV;

		// Create the orig Matrix 
		// The initial sprite setup, after this point standard world will adjust
		this->poMatrix_orig = new Mat4();

		Scale Scale(this->origWidth, this->origHeight, 1.0f);
		*this->poMatrix_orig = Scale ;
	}

	GraphicsObject_Sprite::GraphicsObject_Sprite(Image::Name _pImage, Rect rect)
		: GraphicsObject(MeshNodeMan::Find(Mesh::Name::SPRITE), ShaderObject::Name::Sprite)
	{
		this->color.Set(1.0f, 1.0f, 1.0f, 1.0f);
		// w1(7)
		
		this->origWidth = rect.width;
		this->origHeight = rect.height;

		this->origPosX = rect.x;
		this->origPosY = rect.y;

		// Create the UV matrix
		this->poMatrix_uv = new Mat4();

		this->SetImage(_pImage);
		assert(pImage);

		// Create the orig Matrix 
		// The initial sprite setup, after this point standard world will adjust
		this->poMatrix_orig = new Mat4();

		Scale Scale(this->origWidth, this->origHeight, 1.0f);
		*this->poMatrix_orig = Scale;
	}

	// w1(7)
	GraphicsObject_Sprite::~GraphicsObject_Sprite()
	{
		delete this->poMatrix_uv;
		delete this->poMatrix_orig;
		//this->pImage = nullptr;
		//delete this->pImage;
	}

	void GraphicsObject_Sprite::SetScreenRect(Rect &rect)
	{
		this->origWidth = rect.width;
		this->origHeight = rect.height;

		this->origPosX = rect.x;
		this->origPosY = rect.y;

		Scale Scale(this->origWidth, this->origHeight, 1.0f);
		*this->poMatrix_orig = Scale;
	}

	void GraphicsObject_Sprite::SetImage(Rect &imageRect, TextureObject *pText)
	{
		assert(pText);

		float w = imageRect.width / (float)pText->width;
		float h = imageRect.height / (float)pText->height;
		float u = imageRect.x / (float)pText->width;
		float v = imageRect.y / (float)pText->height;
		Scale ScaleUV(w, h, 1.0f);
		Trans TransUV(u, v, 0.0f);
		*this->poMatrix_uv = ScaleUV * TransUV;
	}

	void GraphicsObject_Sprite::SetImage(Image::Name imageName)
	{
		this->pImage = ImageMan::Find(imageName);
		assert(pImage);

		float w = pImage->imageRect.width / (float)pImage->pText->width;
		float h = pImage->imageRect.height / (float)pImage->pText->height;
		float u = pImage->imageRect.x / (float)pImage->pText->width;
		float v = pImage->imageRect.y / (float)pImage->pText->height;
		Scale ScaleUV(w, h, 1.0f);
		Trans TransUV(u, v, 0.0f);
		*this->poMatrix_uv = ScaleUV * TransUV;
	}


	void GraphicsObject_Sprite::SetState()
	{
		//  settings to directX
		// enable alpha blending
		this->pImage->pText->ActivateTexture();

		if(this->pImage->pText->HasAlpha())
		{
			Game *pGame = GameMan::GetGame();
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			UINT sampleMask = 0xffffffff;
			pGame->g_d3dDeviceContext->OMSetBlendState(pGame->g_d3eBlendStateAlpha, blendFactor, sampleMask);

		}
	}

	void GraphicsObject_Sprite::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		//Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		assert(pCam);
		// World matrix ----------------------------
		Trans TransToOriginLowerLeft((float)-pCam->getScreenWidth() / 2.0f, (float)-pCam->getScreenHeight() / 2.0f, 0.0f);
		Mat4 tmpMatrix = *this->poMatrix_orig * this->GetWorld() * TransToOriginLowerLeft;

		pMesh->TransferConstantBufferWorldViewProj(pCam, &tmpMatrix);

		pMesh->TransferUVCorrection(this->poMatrix_uv);

		pMesh->TransferColor((Vec4 *)&(color.red));
	}

	void GraphicsObject_Sprite::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_Sprite::RestoreState()
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
