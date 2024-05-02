#ifndef HEAPSAP_H
#define HEAPSAP_H


#include "Heap.h"

namespace Azul
{

	class HeapSAP : Heap
	{
	public:
		// "Protected" Interface ---------------- (behind the scenes)
		~HeapSAP() = delete;

		void sapSetNext(Heap* pHeap) 
		{
			this->DebugSetNext(pHeap);
		}

		void sapSetPrev(Heap* pHeap) 
		{
			this->DebugSetPrev(pHeap);
		}
		void sapInitHeap(HANDLE winHeapHandle, size_t HeapSize, const char* const HeapName, Heap::Type hType, Mem* const mem)
		{
			this->initHeap(winHeapHandle, HeapSize, HeapName, hType, mem);
		}

		void sapPostInitFixed(int numBlocks, int sizePerBlock) 
		{
			this->postInitFixed(numBlocks, sizePerBlock);
		}

		//Alloc
		void* sapAlloc(Azul::Mem::Align align, unsigned int inSize, const char* inName, size_t lineNum)
		{
			return this->Alloc(align, inSize, inName, lineNum);
		}
	
		void sapDealloc(void* p)
		{
			this->Dealloc(p);
		}



	};

}

#endif 

// --- End of File ---
