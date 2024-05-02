// 2024. Caleb Papay

#ifndef DLINK_H
#define DLINK_H

namespace Azul
{
	class MemLink
	{
	public:
		// Big Four
		MemLink();
		MemLink(const MemLink &);
		MemLink &operator = (const MemLink &);
		~MemLink();

		void Reset();

	public:
		// data:------------------------
		MemLink *pNext;
		MemLink *pPrev;
	};

}

#endif

// ---  End of File ---------------
