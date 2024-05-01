#ifndef Camera_NODE_H
#define Camera_NODE_H

#include "DLink.h"
#include "Camera.h"
//#include "CameraStrategy.h"
namespace Azul
{
	class CameraNode : public DLink
	{
	public:
		CameraNode();
		CameraNode(const Camera &) = delete;
		CameraNode &operator = (const Camera &) = delete;
		virtual ~CameraNode();

		void Set(Camera::Name name, Camera *pCamera/*, CameraStrategy *camStrat*/);
		Camera *GetCamera();

		//virtual char *GetName() override;
		virtual void Wash() override;
		virtual bool Compare(DLink *pTargetNode) override;
		virtual void Dump() override;

		void Update();



		Camera::Name name;

	private:
		void privClear();

		//--------------------------------------------------
		// Data
		//--------------------------------------------------
		Camera *poCamera;
		//CameraStrategy *poCamStrat;

	};
}

#endif

// --- End of File ---