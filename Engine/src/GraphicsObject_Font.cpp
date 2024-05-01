//2024. Caleb Papay

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_Font.h"
#include "CameraMan.h"
#include "GameMan.h"
#include "MeshNodeMan.h"
#include "GlyphMan.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_Font::GraphicsObject_Font(Image *_pImage, Rect rect)
		: GraphicsObject(MeshNodeMan::Find(Mesh::Name::SPRITE), ShaderObject::Name::Sprite)
	{
		AZUL_UNUSED_VAR(rect);
		// w1(7)
		assert(_pImage);
		this->pImage = _pImage;
		this->poMatrix_uv = new Mat4();
		this->poMatrix_orig = new Mat4();

		Scale Scale(this->origWidth, this->origHeight, 1.0f);
		*this->poMatrix_orig = Scale;
	}

	void GraphicsObject_Font::SwapChar(Glyph* currGlyph)
	{

		pImage->Swap(currGlyph->pText, currGlyph->glyphRect);
		Rect rect(0.0f, 0.0f, currGlyph->glyphRect.width, currGlyph->glyphRect.height);

		this->origWidth = rect.width;
		this->origHeight = rect.height;

		this->origPosX = rect.x;
		this->origPosY = rect.y;

		// Create the UV matrix
		
		assert(this->poMatrix_uv);

		float w = pImage->imageRect.width / (float)pImage->pText->width;
		float h = pImage->imageRect.height / (float)pImage->pText->height;
		float u = pImage->imageRect.x / (float)pImage->pText->width;
		float v = pImage->imageRect.y / (float)pImage->pText->height;
		Scale ScaleUV(w, h, 1.0f);
		Trans TransUV(u, v, 0.0f);
		*this->poMatrix_uv = ScaleUV * TransUV;

		// Create the orig Matrix 
		// The initial Font setup, after this point standard world will adjust
		assert(this->poMatrix_orig);// = new Mat4();

		Scale Scale(this->origWidth, this->origHeight, 1.0f);
		*this->poMatrix_orig = Scale;
	}

	// w1(7)
	GraphicsObject_Font::~GraphicsObject_Font()
	{
		delete this->poMatrix_uv;
		delete this->poMatrix_orig;
		delete this->pImage;
	}


	void GraphicsObject_Font::SetState()
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

	void GraphicsObject_Font::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		assert(pCam);

		// World matrix ----------------------------
		Trans TransToOriginLowerLeft((float)-pCam->getScreenWidth() / 2.0f, (float)-pCam->getScreenHeight() / 2.0f, 0.0f);
		Mat4 tmpMatrix = *this->poMatrix_orig * this->GetWorld() * TransToOriginLowerLeft;

		pMesh->TransferConstantBufferWorldViewProj(pCam, &tmpMatrix);
		pMesh->TransferUVCorrection(this->poMatrix_uv);
	}

	void GraphicsObject_Font::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_Font::RestoreState()
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
