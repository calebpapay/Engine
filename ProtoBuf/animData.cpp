//2024. Caleb Papay

#include "animData.h"

namespace Azul
{
	animData::~animData()
	{
		delete[] this->poFrameBucketEntry;
		this->poFrameBucketEntry = nullptr;
	}

	animData::animData()
		:numKeyFrames(0),
		numBones(0),
		poFrameBucketEntry{ 0 },
		pClipName{ 0 }
	{

		strcpy_s(this->pClipName, animData::CLIP_NAME_SIZE, "--Uninitialized--");
		// Make sure within the bytes for serialization
		assert(strlen(this->pClipName) < animData::CLIP_NAME_SIZE);
	}

	animData::animData(unsigned int _numKeyFrames, unsigned int _numBones)
	{
		this->numKeyFrames = _numKeyFrames;
		this->numBones = _numBones;

		this->poFrameBucketEntry = new FrameBucketEntry[_numKeyFrames]();

		for(size_t i = 0; i < _numKeyFrames; i++)
		{
			this->poFrameBucketEntry[i] = FrameBucketEntry(_numBones);
		}

		assert(this->poFrameBucketEntry);
	}

	void animData::SetName(const char *_pClipName)
	{
		assert(_pClipName);
		memcpy_s(this->pClipName, animData::CLIP_NAME_SIZE, _pClipName, animData::CLIP_NAME_SIZE);
	}

	void animData::Serialize(animData_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		// Add the number of bones
		out.set_numkeyframes(this->numKeyFrames);
		out.set_numbones(this->numBones);

		for(unsigned int i = 0; i < this->numKeyFrames; i++)
		{
			// Add the FrameBucketEntry
			// Crazy - issue... 
			//     this needs to be unique for the add
			//     Cannot pull out of the loop   
			FrameBucketEntry_proto tmpFrameBucketEntry_proto;

			// create one proto
			this->poFrameBucketEntry[i].Serialize(tmpFrameBucketEntry_proto);

			// add it to the message(package)
			*out.add_poframebucketentry() = tmpFrameBucketEntry_proto;
		}

		//assert(out.numkeyframes() == this->numKeyFrames);

		std::string sName((const char *)this->pClipName, animData::CLIP_NAME_SIZE);
		out.set_pclipname(sName);
	}

	void animData::Deserialize(const animData_proto &in)
	{
		AZUL_UNUSED_VAR(in);
		// Safety
		delete[] this->poFrameBucketEntry;
		this->poFrameBucketEntry = nullptr;

		this->numKeyFrames = in.numkeyframes();
		this->numBones = in.numbones();

		// Create the EMPTY space...
		//    High-level only
		//       the serializer will create the bone array dynamically
		this->poFrameBucketEntry = new FrameBucketEntry[this->numKeyFrames]();
		assert(this->poFrameBucketEntry);

		// Fill it
		for(unsigned int i = 0; i < this->numKeyFrames; i++)
		{
			poFrameBucketEntry[i].Deserialize(in.poframebucketentry((int)i));
		}

		memcpy_s(this->pClipName, animData::CLIP_NAME_SIZE, in.pclipname().data(), animData::CLIP_NAME_SIZE);
	}

	void animData::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);

		Trace::out("%s: \n", pName);
		Trace::out("numkeyframe: %d\n", this->numKeyFrames);

		for(size_t i = 0; i < this->numKeyFrames; i++)
		{
			char pKeyName[32];
			sprintf_s(pKeyName, 32, "Key_%d", (int)this->poFrameBucketEntry[i].keyFrame);
			this->poFrameBucketEntry[i].Print(pKeyName);
		}

		Trace::out("\n");
	}
}

// --- End of File ---


