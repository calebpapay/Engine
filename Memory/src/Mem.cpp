//---------------------------------------------------------------
// 2024. Caleb Papay
//---------------------------------------------------------------

#include "Mem.h"
#include "Block.h"
#include "Registration.h"
#include "Heap.h"
#include "HeapSAP.h"
#include "BlockSAP.h"

namespace Azul
{
	// Create the heap.
	Mem::Code Mem::NormalHeap(Heap*& newHeap, unsigned int heapSize, const char* const Name)
	{
		if (privInst()->mInitialized == false) 
		{
			newHeap = nullptr;
			return  Mem::Code::ERROR_Mem_Not_Initialized;
		}
		//Creating Heap
		HANDLE heapWinHandle = HeapCreate(0, heapSize + sizeof(Heap), 0);

		//allocating room for header
		void* s = HeapAlloc(heapWinHandle, 0, sizeof(Heap));

		//initializing Heap header
		newHeap = (Heap*)s;
		HeapSAP* SAP = (HeapSAP*)newHeap;
		SAP->sapInitHeap(heapWinHandle, heapSize, Name, Heap::Type::NORMAL, privInst());

		//put Heap on list
		Mem::AddHeap(newHeap);
		
		return Mem::Code::OK;
	}

	Mem::Code Mem::FixedHeap(Heap*& newHeap, unsigned int numBlocks, int sizePerBlock, const char* const Name)
	{
		if (privInst()->mInitialized == false)
		{
			newHeap = nullptr;
			return  Mem::Code::ERROR_Mem_Not_Initialized;
		}
		unsigned int heapSize = ( numBlocks * (sizePerBlock + sizeof(Block)) ) ;
		//Creating Heap
		HANDLE heapWinHandle = HeapCreate(0, heapSize + sizeof(Heap) + Heap::FreeHeapExtra, 0);

		//allocating room for header
		void* s = HeapAlloc(heapWinHandle, 0, sizeof(Heap)+4);

		//initializing Heap header
		newHeap = (Heap*)s;
		HeapSAP* SAP = (HeapSAP*)newHeap;

		SAP->sapInitHeap(heapWinHandle, heapSize, Name, Heap::Type::FIXED, privInst());
		SAP->sapPostInitFixed(numBlocks, sizePerBlock);

		Mem::AddHeap(newHeap);

		return Mem::Code::OK;
	}

	// Initialize the memory system  (Public method)
	Mem::Code Mem::Create(void)
	{
		privInst()->privInitialize();

		return Mem::Code::OK;
	}

	// Get the instance (singleton)
	Mem* Mem::privInst()
	{
		static Mem instance;
		return &instance;
	}


	// This is where the real work happens
	void Mem::privInitialize(void)
	{
		this->poHead = nullptr;
		this->pGlobalHead = nullptr;
		this->mInfo.CurrAllocIndex = 0;
		this->mInfo.PeakHeapCount = 0;
		this->mInfo.CurrHeapCount = 0;
		this->mInfo.PeakNumAlloc = 0;
		this->mInfo.CurrNumAlloc = 0;
		this->mInfo.PeakBytesUsed = 0;
		this->mInfo.CurrBytesUsed = 0;

		this->mInitialized = true;

		this->addressBook = new Registration();
	}

	Mem::Code Mem::Destroy(void)
	{
		if (privInst()->mInitialized == false) {
			return  Mem::Code::ERROR_Mem_Not_Initialized;
		}
		Mem* trash = privInst();
		trash->mInitialized = false;
		trash->poHead = nullptr;
		trash->pGlobalHead = nullptr;
		trash->mInfo.CurrAllocIndex = 0;
		trash->mInfo.PeakHeapCount = 0;
		trash->mInfo.CurrHeapCount = 0;
		trash->mInfo.PeakNumAlloc = 0;
		trash->mInfo.CurrNumAlloc = 0;
		trash->mInfo.PeakBytesUsed = 0;
		trash->mInfo.CurrBytesUsed = 0;
		/*trash = nullptr;*/
		//trash->set.clear();
		delete trash->addressBook;
		return  Mem::Code::OK;
	}


	Mem::~Mem() 
	{

		Mem* trash = privInst();
		trash->mInitialized = false;
		trash->poHead = nullptr;
		trash->pGlobalHead = nullptr;
		trash->mInfo.CurrAllocIndex = 0;
		trash->mInfo.PeakHeapCount = 0;
		trash->mInfo.CurrHeapCount = 0;
		trash->mInfo.PeakNumAlloc = 0;
		trash->mInfo.CurrNumAlloc = 0;
		trash->mInfo.PeakBytesUsed = 0;
		trash->mInfo.CurrBytesUsed = 0;

	}

	Mem::Code Mem::GetInfo(Mem::Info& retInfo)
	{
		if (privInst()->mInitialized == false) {
			return  Mem::Code::ERROR_Mem_Not_Initialized;
		}
		if (privInst()->mInfo.PeakHeapCount < privInst()->mInfo.CurrHeapCount) {
			privInst()->mInfo.PeakHeapCount = privInst()->mInfo.CurrHeapCount;
		}
		retInfo = privInst()->mInfo;
		return  Mem::Code::OK;
	}

	Heap* Mem::DebugGetHeapHead()
	{
		return privInst()->poHead;
	}

	Block* Mem::DebugGetGlobalTrackingHead()
	{
		return privInst()->pGlobalHead;
	}

	void Mem::AddHeap(Heap*& pInHeap)
	{
		Heap* oldHead = privInst()->poHead;
		
		if (oldHead != nullptr) {
			((HeapSAP*)privInst()->poHead)->sapSetPrev(pInHeap);
		}
		privInst()->poHead = pInHeap;
		((HeapSAP*)pInHeap)->sapSetNext(oldHead);
		privInst()->mInfo.CurrHeapCount++;
		privInst()->addressBook->Register((void*)pInHeap);
	}

	Mem::Code Mem::RemoveHeap(Heap* pInHeap)
	{
		if (privInst()->mInitialized == false) {
			return  Mem::Code::ERROR_Mem_Not_Initialized;
		}

		bool isMyHeap = privInst()->addressBook->Find((void*)pInHeap);

		if (pInHeap == nullptr || !isMyHeap) {
			return  Mem::Code::ERROR_Illegal_Heap;
		}
		Heap::Info heap_Info;
		pInHeap->GetInfo(heap_Info);
		privInst()->mInfo.CurrBytesUsed -= heap_Info.CurrBytesUsed;

		privInst()->mInfo.CurrNumAlloc -= heap_Info.CurrNumAlloc;


		if (pInHeap->DebugGetNext() == nullptr && pInHeap->DebugGetPrev() == nullptr) {
			privInst()->poHead = nullptr;
			pInHeap->Destroy();
		}
		else if (pInHeap->DebugGetPrev() == nullptr) {
			//set next's prev to null
			((HeapSAP*)pInHeap->DebugGetNext())->sapSetPrev(nullptr);

			privInst()->poHead = pInHeap->DebugGetNext();

			//remove link to next
			((HeapSAP*)pInHeap)->sapSetNext(nullptr);
			pInHeap->Destroy();
		}
		else if (pInHeap->DebugGetNext() == nullptr) {
			//set prev's next to null
			((HeapSAP*)pInHeap->DebugGetPrev())->sapSetNext(nullptr);
			//remove link to prev
			((HeapSAP*)pInHeap)->sapSetPrev(nullptr);
			pInHeap->Destroy();
		}
		else {
			((HeapSAP*)pInHeap->DebugGetPrev())->sapSetNext(pInHeap->DebugGetNext());
			((HeapSAP*)pInHeap->DebugGetNext())->sapSetPrev(pInHeap->DebugGetPrev());

			((HeapSAP*)pInHeap)->sapSetPrev(nullptr);
			((HeapSAP*)pInHeap)->sapSetNext(nullptr);

			pInHeap->Destroy();
		}
		privInst()->mInfo.CurrHeapCount--;

		return Mem::Code::OK;
	}

	Mem::Code Mem::GetHeapByAddr(Heap*& pHeap, void* p)
	{
		if (privInst()->mInitialized == false) {
			pHeap = nullptr;
			return  Mem::Code::ERROR_Mem_Not_Initialized;
		}

		//bool isMine = privInst()->addressBook->Find((void*)p);
			bool isMyBlock = privInst()->addressBook->Find(p);

		
		if (!isMyBlock) {
			pHeap = nullptr;
			return  Mem::Code::ERROR_Invalid_Addr;
		}
		else{
			void* secret = (void*)((char*)p - 4);
			Block** realBlock = (Block**)secret;
			Block* pBlock = *realBlock;
			pHeap = pBlock->GetHeap();
		}
		return Mem::Code::OK;
	}

	void Mem::UnRegisterPtr(void* b) {
		privInst()->addressBook->Register(b);
	}
	void Mem::RegisterPtr(void* b) {
		privInst()->addressBook->Register(b);
	}


	void Mem::AddGlobalBlock(Block*& b)
	{
		privInst()->mInfo.CurrBytesUsed += b->GetAllocSize();
		privInst()->mInfo.CurrNumAlloc++;
		privInst()->mInfo.CurrAllocIndex++;

		if (privInst()->mInfo.PeakNumAlloc < privInst()->mInfo.CurrNumAlloc)
		{
			privInst()->mInfo.PeakNumAlloc = privInst()->mInfo.CurrNumAlloc;
		}
		if (privInst()->mInfo.PeakBytesUsed < privInst()->mInfo.CurrBytesUsed) 
		{
			privInst()->mInfo.PeakBytesUsed = privInst()->mInfo.CurrBytesUsed;
		}


		if (privInst()->pGlobalHead == nullptr) {
			privInst()->pGlobalHead = b;
		}
		else {
			Block* oldHead = privInst()->pGlobalHead;
			privInst()->pGlobalHead = b;
			((BlockSAP*)b)->sapSetGlobalNext(oldHead);
			((BlockSAP*)oldHead)->sapSetGlobalPrev(b);
		}
	}

	void Mem::RemoveGlobalBlock(Block*& b)
	{
		privInst()->mInfo.CurrBytesUsed -= b->GetAllocSize();
		privInst()->mInfo.CurrNumAlloc--;

		if (b == privInst()->pGlobalHead && b->GetGlobalNext() == nullptr)
		{
			privInst()->pGlobalHead = nullptr;
		}
		else if (b == privInst()->pGlobalHead)
		{
			privInst()->pGlobalHead = b->GetGlobalNext();
			((BlockSAP*)privInst()->pGlobalHead)->sapSetGlobalPrev(nullptr);
			((BlockSAP*)b)->sapSetGlobalNext(nullptr);
		}
		else if (b->GetGlobalNext() != nullptr)
		{
			((BlockSAP*)b->GetGlobalPrev())->sapSetGlobalNext(b->GetGlobalNext());
			((BlockSAP*)b->GetGlobalNext())->sapSetGlobalPrev(b->GetGlobalPrev());

			((BlockSAP*)b)->sapSetGlobalNext(nullptr);
			((BlockSAP*)b)->sapSetGlobalPrev(nullptr);
		}
		else
		{
			((BlockSAP*)b->GetGlobalPrev())->sapSetGlobalNext(nullptr);
			((BlockSAP*)b)->sapSetGlobalPrev(nullptr);
		}
	}




}

// --- End of File ---
