#ifndef BLOCKSAP_H
#define BLOCKSAP_H


#include "Block.h"

namespace Azul
{


	class BlockSAP : Block
	{
	public:
		// "Protected" Interface ---------------- (behind the scenes)

		void* sapInitUsedFixed(Heap* h, unsigned int inSize)
		{
			return this->initUsedFixed( h, inSize);
		}

		void* sapUpdateUsedFixed(const char* inName, size_t lineNum)
		{
			return this->updateUsedFixed(inName, lineNum);
		}

		void sapSetHeapNext(Block* pBlock)
		{
			this->SetHeapNext(pBlock);
		}

		void sapSetHeapPrev(Block* pBlock)
		{
			this->SetHeapPrev(pBlock);
		}

		void sapSetGlobalNext(Block* pBlock)
		{
			this->SetGlobalNext(pBlock);
		}

		void sapSetGlobalPrev(Block* pBlock)
		{
			this->SetGlobalPrev(pBlock);
		}


	};

}

#endif 

// --- End of File ---
