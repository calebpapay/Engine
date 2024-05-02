// 2024. Caleb Papay

#include "Mem.h"
#include "GlobalNew.h"
#include "HeapSAP.h"

//   Don't use namespace here...
//   new/delete isn't allowed namespace

// --------------------------------------------
// For Normal Heap
// --------------------------------------------
	void *operator new(size_t inSize, Azul::Heap *const pHeap, Azul::Mem::Align align, const char *inName, size_t lineNum)
	{

		void *p = ((Azul::HeapSAP *)pHeap)->sapAlloc(align, (unsigned int)inSize, inName, lineNum);
		return p;
	}

	void operator delete(void *p, Azul::Heap *const pHeap, Azul::Mem::Align align, const char *inName, size_t lineNum)
	{
		// -----------------------------------------
		// You don't need to implement this... 
		// its here to shut up compiler warnings
		// just this function
		//------------------------------------------
		AZUL_REPLACE_ME(p);
		AZUL_REPLACE_ME(pHeap);
		AZUL_REPLACE_ME(align);
		AZUL_REPLACE_ME(inName);
		AZUL_REPLACE_ME(lineNum);
	}

	void *operator new[](size_t inSize, Azul::Heap *const pHeap, Azul::Mem::Align align, const char *inName, size_t lineNum)
	{

		void *p = ((Azul::HeapSAP *)pHeap)->sapAlloc(align, (unsigned int)inSize, inName, lineNum);
		return p;
	}

	void operator delete[](void *p, Azul::Heap *const pHeap, Azul::Mem::Align align, const char *inName, size_t lineNum)
	{
		AZUL_REPLACE_ME(p);
		AZUL_REPLACE_ME(pHeap);
		AZUL_REPLACE_ME(align);
		AZUL_REPLACE_ME(inName);
		AZUL_REPLACE_ME(lineNum);
	}

	// --------------------------------------------
	// For Fixed Heap
	// --------------------------------------------

	void *operator new(size_t inSize, Azul::Heap *const pHeap, const char *inName, size_t lineNum)
	{
		void *p = ((Azul::HeapSAP *)pHeap)->sapAlloc(Azul::Mem::Align::Byte_4, (unsigned int)inSize, inName, lineNum);
		return p;
	}

	void operator delete(void *p, Azul::Heap *const pHeap, const char *inName, size_t lineNum)
	{

		//here to shut up compiler warnings
		AZUL_REPLACE_ME(p);
		AZUL_REPLACE_ME(pHeap);
		AZUL_REPLACE_ME(inName);
		AZUL_REPLACE_ME(lineNum);
	}

	// --------------------------------------------
	// For Global Standard new/delete
	// --------------------------------------------

	void *operator new(size_t inSize)
	{
		void *p = malloc(inSize);
		return p;
	}

	void operator delete(void *p)
	{
		Azul::Heap *pHeap;
		Azul::Mem::GetHeapByAddr(pHeap, p);

		if(pHeap != nullptr)
		{
			((Azul::HeapSAP *)pHeap)->sapDealloc(p);

		}
		else
		{
			free(p);
		}
	}

	void *operator new[](size_t inSize)
	{
		void *p = malloc(inSize);
		return p;
	}

	void operator delete[](void *p)
	{
		Azul::Heap *pHeap;
		Azul::Mem::GetHeapByAddr(pHeap, p);

		if(pHeap != nullptr)
		{
			((Azul::HeapSAP *)pHeap)->sapDealloc(p);
		}
		else
		{
			free(p);
		}
	}

// --- End of File ---
