//2024. Caleb Papay

#ifndef STRING_THIS_H
#define STRING_THIS_H

#include "Mesh.h"
#include "ShaderObject.h"
#include "TextureObject.h"
//
#include "Anim.h"

namespace Azul
{
	class StringThis
	{
	public:
		static const unsigned int BUFFER_SIZE = 64;
	public:

		StringThis(Mesh::Name);
		StringThis(ShaderObject::Name);
		StringThis(TextureObject::Name);
		StringThis(Camera::Name);
		StringThis(Anim::Name);
		//StringThis(AnimPod::Name);


		operator char *();

		// data:
		char buffer[BUFFER_SIZE];
	};

#define StringMe(x)  ((char *)StringThis(x)) 
}

#endif

// --- End of File ---