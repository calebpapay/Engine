//2024. Caleb Papay

#ifndef ANIM_DATA_H
#define ANIM_DATA_H

#include "animData.pb.h"
#include "FrameBucketEntry.h"
namespace Azul
{

class animData
{
public:
	static const unsigned int CLIP_NAME_SIZE = 64;
public:
	animData();
	animData(const animData &) = delete;
	animData &operator = (const animData &) = delete;
	~animData();

	animData(unsigned int _numKeyFrames, unsigned int _numBones);
	void SetName(const char *_pNodeName);
	// Serialization 
	void Serialize(animData_proto &out) const;
	void Deserialize(const animData_proto &in);

	void Print(const char *const pName) const;

public:
	unsigned int numKeyFrames;
	unsigned int numBones;
	char  pClipName[CLIP_NAME_SIZE];
	FrameBucketEntry *poFrameBucketEntry;
	//vboData			vbo_keyTimes;

};

}

#endif

// --- End of File ---
