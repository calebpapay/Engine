#ifndef RESISTRATION_H
#define RESISTRATION_H
#include <unordered_set>

namespace Azul
{
	class Registration
	{
	public:
		static const unsigned int ReserveSize = 256;

		Registration();
		Registration(const Registration&) = delete;
		Registration& operator = (const Registration&) = delete;
		~Registration() = default;

		bool Register(void* p);
		bool Find(void* p);
		bool UnRegister(void* p);

	private:
		std::unordered_set<void*> set;
	};
}
#endif