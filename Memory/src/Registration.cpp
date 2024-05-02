#include "Registration.h"

namespace Azul
{
	Registration::Registration() {
		//this->set.reserve(ReserveSize);
	}

	bool Registration::Register(void* p)
	{
		this->set.insert(p);
		return true;
	}
	bool Registration::Find(void* p)
	{
		size_t isMyBlock = this->set.count(p);
		if (isMyBlock == 0) {
			
			return false;
		}
		else
		{
			return true;
		}
	}
	bool Registration::UnRegister(void* p)
	{
		this->set.erase(p);
		return true;
	}


}