//2024. Caleb Papay

#ifndef GRAPHICS_OBJECT_SKIN_LIGHT_TEXTURE_H
#define GRAPHICS_OBJECT_SKIN_LIGHT_TEXTURE_H

#include "GraphicsObject.h"
#include "TextureObject.h"
#include "Mixer.h"
#include "WorldCompute.h"

namespace Azul
{
	class GraphicsObject_SkinLightTexture :public GraphicsObject
	{
	public:
		GraphicsObject_SkinLightTexture(Mesh::Name meshName,
									   ShaderObject::Name shaderName,
									   TextureObject::Name textName,
									   Mixer *pMixer,
									   WorldCompute *pWorldCompute, Vec3 &LightColor,
										Vec3 &LightPos);

		GraphicsObject_SkinLightTexture() = delete;
		GraphicsObject_SkinLightTexture(const GraphicsObject_SkinLightTexture &) = delete;
		GraphicsObject_SkinLightTexture &operator = (const GraphicsObject_SkinLightTexture &) = delete;
		virtual ~GraphicsObject_SkinLightTexture();

		// Render material contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// ---------------------------------------------
		// Data
		// ---------------------------------------------
		TextureObject *pTex;

		// Compute Data
		Mixer *pMixer;
		WorldCompute *pWorldCompute;

		Vec3 *poLightColor;
		Vec3 *poLightPos;
	};
}

#endif


// --- End of File ---
