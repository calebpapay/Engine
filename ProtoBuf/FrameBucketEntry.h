//2024. Caleb Papay

#ifndef FRAME_BUCKET_ENTRY_H
#define FRAME_BUCKET_ENTRY_H

#include "boneData.h"

#include "FrameBucketEntry.pb.h"

namespace Azul
{
	class FrameBucketEntry
	{
	public:
		FrameBucketEntry();
		FrameBucketEntry(const FrameBucketEntry &) = delete;
		FrameBucketEntry &operator = (const FrameBucketEntry &);
		~FrameBucketEntry();

		FrameBucketEntry(unsigned int _numBones);

		// Serialization 
		void Serialize(FrameBucketEntry_proto &out) const;
		void Deserialize(const FrameBucketEntry_proto &in);

		void Print(const char *const pName) const;

	public:
		unsigned int  keyFrame;
		unsigned int  numBones;
		float         keyTime;
		int           keyTimeIndex;
		boneData *poBoneEntry;
	};

}

#endif

// --- End of File ---
