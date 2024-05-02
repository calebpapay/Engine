#ifndef MEMSAP_H
#define MEMSAP_H


#include "Mem.h"

namespace Azul
{

	//-------------------------------------------------------------------------
	// Namespace Weird thing
	//   Please declare your forward declarations INSIDE namespace
	//   Outside the namespace cause all kinds of hell
	//-------------------------------------------------------------------------

	// forward declaration
	class Heap;
	class Block;

	// Singleton
	class MemSAP : Mem
	{
	public:
		~MemSAP() = delete;
		// "Protected" Interface ---------------- (behind the scenes)
		
		static void sapUnRegister(void* b) {
			Mem::UnRegisterPtr(b);
		}
		static void sapRegister(void* b) {
			Mem::RegisterPtr(b);
		}



		// want private
		static void sapAddGlobalBlock(Block*& b) {
			Mem::AddGlobalBlock(b);
		}
		static void sapRemoveGlobalBlock(Block*& b) {
			Mem::RemoveGlobalBlock(b);
		}

	};

}

#endif 

// --- End of File ---
