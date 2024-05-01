//2024. Caleb Papay

#include "GraphicsObject_Null.h"

namespace Azul
{

	GraphicsObject_Null::GraphicsObject_Null(Mesh *pMesh)
		: GraphicsObject(pMesh, ShaderObject::Name::NullShader)
	{

	}

	GraphicsObject_Null::GraphicsObject_Null(Mesh::Name meshName)
		: GraphicsObject(meshName, ShaderObject::Name::NullShader)
	{

	}

	void GraphicsObject_Null::SetState()
	{

	}

	void GraphicsObject_Null::SetDataGPU()
	{

	}

	void GraphicsObject_Null::Draw()
	{

	}

	void GraphicsObject_Null::RestoreState()
	{

	}
}

// ---  End of File ---
