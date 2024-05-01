#include "PCSTreeForwardIterator.h"

namespace Azul
{
	PCSTreeForwardIterator::PCSTreeForwardIterator(PCSNode *rootNode)
	{
		this->root = rootNode;
		this->current = rootNode;
	}

	PCSNode *PCSTreeForwardIterator::First()
	{
		return  this->root;
	}

	PCSNode *PCSTreeForwardIterator::Next()
	{
		this->current = this->current->GetForward();
		return  this->current;
	}

	bool PCSTreeForwardIterator::IsDone()
	{
		if (this->current == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	PCSNode *PCSTreeForwardIterator::Current()
	{
		return  this->current;
	}

}

// ---  End of File 
