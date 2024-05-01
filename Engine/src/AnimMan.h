//2024. Caleb Papay

#ifndef ANIM_MAN_H
#define ANIM_MAN_H 

#include "ManBase.h"
#include "Anim.h"
#include "DLinkMan.h"

namespace Azul
{
	class AnimMan : public ManBase
	{

		// Static Methods
	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();
		

		static void Add(Anim::Name name, Clip *clip, Mixer* pMix, WorldCompute *pWorldCompute);
		static Anim *Find(Anim::Name name);
		static void Remove(Anim *pNode);
		static void Dump();

		static void SetClip(Anim::Name name, Clip *clipName);

		
		// Private methods
	private:
		static AnimMan *privGetInstance();

		AnimMan() = delete;
		AnimMan(const AnimMan &) = delete;
		AnimMan &operator = (const AnimMan &) = delete;

		~AnimMan();

		AnimMan( int reserveNum, int reserveGrow);

		
		// Override Abstract methods
	protected:
		DLink *derivedCreateNode() override;

		
		// Data: unique data for this manager 
	private:
		Anim *poNodeCompare;
		static AnimMan *posInstance;

	};
}

#endif

// --- End of File ---
