////----------------------------------------------------------------------------
//// Copyright 2023, Ed Keenan, all rights reserved.
////----------------------------------------------------------------------------
//
//#ifndef ANIM_BASE_H
//#define ANIM_BASE_H
//
//#include "AnimTimer.h"
//#include "MathEngine.h"
//#include "GameObjectAnimSkin.h"
//#include "GameObjectAnimSkeleton.h"
//#include "Clip.h"
//#include "Hierarchy.h"
//#include "TextureObject.h"
//
//namespace Azul
//{
//
//
//	class AnimBase
//	{
//		
//
//	public:
//
//		enum class Name
//		{
//			WalkingBot,
//			BlastUpBot,
//			FallBot,
//			SideStepBot,
//			Anim0,
//			Anim1,
//			Anim2,
//			Anim3,
//			Anim4,
//			NULL_ANIM
//
//		};
//		
//		AnimBase()
//			:name(Anim::Name::NULL_ANIM)
//		{
//		};
//		AnimBase(const AnimBase &) = delete;
//		AnimBase &operator = (const AnimBase &) = delete;
//		virtual ~AnimBase()
//		{
//
//		}
//		virtual char *GetName() = 0;
//		virtual void SetName(Anim::Name _name) = 0;
//
//		virtual void Animate(AnimTime tCurr) = 0;
//		virtual AnimTime FindMaxTime() = 0;
//		virtual AnimTime FindDeltaTime() = 0;
//
//	//	//static void PoseSkeleton(GameObjectAnimSkeleton *node);
//	Anim::Name name;
//
//	protected:
//
//	/*	char *baseGetName()
//		{
//			static char pTmp[128];
//			strcpy_s(pTmp, 128, StringMe(this->name));
//			return pTmp;
//		}
//		void baseSetName(Anim::Name _name)
//		{
//			this->name = _name;
//		}*/
//
//	//private:
//	//	void  privBuildHeirarchy(MultiMesh *animatedMesh, TextureObject::Name tex, int _numBones, int *parentIndice, Vec3 *startPos);
//	};
//
//}
//
//#endif
//
//// --- End of File ---