
#include "Camera_Debug.h"

namespace Azul
{

	CameraDebug::CameraDebug()
		: Camera(Camera::Type::ORTHOGRAPHIC_2D)
	{

	}

	CameraDebug::~CameraDebug()
	{
		// remove anything dynamic here
	}

	void CameraDebug::updateCamera()
	{
		//float totalSpeed = 170.0f;
		//float camSpeed = 0.025f * totalSpeed;
		////float rotSpeed = 0.006f * totalSpeed;

		//	if(GetAsyncKeyState('W') & 0x08000)
		//	{
		//		TranslateFwdBack(camSpeed);
		//	}
		//	else if(GetAsyncKeyState('S') & 0x08000)
		//	{
		//		TranslateFwdBack(-camSpeed);
		//	}

		//if(GetAsyncKeyState('A') & 0x08000)
		//{
		//	TranslateLeftRight(-camSpeed);
		//}
		//else if(GetAsyncKeyState('D') & 0x08000)
		//{
		//	TranslateLeftRight(camSpeed);
		//}
		baseUpdateCamera();
		////TranslateFwdBack(0.0f);
	}
}


// --- End of File ---
