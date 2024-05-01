//2024. Caleb Papay

#include "CameraMan.h"
#include "CameraNode.h"
#include "ManBase.h"
#include "DLinkMan.h"
#include "CameraNull.h"
namespace Azul
{
	CameraMan *CameraMan::posInstance = nullptr;


	// Constructor

	CameraMan::CameraMan(int reserveNum, int reserveGrow)
		: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
	{
		// Preload the reserve
		this->proFillReservedPool(reserveNum);

		// initialize derived data here
		Camera *pCamera = new CameraNull(Camera::Type::PERSPECTIVE_3D);
		//assert(pCamera);
		this->poNodeCompare = new CameraNode();
		assert(this->poNodeCompare);
		this->poNodeCompare->Set(Camera::Name::NullCamera, pCamera);



		pActiveCam_Orthographic = nullptr;
		pActiveCam_Perspective = nullptr;
	}

	CameraMan::~CameraMan()
	{
		delete this->poNodeCompare;
		this->poNodeCompare = nullptr;

		// iterate through the list and delete
		Iterator *pIt = this->baseGetActiveIterator();

		DLink *pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			CameraNode *pDeleteMe = (CameraNode *)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}

		pIt = this->baseGetReserveIterator();

		pNode = pIt->First();

		// Walk through the nodes
		while(!pIt->IsDone())
		{
			CameraNode *pDeleteMe = (CameraNode *)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}
	}

	
	// Static Methods
	void CameraMan::Create(int reserveNum, int reserveGrow)
	{
		// make sure values are ressonable 
		assert(reserveNum >= 0);
		assert(reserveGrow > 0);

		// initialize the singleton here
		assert(posInstance == nullptr);

		// Do the initialization
		if(posInstance == nullptr)
		{
			posInstance = new CameraMan(reserveNum, reserveGrow);
		}
	}

	void CameraMan::Destroy()
	{
		CameraMan *pMan = CameraMan::privGetInstance();
		assert(pMan != nullptr);
		AZUL_UNUSED_VAR(pMan);

		delete CameraMan::posInstance;
		CameraMan::posInstance = nullptr;
	}



	void CameraMan::SetCurrent(const Camera::Name name, Camera::Type type)
	{
		CameraMan *pCamMan = CameraMan::privGetInstance();
		assert(pCamMan);

		CameraNode *pCam = CameraMan::Find(name);
		assert(pCam);

		// w1(7)
		switch(type)
		{
		case Camera::Type::PERSPECTIVE_3D:
			assert(pCam->GetCamera()->getType() == Camera::Type::PERSPECTIVE_3D);
			pCamMan->pActiveCam_Perspective = pCam;
			break;

		case Camera::Type::ORTHOGRAPHIC_2D:
			assert(pCam->GetCamera()->getType() == Camera::Type::ORTHOGRAPHIC_2D);
			pCamMan->pActiveCam_Orthographic = pCam;
			break;

		default:
			assert(false);
			break;
		}

	}

	// w1(7)
	Camera *CameraMan::GetCurrent(Camera::Type type)
	{
		Camera *pCam = nullptr;
		switch(type)
		{
		case Camera::Type::PERSPECTIVE_3D:
			pCam = CameraMan::privGetInstance()->pActiveCam_Perspective->GetCamera();
			break;

		case Camera::Type::ORTHOGRAPHIC_2D:
			pCam = CameraMan::privGetInstance()->pActiveCam_Orthographic->GetCamera();
			break;

		default:
			assert(false);
			break;
		}

		assert(pCam != nullptr);
		return pCam;
	}

	//void CameraMan::SetActiveCam(Camera::Name camName)
	//{
	//	CameraMan *pMan = CameraMan::privGetInstance();
	//
	//	CameraNode *pNode = pMan->Find(camName);
	//	assert(pNode);
	//
	//	pMan->pActiveCam = pNode;
	//	pMan->pActiveCam->Update();
	//}

	void CameraMan::Update()
	{
		CameraMan *pMan = CameraMan::privGetInstance();
		assert(pMan->pActiveCam_Perspective != nullptr);
		pMan->pActiveCam_Perspective->Update();
		pMan->pActiveCam_Orthographic->Update();
	}

	//Camera *CameraMan::GetActiveCam()
	//{
	//	CameraMan *pMan = CameraMan::privGetInstance();
	//
	//	return pMan->pActiveCam->GetCamera();
	//}





	CameraNode *CameraMan::Add(Camera *pCam, Camera::Name name/*, CameraStrategy *type*/)
	{
		CameraMan *pMan = CameraMan::privGetInstance();

		CameraNode *pNode = (CameraNode *)pMan->baseAddToFront();
		assert(pNode != nullptr);
		// Initialize the data
		pNode->Set(name, pCam);

		return pNode;
	}

	CameraNode *CameraMan::Find(Camera::Name _name)
	{
		CameraMan *pMan = CameraMan::privGetInstance();
		assert(pMan != nullptr);

		// Compare functions only compares two Nodes

		// So:  Use the Compare Node - as a reference
		//      use in the Compare() function
		CameraNode *pCamera = pMan->poNodeCompare;
		assert(pCamera);

		pCamera->name = _name;

		CameraNode *pData = (CameraNode *)pMan->baseFind(pMan->poNodeCompare);
		return pData;
	}



	void CameraMan::Remove(CameraNode *pNode)
	{
		assert(pNode != nullptr);

		CameraMan *pMan = CameraMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseRemove(pNode);
	}

	void CameraMan::Dump()
	{
		CameraMan *pMan = CameraMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseDump();
	}

	// Private methods
	CameraMan *CameraMan::privGetInstance()
	{
		// Safety - this forces users to call Create() first before using class
		assert(posInstance != nullptr);

		return posInstance;
	}

	
	// Override Abstract methods
	DLink *CameraMan::derivedCreateNode()
	{
		DLink *pNodeBase = new CameraNode();
		assert(pNodeBase != nullptr);

		return pNodeBase;
	}
}

// --- End of File ---




