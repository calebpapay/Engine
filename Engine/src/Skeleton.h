//#ifndef Skeleton_H
//#define Skeleton_H
//
//#include "GameObjectBasic.h"
//#include "GameObjectAnim.h"
//#include "Bone.h"
//#include "TextureObject.h"
//#include "Skel.h"
//#include "Mesh.h"
//
//namespace Azul
//{
//	class Skeleton
//	{
//
//	public:
//		//Skeleton(Skel::Name skelName, Mesh::Name meshName, TextureObject::Name tex, Bone *pBoneResult);
//		void Set(Skel::Name skelName, Mesh::Name meshName, TextureObject::Name tex, Bone *pBoneResult);
//
//		Skeleton();
//		Skeleton(const Skeleton &) = delete;
//		Skeleton &operator = (const Skeleton &) = delete;
//		~Skeleton();
//
//		int GetNumBones() const;
//
//		//void MoveToPosition(Vec3* pos);
//		GameObjectAnim *GetFirstBone();
//		GameObjectBasic *GetPivot();
//		GameObjectAnim *FindBoneByIndex(int index);
//
//	private:
//		void privSetAnimationSkeleton(Skel::Name skelName, Mesh::Name meshName, TextureObject::Name tex, Bone *pBone);
//		GameObjectAnim *privFindBoneByIndex(int index);
//
//	private:
//		GameObjectAnim *pFirstBone;
//		GameObjectBasic *pPivot;
//		int numBones;
//		//Bone *poBoneResult;
//		//int             numEntities;
//	};
//}
//
//#endif
//
//// --- End of File ---