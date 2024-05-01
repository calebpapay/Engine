#include "Camera_LookAt.h"

Camera_LookAt::Camera_LookAt(GameObject *_pGO)
{
	this->pGO = _pGO;
	
}

void Camera_LookAt::SetTrackingObject(GameObject *_pGO)
{
	this->pGO = _pGO;
}

void Camera_LookAt::updateCamera(Camera *pCam)
{
	
	//Vec3 offset(0.0f, 10.0f, -10.0f);

	//DO NOT USE --------------------------------------

	//Vec3 obj = *(this->pGO->GetPos());

	//DO NOT USE --------------------------------------

	//Vec3 lookAt = obj;
	//Vec3 cameraPosition = obj + offset;
	//Vec3 up = Vec3(0.0f, 1.0f, 0.0f);

	//pCam->setOrientAndPosition(up, lookAt, cameraPosition);

}