#ifndef CAMERA_FIRSTP_H
#define CAMERA_FIRSTP_H

#include "MathEngine.h"
#include "CameraStrategy.h"
#include "GameObject.h"
//#include "Camera.h"

//using namespace Azul;

class Camera_FirstPerson : public CameraStrategy
{

public:
	// Default constructor

	Camera_FirstPerson(GameObject *pFollow);
	Camera_FirstPerson() = delete;
	Camera_FirstPerson(const Camera_FirstPerson &) = delete;
	Camera_FirstPerson &operator = (const Camera_FirstPerson &) = delete;
	virtual ~Camera_FirstPerson() = default;

	void SetTrackingObject(GameObject *pGO);
	// update camera system
	virtual void updateCamera(Camera *pCam);

	GameObject *pGO;
	float zoom;

};

#endif

// --- End of File ---