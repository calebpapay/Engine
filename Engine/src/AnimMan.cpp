//2024. Caleb Papay

#include "AnimMan.h"
#include "ManBase.h"
#include "DLinkMan.h"
//#include "AnimNull.h"

namespace Azul
{
	AnimMan *AnimMan::posInstance = nullptr;


	AnimMan::AnimMan(int reserveNum, int reserveGrow)
		: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
	{
		// Preload the reserve
		this->proFillReservedPool(reserveNum);

		// initialize derived data here
		
		//assert(pAnim);
		this->poNodeCompare = new Anim();
		assert(this->poNodeCompare);
		this->poNodeCompare->SetName(Anim::Name::Not_Initialized);
	}

	AnimMan::~AnimMan()
	{
		delete this->poNodeCompare;
		this->poNodeCompare = nullptr;

		// iterate through the list and delete
		Iterator *pIt = this->baseGetActiveIterator();

		DLink *pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			Anim *pDeleteMe = (Anim *)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}

		pIt = this->baseGetReserveIterator();

		pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			Anim *pDeleteMe = (Anim *)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}
	}

	
	// Static Methods
	void AnimMan::Create(int reserveNum, int reserveGrow)
	{
		// make sure values are ressonable 
		assert(reserveNum >= 0);
		assert(reserveGrow > 0);

		// initialize the singleton here
		assert(posInstance == nullptr);

		// Do the initialization
		if(posInstance == nullptr)
		{
			posInstance = new AnimMan(reserveNum, reserveGrow);
		}
	}

	void AnimMan::Destroy()
	{
		AnimMan *pMan = AnimMan::privGetInstance();
		assert(pMan != nullptr);
		AZUL_UNUSED_VAR(pMan);

		delete AnimMan::posInstance;
		AnimMan::posInstance = nullptr;
	}
	
	

	void AnimMan::SetClip(Anim::Name name, Clip* clipName)
	{
		AnimMan *pMan = AnimMan::privGetInstance();
		Anim* pAnim = pMan->Find(name);
		pAnim->SetClip(clipName);

	}


	//must be added as an Anim
	void AnimMan::Add(Anim::Name name, Clip* clip, Mixer* pMix, WorldCompute* pWorldCompute)
	{
		AnimMan *pMan = AnimMan::privGetInstance();

		//assert(pAnim);

		Anim *pNode = (Anim *)pMan->baseAddToFront();
		assert(pNode != nullptr);

		pNode->Set(name, clip, pMix, pWorldCompute);
		// Initialize the date
		//pNode->SetName(name);
	}


	//so we can safely find as an anim
	Anim *AnimMan::Find(Anim::Name _name)
	{
		AnimMan *pMan = AnimMan::privGetInstance();
		assert(pMan != nullptr);

		// Compare functions only compares two Nodes

		// So:  Use the Compare Node - as a reference
		//      use in the Compare() function
		assert(pMan->poNodeCompare);

		pMan->poNodeCompare->name = _name;

		Anim*pData = (Anim*)pMan->baseFind(pMan->poNodeCompare);

		return pData;
	}

	void AnimMan::Remove(Anim *pNode)
	{
		assert(pNode != nullptr);

		AnimMan *pMan = AnimMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseRemove(pNode);
	}

	void AnimMan::Dump()
	{
		AnimMan *pMan = AnimMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseDump();
	}

	
	// Private methods
	AnimMan *AnimMan::privGetInstance()
	{
		// Safety - this forces users to call Create() first before using class
		assert(posInstance != nullptr);

		return posInstance;
	}

	
	// Override Abstract methods
	DLink *AnimMan::derivedCreateNode()
	{
		DLink *pNodeBase = new Anim();
		assert(pNodeBase != nullptr);

		return pNodeBase;
	}
}

// --- End of File ---




