//2024. Caleb Papay

#ifndef ANIM_H
#define ANIM_H

#include "AnimTimer.h"
#include "DLink.h"
#include "WorldCompute.h"

namespace Azul
{
	class Clip;
	class Mixer;
	
	class Anim : public DLink
	{
	public:
		enum class Name
		{
			WalkingBot,
			BlastUpBot,
			FallBot,
			SideStepBot,
			Anim0,
			Anim1,
			Anim2,
			Anim3,
			Anim4,
			Not_Initialized,
			NULL_ANIM

		};// TexNodeMan::Find(TextureObject::Name::NullTexture)
	public:
		Anim();
		Anim(const Anim &) = delete;
		Anim &operator = (const Anim &) = delete;
		virtual ~Anim();

		void Set(Anim::Name _name, Clip* pClip, Mixer* pMix, WorldCompute* pWC);

		char *GetName();
		void SetName(Anim::Name _name);

		void Animate(AnimTime tCurr);
		AnimTime FindMaxTime();
		//TextureObject *GetTexture();
		//TextureObject::Name GetTextureName();
		/*Bone *FetchBones();*/
		//Skel::Name GetSkelName();
		//Mesh::Name GetMeshName();
		//virtual AnimTime FindDeltaTime();

		//static void PoseSkeleton(GameObjectAnimSkeleton *node);
	//	void Clear();
		Clip *GetClip();
		void SetClip(Clip *_pClip);
	/*	void SetQuat(Quat &r);
		void SetDeltaRotXYX(float rX, float rY, float rZ);*/

		virtual void Wash() override;
		virtual bool Compare(DLink *pTargetNode) override;
		virtual void Dump() override;

		Anim::Name name;
		
	private:
		Clip *pClip;
		Mixer *pMixer;
		WorldCompute *poWorldCompute;
		//Bone *poBoneResult;
		//TextureObject::Name texName;
		//Hierarchy *poHierarchy;
		//Skel *skel;
		//FontNode *pTag;
		//Quat *poQuat;
		

	//private:
		
	};

}

#endif

// --- End of File ---