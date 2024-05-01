//2024. Caleb Papay

#include "AnimInstanceMan.h"
#include "AnimController.h"
#include "ManBase.h"
#include "DLinkMan.h"

namespace Azul
{
	AnimInstanceMan *AnimInstanceMan::posInstance = nullptr;

	
	AnimInstanceMan::AnimInstanceMan(int reserveNum, int reserveGrow)
		: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
	{
		// Preload the reserve
		this->proFillReservedPool(reserveNum);

		// initialize derived data here
		this->poNodeCompare = new AnimController();
		assert(this->poNodeCompare);
	
	}

	AnimInstanceMan::~AnimInstanceMan()
	{
		delete this->poNodeCompare;
		this->poNodeCompare = nullptr;

		// iterate through the list and delete
		Iterator *pIt = this->baseGetActiveIterator();

		DLink *pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			AnimController *pDeleteMe = (AnimController *)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}

		pIt = this->baseGetReserveIterator();

		pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			AnimController *pDeleteMe = (AnimController *)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}
	}

	
	// Static Methods
	void AnimInstanceMan::Create(int reserveNum, int reserveGrow)
	{
		// make sure values are ressonable 
		assert(reserveNum >= 0);
		assert(reserveGrow > 0);

		// initialize the singleton here
		assert(posInstance == nullptr);

		// Do the initialization
		if(posInstance == nullptr)
		{
			posInstance = new AnimInstanceMan(reserveNum, reserveGrow);
		}
	}

	void AnimInstanceMan::Destroy()
	{
		AnimInstanceMan *pMan = AnimInstanceMan::privGetInstance();
		assert(pMan != nullptr);
		AZUL_UNUSED_VAR(pMan);

		delete AnimInstanceMan::posInstance;
		AnimInstanceMan::posInstance = nullptr;
	}

	void AnimInstanceMan::Update()
	{
		AnimInstanceMan *pMan = AnimInstanceMan::privGetInstance();

		Iterator *pIt = pMan->baseGetActiveIterator();

		DLink *pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			AnimController *pControlMe = (AnimController *)pIt->Curr();
			assert(pControlMe);
			pNode = pIt->Next();
			pControlMe->Update();
		}
	}



	//void AnimInstanceMan::Reverse()
	//{
	//	AnimInstanceMan *pMan = AnimInstanceMan::privGetInstance();

	//	Iterator *pIt = pMan->baseGetActiveIterator();

	//	DLink *pNode = pIt->First();

	//	// Walk through the nodes
	//	while(!pIt->IsDone())
	//	{
	//		AnimController *pControlMe = (AnimController *)pIt->Curr();
	//		assert(pControlMe);
	//		pNode = pIt->Next();
	//		pControlMe->ReverseDeltaTime();
	//	}
	//}

	//must be added as an Anim
	AnimController* AnimInstanceMan::Add(AnimController::Name _name, Anim::Name animName, GameObjectAnimSkin* pGameSkin)
	{
		AnimInstanceMan *pMan = AnimInstanceMan::privGetInstance();

		AnimController *pNode = (AnimController *)pMan->baseAddToFront();
		assert(pNode != nullptr);

		// Initialize the date
		pNode->Set(_name, animName, pGameSkin);

		return pNode;
	}


	//so we can safely find as an anim
	AnimController *AnimInstanceMan::Find(AnimController::Name _name)
	{
		AnimInstanceMan *pMan = AnimInstanceMan::privGetInstance();
		assert(pMan != nullptr);

		// Compare functions only compares two Nodes

		// So:  Use the Compare Node - as a reference
		//      use in the Compare() function
		AnimController *pAnimController = pMan->poNodeCompare;

		pAnimController->SetName(_name);

		AnimController *pData = (AnimController *)pMan->baseFind(pMan->poNodeCompare);

		return pData;
	}

	void AnimInstanceMan::Remove(AnimController *pNode)
	{
		assert(pNode != nullptr);

		AnimInstanceMan *pMan = AnimInstanceMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseRemove(pNode);
	}

	void AnimInstanceMan::Dump()
	{
		AnimInstanceMan *pMan = AnimInstanceMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseDump();
	}

	
	// Private methods
	AnimInstanceMan *AnimInstanceMan::privGetInstance()
	{
		// Safety - this forces users to call Create() first before using class
		assert(posInstance != nullptr);

		return posInstance;
	}

	
	// Override Abstract methods
	
	DLink *AnimInstanceMan::derivedCreateNode()
	{
		DLink *pNodeBase = new AnimController();
		assert(pNodeBase != nullptr);

		return pNodeBase;
	}
}

// --- End of File ---




