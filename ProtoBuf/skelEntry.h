//2024. Caleb Papay

#ifndef SKEL_ENTRY_H
#define SKEL_ENTRY_H

#include "skelEntry.pb.h"

namespace Azul
{

	class skelEntry
	{
	public:
		static const unsigned int SKELETON_NAME_SIZE = 64;

	public:
		skelEntry();
		skelEntry(const skelEntry &) = delete;
		skelEntry &operator = (const skelEntry &) = delete;
		~skelEntry();

		void set(int _nodeIndex, int  _parentIndex, const char *pNodeName);
	//	void setParent(int  _parentIndex);
		// Serialization 
		void Serialize(skelEntry_proto &out) const;
		void Deserialize(const skelEntry_proto &in);

		void Print(const char *const pName) const;

	public:
		int   nodeIndex;
		int   parentIndex;
		char  pNodeName[SKELETON_NAME_SIZE];

	};

}

#endif

// --- End of File ---
