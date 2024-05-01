#include "PCSTree.h"
#include "PCSNode.h"
#include "PCSTreeForwardIterator.h"

namespace Azul
{

	// constructor
	PCSTree::PCSTree()
	{
		this->pRoot = nullptr;
		this->mInfo.currNumLevels = 0;
		this->mInfo.currNumNodes = 0;
		this->mInfo.maxNumLevels = 0;
		this->mInfo.currNumLevels = 0;
	};

	// destructor
	PCSTree::~PCSTree()
	{

	};

	
	// get Root
	PCSNode * PCSTree::GetRoot() const
	{
		return this->pRoot;
	}


	// insert
	void PCSTree::Insert(PCSNode * const pInNode, PCSNode * const pParent)
	{
		assert(pInNode != nullptr);

		//adding to somewhere in the middle or end of tree
		if (this->pRoot != nullptr && pParent != nullptr)
		{
			//add to Iterator list
			if (pParent->GetForward() != nullptr) 
			{
				pParent->GetForward()->SetReverse(pInNode);
			}
			else //at end of Forward list, start of Reverse List
			{
				
				pRoot->SetReverse(pInNode);
			}
			pInNode->SetForward(pParent->GetForward());
			pParent->SetForward(pInNode);
			pInNode->SetReverse(pParent);

			//add to Tree
			PCSNode* pOldChild = pParent->GetChild();

			pParent->SetChild(pInNode);
			pInNode->SetNextSibling(pOldChild);
			pInNode->SetParent(pParent);

			if (pOldChild != nullptr)
			{
				pOldChild->SetPrevSibling(pInNode);
			}
			else
			{
				PCSNode* pCurrNode = pInNode;
				int levelCount = 1;
				while (pCurrNode->GetParent() != nullptr) 
				{
					levelCount++;
					pCurrNode = pCurrNode->GetParent();
				}
				if (mInfo.currNumLevels < levelCount) this->mInfo.currNumLevels = levelCount;
				if (mInfo.currNumLevels > mInfo.maxNumLevels) this->mInfo.maxNumLevels++;
			}
			this->mInfo.currNumNodes++;
			if (mInfo.currNumNodes > mInfo.maxNumNodes) this->mInfo.maxNumNodes++;
		}
		//no root currently, making the parent the Root
		else if (pParent != nullptr)
		{
			assert(pParent->GetChild() == nullptr); //Confirm new root has no current children

			//add to iterator list
			pParent->SetForward(pInNode);
			pInNode->SetReverse(pParent);

			//for accessing First in Rev iterator
			pParent->SetReverse(pInNode);

			//add to tree
			this->pRoot = pParent;
			pParent->SetChild(pInNode);
			pInNode->SetParent(pParent);
			this->mInfo.currNumLevels = 2;
			this->mInfo.currNumNodes = 2;
			this->mInfo.maxNumNodes = 2;
			this->mInfo.maxNumLevels = 2;
		}
		//no root currently, no parent provided, making pInNode the root
		else 
		{
			//(this->pRoot == nullptr && pParent == nullptr) 
			assert(pInNode->GetChild() == nullptr); //Confirm new root has no current children

			pInNode->SetForward(nullptr);
			pInNode->SetReverse(nullptr);

			this->pRoot = pInNode;
			this->mInfo.currNumLevels = 1;
			this->mInfo.currNumNodes = 1;
			this->mInfo.maxNumNodes = 1;
			this->mInfo.maxNumLevels = 1;
		}

		return;

	}

	//HORRIBLE NEEDS FIXING
	// Remove
	void PCSTree::Remove(PCSNode * const pInNode)
	{
		RemoveTree(pInNode);

		if (mInfo.currNumNodes == 0)
		{
			mInfo.currNumLevels = 0;
		}
		else 
		{
			this->mInfo.currNumLevels = RecursiveLevelNum(this->pRoot, 1, 1, false);
		}
	}

	void PCSTree::RemoveTree(PCSNode *node)
	{
		
		if(node->GetPrevSibling() != nullptr)
		{
			
			node->GetPrevSibling()->SetNextSibling(node->GetNextSibling());
			node->SetPrevSibling(nullptr);
		}
		else if(node->GetParent() != nullptr) //&& node->GetPrevSibling() == nullptr
		{
			node->GetParent()->SetChild(node->GetNextSibling());
		}

		if(node->GetNextSibling() != nullptr)
		{
			node->GetNextSibling()->SetPrevSibling(node->GetPrevSibling());
			node->SetNextSibling(nullptr);
		}
		//RemoveLinks to simulate this being root;
	

		node->SetParent(nullptr);
		while(node != nullptr)
		{
			PCSNode *onDeck = node->GetChild();

			node->SetChild(nullptr);

			if(onDeck == nullptr) //if child is nullptr, pick an onDeck -> back to parent, or on to NextSib if available.
			{ 
				//removing current node and selcting onDeck
				if(node->GetNextSibling() != nullptr) 
				{
					onDeck = node->GetNextSibling();
					assert(node->GetPrevSibling() == nullptr);
					node->GetNextSibling()->SetPrevSibling(nullptr); //nullptr
					node->SetNextSibling(nullptr);
				}
				else
				{
					onDeck = node->GetParent();

					assert(node->GetPrevSibling() == nullptr);
					assert(node->GetNextSibling() == nullptr);
					assert(node->GetChild() == nullptr);

				}
				node->SetParent(nullptr);

				if(node->GetForward() != nullptr)
				{
					node->GetForward()->SetReverse(node->GetReverse());
				}
				else
				{
					//assert(this->pRoot->GetReverse() == node);
					if(node->GetReverse() != this->pRoot)
					{
						this->pRoot->SetReverse(node->GetReverse());
					}
					else
					{
						this->pRoot->SetReverse(nullptr);
					}
				}

				if(node->GetReverse() != nullptr)
				{
					node->GetReverse()->SetForward(node->GetForward());
				}
				this->mInfo.currNumNodes--;
			}

			node = onDeck;
		}
	}

	

	int PCSTree::RecursiveLevelNum(PCSNode const * currNode, int level, int maxLevel, bool child) const {
		if (currNode == nullptr) {
			if (maxLevel < level) return level;
			else return maxLevel;
		}
		if (child == true) level++;
		maxLevel = RecursiveLevelNum(currNode->GetNextSibling(), level, maxLevel, false);


		maxLevel = RecursiveLevelNum(currNode->GetChild(), level, maxLevel, true);

		return maxLevel;
	}


	// get tree info
	void PCSTree::GetInfo(Info & info)
	{
		info.currNumLevels = this->mInfo.currNumLevels;
		info.currNumNodes = this->mInfo.currNumNodes;
		info.maxNumNodes = this->mInfo.maxNumNodes;
		info.maxNumLevels = this->mInfo.maxNumLevels;
	}

	void PCSTree::RecursivePrint(PCSNode const* currNode, int level, bool child) const {
		if (currNode == nullptr) {
			return;
		}
		if (child == true) level++;

		Trace::out("level: %d\n", level);
		currNode->PrintNode();
		
		RecursivePrint(currNode->GetNextSibling(), level, false);
		RecursivePrint(currNode->GetChild(), level, true);

		return;
	}

	void PCSTree::Print() const
	{
		RecursivePrint(this->pRoot, 1, false);
	}

}

// ---  End of File ---
