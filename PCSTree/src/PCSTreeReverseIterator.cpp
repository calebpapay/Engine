

#include "PCSTreeReverseIterator.h"

namespace Azul
{
	PCSTreeReverseIterator::PCSTreeReverseIterator(PCSNode *rootNode)
	{
		assert(rootNode != nullptr);

		
		this->root = rootNode;

		this->prevNode = rootNode->GetReverse();
		this->current = this->prevNode;

	}

	PCSNode *PCSTreeReverseIterator::First()
	{
		
		return  this->prevNode;
	}

	PCSNode *PCSTreeReverseIterator::Next()
	{
		if (this->current == nullptr)
		{
			return this->current;
		}
		else if (this->current == this->root) {
			this->current = nullptr;
			return this->current;
		}
		else
		{
			this->current = current->GetReverse();
			return  this->current;
		}
	}

	bool PCSTreeReverseIterator::IsDone()
	{
		if (this->current == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	PCSNode *PCSTreeReverseIterator::Current()
	{
		return  this->current;
	}

}

// ---  End of File 
