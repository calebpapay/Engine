////----------------------------------------------------------------------------
//// Copyright 2023, Ed Keenan, all rights reserved.
////----------------------------------------------------------------------------
//#include "MultiMesh.h"
//#include "MeshNodeMan.h"
//#include "multiMeshData.h"
//#include "File.h"
//
//namespace Azul
//{
//
//	MultiMesh::MultiMesh(const char *fileName, Mesh::Name multiMeshName)
//		: multiMesh(nullptr),
//		numMeshes(0)
//	{
//		File::Handle fh;
//		File::Error  ferror;
//
//		ferror = File::Open(fh, fileName, File::Mode::READ);
//		assert(ferror == File::Error::SUCCESS);
//
//		// Get the size
//		ferror = File::Seek(fh, File::Position::END, 0);
//		assert(ferror == File::Error::SUCCESS);
//
//		DWORD length;
//		ferror = File::Tell(fh, length);
//		assert(ferror == File::Error::SUCCESS);
//
//		ferror = File::Seek(fh, File::Position::BEGIN, 0);
//		assert(ferror == File::Error::SUCCESS);
//
//		char *poBuff = new char[length];
//		assert(poBuff);
//
//		ferror = File::Read(fh, poBuff, length);
//		assert(ferror == File::Error::SUCCESS);
//
//		ferror = File::Close(fh);
//		assert(ferror == File::Error::SUCCESS);
//
//		// Now the raw data is poBUff
//		// deserialize the data --> mB
//		std::string strIn(poBuff, length);
//		multiMeshData_proto sB_proto;
//
//		sB_proto.ParseFromString(strIn);
//
//		multiMeshData sB;
//		sB.Deserialize(sB_proto);
//		delete[] poBuff;
//
//		numMeshes = sB.numMeshes;
//
//		multiMesh = new MultiMesh::Data[numMeshes]();
//		// Now the model is sB...
//		// move it into the Mesh
//		for(int i = 0; i < numMeshes; i++)
//		{
//			//Get the i'th meshData from the BoneMesh Array
//			meshData mb = sB.meshMap[i].mD;
//
//			//assert(strcmp(mB.pVersion, "1.0.2") == 0);
//			multiMesh[i].mesh = new MeshProto(&mb);
//			multiMesh[i].mappedToBone = i + 4;
//			MeshNodeMan::Add(multiMeshName, multiMesh[i].mesh); //hardcoded
//			memcpy_s(this->multiMesh[i].name, meshData::FILE_NAME_SIZE, multiMesh[i].mesh->GetName(), meshData::FILE_NAME_SIZE);
//		}
//		delete[] sB.meshMap;
//	}
//
//
//
//
//	MultiMesh::~MultiMesh()
//	{
//		delete[] multiMesh;
//
//	}
//
//	MultiMesh::Data *MultiMesh::GetMeshArray()
//	{
//		assert(multiMesh[0].mesh);
//		return this->multiMesh;
//	}
//	
//	int MultiMesh::GetBoneForMesh(int meshIndex)
//	{
//		return this->multiMesh[meshIndex].mappedToBone;
//	}
//
//
//	Mesh *MultiMesh::GetMeshForBone(int boneIndex)
//	{
//		for(int i = 0; i < numMeshes; i++)
//		{
//			if(this->multiMesh[i].mappedToBone == boneIndex)
//			{
//				return this->multiMesh[i].mesh;
//			}
//			//Get the i'th meshData from the BoneMesh Array
//		
//		}
//		return nullptr;
//	}
//
//
//}
//// --- End of File ---