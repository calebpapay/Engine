
//2024. Caleb Papay


#ifndef TEXTURE_OBJECT_H
#define TEXTURE_OBJECT_H

#include <d3d11.h>

#include "DirectXTex.h"

namespace Azul
{
	class TextureObject
	{
	public:
		enum class Name
		{
			NullTexture,
			SARDAUKAR,
			Duckweed,
			Brick,
			Stone,
			Rocks,
			Crate,
			Frigate,
			R2,
			ChickenBot,
			RatThing,
			Stitch,
			Test0,
			Test1,
			Test2,
			Test3,
			FontAriel36,
			FontConsolas15,
			Font2,
			Uninitialized
		};


	public:
		TextureObject();
		TextureObject(const TextureObject &) = delete;
		TextureObject &operator = (const TextureObject &) = delete;
		virtual ~TextureObject();

		TextureObject(LPCWSTR filepath,
					  D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR);

		void ActivateTexture();


		bool HasAlpha() const;

		char *GetName();
		void SetName(TextureObject::Name _name);

	protected:


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------
	public:
		TextureObject::Name name;

		unsigned int    width;
		unsigned int    height;

		int TexResourceSlot;
		int SamplerSlot;

		ID3D11ShaderResourceView *poTextureRV;
		ID3D11SamplerState *poSampler;

		bool AlphaEnabled;
	};
}

#endif

// --- End of File ---
