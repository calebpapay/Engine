
//2024. Caleb Papay


#ifndef LIST_BASE_H
#define LIST_BASE_H

#include "DLink.h"
#include "Iterator.h"

namespace Azul
{
	class ListBase
	{
	public:
		virtual ~ListBase() = default;

		virtual void AddToFront(DLink *pNode) = 0;
		virtual void AddToEnd(DLink *pNode) = 0;
		virtual void Remove(DLink *pNode) = 0;
		virtual DLink *RemoveFromFront() = 0;

		virtual Iterator *GetIterator() = 0;
	};
}
#endif

// --- End of File ---