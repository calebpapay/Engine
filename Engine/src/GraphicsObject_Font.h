//2024. Caleb Papay
#ifndef GRAPHICS_OBJECT_Font_H
#define GRAPHICS_OBJECT_Font_H

#include "GraphicsObject.h"
#include "Image.h"
#include "Rect.h"
#include "Glyph.h"

namespace Azul
{

	class GraphicsObject_Font :public GraphicsObject
	{
	public:
		GraphicsObject_Font( Image *_pImage, Rect rect);

		GraphicsObject_Font() = delete;
		GraphicsObject_Font(const GraphicsObject_Font &) = delete;
		GraphicsObject_Font &operator = (const GraphicsObject_Font &) = delete;
		virtual ~GraphicsObject_Font();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// data:  place uniform instancing here
		void SwapChar(Glyph *glyph);
		//TextureObject *pTex; texture now contained in image


		Image *pImage;
		Mat4 *poMatrix_uv;
		Mat4 *poMatrix_orig;

		float origWidth;
		float origHeight;

		float origPosX;
		float origPosY;

	};
}

#endif


// --- End of File ---
