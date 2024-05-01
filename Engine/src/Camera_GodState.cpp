#include "Camera_GodState.h"
#include "MathEngine.h"
namespace Azul
{
	Camera_GodState::Camera_GodState(Camera::Type type)
		: Camera(type)
	{

		//float totalSpeed = 10.0f;

	}

	Camera_GodState::~Camera_GodState()
	{
		// remove anything dynamic here
	}

	void Camera_GodState::updateCamera()
	{
		float totalSpeed = 7.0f;
		float camSpeed = 0.025f * totalSpeed;
		float rotSpeed = 0.003f * totalSpeed;

		if(GetAsyncKeyState('W') & 0x08000)
		{
			TranslateFwdBack(camSpeed);
		}
		else if(GetAsyncKeyState('S') & 0x08000)
		{
			TranslateFwdBack(-camSpeed);
		}

		if(GetAsyncKeyState('A') & 0x08000)
		{
			TranslateLeftRight(-camSpeed );
		}
		else if(GetAsyncKeyState('D') & 0x08000)
		{
			TranslateLeftRight(camSpeed );
		}


		if(GetAsyncKeyState(VK_LEFT) & 0x08000)
		{
			TurnLeftRight(rotSpeed);
		}
		else if(GetKeyState(VK_RIGHT) & 0x08000)
		{
			TurnLeftRight(-rotSpeed);
		}


		if(GetAsyncKeyState(VK_SHIFT) & 0x08000)
		{
			if((GetAsyncKeyState(VK_UP) & 0x8000))
			{
				ChangeFOV(-0.007f);

			}
			else if((GetAsyncKeyState(VK_DOWN) & 0x8000))
			{
				ChangeFOV(0.007f);
			}
		}
		else
		{
			if(GetAsyncKeyState(VK_UP) & 0x08000)
			{
				TiltUpDown(rotSpeed);
			}
			else if(GetAsyncKeyState(VK_DOWN) & 0x08000)
			{
				TiltUpDown(-rotSpeed);
			}
		}

		baseUpdateCamera();

	}
}