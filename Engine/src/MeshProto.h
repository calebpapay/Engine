//2024. Caleb Papay

#ifndef MESH_PROTO_H
#define MESH_PROTO_H

#include "Mesh.h"
#include "meshData.h"

namespace Azul
{
	class MeshProto : public Mesh
	{
	public:
		// Data
		MeshProto(const char *const pMeshFileName);
		//MeshProto(meshData *mB);
		MeshProto() = delete;
		MeshProto(const MeshProto &) = delete;
		MeshProto &operator = (MeshProto &) = delete;
		virtual ~MeshProto();

	private:
		//	virtual void privCreateVAO(const char *const pMeshFileName) override;

	};
}

#endif

// --- End of File ---