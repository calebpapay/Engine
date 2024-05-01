//2024. Caleb Papay

#ifndef ANIM_INSTANCE_MAN_H
#define ANIM_INSTANCE_MAN_H 

#include "ManBase.h"
#include "AnimController.h"
#include "DLinkMan.h"

namespace Azul
{
	class AnimInstanceMan : public ManBase
	{
		
		// Static Methods
		
	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();

		//static void Reverse();
		static void Update();

		//static AnimController *LoadAnim(Anim::Name name, AnimPod::Name pod, AnimPod::ModelName model, AnimPod::ClipName clip, TextureObject::Name tex, Vec3 *startPos);
		static AnimController *Add(AnimController::Name _name, Anim::Name animName, GameObjectAnimSkin* gObj);
		static AnimController *Find(AnimController::Name name);
		static void Remove(AnimController *pNode);
		static void Dump();

		//static void SetClip(AnimController::Name name, Clip *clipName);

		
		// Private methods
		
	private:
		static AnimInstanceMan *privGetInstance();

		AnimInstanceMan() = delete;
		AnimInstanceMan(const AnimInstanceMan &) = delete;
		AnimInstanceMan &operator = (const AnimInstanceMan &) = delete;

		~AnimInstanceMan();

		AnimInstanceMan(int reserveNum, int reserveGrow);

		
		// Override Abstract methods
		
	protected:
		DLink *derivedCreateNode() override;

		
		// Data: unique data for this manager 
		
	private:
		AnimController *poNodeCompare;
		static AnimInstanceMan *posInstance;

	};
}

#endif

// --- End of File ---
