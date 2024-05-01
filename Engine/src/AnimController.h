//2024. Caleb Papay

#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "TimerController.h"
#include "DLink.h"
#include "Anim.h"
#include "GameObjectAnimSkin.h"
//#include "Skeleton.h"
//#include "FontNode.h"

namespace Azul
{
	class AnimController : public DLink
	{
	public:
		enum class Name
		{
			Not_Initialized,
			ZERO,
			ONE,
			TWO,
			THREE,
			FOUR,
			FIVE,
			SIX,
			SEVEN
		};
	public:



		AnimController();
		AnimController(const AnimController &) = delete;
		AnimController &operator = (const AnimController &) = delete;
		~AnimController();

		void Set(AnimController::Name _name, Anim::Name animName, GameObjectAnimSkin *pGameObj);
	
		void ReverseDeltaTime();
		void Update();

		Anim *GetAnim();

		void Enable();
		void Disable();

		void SetScale(float x, float y, float z);
		void SetQuat(Quat &r);
		void SetPos(float x, float y, float z);
		void SetDeltaRotXYX(float rX, float rY, float rZ);

		void SetName(AnimController::Name _name);
		virtual char *GetName() override;
		virtual void Wash() override;
		virtual bool Compare(DLink *pTargetNode) override;
		virtual void Dump() override;

	private:
		void privClear();
		
		AnimController::Name name;

		TimerController     *poTimerControl;
		GameObjectAnimSkin *pControlObj;
		//Skeleton *poSkeleton;
		Anim *pAnim;
		//FontNode *pTag;

		bool enabled;
	
	};
}

#endif

// --- End of File ---
