#ifndef CAMERA_THIRDP_H
#define CAMERA_THIRDP_H

#include "MathEngine.h"
#include "CameraStrategy.h"
#include "GameObject.h"
//#include "Camera.h"

//using namespace Azul;

class Camera_ThirdPerson : public CameraStrategy
{

public:
	// Default constructor

	Camera_ThirdPerson(GameObject *pFollow);
	Camera_ThirdPerson() = delete;
	Camera_ThirdPerson(const Camera_ThirdPerson &) = delete;
	Camera_ThirdPerson &operator = (const Camera_ThirdPerson &) = delete;
	virtual ~Camera_ThirdPerson() = default;

	void SetTrackingObject(GameObject* pGO);
	// update camera system
	virtual void updateCamera(Camera *pCam);

	GameObject *pGO;
	float height;

};

#endif

// --- End of File ---