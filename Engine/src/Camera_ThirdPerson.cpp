#include "Camera_ThirdPerson.h"

 
Camera_ThirdPerson::Camera_ThirdPerson(GameObject* _pGO)
{
	this->pGO = _pGO;
	this->height = 2.0f;
}

void Camera_ThirdPerson::SetTrackingObject(GameObject *_pGO)
{
	this->pGO = _pGO;
	this->height = 2.0f;
}


void Camera_ThirdPerson::updateCamera(Camera *pCam)
{
	/*float offset = -4;

	Mat4* world = this->pGO->GetWorld();
	Vec4 forward = world->get(Row4::i2);
	Vec3 obj = *(this->pGO->GetPos());

	
	if((GetKeyState('W') & 0x8000))
	{
		if(height >= 1.4f)
		{
			height -= 0.025f;
		}
		else if(height >= 0.9f)
		{
			height -= 0.02f;
		}
		else if(height >= 0.65f)
		{
			height -= 0.015f;
		}
		
	}
	else
	{
		if(height <= 0.9f)
		{
			height += 0.01f;
		}
		else if(height <= 1.5f)
		{
			height += 0.02f;
		}
		else if(height <= 2.0f)
		{
			height += 0.025f;
		}

	}


	Vec3 fwd = Vec3(forward[x], forward[y] - (height*0.5f), forward[z]);
	Vec3 lookAt = obj + fwd;

	Vec3 cameraPosition = obj + offset * fwd;

	Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
	
	pCam->setOrientAndPosition(up, lookAt, cameraPosition);*/



}