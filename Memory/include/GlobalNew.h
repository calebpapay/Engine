// 2024. Caleb Papay


#ifndef GLOBAL_NEW_H
#define GLOBAL_NEW_H

#include "Mem.h"
#include "Heap.h"


//    Namespaces are not allowed for new/delete


	// For Normal Heap
	void *operator new(size_t inSize, Azul::Heap *const pHeap, Azul::Mem::Align align, const char *inName, size_t lineNum);
	void operator delete(void *p, Azul::Heap *const pHeap, Azul::Mem::Align align, const char *inName, size_t lineNum);

	void *operator new[](size_t inSize, Azul::Heap *const pHeap, Azul::Mem::Align align, const char *inName, size_t lineNum);
	void operator delete[](void *p, Azul::Heap *const pHeap, Azul::Mem::Align align, const char *inName, size_t lineNum);

	// For Fixed Heap
	void *operator new(size_t inSize, Azul::Heap *const pHeap, const char *inName, size_t lineNum);
	void operator delete(void *p, Azul::Heap *const pHeap, const char *inName, size_t lineNum);


	void *operator new(size_t inSize);
	void operator delete(void *p);

	void *operator new[](size_t inSize);
	void operator delete[](void *p);

#endif

// --- End of File ---
