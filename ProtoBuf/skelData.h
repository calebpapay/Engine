//2024. Caleb Papay

#ifndef SKEL_DATA_H
#define SKEL_DATA_H

#include "skelData.pb.h"
#include "skelEntry.h"

namespace Azul
{
	class skelData
	{
	public:
		skelData();
		skelData(const skelData &) = delete;
		skelData &operator = (const skelData &) = delete;
		~skelData();

		skelData(unsigned int _numBones);

		// Serialization 
		void Serialize(skelData_proto &out) const;
		void Deserialize(const skelData_proto &in);

		void Print(const char *const pName) const;

	public:
		unsigned int   numBones;
		skelEntry *poSkelEntry;
	};

}

#endif

// --- End of File ---
