////----------------------------------------------------------------------------
//// Copyright 2023, Ed Keenan, all rights reserved.
////----------------------------------------------------------------------------
//
//#ifndef MultiMesh_H
//#define MultiMesh_H
//
//#include "MeshProto.h"
//
//namespace Azul
//{
//	class MultiMesh
//	{
//	public:
//		static const unsigned int FILE_NAME_SIZE = 64;
//
//		struct Data
//		{
//			Data()
//				:mappedToBone(0),
//				mesh(nullptr),
//				name()
//			{
//
//			}
//			~Data()
//			{
//				this->mesh = nullptr;
//			}
//			Mesh* GetFirstMesh()
//			{
//				assert(mesh);
//				return mesh;
//			}
//			MeshProto *mesh;
//			int mappedToBone;
//			char name[FILE_NAME_SIZE];
//		};
//
//	public:
//		MultiMesh(const char *multiMeshFile, Mesh::Name multiMeshName);
//	
//		MultiMesh() = delete;
//		MultiMesh(const MultiMesh &) = delete;
//		MultiMesh &operator = (const MultiMesh &) = delete;
//		~MultiMesh();
//
//
//		MultiMesh::Data *GetMeshArray();
//		Mesh *GetMeshForBone(int boneIndex);
//		int GetBoneForMesh(int meshIndex);
//
//	public:
//		int             numMeshes;
//		MultiMesh::Data *multiMesh;
//	};
//}
//
//#endif
//// --- End of File ---