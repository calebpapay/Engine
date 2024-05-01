
//2024. Caleb Papay


#ifndef SHADER_OBJECT_SKIN_LIGHT_TEXTURE_H
#define SHADER_OBJECT_SKIN_LIGHT_TEXTURE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_SkinLightTexture : public ShaderObject
	{
	public:

	public:
		ShaderObject_SkinLightTexture() = delete;
		ShaderObject_SkinLightTexture(const ShaderObject_SkinLightTexture &) = delete;
		ShaderObject_SkinLightTexture &operator = (const ShaderObject_SkinLightTexture &) = delete;
		virtual ~ShaderObject_SkinLightTexture();

		ShaderObject_SkinLightTexture(ShaderObject_SkinLightTexture::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
