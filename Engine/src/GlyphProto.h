//2024. Caleb Papay

#ifndef GLYPH_PROTO_H
#define GLYPH_PROTO_H

#include "TextureObject.h"
#include "Glyph.h"

namespace Azul
{
	class GlyphProto
	{
	public:
		// Data
		GlyphProto(const char *const pMeshFileName, Glyph::Name name, TextureObject::Name texName);

		GlyphProto() = delete;
		GlyphProto(const GlyphProto &) = delete;
		GlyphProto &operator = (GlyphProto &) = delete;
		 ~GlyphProto() = default;

	public:

	};
}

#endif

//--- End of File ---

