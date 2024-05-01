//2024. Caleb Papay

#include "CameraNull.h"

namespace Azul
{

	CameraNull::CameraNull(Camera::Type type)
		: Camera(type)
	{

	}

	CameraNull::~CameraNull()
	{
		// remove anything dynamic here
	}

	void CameraNull::updateCamera()
	{
		//TranslateFwdBack(0.0f);
	}
}


// --- End of File ---
