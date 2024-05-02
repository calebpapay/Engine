// 2024. Caleb Papay

#include "MemLink.h"

namespace Azul
{

	MemLink &MemLink::operator = (const MemLink &)
	{
		this->Reset();
		return *this;
	}

	MemLink::MemLink()
	{
		this->Reset();
	}

	MemLink::MemLink(const MemLink &)
	{
		this->Reset();
	}

	MemLink::~MemLink()
	{
		// do nothing
	}

	void MemLink::Reset()
	{
		this->pNext = nullptr;
		this->pPrev = nullptr;
	}

}

// ---  End of File ---
