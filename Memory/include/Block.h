//------------------
// 2024. Caleb Papay
//------------------

#ifndef BLOCK_H
#define BLOCK_H

#include "MemLink.h"

namespace Azul
{
	class Heap;  // forward declare

	//-------------------------------------------------------------------------
	// Weird thing
	//   Please declare your forward declarations INSIDE namespace
	//   Outside the namespace cause all kinds of hell
	//-------------------------------------------------------------------------

	class Block
	{
	public:
		// defines for the heap name length
		static const uint32_t NameLength = 64;
		static const uint32_t NameNumChar = (Block::NameLength - 1);

	public:
		//need to make private someway
		void* initBlock(Heap* h, int align, unsigned int inSize, const char* inName, size_t lineNum);
		// Public methods
		Block *GetHeapNext() const;
		Block *GetHeapPrev() const;
		Block *GetGlobalNext() const;
		Block *GetGlobalPrev() const;
		const char *GetFileName() const;
		size_t GetLineNum() const;
		size_t GetAllocIndex() const;
		size_t GetAllocSize() const;
		Heap *GetHeap() const;

	protected:
		void* initUsedFixed(Heap* h, unsigned int inSize);

		void* updateUsedFixed( const char* inName, size_t lineNum);

		void SetHeapNext(Block* pBlock);

		void SetHeapPrev(Block* pBlock);

		void SetGlobalNext(Block* pBlock);

		void SetGlobalPrev(Block* pBlock);

	private:
		void privSetBlockName(const char* const hName);
		// Add tracking links 
		MemLink bLink;   // Block links
		MemLink gLink;   // Global links

		// stats 
		Heap *pHeap;
		void *pUserBlock;

		size_t	mLineNum;
		size_t	mAllocIndex;
		size_t	mAllocSize;

		char	mFileName[Block::NameLength];

		// back pointer
		Block **pSecret;   // back pointer to the top of the trackingblock
	};

}

#endif

// ---  End of File ---