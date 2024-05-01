//2024. Caleb Papay

#include "MeshNull.h"
#include "GraphicsObject_Null.h"
#include "ShaderObject_Null.h"
#include "GameObject.h"
#include "GameObjectRigid.h"
#include "GameObjectMan.h"
#include "PCSTreeForwardIterator.h"
#include "MeshNodeMan.h"
#include "ShaderObjectNodeMan.h"

namespace Azul
{


	void GameObjectMan::Add(GameObject *pObj, GameObject *pParent)
	{
		assert(pObj);
		assert(pParent);

		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();

		// insert object to root
		pGOM->poRootTree->Insert(pObj, pParent);
	}

	PCSTree *GameObjectMan::GetPCSTree()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		return pGOM->poRootTree;
	}

	GameObject *GameObjectMan::GetRoot()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		//GameObject *pGameObj = (GameObject *)pGOM->poRootTree->GetRoot();
		//assert(pGameObj);

		return pGOM->pBatch;
	}

	GameObject *GameObjectMan::GetRootTransparent()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		//GameObject *pGameObj = (GameObject *)pGOM->poRootTree->GetRoot();
		//assert(pGameObj);

		return pGOM->pBatchTransparent;
	}



	void GameObjectMan::Create()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);
		AZUL_UNUSED_VAR(pGOM);
	}

	void GameObjectMan::Destroy()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSTree *pTree = pGOM->poRootTree;
		PCSNode *pNode = nullptr;

		PCSTreeForwardIterator pForIter(pTree->GetRoot());
		pNode = pForIter.First();
		PCSNode *pTmp = nullptr;

		// todo: create an Erase() like SE456
		while(!pForIter.IsDone())
		{
			pTmp = pForIter.Current();

			pNode = pForIter.Next();
			delete pTmp;
		}
	}

	void GameObjectMan::Update(AnimTime currentTime)
	{
		//Trace::out("\n");
		//Trace::out("------ GameObjectMan::Update() -----------------\n");
		//Trace::out("\n");

		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSNode *pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pIt(pRootNode);

		GameObject *pGameObj = nullptr;

		for(pIt.First(); !pIt.IsDone(); pIt.Next())
		{
			pGameObj = (GameObject *)pIt.Current();
			//pGameObj->PrintNode();
			pGameObj->Update(currentTime);
		}
	}

	void GameObjectMan::Draw()
	{
		//	Trace::out("\n");
		//	Trace::out("--- GameObjectMan::Draw() ----\n");
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSNode *pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pIt(pRootNode);

		GameObject *pGameObj = nullptr;

		for(pIt.First(); !pIt.IsDone(); pIt.Next())
		{
			pGameObj = (GameObject *)pIt.Current();
			//	pGameObj->PrintNode();
			pGameObj->Draw();
		}
	}


	void GameObjectMan::Remove(GameObject *pRootRemove)
	{
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		pGOM->privRemove(pRootRemove);
	}


	void GameObjectMan::privRemove(PCSNode *const pInNode)
	{
		if(pInNode->GetNextSibling() != nullptr)
		{
			pInNode->GetNextSibling()->SetPrevSibling(pInNode->GetPrevSibling());
		}
		if(pInNode->GetPrevSibling() != nullptr)
		{
			pInNode->GetPrevSibling()->SetNextSibling(pInNode->GetNextSibling());
		}
		else if(pInNode->GetParent() != nullptr)
		{
			pInNode->GetParent()->SetChild(pInNode->GetNextSibling());
		}
		pInNode->SetParent(nullptr);
		pInNode->SetNextSibling(nullptr);
		pInNode->SetPrevSibling(nullptr);

		assert(pInNode->GetParent() == nullptr);
		assert(pInNode->GetNextSibling() == nullptr);
		assert(pInNode->GetPrevSibling() == nullptr);
		this->poRootTree->mInfo.currNumNodes--;
		PCSNode *currNode = pInNode->GetChild();
		//if(currNode)
		//{
		//	currNode->GetParent()->SetChild(nullptr);
		//	//currNode->SetParent(nullptr);
		//	//delete pInNode;
		//}
		PCSNode *lastNode = currNode;
		while(currNode != nullptr)
		{
			//PCSNode *currParent = currNode->GetParent(); //wont be nullptr unless we delete;
			currNode->GetParent()->SetChild(nullptr);
			currNode->SetParent(nullptr);

			PCSNode *currChild = currNode->GetChild(); //may be nullptr;
			if(currChild)
			{
				PCSNode *nextSib = currNode->GetNextSibling();
				if(nextSib)
				{
					//currNode->SetChild(nullptr);
					PCSNode *endSibLine = privFindLastSib(currChild);
					assert(endSibLine->GetNextSibling() == nullptr);
					nextSib->SetPrevSibling(endSibLine);
					endSibLine->SetNextSibling(nextSib);
					//endSibLine may be the same node as currChild, that is fine
					currNode->SetNextSibling(currChild);
					currChild->SetPrevSibling(currNode);
					currNode->SetChild(nullptr);
				}
				else
				{
					currNode->SetNextSibling(currChild);
					currChild->SetPrevSibling(currNode);
					currNode->SetChild(nullptr);
				}
			}


			if(currNode->GetPrevSibling() != nullptr)
			{
				PCSNode *prevSib = currNode->GetPrevSibling();
				currNode->GetPrevSibling()->SetNextSibling(nullptr);
				currNode->SetPrevSibling(nullptr);
				delete prevSib;
			}
			this->poRootTree->mInfo.currNumNodes--;
			assert(currNode->GetChild() == nullptr);
			lastNode = currNode;
			currNode = currNode->GetNextSibling();


		}
		if(lastNode) { delete lastNode; }

		//mInfo.currNumNodes--;

		if(this->poRootTree->mInfo.currNumNodes == 0)
		{
			this->poRootTree->mInfo.currNumLevels = 0;
		}
		else
		{
			this->poRootTree->mInfo.currNumLevels = this->privRecursiveLevelNum(this->poRootTree->GetRoot(), 1, 1, false);
		}
	}
	

	PCSNode* GameObjectMan::privFindLastSib(PCSNode *currNode)
	{
		while(currNode->GetNextSibling() != nullptr)
		{
			currNode = currNode->GetNextSibling();
		}

		return currNode;
	}

	void GameObjectMan::privRecursiveDelete(PCSNode *currNode)
	{
		if(currNode == nullptr)  return;
		privRecursiveDelete(currNode->GetNextSibling());

		privRecursiveDelete(currNode->GetChild());

		assert(currNode->GetChild() == nullptr);
		assert(currNode->GetNextSibling() == nullptr);

		currNode->GetParent()->SetChild(nullptr);
		currNode->SetParent(nullptr);

		if(currNode->GetPrevSibling() != nullptr)
		{
			currNode->GetPrevSibling()->SetNextSibling(nullptr);
			currNode->SetPrevSibling(nullptr);
		}
		this->poRootTree->mInfo.currNumNodes--;

		return;
	}

	int GameObjectMan::privRecursiveLevelNum(PCSNode const *currNode, int level, int maxLevel, bool child) const
	{
		if(currNode == nullptr)
		{
			if(maxLevel < level) return level;
			else return maxLevel;
		}
		if(child == true) level++;
		maxLevel = privRecursiveLevelNum(currNode->GetNextSibling(), level, maxLevel, false);


		maxLevel = privRecursiveLevelNum(currNode->GetChild(), level, maxLevel, true);

		return maxLevel;
	}




	GameObjectMan::GameObjectMan()
	{
		// Create the root node (null object)
		MeshNull *pMesh = new MeshNull();
		assert(pMesh);

		MeshNodeMan::Add(Mesh::Name::NULL_MESH, pMesh);

		ShaderObject *pShader = ShaderObjectNodeMan::Find(ShaderObject::Name::NullShader);
		assert(pShader);
		//ShaderObjectNodeMan::Add(pShader);

				// Create the tree
		this->poRootTree = new PCSTree();
		assert(this->poRootTree);

		GraphicsObject_Null *pGraphicsObject = new GraphicsObject_Null(pMesh);
		pBatch = new GameObjectRigid(pGraphicsObject);
		pBatch->SetName("GameObject_Root");

		// Attach the root node
		this->poRootTree->Insert(pBatch, this->poRootTree->GetRoot());


		pGraphicsObject = new GraphicsObject_Null(pMesh);
		pBatchTransparent = new GameObjectRigid(pGraphicsObject);
		pBatchTransparent->SetName("FontObject_Root");

		// Attach the root node
		this->poRootTree->Insert(pBatchTransparent, this->poRootTree->GetRoot());
	}

	GameObjectMan::~GameObjectMan()
	{
		delete this->poRootTree;
	}

	GameObjectMan *GameObjectMan::privGetInstance(void)
	{
		// This is where its actually stored (BSS section)
		static GameObjectMan gom;
		return &gom;
	}

}

// --- End of File ---