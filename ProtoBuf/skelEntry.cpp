//2024. Caleb Papay

#include "skelEntry.h"

namespace Azul
{
	skelEntry::~skelEntry()
	{

	}

	skelEntry::skelEntry()
		:nodeIndex(-1),
		parentIndex(-1),
		pNodeName{ 0 }
	{
		strcpy_s(this->pNodeName, skelEntry::SKELETON_NAME_SIZE, "--Uninitialized--");
		// Make sure version is within the bytes for serialization
		assert(strlen(this->pNodeName) < skelEntry::SKELETON_NAME_SIZE);
	}
	
	void skelEntry::set(int _nodeIndex, int _parentIndex,const char *_pNodeName)
	{
		assert(_pNodeName);
		this->nodeIndex = _nodeIndex;
		this->parentIndex = _parentIndex;
		memcpy_s(this->pNodeName, skelEntry::SKELETON_NAME_SIZE, _pNodeName, skelEntry::SKELETON_NAME_SIZE);
	}


	//void skelEntry::setParent(int _parentIndex)
	//{
	//	this->parentIndex = _parentIndex;
	//}

	void skelEntry::Serialize(skelEntry_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		out.set_nodeindex(this->nodeIndex);
		out.set_parentindex(this->parentIndex);

		std::string sName((const char *)this->pNodeName, skelEntry::SKELETON_NAME_SIZE);
		out.set_pnodename(sName);
	}

	void skelEntry::Deserialize(const skelEntry_proto &in)
	{
		AZUL_UNUSED_VAR(in);

		this->nodeIndex = in.nodeindex();
		this->parentIndex = in.parentindex();

		memcpy_s(this->pNodeName, skelEntry::SKELETON_NAME_SIZE, in.pnodename().data(), skelEntry::SKELETON_NAME_SIZE);
	}

	void skelEntry::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);
		Trace::out("{%2d, %2d, \"%s\" },\n",
				   this->nodeIndex,
				   this->parentIndex,
				   this->pNodeName);
	}
}

// --- End of File ---





