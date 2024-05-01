//2024. Caleb Papay


#include "AnimController.h"
#include "AnimMan.h"
#include "StringThis.h"

namespace Azul
{

	AnimController::AnimController()
		:	DLink(),
			pControlObj(nullptr),
			//pTag(nullptr),
			name(Name::Not_Initialized),
			poTimerControl(new TimerController()),
			pAnim(nullptr),
			enabled(true)
	{
		
		//this->privClear();
	}
	void AnimController::SetName(AnimController::Name _name)
	{ 
		this->name = _name;
	}
	void AnimController::SetPos(float x, float y, float z)
	{
		this->pControlObj->SetTrans(x,y,z);
		
	}

	void AnimController::Set(AnimController::Name _name, Anim::Name animName, GameObjectAnimSkin* pGameObj)
	{
		this->pAnim = AnimMan::Find(animName);
		this->pControlObj = pGameObj;
		this->name = _name;

		assert(pAnim);
		assert(poTimerControl);

		AnimTime maxTime = pAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerControl->Set((0.25f * AnimTime(AnimTime::Duration::FILM_24_FRAME)), minTime, maxTime);
		//const char *label = pAnim->GetName();
		//pTag = FontMan::Add(Font::Name::TestMessage1, pAnim->GetName(), Glyph::Name::Consolas15pt, 0.0f, 0.0f);

		//this->poHierarchy = new Hierarchy( pAnim->GetSkelName(), pAnim->GetMeshName(), pAnim->GetTextureName(), pAnim->FetchBones());
		//pTag->SetScreenPosTrack(this->poHierarchy->GetFirstBone());
		//this->pTag->UpdateMessage(pAnim->GetClip()->GetName());
		//assert(poHierarchy);

	}

	void AnimController::ReverseDeltaTime()
	{
		this->poTimerControl->SetDeltaTime(-this->poTimerControl->GetDeltaTime());
	}

	void AnimController::Update()
	{
		if(enabled)
		{
			
			AnimTime maxTime = pAnim->FindMaxTime();
			AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
			this->poTimerControl->SetMaxTime(maxTime);
			this->poTimerControl->SetMinTime(minTime);
			this->poTimerControl->Update();

			// interpolate all bones
			//this->pTag->UpdateMessage(pAnim->GetClip()->GetName());
			//this->pTag->SetScreenPosTrack(this->poHierarchy->GetFirstBone());
			this->pAnim->Animate(this->poTimerControl->GetCurrTime());
		}

	}
	void AnimController::SetQuat(Quat &q)
	{
		//this->pAnim->SetQuat(q);
		this->pControlObj->SetQuat(q);
	}
	void AnimController::SetScale(float x, float y, float z)
	{
		this->pControlObj->SetScale(x, y, z);
	}

	void AnimController::SetDeltaRotXYX(float rX, float rY, float rZ)
	{
		//this->pAnim->SetDeltaRotXYX( rX,  rY,  rZ);
		
		this->pControlObj->delta_x = rX;
		this->pControlObj->delta_y = rY;
		this->pControlObj->delta_z = rZ;
	}



	Anim *AnimController::GetAnim()
	{
		return this->pAnim;
	}

	void AnimController::Enable()
	{
		enabled = true;
	}
	void AnimController::Disable()
	{
		enabled = false;
	}

	void AnimController::privClear()
	{
		this->pAnim = nullptr;
		//delete   this->poHierarchy;
	}

	char *AnimController::GetName()
	{
		char *pName = nullptr;
		if(this->pAnim)
		{
			pName = this->pAnim->GetName();
		}

		return pName;
	}

	void AnimController::Wash()
	{
		this->privClear();
	}

	bool AnimController::Compare(DLink *pTargetNode)
	{
		// This is used in ManBase.Find() 
		assert(pTargetNode);

		AnimController *pDataB = (AnimController *)pTargetNode;

		bool status = false;

		assert(pDataB->pAnim);
		assert(this->pAnim);

		if(this->pAnim->name == pDataB->pAnim->name)
		{
			status = true;
		}

		return status;
	}

	void AnimController::Dump()
	{
		Trace::out("      AnimController(%p)\n", this);

		// Data:
		if(this->pAnim)
		{
			Trace::out("      Mesh(%p) \n", this->pAnim);
			Trace::out("      Name: %s \n", StringMe(this->pAnim->name));
		}
		else
		{
			Trace::out("      Name: %s \n", "null");
		}

		DLink::Dump();
	}
	

	AnimController::~AnimController()
	{
		this->privClear();
		delete   this->poTimerControl;
		//pTag = nullptr;
	}

	
}

// --- End of File ---
