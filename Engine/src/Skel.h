//2024. Caleb Papay

#ifndef SKEL_H
#define SKEL_H

#include "DLink.h"
#include "skelData.h"
#include "Mesh.h"

namespace Azul
{
	class Skel : public DLink
	{
	public:
		static const unsigned int SKELETON_NAME_SIZE = 64;

		enum Name
		{
			ChickenBot,
			RatThing,
			SARDAUKAR,
			Not_Initialized
		};

		struct Data
		{
			void Set(int _nodeIndex, int _parentIndex, const char *_pNodeName)
			{
				assert(_pNodeName);
				this->index = _nodeIndex;
				this->parentIndex = _parentIndex;
				memcpy_s(this->name, skelEntry::SKELETON_NAME_SIZE, _pNodeName, skelEntry::SKELETON_NAME_SIZE);
			}

			int  index;
			int  parentIndex;
			char name[SKELETON_NAME_SIZE];
		};

	public:
		// public methods: -------------------------------------------------------------
		Skel();
		Skel(const Skel &) = delete;
		Skel &operator = (const Skel &) = delete;
		virtual ~Skel();


		virtual bool Compare(DLink *pTarget) override;
		virtual void Dump() override;
		virtual void Wash() override;

		void Set(Skel::Name skelName, unsigned int numBones, skelEntry *poSkelEntry);

	public:
		Name           mName;
		Mesh::Name meshName;
		unsigned int   numBones;
		Data *poTableArray;

	};

}


#endif

//--- End of File ---
