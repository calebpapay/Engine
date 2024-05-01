
#ifndef PCSTREE_H
#define PCSTREE_H

namespace Azul
{

	// forward declare
	class PCSNode;

	// PCSTree class 
	class PCSTree
	{
	public:
		// Simple data structure
		struct Info
		{
			int currNumNodes;
			int maxNumNodes;
			int currNumLevels;
			int maxNumLevels;
		};

	public:
		// constructor
		PCSTree();

		// copy constructor 
		PCSTree(const PCSTree &in) = delete;

		// assignment operator
		PCSTree &operator = (const PCSTree &in) = delete;

		// destructor
		~PCSTree();

		// get Root
		PCSNode *GetRoot() const;

		// insert
		void Insert(PCSNode *const pInNode, PCSNode *const pParent);

		// remove
		void Remove(PCSNode *const pInNode);

		// get info
		void GetInfo(Info &info);
		void Print() const;
		Info	mInfo;

	private:
		void RemoveTree(PCSNode* node);
		int RecursiveLevelNum(PCSNode const* currNode, int level, int maxLevel, bool child) const;
		void RecursivePrint(PCSNode const* currNode, int level, bool child) const;
		// Data
		
		PCSNode *pRoot;

	};

}

#endif

// ---  End of File ---
