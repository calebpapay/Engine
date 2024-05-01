//2024. Caleb Papay

#ifndef MESH_NULL_H
#define MESH_NULL_H
	
#include "Mesh.h"

namespace Azul
{
	class MeshNull : public Mesh
	{
	public:
		MeshNull();
		MeshNull(const MeshNull &) = delete;
		MeshNull &operator=(const MeshNull &other) = delete;
		virtual ~MeshNull();


	private:

	};
}

#endif

// --- End of File ---
