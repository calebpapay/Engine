#include "PCSTree.h"
#include "PCSNode.h"

namespace Azul
{
	// constructor
	PCSNode::PCSNode()
	{
		this->pChild = nullptr;
		this->pParent = nullptr;
		this->pNextSibling = nullptr;
		this->pPrevSibling = nullptr;

		this->pForward = nullptr;
		this->pReverse = nullptr;

		memset(&this->pName[0], 0x0, PCSNode::NAME_SIZE);
	}

	// copy constructor
	PCSNode::PCSNode(const PCSNode& in)
		: pParent(in.GetParent()), pChild(in.GetChild()), pNextSibling(in.GetNextSibling()), pPrevSibling(in.GetPrevSibling())
	{
		memcpy(this->pName, in.pName, sizeof(pName));
	}

	// Specialize Constructor
	PCSNode::PCSNode(PCSNode* const pInParent, PCSNode* const pInChild, PCSNode* const pInNextSibling, PCSNode* const pInPrevSibling, const char* const pInName)
	{
		this->pChild = pInChild;
		this->pParent = pInParent;
		this->pNextSibling = pInNextSibling;
		this->pPrevSibling = pInPrevSibling;
		memset(&this->pName[0], 0x0, PCSNode::NAME_SIZE);
		memcpy(this->pName, pInName, sizeof(pName) - 1);
	}

	PCSNode::PCSNode(const char* const pInName)
	{
		this->pChild = nullptr;
		this->pParent = nullptr;
		this->pNextSibling = nullptr;
		this->pPrevSibling = nullptr;
		memset(&this->pName[0], 0x0, PCSNode::NAME_SIZE);
		memcpy(this->pName, pInName, sizeof(pName) - 1);
	}

	// destructor
	PCSNode::~PCSNode()
	{


	}

	// assignment operator
	PCSNode& PCSNode::operator = (const PCSNode& in)
	{
		this->pChild = in.pChild;
		this->pParent = in.pParent;
		this->pNextSibling = in.pNextSibling;
		this->pPrevSibling = in.pPrevSibling;

		memcpy(this->pName, in.pName, sizeof(pName) - 1);
		return *(PCSNode*)this;
	}

	void PCSNode::SetParent(PCSNode* const pIn)
	{
		this->pParent = pIn;
	}

	void PCSNode::SetChild(PCSNode* const pIn)
	{
		this->pChild = pIn;

	}

	void PCSNode::SetNextSibling(PCSNode* const pIn)
	{
		this->pNextSibling = pIn;
	}

	void PCSNode::SetPrevSibling(PCSNode* const pIn)
	{
		this->pPrevSibling = pIn;
	}

	PCSNode* PCSNode::GetParent(void) const
	{
		return (PCSNode*)this->pParent;
	}

	PCSNode* PCSNode::GetChild(void) const
	{
		return (PCSNode*)this->pChild;
	}

	PCSNode* PCSNode::GetNextSibling(void) const
	{
		return (PCSNode*)this->pNextSibling;
	}

	PCSNode* PCSNode::GetPrevSibling(void) const
	{
		return (PCSNode*)this->pPrevSibling;
	}

	PCSNode::Code PCSNode::SetName(const char* const pInName)
	{
		if (pInName == nullptr) return (Code)1;

		memcpy(this->pName, pInName, sizeof(pName) - 1);
		return (Code)0;
	}

	PCSNode::Code PCSNode::GetName(char* const pOutBuffer, unsigned int sizeOutBuffer) const
	{
		if (pOutBuffer == nullptr) return (Code)1;
		memcpy(pOutBuffer, this->pName, sizeOutBuffer);
		pOutBuffer[sizeOutBuffer - 1] = '\0';

		return (Code)0;
	}

	void PCSNode::PrintNode() const
	{
		char buff[PCSNode::NAME_SIZE];

		Trace::out("	Name: %s\n", this->pName);
		Trace::out("	addr: 0x%X\n", this);
		if (this->pParent != nullptr)
		{
			this->pParent->GetName(buff, PCSNode::NAME_SIZE);
			Trace::out("  parent: %s (0x%X)\n", buff, this->pParent);
		}
		else {
			Trace::out("  parent: null\n");
		}
		if (this->pChild != nullptr)
		{
			this->pChild->GetName(buff, PCSNode::NAME_SIZE);
			Trace::out("   child: %s (0x%X)\n", buff, this->pChild);
		}
		else {
			Trace::out("   child: null\n");
		}
		if (this->pNextSibling != nullptr)
		{
			this->pNextSibling->GetName(buff, PCSNode::NAME_SIZE);
			Trace::out(" nextSib: %s (0x%X)\n", buff, this->pNextSibling);
		}
		else {
			Trace::out(" nextSib: null\n");
		}
		if (this->pPrevSibling != nullptr)
		{
			this->pPrevSibling->GetName(buff, PCSNode::NAME_SIZE);
			Trace::out(" prevSib: %s (0x%X)\n", buff, this->pPrevSibling);
		}
		else {
			Trace::out(" prevSib: null\n");
		}
		Trace::out("\n");
	}

	void PCSNode::PrintChildren() const
	{
		Trace::out("\nPrinting %s Children...\n", this->pName);

		if (this->pChild == nullptr) {
			Trace::out("***NO CHILDREN FOR NODE***\n");
			return;
		}

		char buff[PCSNode::NAME_SIZE];

		PCSNode* pCurrNode = this->GetChild();

		while (pCurrNode != nullptr) {
			pCurrNode->GetName(buff, PCSNode::NAME_SIZE);
			Trace::out("  child: %s (0x%X)\n", buff, pCurrNode);
			pCurrNode = pCurrNode->GetNextSibling();
		}
		Trace::out("\n");
		return;

	}


	void PCSNode::PrintSiblings() const
	{

		Trace::out("\nPrinting %s Sibilings...\n", this->pName);

		if (this->pParent == nullptr) {
			Trace::out("    sib: %s (0x%X)\n", this->pName, this);

			return;//root
		}
		char buff[PCSNode::NAME_SIZE];

		PCSNode* pCurrNode = this->pParent->GetChild();

		while (pCurrNode != nullptr) {
			pCurrNode->GetName(buff, PCSNode::NAME_SIZE);
			Trace::out("    sib: %s (0x%X)\n", buff, pCurrNode);
			pCurrNode = pCurrNode->GetNextSibling();
		}
		Trace::out("\n");
		return;
	}

	int PCSNode::GetNumSiblings() const
	{
		if (this->pParent == nullptr) return 1;//root

		PCSNode* pCurrNode = this->pParent->GetChild();
		int numSibs = 0;
		while (pCurrNode != nullptr) {
			numSibs++;
			pCurrNode = pCurrNode->GetNextSibling();
		}
		return numSibs;
	}

	int PCSNode::GetNumChildren() const
	{
		if (this->pChild == nullptr) return 0;
		return this->pChild->GetNumSiblings();
	}

	void PCSNode::SetForward(PCSNode* const pIn)
	{
		this->pForward = pIn;
	}
	void PCSNode::SetReverse(PCSNode* const pIn)
	{
		this->pReverse = pIn;
	}

	PCSNode* PCSNode::GetForward(void) const
	{
		return this->pForward;
	}
	PCSNode* PCSNode::GetReverse(void) const
	{
		return this->pReverse;
	}
}

// ---  End of File ---
