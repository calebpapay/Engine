//2024. Caleb Papay

#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "PCSTree.h"
#include "AnimTime.h"
#include "GameObjectRigid.h"

namespace Azul
{
	// Singleton
	class GameObjectMan
	{

		
	public:
		static void Add(GameObject* pObj, GameObject *pParent);
		static void Draw();
		static void Update(AnimTime currentTime);

		static GameObject *GetRoot(void);
		static GameObject *GetRootTransparent(void);
		static PCSTree *GetPCSTree();

		static void Create();
		static void Destroy();
		static void Remove(GameObject* pRootRemove);

		GameObjectMan(const GameObjectMan &) = delete;
		GameObjectMan &operator = (const GameObjectMan &) = delete;

		~GameObjectMan();

	private:
		GameObjectMan();
		void privRemove(PCSNode *const pInNode);
		void privRecursiveDelete(PCSNode *const pInNode);
		int privRecursiveLevelNum(PCSNode const *currNode, int level, int maxLevel, bool child) const;
		PCSNode *privFindLastSib(PCSNode *currNode);
		static GameObjectMan *privGetInstance();

		// data
		PCSTree *poRootTree;
		GameObjectRigid *pBatch;
		GameObjectRigid *pBatchTransparent;
	};

}

#endif


// --- End of File ---
