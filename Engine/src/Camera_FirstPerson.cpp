#include "Camera_FirstPerson.h"


Camera_FirstPerson::Camera_FirstPerson(GameObject *_pGO)
{
	this->pGO = _pGO;
	this->zoom = 2.0f;
}

void Camera_FirstPerson::SetTrackingObject(GameObject *_pGO)
{
	this->pGO = _pGO;
	this->zoom = 2.0f;
}


void Camera_FirstPerson::updateCamera(Camera *pCam)
{
	//float offset = 0.1f;

	//Mat4 *world = this->pGO->GetWorld();
	///*Vec4 forward = world->get(Mat4::Row::i2);*/
	//Vec4 forward = world->get(Row4::i2);
	//
	
	
	//DO NOT USE-----------------------------------
	
	
	//Vec3 obj = *(this->pGO->GetPos());

	//DO NOT USE-----------------------------------

	/*if((GetKeyState(VK_UP) & 0x8000))
	{
		pCam->ChangeFOV(-0.04f);

	}
	else if((GetKeyState(VK_DOWN) & 0x8000))
	{
		pCam->ChangeFOV(0.04f);
	}


	Vec3 fwd = Vec3(forward[x], forward[y] , forward[z]);
	Vec3 lookAt = obj + fwd;

	Vec3 cameraPosition = obj + offset * fwd;

	Vec3 up = Vec3(0.0f, 1.0f, 0.0f);

	pCam->setOrientAndPosition(up, lookAt, cameraPosition);*/


}