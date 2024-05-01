//2024. Caleb Papay

#ifndef CAMERA_NULL_H
#define CAMERA_NULL_H

#include "Camera.h"
namespace Azul
{

	class CameraNull : public Camera
	{
	public:
		CameraNull(Camera::Type type);
		CameraNull(const CameraNull &) = delete;
		CameraNull &operator=(const CameraNull &other) = delete;
		virtual ~CameraNull();

		virtual void updateCamera() override;

	private:


	};
}

#endif

// --- End of File ---
