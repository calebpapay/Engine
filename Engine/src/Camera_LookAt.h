#ifndef CAMERA_LOOATAT_H
#define CAMERA_LOOATAT_H

#include "MathEngine.h"
#include "CameraStrategy.h"
#include "GameObject.h"
//#include "Camera.h"

//using namespace Azul;

class Camera_LookAt : public CameraStrategy
{

public:
	// Default constructor
	Camera_LookAt() = delete;
	Camera_LookAt(GameObject *_pGO);
	Camera_LookAt(const Camera_LookAt &) = delete;
	Camera_LookAt &operator = (const Camera_LookAt &) = delete;
	virtual ~Camera_LookAt() = default;

	void SetTrackingObject(GameObject *pGO);
	// update camera system
	virtual void updateCamera(Camera *pCam);

	GameObject *pGO;


};

#endif

// --- End of File ---