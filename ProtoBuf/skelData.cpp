//2024. Caleb Papay
#include "skelData.h"

namespace Azul
{
	skelData::~skelData()
	{
		delete[] this->poSkelEntry;
		this->poSkelEntry = nullptr;
	}

	skelData::skelData()
	{
		this->numBones = 0;
		this->poSkelEntry = nullptr;
	}

	skelData::skelData(unsigned int _numBones)
	{
		this->numBones = _numBones;

		this->poSkelEntry = new skelEntry[_numBones]();
		assert(this->poSkelEntry);
	}

	void skelData::Serialize(skelData_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		// Add the number of bones
		out.set_numbones(this->numBones);

		// Add the skelEntry
		skelEntry_proto tmpSkelEntry_proto;

		for(unsigned int i = 0; i < this->numBones; i++)
		{
			// create one proto
			this->poSkelEntry[i].Serialize(tmpSkelEntry_proto);

			// add it to the message(package)
			skelEntry_proto *p = out.add_poskelentry();
			assert(p);
			*p = tmpSkelEntry_proto;
		}

		assert(out.numbones() == this->numBones);
	}

	void skelData::Deserialize(const skelData_proto &in)
	{
		AZUL_UNUSED_VAR(in);
		// safety
		delete[] this->poSkelEntry;
		this->poSkelEntry = nullptr;

		this->numBones = in.numbones();

		this->poSkelEntry = new skelEntry[this->numBones]();
		assert(this->poSkelEntry);

		for(unsigned int i = 0; i < this->numBones; i++)
		{
			poSkelEntry[i].Deserialize(in.poskelentry((int)i));
		}
	}

	void skelData::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);
		Trace::out("%s: \n", pName);

		for(size_t i = 0; i < this->numBones; i++)
		{
			this->poSkelEntry[i].Print(pName);
		}

		Trace::out("\n");


	}
}

// --- End of File ---


