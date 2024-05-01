//
//#include "Skeleton.h"
//#include "GraphicsObject_LightTexture.h"
//#include "GraphicsObject_SkinFlatTexture.h"
//#include "GameObjectBasic.h"
//#include "GameObjectMan.h"
//#include "GraphicsObject_Null.h"
//#include "MeshNodeMan.h"
//#include "GameObjectAnimSkeleton.h"
//#include "GameObjectAnimSkin.h"
//#include "TexNodeMan.h"
//#include "PCSTreeForwardIterator.h"
//#include "SkelMan.h"
//
//
//namespace Azul
//{
//
//
//	Skeleton::Skeleton()
//		: pFirstBone(nullptr),
//		pPivot(nullptr),
//		numBones(0)
//	{
//		
//	}
//
//	void Skeleton::Set(Skel::Name skelName, Mesh::Name meshName, TextureObject::Name tex, Bone *pBoneResult)
//	{
//		assert(pFirstBone == nullptr);
//		assert(pPivot == nullptr);
//		assert(numBones == 0);
//		this->privSetAnimationSkeleton(skelName, meshName, tex, pBoneResult);
//		assert(pFirstBone);
//		assert(pPivot);
//		assert(numBones > 0);
//	}
//
//	Skeleton::~Skeleton()
//	{
//	}
//
//	int Skeleton::GetNumBones() const
//	{
//		return this->numBones;
//	}
//
//
//	GameObjectAnim *Skeleton::GetFirstBone()
//	{
//		assert(pFirstBone);
//		return this->pFirstBone;
//	}
//	GameObjectBasic *Skeleton::GetPivot()
//	{
//		assert(pPivot);
//		return this->pPivot;
//	}
//	GameObjectAnim *Skeleton::FindBoneByIndex(int index)
//	{
//		return privFindBoneByIndex(index);
//	}
//
//	GameObjectAnim *Skeleton::privFindBoneByIndex(int index)
//	{
//		GameObjectAnim *pFound = nullptr;
//
//		GameObjectAnim *pObj = this->GetFirstBone();
//
//		// TODO - add test bed for an interator of a tree with only one node
//		if(pObj->index == index)
//		{
//			pFound = pObj;
//		}
//		else
//		{
//			PCSTreeForwardIterator pIter(pObj);
//			PCSNode *pNode = pIter.First();
//			GameObjectAnim *pGameObj = nullptr;
//
//			// walks the anim node does the pose for everything that
//			while(pNode != nullptr)
//			{
//				assert(pNode);
//				// Update the game object
//				pGameObj = (GameObjectAnim *)pNode;
//				if(pGameObj->index == index)
//				{
//					pFound = pGameObj;
//					break;
//				}
//				pNode = pIter.Next();
//			}
//		}
//
//		return pFound;
//	}
//
//
//
//
//	void Skeleton::privSetAnimationSkeleton(Skel::Name skelName, Mesh::Name meshName, TextureObject::Name tex, Bone *pBoneResult)
//	{
//		//assert(pBoneResult);
//		//Skel *pSkel = SkelMan::Find(skelName);
//		//assert(pSkel);
//
//		//numBones = pSkel->numBones;
//		//assert(pSkel);
//
//		AZUL_UNUSED_VAR(skelName);
//		AZUL_UNUSED_VAR(meshName);
//		AZUL_UNUSED_VAR(tex);
//		AZUL_UNUSED_VAR(pBoneResult);
//
//
//		//// GraphicsObject for a specific instance
//		//GraphicsObject *pGraphicsObj;
//
//		//// Create GameObject
//		//Vec3 color(1, 1, 1);
//		//Vec3 pos(1, 1, 1);
//
//		////---------------------------------------
//		//// ChickenBot
//		////---------------------------------------
//
//		//// Add A Dummy pivot object
//		//pGraphicsObj = new GraphicsObject_Null(Mesh::Name::NULL_MESH);
//		//pPivot = new GameObjectBasic(pGraphicsObj);
//		//pPivot->SetName("Pivot");
//		//pPivot->DrawDisable();
//
//		//// Add Bones in Skeleton
//		//GameObjectMan::Add(pPivot, GameObjectMan::GetRoot());
//
//		//// Animation
//		//GameObjectAnim *pGameObj;
//
//		//// Skin Mesh
//		//GameObjectAnimSkin *pGameSkin;
//		//GraphicsObject_SkinFlatTexture *pGraphicsSkin;
//
//		//pGraphicsSkin = new GraphicsObject_SkinFlatTexture(meshName,
//		//												   tex);
//		//pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, this);
//
//		//// Glue the bone array together - Hack
//		//pGraphicsSkin->SetBoneWorld(pGameSkin->poBoneWorld);
//
//		//GameObjectMan::Add(pGameSkin, pPivot);
//		//pGameSkin->SetName("ChickenSkin");
//
//
//		//// Root animation is treated differently
//		//for(int i = 0; i < 1; i++)
//		//{
//
//		//	pGraphicsObj = new GraphicsObject_Null(Mesh::Name::NULL_MESH);
//		//	pGameObj = new GameObjectAnimSkeleton(pGraphicsObj, pBoneResult);
//		//	pGameObj->SetIndex(pSkel->poTableArray[i].index);
//		//	pGameObj->SetName(pSkel->poTableArray[i].name);
//
//		//	GameObjectMan::Add(pGameObj, pPivot);
//		//	this->pFirstBone = pGameObj;
//		//}
//
//		//for(int i = 1; i < numBones; i++)
//		//{
//		//	//pGraphicsObj = new GraphicsObject_SkinFlatTexture(Mesh::Name::ChickenBot,
//		//	//												  ShaderObject::Name::FlatTexture,
//		//	//												  TextureObject::Name::ChickenBot);
//		//	//pGameObj = new GameObjectAnimSkin(pGraphicsObj, pBoneResult);
//
//		//	pGraphicsObj = new GraphicsObject_Null(Mesh::Name::NULL_MESH);
//		//	pGameObj = new GameObjectAnimSkeleton(pGraphicsObj, pBoneResult);
//		//	pGameObj->SetIndex(pSkel->poTableArray[i].index);
//		//	pGameObj->SetName(pSkel->poTableArray[i].name);
//
//		//	GameObjectAnim *pParent = this->privFindBoneByIndex(pSkel->poTableArray[i].parentIndex);
//		//	if(!pParent)
//		//	{
//		//		assert(pParent);
//		//	}
//		//	GameObjectMan::Add(pGameObj, pParent);
//		//}
//
//
//	}
//}
//
//// --- End of File ---