
#ifndef CAMERA_DEBUG_H
#define CAMERA_DEBUG_H

#include "Camera.h"
namespace Azul
{

	class CameraDebug : public Camera
	{
	public:
		CameraDebug();
		CameraDebug(const CameraDebug &) = delete;
		CameraDebug &operator=(const CameraDebug &other) = delete;
		virtual ~CameraDebug();

		virtual void updateCamera() override;

	private:


	};
}

#endif

// --- End of File ---
