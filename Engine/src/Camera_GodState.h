#ifndef CAMERA_GOD_H
#define CAMERA_GOD_H


#include "Camera.h"
//#include "Camera.h"

namespace Azul
{

	class Camera_GodState : public Camera
	{

	public:
		// Default constructor
		Camera_GodState(Camera::Type type);
		Camera_GodState(const Camera_GodState &) = delete;
		Camera_GodState &operator = (const Camera_GodState &) = delete;
		virtual ~Camera_GodState();
		// update camera system
		virtual void updateCamera() override;


	};
}

#endif

// --- End of File ---