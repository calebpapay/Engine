//2024. Caleb Papay

#include "Skel.h"
#include "StringThis.h"

namespace Azul
{
	// public methods: -------------------------------------------------------------

	Skel::Skel()
	{
		this->mName = Skel::Name::Not_Initialized;
		this->numBones = 0;;
		this->poTableArray = nullptr;
	}

	Skel::~Skel()
	{
		delete[] this->poTableArray;
		this->poTableArray = nullptr;
	}

	void Skel::Set(Skel::Name skelName, unsigned int _numBones, skelEntry *poSkelEntry)
	{
		this->mName = skelName;
		this->numBones = _numBones;

		this->poTableArray = new Data[numBones]();

		assert(skelEntry::SKELETON_NAME_SIZE == Skel::SKELETON_NAME_SIZE);

		for(size_t i = 0; i < numBones; i++)
		{
			this->poTableArray[i].Set(poSkelEntry[i].nodeIndex, poSkelEntry[i].parentIndex, poSkelEntry[i].pNodeName);
		}
	}

	bool Skel::Compare(DLink *pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget != nullptr);

		Skel *pDataB = (Skel *)pTarget;

		bool status = false;

		if(this->mName == pDataB->mName)
		{
			status = true;
		}

		return status;
	}

	void Skel::Dump()
	{
		Trace::out("      Skel(%p)\n", this);
		//Trace::out("      Name: %s \n", StringMe(this->mName));

		DLink::Dump();
	}

	void Skel::Wash()
	{
		this->mName = Skel::Name::Not_Initialized;
		this->numBones = 0;
		// just in case
		delete[] this->poTableArray;
		this->poTableArray = nullptr;
	}
}

//--- End of File ---
