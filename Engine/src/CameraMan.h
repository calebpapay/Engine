//2024. Caleb Papay

#ifndef Camera_MAN_H
#define Camera_MAN_H 

#include "ManBase.h"
#include "CameraNode.h"


namespace Azul
{

	class CameraMan : public ManBase
	{
	
		// Static Methods
	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();

		static CameraNode *Add(Camera *pCam, Camera::Name name/*, CameraStrategy *type*/);
		static CameraNode *Find(Camera::Name name);

		//static void SetActiveCam(Camera::Name name);
		static void SetCurrent(Camera::Name name, Camera::Type type);
		static Camera *GetCurrent(Camera::Type type);

		//static void SetCullCam(Camera::Name camName);
		//static Camera *GetCullCam();

		static void Update();
		//static void UpdateCullCamPos();


		static void Remove(CameraNode *pNode);
		static void Dump();

		
		// Private methods
	private:
		static CameraMan *privGetInstance();

		~CameraMan();
		CameraMan(int reserveNum, int reserveGrow);

		
		// Override Abstract methods
	protected:
		DLink *derivedCreateNode() override;

		
		// Data: unique data for this manager 
	private:
		CameraNode *poNodeCompare;
		static CameraMan *posInstance;

		CameraNode *pActiveCam_Orthographic;
		CameraNode *pActiveCam_Perspective;


		//Camera_GodState *poGodState;
		//CamStratNull *poNullState;

	};
}

#endif

// --- End of File ---
