// 2024. Caleb Papay


#ifndef HEAP_H
#define HEAP_H

#include "Mem.h"
#include "MemLink.h"

namespace Azul
{

	//-------------------------------------------------------------------------
	// Namespace Weird thing
	//   Please declare your forward declarations INSIDE namespace
	//   Outside the namespace cause all kinds of hell
	//-------------------------------------------------------------------------

	// Forward declaration
	class Block;

	// Heap class
	class Heap
	{
	public:
		// Constants 
		static const uint32_t NameLength = 64;
		static const uint32_t NameNumChar = (NameLength - 1);

		// -----------------------------------------------------------------
		// When declaring a fixed heap... need space for overhead
		//    initial size = numAlloc*sizeBlock+sizeof(Heap)+FreeHeapExtra
		// -----------------------------------------------------------------
		static const uint32_t FreeHeapExtra = 4 * 1024;

		// Heap Types
		enum class Type : size_t
		{
			NORMAL,
			FIXED
		};

		// Info structure
		struct Info
		{
			size_t    TotalSize;
			size_t	  PeakNumAlloc;                
			size_t	  CurrNumAlloc;
			size_t	  PeakBytesUsed;
			size_t	  CurrBytesUsed;
			char Name[Heap::NameLength];
		};

	public:
		Heap() = delete;
		Heap(const Heap&) = delete;
		Heap& operator = (const Heap&) = delete;
		~Heap() = default;
		
		void Destroy();

		// Public Interface (For Customers)
		void GetInfo(Info &info) const;

		// Tracking block 
		Block *GetTrackingHead() const;
		Heap::Type GetHeapType() const;

		// Overflow Heap
		void SetOverflowHeap(Heap *);
		Heap *GetOverflowHeap() const;

		// Needed for Testings (Not for Customers)
		Heap *DebugGetNext() const;
		Heap *DebugGetPrev() const;


	protected:

		void DebugSetNext(Heap* pHeap);

		void DebugSetPrev(Heap* pHeap);


		//Alloc
		void* Alloc(Azul::Mem::Align align, unsigned int inSize, const char* inName, size_t lineNum);
		void Dealloc(void* p);

		void initHeap(HANDLE winHeapHandle, size_t HeapSize, const char* const HeapName, Heap::Type hType, Mem* const mem);
		void postInitFixed(int numBlocks, int sizePerBlock);

	private:

		void privSetHeapName(const char* const hName);

		void AddHeapBlock(Block *&b);
		void RemoveHeapBlock(Block*& b);

		void AddToFixedHead(Block*& b);
		Block* GetFixedHead();

		MemLink   hLink;   // Heap Link
		// data ------------------------------------------------
		Block *pBlkHead;
		Type	mType;
		HANDLE  mWinHeapHandle;
		Info	mInfo;

	

		// null for Normal, used only in FixedHeap
		Block *pFixedFreeHead;

		// Overflow heap
		Heap *pOverflow;

		// Back link to the memory system
		Mem *pMem;

		Block* pFixStart;


	};

}

#endif

// --- End of File ---
