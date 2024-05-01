#include "CameraNode.h"
#include "StringThis.h"
namespace Azul
{
    CameraNode::CameraNode()
        : DLink(),
        poCamera(nullptr)//,
        //poCamStrat(nullptr)
    {
        this->privClear();
    }

    CameraNode::~CameraNode()
    {
        this->privClear();
    }

    void CameraNode::Set(Camera::Name _name, Camera *_pCamera/*, CameraStrategy *_camStrat*/)
    {
        assert(_pCamera);
        this->poCamera = _pCamera;
        // this->poCamStrat = _camStrat;

        this->name = _name;
    }

    Camera *CameraNode::GetCamera()
    {
        return this->poCamera;
    }

    void CameraNode::privClear()
    {
        if(this->poCamera)
        {
            delete this->poCamera;
        }
        /* if(this->poCamStrat)
         {
             delete this->poCamStrat;
         }*/
        this->poCamera = nullptr;
    }

    void CameraNode::Update()
    {
        // this->poCamStrat->updateCamera(this->poCamera);
        this->poCamera->updateCamera();
    }


    void CameraNode::Wash()
    {
        this->privClear();
    }

    bool CameraNode::Compare(DLink *pTargetNode)
    {
        // This is used in ManBase.Find() 
        assert(pTargetNode);

        CameraNode *pDataB = (CameraNode *)pTargetNode;

        bool status = false;

        assert(pDataB->poCamera);
        assert(this->poCamera);

        if(this->name == pDataB->name)
        {
            status = true;
        }

        return status;
    }

    void CameraNode::Dump()
    {
        Trace::out("      CameraNode(%p)\n", this);

        // Data:
        if(this->poCamera)
        {
            Trace::out("      Camera(%p) \n", this->poCamera);
            // Trace::out("      Name: %s \n", StringMe(this->poCamera->name));
        }
        else
        {
            Trace::out("      Name: %s \n", "null");
        }

        DLink::Dump();
    }
}

// --- End of File ---
