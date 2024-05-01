
//2024. Caleb Papay


#ifndef CAMERA_H
#define CAMERA_H

#include "MathEngine.h"
#include "BoundingSphere.h"

namespace Azul
{


	class Camera : public Align16
	{

	public:

		enum class Type
		{
			PERSPECTIVE_3D,
			ORTHOGRAPHIC_2D
		};

		enum class Name
		{
			CAMERA_0,
			CAMERA_1,
			NullCamera,
			NOT_INITIALIZED
		};

		enum class CullResult
		{
			CULL_INSIDE,
			CULL_OUTSIDE,

		};

		CullResult CullTest(const Sphere &Sphere);

		// Default constructor
		Camera() = delete;
		Camera(const Camera &) = delete;
		Camera &operator = (const Camera &) = delete;
		virtual ~Camera() = default;

		Camera(Camera::Type _camType);

		// Setup on single camera
		void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);
		void setOrthographic(const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax);

		void setViewport(const int inX, const int inY, const int width, const int height);
		void setOrientAndPosition(const Vec3 &Up_vect, const Vec3 &inLookAt_pt, const Vec3 &pos_pt);

		// update camera system
		virtual void updateCamera(void) = 0;

		// Get the matrices for rendering
		Mat4 &getViewMatrix();
		Mat4 &getProjMatrix();


		void GetScreenXY(Vec3 &xy, Vec4 *worldPoint);

		// helper functions
		void GetHelper(Vec3 &up, Vec3 &tar, Vec3 &pos, Vec3 &upNorm, Vec3 &forwardNorm, Vec3 &rightNorm);
		void SetHelper(Vec3 &up, Vec3 &tar, Vec3 &pos);

		// accessors
		void getPos(Vec3 &outPos) const;
		void getDir(Vec3 &outDir) const;
		void getUp(Vec3 &outUp) const;
		void getLookAt(Vec3 &outLookAt) const;
		void getRight(Vec3 &outRight) const;

		int getScreenWidth() const;
		int getScreenHeight() const;

		// accessors
		char *GetName() const;
		void SetName(Camera::Name name);
		Camera::Type getType() const;


		void TranslateLeftRight(float delta);
		void TranslateFwdBack(float delta);
		void TiltUpDown(float ang);
		void TurnLeftRight(float ang);
		void getFieldOfView(float &Value) const;
		void ChangeFOV(float ang);
		void getNearDist(float &Value) const;
		void setNearDist(const float Value);

		void getNearTopLeft(Vec3 &vOut) const;
		void getNearTopRight(Vec3 &vOut) const;
		void getNearBottomLeft(Vec3 &vOut) const;
		void getNearBottomRight(Vec3 &vOut) const;
		void getFarTopLeft(Vec3 &vOut) const;
		void getFarTopRight(Vec3 &vOut) const;
		void getFarBottomLeft(Vec3 &vOut) const;
		void getFarBottomRight(Vec3 &vOut) const;

		// Why no SETS for Pos, Dir, Up, LookAt and Right?
		//   They have to be adjusted _together_ in setOrientAndPosition()
	protected:
		void baseUpdateCamera(void);

	private:  // methods should never be public
		void privSetViewState(void);
		void privCalcPlaneHeightWidth(void);
		void privCalcFrustumVerts(void);
		void privCalcFrustumCollisionNormals(void);

		void privUpdateProjectionMatrix_3D(void);
		void privUpdateProjectionMatrix_2D(void);
		void privUpdateViewMatrix(void);


	private: //data (private)
		// Projection Matrix
		Mat4	projMatrix;
		Mat4	viewMatrix;

		// camera unit vectors (up, dir, right)
		Vec3	vUp;
		Vec3	vPos;
		Vec3	vLookAt;

		Vec3	vDir; //lookAt-Pos
		Vec3	vRight;  //derived from up and dir

		// world space coords for viewing frustum
		Vec3	nearTopLeft;
		Vec3	nearTopRight;
		Vec3	nearBottomLeft;
		Vec3	nearBottomRight;

		Vec3	farTopLeft;
		Vec3	farTopRight;
		Vec3	farBottomLeft;
		Vec3	farBottomRight;

		// Normals of the frustum
		Vec3	frontNorm;
		Vec3	backNorm;
		Vec3	rightNorm;

		Vec3	leftNorm;
		Vec3	topNorm;
		Vec3	bottomNorm;

		Camera::Type camType;

		// Define the frustum inputs
		float	nearDist;
		float	farDist;
		float	fovy;  // aka view angle along y axis
		float	aspectRatio;

		// Screen size in world space
		//this + fovy; defines 2 perspective planes (near/far) and their distance apart
		float	near_height;
		float	near_width;
		float	far_height;
		float	far_width;


		// Ortho hacks 
		// defines 2 identical orthographic planes and their distance apart
		float	xMin;
		float	yMin;
		float	zMin;
		float	xMax;
		float	yMax;
		float	zMax;

		// viewports
		int		viewport_x;
		int		viewport_y;
		int		viewport_width;
		int		viewport_height;

		// Name
	public:
		Camera::Name name;
		char pad[12];
	};
}

#endif

// --- End of File ---