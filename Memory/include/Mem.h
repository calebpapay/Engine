// 2024. Caleb Papay

#ifndef MEM_H
#define MEM_H

//#include <unordered_set>
#include "Registration.h"

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
	class Mem
	{
	public:

		// Constants for the library
		static const uint32_t MAJOR_VERSION = 6;
		static const uint32_t MINOR_VERSION = 0;

		// alignment 
		enum class Align : uint32_t
		{
			Byte_4,
			Byte_8,
			Byte_16,
			Byte_32,
			Byte_64,
			Byte_128,
			Byte_256,
			Default = Byte_4
		};

		// Return codes
		enum class Code : uint32_t
		{
			OK,
			ERROR_Heap_Create,
			ERROR_Illegal_Heap,
			ERROR_Mem_Not_Initialized,
			ERROR_Invalid_Addr,
		};

		// info structure
		struct Info
		{
			size_t CurrAllocIndex;
			size_t PeakHeapCount;
			size_t CurrHeapCount;
			size_t PeakNumAlloc;
			size_t CurrNumAlloc;
			size_t PeakBytesUsed;
			size_t CurrBytesUsed;
		};

	public:
		// Public Interface ---------------- (for the customers)

		// Initialize the mem system
		static Code Create();
		static Code Destroy();

		// Create a Heap from the heap system
		static Code NormalHeap(Heap *&newHeap, unsigned int heapSize, const char *const Name);
		static Code FixedHeap(Heap *&newHeap, unsigned int numBlocks, int sizePerBlock, const char *const Name);

		// Remove a Heap from the heap system
		static Code RemoveHeap(Heap *inHeap);

		// Information
		static Code GetInfo(Info &info);
		static Code GetHeapByAddr(Heap *&pHeap, void *p);


		// Needed for Testings (Not for Customers)
		static Block* DebugGetGlobalTrackingHead(void);
		static Heap *DebugGetHeapHead(void);




		//static void Register(void *b);
		// -----------------------------------------------------------------------------------
		// Add extra data or methods below this line
		// -----------------------------------------------------------------------------------
	protected:

		static void RegisterPtr(void* b);
		static void UnRegisterPtr(void* b);


		// want private
		static void AddGlobalBlock(Block*& b);
		static void RemoveGlobalBlock(Block*& b);
	

	private:
		~Mem();

		static void AddHeap(Heap*& inHeap);

		static Mem* privInst(void);

		void privInitialize(void);

		// data -----------------------------------------
		Heap *poHead;
		Block *pGlobalHead;
		
		Info	      mInfo;
		bool	      mInitialized = false;

		Registration* addressBook;

	};

}

#endif 

// --- End of File ---
