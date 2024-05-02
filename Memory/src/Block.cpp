//---------------------------------------------------------------
// 2024. Caleb Papay
//---------------------------------------------------------------

#include "Block.h"
#include "Mem.h"

namespace Azul
{
	void* Block::initBlock(Heap* h, int align, unsigned int inSize, const char* inName, size_t lineNum) {
		
		this->mAllocSize = inSize;

		const char* file = inName;
		while (*inName) {
			if (*inName++ == '\\') {
				file = inName;
			}
		}
		this->privSetBlockName(file);
		
		int mask0 = align - 1;
		void* s = (void*)this;

		this->mLineNum = lineNum;
		this->bLink.pNext = nullptr;
		this->gLink.pNext = nullptr;
		this->bLink.pPrev = nullptr;
		this->gLink.pPrev = nullptr;
		this->pHeap = h;

		void* p = (void*)((Block*)s + 1);
		void* oc = (void*)((char*)p + mask0);
		void* ps = (void*)(((int)oc) & (~mask0)); //hacky, can use int becuase gurantee 4 byte align
		this->pUserBlock = (Block*)ps;

		//get location for secret
		void* secret = (void*)((char*)pUserBlock - 4);
		Block** realSecret = (Block**)secret;
		*realSecret = this;

		Mem::Info mem_Info;
		Mem::GetInfo(mem_Info);
		this->mAllocIndex = ++mem_Info.CurrAllocIndex;
		int x = sizeof(*this);
		assert(x == 104);

		return pUserBlock;
	}

	void* Block::initUsedFixed(Heap* h, unsigned int inSize)
	{
		this->mAllocSize = inSize;
		void* s = (void*)this;
		this->mLineNum = 0;
		this->bLink.pNext = nullptr;
		this->gLink.pNext = nullptr;
		this->bLink.pPrev = nullptr;
		this->gLink.pPrev = nullptr;
		this->pHeap = h;
		
		this->pUserBlock = (void*)((Block*)s + 1);

		//get location for secret
		void* secret = (void*)((char*)pUserBlock - 4);
		Block** realSecret = (Block**)secret;
		*realSecret = this;

		return (void*)this->pUserBlock;
	}


	void* Block::updateUsedFixed( const char* inName, size_t lineNum)
	{
		const char* file = inName;
		while (*inName) {
			if (*inName++ == '\\') {
				file = inName;
			}
		}
		this->privSetBlockName(file);
	
		this->mLineNum = lineNum;
		this->bLink.pNext = nullptr;
		this->gLink.pNext = nullptr;
		this->bLink.pPrev = nullptr;
		this->gLink.pPrev = nullptr;

		Mem::Info mem_Info;
		Mem::GetInfo(mem_Info);
		this->mAllocIndex = ++mem_Info.CurrAllocIndex;

		return (void*)this->pUserBlock;
	}

	void Block::privSetBlockName(const char* const hName)
	{
		// Next couple lines, have safety to only copy a maximum of allowed characters
		assert(hName);

		unsigned int len = strlen(hName);

		//assert(len < NameNumChar);

		if (len > NameNumChar)
		{
			len = NameNumChar;
		}

		memset(this->mFileName, 0x0, NameLength);
		memcpy(this->mFileName, hName, len);
	}

	Block *Block::GetHeapNext() const
	{
		return (Block *)this->bLink.pNext;
	}

	Block *Block::GetHeapPrev() const
	{
		return (Block *)this->bLink.pPrev;
	}

	Block *Block::GetGlobalNext() const
	{
		return (Block *)this->gLink.pNext;
	}

	Block *Block::GetGlobalPrev() const
	{
		return (Block *)this->gLink.pPrev;
	}

	const char *Block::GetFileName() const
	{
		return this->mFileName;
	}

	size_t Block::GetLineNum() const
	{
		return this->mLineNum;
	}

	size_t Block::GetAllocIndex() const
	{
		return this->mAllocIndex;
	}

	size_t Block::GetAllocSize() const
	{
		return this->mAllocSize;
	}

	Heap *Block::GetHeap() const
	{
		return this->pHeap;
	}

	void Block::SetHeapNext(Block* pBlock) 
	{
		this->bLink.pNext = (MemLink*)pBlock;
	}

	void Block::SetHeapPrev(Block* pBlock)
	{
		this->bLink.pPrev = (MemLink*)pBlock;
	}

	void Block::SetGlobalNext(Block* pBlock)
	{
		this->gLink.pNext = (MemLink*)pBlock;
	}

	void Block::SetGlobalPrev(Block* pBlock)
	{
		this->gLink.pPrev = (MemLink*)pBlock;
	}

}

// --- End of File ---