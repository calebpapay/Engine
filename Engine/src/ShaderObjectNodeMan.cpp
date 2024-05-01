//2024. Caleb Papay

#include "ShaderObjectNodeMan.h"
#include "ShaderObject_Null.h"
#include "ShaderObject_FlatTexture.h"
#include "ShaderObject_Sprite.h"
#include "ShaderObject_ConstColor.h"
#include "ShaderObject_ColorByVertex.h"
#include "ShaderObject_LightTexture.h"
#include "ShaderObject_SkinFlatTexture.h"
#include "ShaderObject_WorldCompute.h"
#include "ShaderObject_MixerCompute.h"
#include "ShaderObject_SkinLightTexture.h"

#include "ManBase.h"
#include "DLinkMan.h"

namespace Azul
{
	ShaderObjectNodeMan *ShaderObjectNodeMan::posInstance = nullptr;


	ShaderObjectNodeMan::ShaderObjectNodeMan(int reserveNum, int reserveGrow)
		: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
	{
		// Preload the reserve
		this->proFillReservedPool(reserveNum);

		// initialize derived data here
		ShaderObject *pShaderObject = new ShaderObject_Null(ShaderObject::Name::NullShader);


		this->poNodeCompare = new ShaderObjectNode();
		assert(this->poNodeCompare);

		this->poNodeCompare->Set(pShaderObject);
	}

	ShaderObjectNodeMan::~ShaderObjectNodeMan()
	{
		delete this->poNodeCompare;
		this->poNodeCompare = nullptr;

		// iterate through the list and delete
		Iterator *pIt = this->baseGetActiveIterator();

		DLink *pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			ShaderObjectNode *pDeleteMe = (ShaderObjectNode *)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}

		pIt = this->baseGetReserveIterator();

		pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			ShaderObjectNode *pDeleteMe = (ShaderObjectNode *)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}
	}

	
	// Static Methods
	void ShaderObjectNodeMan::Create(int reserveNum, int reserveGrow)
	{
		// make sure values are ressonable 
		assert(reserveNum >= 0);
		assert(reserveGrow > 0);

		// initialize the singleton here
		assert(posInstance == nullptr);

		// Do the initialization
		if(posInstance == nullptr)
		{
			posInstance = new ShaderObjectNodeMan(reserveNum, reserveGrow);


			ShaderObject *poShader = new ShaderObject_FlatTexture(ShaderObject::Name::FlatTexture);
			Add(poShader);

			poShader = new ShaderObject_Sprite(ShaderObject::Name::Sprite);
			Add(poShader);

			poShader = new ShaderObject_ConstColor(ShaderObject::Name::ConstColor);
			Add(poShader);

			poShader = new ShaderObject_ColorByVertex(ShaderObject::Name::ColorByVertex);
			Add(poShader);

			poShader = new ShaderObject_LightTexture(ShaderObject::Name::LightTexture);
			Add(poShader);

			poShader = new ShaderObject_Null(ShaderObject::Name::NullShader);
			Add(poShader);

			poShader = new ShaderObject_SkinFlatTexture(ShaderObject::Name::SkinFlatTexture);
			Add(poShader);

			poShader = new ShaderObject_WorldCompute(ShaderObject::Name::WorldCompute);
			Add(poShader);

			poShader = new ShaderObject_MixerCompute(ShaderObject::Name::MixerCompute);
			Add(poShader);


			poShader = new ShaderObject_SkinLightTexture(ShaderObject::Name::SkinLightTexture);
			Add(poShader);
		}
	}

	void ShaderObjectNodeMan::Destroy()
	{
		ShaderObjectNodeMan *pMan = ShaderObjectNodeMan::privGetInstance();
		assert(pMan != nullptr);
		AZUL_UNUSED_VAR(pMan);

		delete ShaderObjectNodeMan::posInstance;
		ShaderObjectNodeMan::posInstance = nullptr;
	}

	ShaderObjectNode *ShaderObjectNodeMan::Add(ShaderObject *pMesh)
	{
		ShaderObjectNodeMan *pMan = ShaderObjectNodeMan::privGetInstance();

		assert(pMesh);

		ShaderObjectNode *pNode = (ShaderObjectNode *)pMan->baseAddToFront();
		assert(pNode != nullptr);

		// Initialize the date
		pNode->Set(pMesh);

		return pNode;
	}

	ShaderObject *ShaderObjectNodeMan::Find(ShaderObject::Name _name)
	{
		ShaderObjectNodeMan *pMan = ShaderObjectNodeMan::privGetInstance();
		assert(pMan != nullptr);

		// Compare functions only compares two Nodes

		// So:  Use the Compare Node - as a reference
		//      use in the Compare() function
		ShaderObject *pShaderObject = pMan->poNodeCompare->GetShaderObject();
		assert(pShaderObject);

		pShaderObject->name = _name;

		ShaderObjectNode *pData = (ShaderObjectNode *)pMan->baseFind(pMan->poNodeCompare);
		return pData->GetShaderObject();
	}

	void ShaderObjectNodeMan::Remove(ShaderObjectNode *pNode)
	{
		assert(pNode != nullptr);

		ShaderObjectNodeMan *pMan = ShaderObjectNodeMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseRemove(pNode);
	}

	void ShaderObjectNodeMan::Dump()
	{
		ShaderObjectNodeMan *pMan = ShaderObjectNodeMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseDump();
	}

	
	// Private methods
	
	ShaderObjectNodeMan *ShaderObjectNodeMan::privGetInstance()
	{
		// Safety - this forces users to call Create() first before using class
		assert(posInstance != nullptr);

		return posInstance;
	}

	
	// Override Abstract methods
	
	DLink *ShaderObjectNodeMan::derivedCreateNode()
	{
		DLink *pNodeBase = new ShaderObjectNode();
		assert(pNodeBase != nullptr);

		return pNodeBase;
	}

}

// --- End of File ---
