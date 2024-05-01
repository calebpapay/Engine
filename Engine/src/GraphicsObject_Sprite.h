//2024. Caleb Papay

#ifndef GRAPHICS_OBJECT_SPRITE_H
#define GRAPHICS_OBJECT_SPRITE_H

#include "GraphicsObject.h"
#include "TextureObject.h"
#include "Image.h"
#include "Rect.h"
#include "Color.h"

namespace Azul
{

	class GraphicsObject_Sprite :public GraphicsObject
	{
	public:
		GraphicsObject_Sprite(Image *_pImage, Rect rect);
		GraphicsObject_Sprite(Image::Name imageName, Rect rect);

		GraphicsObject_Sprite() = delete;
		GraphicsObject_Sprite(const GraphicsObject_Sprite &) = delete;
		GraphicsObject_Sprite &operator = (const GraphicsObject_Sprite &) = delete;
		virtual ~GraphicsObject_Sprite();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		void SetImage(Image::Name image);
		//void SetTexture(TextureObject *pText);
		void SetImage(Rect &imageRect, TextureObject *pText);
		void SetScreenRect(Rect &rect);


		//TextureObject *pTex; texture now contained in image
		Image *pImage;
		Mat4 *poMatrix_uv;
		Mat4 *poMatrix_orig;
		Color color;

		float origWidth;
		float origHeight;

		float origPosX;
		float origPosY;

	};
}

#endif


// --- End of File ---
