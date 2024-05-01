
//2024. Caleb Papay


#include "Camera.h"
#include "StringThis.h"
#include "DirectXDeviceMan.h"


namespace Azul
{

	Camera::CullResult Camera::CullTest(const Sphere &Sphere)
	{
		CullResult result = Camera::CullResult::CULL_INSIDE;

		Vec3 A = Sphere.cntr - this->nearTopLeft;

		if((A.dot(this->topNorm) > Sphere.rad) ||
		   (A.dot(this->leftNorm) > Sphere.rad) ||
		   (A.dot(this->frontNorm) > Sphere.rad))
		{
			result = Camera::CullResult::CULL_OUTSIDE;
		}
		else
		{

			Vec3 B = Sphere.cntr - this->farBottomRight;
			if((B.dot(this->backNorm) > Sphere.rad) ||
			   (B.dot(this->rightNorm) > Sphere.rad) ||
			   (B.dot(this->bottomNorm) > Sphere.rad))
			{
				result = Camera::CullResult::CULL_OUTSIDE;
			}
		}
		return result;

	}


	void Camera::GetScreenXY(Vec3 &xy, Vec4 *worldPoint)
	{
		Mat4 viewProjectionMatrix = viewMatrix * projMatrix;

		// Transform the world-space point to clip space
		Vec4 clipSpacePoint = *worldPoint * viewProjectionMatrix;

		// Perform perspective divide to get normalized device coordinates (NDC)
		Vec3 ndcPoint;
		ndcPoint.set(clipSpacePoint.x() / clipSpacePoint.w(),
					 clipSpacePoint.y() / clipSpacePoint.w(),
					 clipSpacePoint.z() / clipSpacePoint.w());

		// Map NDC coordinates to screen space
		// Assuming your screen dimensions are in screen_width and screen_height
	//	float screen_width = /* your screen width */;
		//float screen_height = /* your screen height */;
		float half_screen_width = this->getScreenWidth() * 0.5f;
		float half_screen_height = this->getScreenHeight() * 0.5f;

		float screenX = (ndcPoint.x() + 1.0f) * half_screen_width;
		float screenY = (-ndcPoint.y() + 1.0f) * half_screen_height;

		xy.set(screenX, this->getScreenHeight()- screenY, 0.0f);

	}


	void Camera::GetHelper(Vec3 &up, Vec3 &tar, Vec3 &pos,
						   Vec3 &upNorm, Vec3 &forwardNorm, Vec3 &pRightNorm)
	{
		this->getPos(pos);
		this->getLookAt(tar);
		this->getUp(upNorm);
		up = pos + upNorm;

		forwardNorm = tar - pos;
		forwardNorm.norm();

		this->getRight(pRightNorm);
	}

	void Camera::SetHelper(Vec3 &up_pt, Vec3 &tar_pt, Vec3 &pos_pt)
	{
		Vec3 upVect = up_pt - pos_pt;
		this->setOrientAndPosition(upVect, tar_pt, pos_pt);
	}

	Camera::Camera(Camera::Type _camType)
		:pad{ 0 }, aspectRatio(0), farDist(0), fovy(0), nearDist(0)
	{
		//out("Camera(): ---------\n");
		this->name = Camera::Name::NOT_INITIALIZED;
		this->camType = _camType;
	}

	//Camera::Camera()
	//	: pad{ 0 }, aspectRatio(0), farDist(0), fovy(0), nearDist(0)
	//{
	//	this->name = Camera::Name::NOT_INITIALIZED;
	//}


	char *Camera::GetName() const
	{
		static char pTmp[128];
		strcpy_s(pTmp, 128, StringMe(this->name));
		return pTmp;
	}
	void Camera::SetName(Camera::Name inName)
	{
		this->name = inName;
	}


	void Camera::setPerspective(const float Fovy, const float Aspect, const float NearDist, const float FarDist)
	{
		this->aspectRatio = Aspect;
		this->fovy = MATH_PI_180 * Fovy;
		this->nearDist = NearDist;
		this->farDist = FarDist;
	};
	void Camera::setOrthographic(const float _xMin, const float _xMax, const float _yMin, const float _yMax, const float _zMin, const float _zMax)
	{
		assert(this->camType == Camera::Type::ORTHOGRAPHIC_2D);

		this->xMin = _xMin;
		this->yMin = _yMin;
		this->zMin = _zMin;

		this->xMax = _xMax;
		this->yMax = _yMax;
		this->zMax = _zMax;

		this->far_height = this->yMax - this->yMin;
		this->far_width = this->xMax - this->xMin;
		this->near_width = this->yMax - this->yMin;
		this->nearDist = this->zMin;
		this->farDist = this->zMax;
	};



	int Camera::getScreenWidth() const
	{
		return this->viewport_width;
	}

	int Camera::getScreenHeight() const
	{
		return this->viewport_height;
	}

	// Just a pass through to setup the view port screen sub window
	void Camera::setViewport(const int inX, const int inY, const int width, const int height)
	{
		this->viewport_x = inX;
		this->viewport_y = inY;
		this->viewport_width = width;
		this->viewport_height = height;

		this->privSetViewState();
	};

	// Simple wrapper
	void Camera::privSetViewState(void)
	{
		D3D11_VIEWPORT tmp;

		tmp.Width = (float)this->viewport_width;
		tmp.Height = (float)this->viewport_height;
		tmp.TopLeftX = (float)this->viewport_x;
		tmp.TopLeftY = (float)this->viewport_y;
		tmp.MinDepth = 0.0f;
		tmp.MaxDepth = 1.0f;
		DirectXDeviceMan::GetContext()->RSSetViewports(1, &tmp);
	};

	void Camera::privCalcPlaneHeightWidth(void)
	{

		this->near_height = 2.0f * tanf(this->fovy * .5f) * this->nearDist;
		this->near_width = this->near_height * this->aspectRatio;

		this->far_height = 2.0f * tanf(this->fovy * .5f) * this->farDist;
		this->far_width = this->far_height * this->aspectRatio;

	};

	void Camera::privCalcFrustumVerts(void)
	{
		// Top Left corner and so forth.  In this form to see the pattern
		// Might be confusing (remember the picture) vDir goes from screen into your EYE
		// so distance from the eye is "negative" vDir
		this->nearTopLeft = this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;
		this->nearTopRight = this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;
		this->nearBottomLeft = this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;
		this->nearBottomRight = this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;
		this->farTopLeft = this->vPos - this->vDir * this->farDist + this->vUp * this->far_height * 0.5f - this->vRight * this->far_width * 0.5f;
		this->farTopRight = this->vPos - this->vDir * this->farDist + this->vUp * this->far_height * 0.5f + this->vRight * this->far_width * 0.5f;
		this->farBottomLeft = this->vPos - this->vDir * this->farDist - this->vUp * this->far_height * 0.5f - this->vRight * this->far_width * 0.5f;
		this->farBottomRight = this->vPos - this->vDir * this->farDist - this->vUp * this->far_height * 0.5f + this->vRight * this->far_width * 0.5f;
	};

	void Camera::privCalcFrustumCollisionNormals(void)
	{
		// Normals of the frustum around nearTopLeft
		Vec3 A = this->nearBottomLeft - this->nearTopLeft;
		Vec3 B = this->nearTopRight - this->nearTopLeft;
		Vec3 C = this->farTopLeft - this->nearTopLeft;

		this->frontNorm = A.cross(B);
		this->frontNorm.norm();

		this->leftNorm = C.cross(A);
		this->leftNorm.norm();

		this->topNorm = B.cross(C);
		this->topNorm.norm();

		// Normals of the frustum around farBottomRight
		A = this->farBottomLeft - this->farBottomRight;
		B = this->farTopRight - this->farBottomRight;
		C = this->nearBottomRight - this->farBottomRight;

		this->backNorm = A.cross(B);
		this->backNorm.norm();

		this->rightNorm = B.cross(C);
		this->rightNorm.norm();

		this->bottomNorm = C.cross(A);
		this->bottomNorm.norm();
	};

	void Camera::setOrientAndPosition(const Vec3 &inUp, const Vec3 &inLookAt, const Vec3 &inPos)
	{
		// Remember the up, dir and right are unit length, and are perpendicular.
		// Treat lookAt as king, find Right vect, then correct Up to insure perpendiculare.
		// Make sure that all vectors are unit vectors.

		this->vLookAt = inLookAt;
		this->vDir = -(inLookAt - inPos); // Right-Hand camera: vDir is flipped
		this->vDir.norm();

		// Clean up the vectors (Right hand rule)
		this->vRight = inUp.cross(this->vDir);
		this->vRight.norm();

		this->vUp = this->vDir.cross(this->vRight);
		this->vUp.norm();

		this->vPos = inPos;
	};


	// The projection matrix 
	void Camera::privUpdateProjectionMatrix_3D(void)
	{
		float d = 1 / tanf(fovy / 2);

		this->projMatrix[m0] = d / aspectRatio;
		this->projMatrix[m1] = 0.0f;
		this->projMatrix[m2] = 0.0f;
		this->projMatrix[m3] = 0.0f;

		this->projMatrix[m4] = 0.0f;
		this->projMatrix[m5] = d;
		this->projMatrix[m6] = 0.0f;
		this->projMatrix[m7] = 0.0f;

		this->projMatrix[m8] = 0.0f;
		this->projMatrix[m9] = 0.0f;
		this->projMatrix[m10] = -(this->farDist + this->nearDist) / (this->farDist - this->nearDist);
		this->projMatrix[m11] = -1.0f;

		this->projMatrix[m12] = 0.0f;
		this->projMatrix[m13] = 0.0f;
		this->projMatrix[m14] = (-2.0f * this->farDist * this->nearDist) / (this->farDist - this->nearDist);
		this->projMatrix[m15] = 0.0f;

		// Converting from OpenGL-style NDC of [-1,1] to DX's [0,1].  See note: https://anteru.net/blog/2011/12/27/1830/
		// (Note: NDCConvert should be precomputed once and stored for reuse)
		Trans B(0.0f, 0.0f, 1.0f);
		Scale S(1.0f, 1.0f, 0.5f);

		projMatrix = projMatrix * B * S;
	};

	void Camera::privUpdateProjectionMatrix_2D(void)
	{
		this->projMatrix[m0] = 2.0f / (xMax - xMin);
		this->projMatrix[m1] = 0.0f;
		this->projMatrix[m2] = 0.0f;
		this->projMatrix[m3] = 0.0f;

		this->projMatrix[m4] = 0.0f;
		this->projMatrix[m5] = 2.0f / (yMax - yMin);
		this->projMatrix[m6] = 0.0f;
		this->projMatrix[m7] = 0.0f;

		this->projMatrix[m8] = 0.0f;
		this->projMatrix[m9] = 0.0f;
		this->projMatrix[m10] = -1.0f / (zMax - zMin); // -2.0f / (zMax - zMin);
		this->projMatrix[m11] = 0.0f;

		this->projMatrix[m12] = 0;
		this->projMatrix[m13] = 0;
		this->projMatrix[m14] = -(zMin) / (zMax - zMin); //-(zMax + zMin) / (zMax - zMin);
		this->projMatrix[m15] = 1.0f;
	};


	void Camera::privUpdateViewMatrix(void)
	{
		// This functions assumes the your vUp, vRight, vDir are still unit
		// And perpendicular to each other

		// Set for DX Right-handed space
		this->viewMatrix[m0] = this->vRight[x];
		this->viewMatrix[m1] = this->vUp[x];
		this->viewMatrix[m2] = this->vDir[x];
		this->viewMatrix[m3] = 0.0f;

		this->viewMatrix[m4] = this->vRight[y];
		this->viewMatrix[m5] = this->vUp[y];
		this->viewMatrix[m6] = this->vDir[y];
		this->viewMatrix[m7] = 0.0f;

		this->viewMatrix[m8] = this->vRight[z];
		this->viewMatrix[m9] = this->vUp[z];
		this->viewMatrix[m10] = this->vDir[z];
		this->viewMatrix[m11] = 0.0f;

		// Apply R^t( -Pos ). Use dot-product with the basis vectors
		this->viewMatrix[m12] = -vPos.dot(vRight);
		this->viewMatrix[m13] = -vPos.dot(vUp);
		this->viewMatrix[m14] = -vPos.dot(vDir);
		this->viewMatrix[m15] = 1.0f;
	};


	// Update everything (make sure it's consistent)
	void Camera::baseUpdateCamera(void)
	{
		this->privCalcPlaneHeightWidth();
		this->privCalcFrustumVerts();
		this->privCalcFrustumCollisionNormals();

		// update the projection matrix
		if(this->camType == Camera::Type::PERSPECTIVE_3D)
		{
			this->privUpdateProjectionMatrix_3D();
		}
		else
		{
			this->privUpdateProjectionMatrix_2D();
		}
		// update the view matrix
		this->privUpdateViewMatrix();
	}


	Camera::Type Camera::getType() const
	{
		return this->camType;
	}

	Mat4 &Camera::getViewMatrix(void)
	{
		return this->viewMatrix;
	}

	Mat4 &Camera::getProjMatrix(void)
	{
		return this->projMatrix;
	}

	void Camera::getPos(Vec3 &outPos) const
	{
		outPos = this->vPos;
	}

	void  Camera::getDir(Vec3 &outDir) const
	{
		outDir = this->vDir;
	}

	void  Camera::getUp(Vec3 &outUp) const
	{
		outUp = this->vUp;
	}

	void Camera::getLookAt(Vec3 &outLookAt) const
	{
		outLookAt = this->vLookAt;
	}

	void Camera::getRight(Vec3 &outRight) const
	{
		outRight = this->vRight;
	}

	void Camera::TranslateLeftRight(float _delta)
	{
		vPos += vRight * _delta;
	}

	void Camera::getFieldOfView(float &Value) const
	{
		Value = this->fovy;
	};

	void Camera::TranslateFwdBack(float delta)
	{
		vPos -= vDir * delta;
	}

	void Camera::TiltUpDown(float ang)
	{
		Rot rot = Rot(Axis::AxisAngle, vRight, ang);
		vDir = Vec4(vDir, 1) * rot;
		vUp = Vec4(vUp, 1) * rot;
		setOrientAndPosition(vUp, vPos - vDir, vPos);
	}


	void Camera::TurnLeftRight(float ang)
	{
		Rot rot = Rot(Rot1::Y, ang);
		vDir = Vec4(vDir, 1) * rot;
		vUp = Vec4(vUp, 1) * rot;
		setOrientAndPosition(vUp, vPos - vDir, vPos);
	}



	void Camera::ChangeFOV(float ang)
	{
		if(this->fovy + ang > 0.25f && this->fovy + ang < 1.5f)
		{

			this->fovy += ang;
		}
	}


	void Camera::getNearDist(float &Value) const
	{
		Value = this->nearDist;
	}

	void Camera::setNearDist(const float Value)
	{
		this->nearDist = Value;
	}

	void Camera::getNearTopLeft(Vec3 &vOut) const
	{
		vOut = this->nearTopLeft;
	}
	void Camera::getNearTopRight(Vec3 &vOut) const
	{
		vOut = this->nearTopRight;
	}
	void Camera::getNearBottomLeft(Vec3 &vOut)const
	{
		vOut = this->nearBottomLeft;
	}
	void Camera::getNearBottomRight(Vec3 &vOut) const
	{
		vOut = this->nearBottomRight;
	}
	void Camera::getFarTopLeft(Vec3 &vOut) const
	{
		vOut = this->farTopLeft;
	}
	void Camera::getFarTopRight(Vec3 &vOut) const
	{
		vOut = this->farTopRight;
	}
	void Camera::getFarBottomLeft(Vec3 &vOut) const
	{
		vOut = this->farBottomLeft;
	}
	void Camera::getFarBottomRight(Vec3 &vOut)const
	{
		vOut = this->farBottomRight;
	}

}
// --- End of File ---
