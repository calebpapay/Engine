// 2024. Caleb Papay


#include "Heap.h"
#include "Block.h"
#include "MemSAP.h"
#include "BlockSAP.h"

namespace Azul
{

	void Heap::initHeap(HANDLE winHeapHandle, size_t heapSize, const char* const HeapName, Heap::Type hType, Mem* const mem)
	{
		this->mWinHeapHandle = winHeapHandle;
		this->mType = hType;
		this->mInfo.TotalSize = heapSize;
		this->mInfo.PeakNumAlloc = 0;
		this->mInfo.CurrNumAlloc = 0;
		this->mInfo.PeakBytesUsed = 0;
		this->mInfo.CurrBytesUsed = 0;
		// set the name
		this->privSetHeapName(HeapName);

		pBlkHead = nullptr;
		hLink.pNext = nullptr;
		hLink.pPrev = nullptr;
		pMem = mem;

		pOverflow = nullptr;
		pFixedFreeHead = nullptr;
		pFixStart = nullptr;

	};

	void Heap::postInitFixed(int numBlocks, int sizePerBlock)
	{
		int i = 0;

		//preAllocating Memory For Fixed Heap
		void* memStart = HeapAlloc(mWinHeapHandle, 0, (numBlocks * (sizePerBlock + sizeof(Block))));

		//fixed free head = start of user mem
		this->pFixedFreeHead = (Block*)memStart;
		this->pFixStart = (Block*)memStart;
		BlockSAP* pCurrBlock = (BlockSAP*) this->pFixedFreeHead;

		while (i < numBlocks-1)
		{
			//initialize the current block and get pointer to user data
			void* userBlockLocation = pCurrBlock->sapInitUsedFixed(this, sizePerBlock);
			void* pNextLocation = (void*)((char*)userBlockLocation + sizePerBlock);
			Block* pNextBlock = (Block*)pNextLocation;
			pCurrBlock->sapSetHeapNext(pNextBlock);
			
			//increment
			pCurrBlock = (BlockSAP*)pNextBlock;
			i++;
		}
		pCurrBlock->sapInitUsedFixed(this, sizePerBlock);
		Block* pNextBlock = nullptr;
		pCurrBlock->sapSetHeapNext(pNextBlock);
	}


	void* Heap::Alloc(Azul::Mem::Align align, unsigned int inSize, const char* inName, size_t lineNum) 
	{
		if (this->mType == Heap::Type::FIXED) 
		{
			if (this->pFixedFreeHead != nullptr) {

				BlockSAP* newBlock = (BlockSAP*) this->GetFixedHead();
				void* p = newBlock->sapUpdateUsedFixed(inName, lineNum);
				this->AddHeapBlock((Block*&)newBlock);
				MemSAP::sapAddGlobalBlock((Block*&)newBlock);
				MemSAP::sapRegister(p); //registering USER BLOCK
				return p;
			}
			else if (pOverflow != nullptr) {
				void* p = pOverflow->Alloc(Mem::Align::Byte_4, inSize, inName, lineNum);
				return p;
			}
			else {
				return nullptr;
			}
		}
		int alignment;
		switch (align)
			{
			case (Azul::Mem::Align::Byte_4):
				alignment = 4;
				break;
			case (Azul::Mem::Align::Byte_8):
				alignment = 8;
				break;
			case (Azul::Mem::Align::Byte_16):
				alignment = 16;
				break;
			case (Azul::Mem::Align::Byte_32):
				alignment = 32;
				break;
			case (Azul::Mem::Align::Byte_64):
				alignment = 64;
				break;
			case (Azul::Mem::Align::Byte_128):
				alignment = 128;
				break;
			case (Azul::Mem::Align::Byte_256):
				alignment = 256;
				break;
			default:
				alignment = 4;
				break;
			}

		void* s = HeapAlloc(mWinHeapHandle, 0, sizeof(Block) + (inSize + alignment));

		Block* newBlock = (Block*)s;
		void *p = newBlock->initBlock(this, alignment, inSize, inName, lineNum);

		this->AddHeapBlock(newBlock);
		MemSAP::sapAddGlobalBlock(newBlock);
		MemSAP::sapRegister(p); //registering USER BLOCK
		return p;

	}



	void Heap::Dealloc(void* p)
	{
		if (this->GetHeapType() == Heap::Type::FIXED) {
			Block* pRealBlock = ((Block*)p -1);
			
			this->RemoveHeapBlock(pRealBlock);
			MemSAP::sapRemoveGlobalBlock(pRealBlock);
			MemSAP::sapUnRegister(p); //unregistering USER BLOCK
			this->AddToFixedHead(pRealBlock);
			
		}
		else {

			void* secret = (void*)((char*)p - 4);
			Block** ppRealBlock = (Block**)secret;
			Block* pRealBlock = *ppRealBlock;

			this->RemoveHeapBlock(pRealBlock);

			MemSAP::sapRemoveGlobalBlock(pRealBlock);
			MemSAP::sapUnRegister(p); //unregistering USER BLOCK
			HeapFree(mWinHeapHandle, 0, (void*)pRealBlock);
		}
		
	}

	void Heap::AddToFixedHead(Block*& b)
	{
		if (this->pFixedFreeHead == nullptr) {
			this->pFixedFreeHead = b;
		}
		else {
			Block* oldHead = this->pFixedFreeHead;
			this->pFixedFreeHead = b;
			((BlockSAP*)b)->sapSetHeapNext(oldHead);
			((BlockSAP*)oldHead)->sapSetHeapPrev(b);
		}
	}

	Block* Heap::GetFixedHead()
	{
		if (this->pFixedFreeHead == nullptr) 
		{
			return nullptr;
		}
		Block* b = this->pFixedFreeHead;

		this->pFixedFreeHead = b->GetHeapNext();
		if (this->pFixedFreeHead != nullptr) {
			((BlockSAP*)this->pFixedFreeHead)->sapSetHeapPrev(nullptr);
		}
		((BlockSAP*)b)->sapSetHeapNext(nullptr);
		
		return b;

	}

	void Heap::AddHeapBlock(Block*& b) 
	{
		if (this->pBlkHead == nullptr) {
			this->pBlkHead = b;
		}
		else {
			Block* oldHead = this->pBlkHead;
			this->pBlkHead = b;
			((BlockSAP*)b)->sapSetHeapNext(oldHead);
			((BlockSAP*)oldHead)->sapSetHeapPrev(b);
		}
		this->mInfo.CurrBytesUsed += b->GetAllocSize();
		this->mInfo.CurrNumAlloc++;

		if (this->mInfo.PeakNumAlloc < this->mInfo.CurrNumAlloc)
		{
			this->mInfo.PeakNumAlloc = this->mInfo.CurrNumAlloc;
		}
		if (this->mInfo.PeakBytesUsed < this->mInfo.CurrBytesUsed)
		{
			this->mInfo.PeakBytesUsed = this->mInfo.CurrBytesUsed;
		}
	}

	void Heap::RemoveHeapBlock(Block*& b)
	{
		if (b == this->pBlkHead && b->GetHeapNext() == nullptr) 
		{
			this->pBlkHead =nullptr;
		}
		else if (b == this->pBlkHead) 
		{
			this->pBlkHead = b->GetHeapNext();
			((BlockSAP*)this->pBlkHead)->sapSetHeapPrev(nullptr);
			((BlockSAP*)b)->sapSetHeapNext(nullptr);
		}
		else if (b->GetHeapNext() != nullptr)
		{
			((BlockSAP*)b->GetHeapPrev())->sapSetHeapNext(b->GetHeapNext());
			((BlockSAP*)b->GetHeapNext())->sapSetHeapPrev(b->GetHeapPrev());

			((BlockSAP*)b)->sapSetHeapNext(nullptr);
			((BlockSAP*)b)->sapSetHeapPrev(nullptr);
		}
		else 
		{
			((BlockSAP*)b->GetHeapPrev())->sapSetHeapNext(nullptr);
			((BlockSAP*)b)->sapSetHeapPrev(nullptr);
		}

		this->mInfo.CurrBytesUsed -= b->GetAllocSize();
		this->mInfo.CurrNumAlloc--;
	}



	void Heap::privSetHeapName(const char* const hName)
	{
		// Next couple lines, have safety to only copy a maximum of allowed characters
		assert(hName);

		unsigned int len = strlen(hName);

		assert(len < NameNumChar);

		if (len > NameNumChar)
		{
			len = NameNumChar;
		}

		memset(this->mInfo.Name, 0x0, NameLength);
		memcpy(this->mInfo.Name, hName, len);
	}

	void Heap::Destroy() {
		// Destroy heap
		

		HeapDestroy(this->mWinHeapHandle);

	}

	Heap::Type Heap::GetHeapType() const
	{
		return (Heap::Type)this->mType;
	}

	// Overflow Heap
	void Heap::SetOverflowHeap(Heap *pHeap)
	{
		this->pOverflow = pHeap;
		// add Heap to list of Heaps
		

	}

	Heap *Heap::GetOverflowHeap() const
	{
		return this->pOverflow;
	}

	void Heap::GetInfo(Info &retInfo) const
	{
		retInfo = this->mInfo;
	};

	Heap *Heap::DebugGetNext() const
	{
		return (Heap*)this->hLink.pNext;
	};

	Heap *Heap::DebugGetPrev() const
	{
		return (Heap *)this->hLink.pPrev;
	};

	void Heap::DebugSetNext(Heap* pHeap)
	{
		this->hLink.pNext = (MemLink*)pHeap;
	};

	void Heap::DebugSetPrev(Heap* pHeap)
	{
		this->hLink.pPrev = (MemLink*)pHeap;
	};

	Block *Heap::GetTrackingHead() const
	{
		return this->pBlkHead;
	}

}

// --- End of File ---
