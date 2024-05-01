#include "MathEngine.h"

namespace Azul
{
	// Do your magic here

	Rot::Rot()
		:Mat4()
	{
		this->privSetRotHint();
	}

	Rot::Rot(const Rot1 type, const float angle)
		:Mat4()
	{
		this->set(type, angle);
	}
	Rot::Rot(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2)
		:Mat4()
	{
		this->set(mode, angle_0, angle_1, angle_2);
	}

	Rot::Rot(const Axis mode, const Vec3 &vAxis, const float angle_radians)
		:Mat4()
	{
		this->set(mode, vAxis, angle_radians);
	}

	Rot::Rot(const Orient type, const Vec3 &dof, const Vec3 &up)
		:Mat4()
	{
		this->set(type, dof, up);
	}

	Rot &Rot::operator = (const Quat &q)
	{
		this->set(q);

		return *this;
	}


	Rot::Rot(const Special val)
		:Mat4()
	{
		this->set(val);
	}

	Rot::Rot(const Quat &q)
		:Mat4(q)
	{
		this->privSetRotHint();
	}
	
	void Rot::set(const Special type)
	{
		Quat q(0.0f, 0.0f, 0.0f, 0.0f);
		switch(type)
		{
		case Special::Zero:
			q._qw = 0;
			*this = q;
			break;
		case Special::Identity:
			q._qw = 1;
			*this = q;
			break;
		default:
			assert(false);
			break;
		}
		this->privSetRotHint();
	}

	void Rot::set(const Rot1 type, const float angle)
	{
		float sinfloat = Trig::sin(angle);
		float cosfloat = Trig::cos(angle);
		switch(type)
		{
		case Rot1::X:
			_m0 = 1; _m1 = 0; _m2 = 0; _m3 = 0;
			_m4 = 0; _m5 = cosfloat; _m6 = sinfloat; _m7 = 0;
			_m8 = 0; _m9 = -sinfloat; _m10 = cosfloat; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
			break;
		case Rot1::Y:
			_m0 = cosfloat; _m1 = 0; _m2 = -sinfloat; _m3 = 0;
			_m4 = 0; _m5 = 1; _m6 = 0; _m7 = 0;
			_m8 = sinfloat; _m9 = 0; _m10 = cosfloat; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
			break;
		case Rot1::Z:
			_m0 = cosfloat; _m1 = sinfloat; _m2 = 0; _m3 = 0;
			_m4 = -sinfloat; _m5 = cosfloat; _m6 = 0; _m7 = 0;
			_m8 = 0; _m9 = 0; _m10 = 1; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
			break;
		default:
			assert(false);
		}
		this->privSetRotHint();
	}

	void Rot::set(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2)
	{

		float cx = Trig::cos(angle_0);
		float cy = Trig::cos(angle_1);
		float cz = Trig::cos(angle_2);

		float sx = Trig::sin(angle_0);
		float sy = Trig::sin(angle_1);
		float sz = Trig::sin(angle_2);

		switch(mode)
		{
		case Rot3::XYZ:
			_m0 = cy * cz;
			_m1 = cy * sz;
			_m2 = -sy;
			_m3 = 0.0f;

			_m4 = sx * sy * cz + cx * -sz;
			_m5 = sx * sy * sz + cx * cz;
			_m6 = sx * cy;
			_m7 = 0.0f;

			_m8 = cx * sy * cz + sx * sz;
			_m9 = cx * sy * sz + -sx * cz;
			_m10 = cx * cy;
			_m11 = 0.0f;

			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;

			break;
		case Rot3::XZY:
			// Rotation matrix for XZY order
			_m0 = cz * cy;
			_m1 = sz;
			_m2 = cz * -sy;
			_m3 = 0.0f;

			_m4 = cx * -sz * cy + sx * sy;
			_m5 = cx * cz;
			_m6 = cx * -sz * -sy + sx * cy;
			_m7 = 0.0f;

			_m8 = -sx * -sz * cy + cx * sy;
			_m9 = -sx * cz;
			_m10 = -sx * -sz * -sy + cx * cy;
			_m11 = 0.0f;

			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;

			break;
		case Rot3::YXZ:
			_m0 = cy * cz + -sy * -sx * -sz;
			_m1 = cy * sz + -sy * -sx * cz;
			_m2 = -sy * cx;
			_m3 = 0.0f;

			_m4 = cx * -sz;
			_m5 = cx * cz;
			_m6 = sx;
			_m7 = 0.0f;

			_m8 = sy * cz + cy * -sx * -sz;
			_m9 = sy * sz + cy * -sx * cz;
			_m10 = cy * cx;
			_m11 = 0.0f;

			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;

			break;
		case Rot3::YZX:
			_m0 = cy * cz;
			_m1 = cy * sz * cx + -sy * -sx;
			_m2 = cy * sz * sx + -sy * cx;
			_m3 = 0.0f;

			_m4 = -sz;
			_m5 = cz * cx;
			_m6 = cz * sx;
			_m7 = 0.0f;

			_m8 = sy * cz;
			_m9 = sy * sz * cx + cy * -sx;
			_m10 = sy * sz * sx + cy * cx;
			_m11 = 0.0f;

			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;

			break;
		case Rot3::ZXY:
			_m0 = cz * cy + sz * sx * sy;
			_m1 = sz * cx;
			_m2 = cz * -sy + sz * sx * cy;
			_m3 = 0.0f;

			_m4 = -sz * cy + cz * sx * sy;
			_m5 = cz * cx;
			_m6 = -sz * -sy + cz * sx * cy;
			_m7 = 0.0f;

			_m8 = cx * sy;
			_m9 = -sx;
			_m10 = cx * cy;
			_m11 = 0.0f;

			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;

			break;
		case Rot3::ZYX:
			_m0 = cz * cy;
			_m1 = sz * cx + cz * -sy * -sx;
			_m2 = sz * sx + cz * -sy * cx;
			_m3 = 0.0f;

			_m4 = -sz * cy;
			_m5 = cz * cx + -sz * -sy * -sx;
			_m6 = cz * sx + -sz * -sy * cx;
			_m7 = 0.0f;

			_m8 = sy;
			_m9 = cy * -sx;
			_m10 = cy * cx;
			_m11 = 0.0f;

			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;

			break;
		default:
			assert(false);
			break;
		}
		//this->_u_m15 |= (unsigned int)(Mat4::Hint::Rot);
		this->privSetRotHint();
	}

	void Rot::set(const Axis mode, const Vec3 &vAxis, const float angle_radians)
	{
		float s = Trig::sin(angle_radians);
		float c = Trig::cos(angle_radians);
		float t = 1 - c;
		switch(mode)
		{
		case Axis::AxisAngle:
		{
			// Normalize the axis vector
			Vec3 axis = vAxis.getNorm();

			// Set up the rotation matrix
			_m0 = t * axis[x] * axis[x] + c;
			_m1 = t * axis[x] * axis[y] + s * axis[z];
			_m2 = t * axis[x] * axis[z] - s * axis[y];
			_m3 = 0.0f;

			_m4 = t * axis[x] * axis[y] - s * axis[z];
			_m5 = t * axis[y] * axis[y] + c;
			_m6 = t * axis[y] * axis[z] + s * axis[x];
			_m7 = 0.0f;

			_m8 = t * axis[x] * axis[z] + s * axis[y];
			_m9 = t * axis[y] * axis[z] - s * axis[x];
			_m10 = t * axis[z] * axis[z] + c;
			_m11 = 0.0f;

			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;
			break;
		}
		case Axis::UnitAxisAngle:
		{
			// Set up the rotation matrix
			_m0 = t * vAxis[x] * vAxis[x] + c;
			_m1 = t * vAxis[x] * vAxis[y] + s * vAxis[z];
			_m2 = t * vAxis[x] * vAxis[z] - s * vAxis[y];
			_m3 = 0.0f;

			_m4 = t * vAxis[x] * vAxis[y] - s * vAxis[z];
			_m5 = t * vAxis[y] * vAxis[y] + c;
			_m6 = t * vAxis[y] * vAxis[z] + s * vAxis[x];
			_m7 = 0.0f;

			_m8 = t * vAxis[x] * vAxis[z] + s * vAxis[y];
			_m9 = t * vAxis[y] * vAxis[z] - s * vAxis[x];
			_m10 = t * vAxis[z] * vAxis[z] + c;
			_m11 = 0.0f;

			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;
			break;
		}
		default:
			assert(false);
			break;
		}
		this->privSetRotHint();
	}

	void Rot::set(const Orient type, const Vec3 &dof, const Vec3 &up)
	{
		Vec3 vDof = dof.getNorm();
		Vec3 vUp = up.getNorm();
		Vec3 vRight = vUp.cross(vDof);
		vUp = vDof.cross(vRight);

		switch(type)
		{
		case Orient::LocalToWorld:
			_m0 = vRight[x];
			_m1 = vRight[y];
			_m2 = vRight[z];
			_m3 = 0.0f;
			_m4 = vUp[x];
			_m5 = vUp[y];
			_m6 = vUp[z];
			_m7 = 0.0f;
			_m8 = vDof[x];
			_m9 = vDof[y];
			_m10 = vDof[z];
			_m11 = 0.0f;
			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;
			break;
		case Orient::WorldToLocal:
			_m0 = vRight[x];
			_m4 = vRight[y];
			_m8 = vRight[z];
			_m3 = 0.0f;
			_m1 = vUp[x];
			_m5 = vUp[y];
			_m9 = vUp[z];
			_m7 = 0.0f;
			_m2 = vDof[x];
			_m6 = vDof[y];
			_m10 = vDof[z];
			_m11 = 0.0f;
			_m12 = 0.0f;
			_m13 = 0.0f;
			_m14 = 0.0f;
			_m15 = 1.0f;
			break;
		default:
			assert(false);
		}
		this->privSetRotHint();
	}

	Mat4 Rot::operator * (const Mat4 &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
		out._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
		out._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;
		out._m3 = _m0 * A._m3 + _m1 * A._m7 + _m2 * A._m11;

		out._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
		out._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
		out._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;
		out._m7 = _m4 * A._m3 + _m5 * A._m7 + _m6 * A._m11;

		out._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
		out._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
		out._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;
		out._m11 = _m8 * A._m3 + _m9 * A._m7 + _m10 * A._m11;

		out._m12 = 0 * A._m0 + 0 * A._m4 + 0 * A._m8 + 1 * A._m12;
		out._m13 = 0 * A._m1 + 0 * A._m5 + 0 * A._m9 + 1 * A._m13;
		out._m14 = 0 * A._m2 + 0 * A._m6 + 0 * A._m10 + 1 * A._m14;
		out._m15 = 0 * A._m3 + 0 * A._m7 + 0 * A._m11 + 1 * A._m15;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}

	Rot Rot::operator * (const Quat &A) const
	{
		Rot qM(A);
		return *this * qM;


	}

	Rot &Rot::operator *= (const Quat &A)
	{
		Rot qM(A);
		*this = *this * qM;
		return *this;
	}

	Mat4 Rot::operator * (const Scale &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0;
		out._m1 = _m1 * A._m5;
		out._m2 = _m2 * A._m10;

		out._m4 = _m4 * A._m0;
		out._m5 = _m5 * A._m5;
		out._m6 = _m6 * A._m10;

		out._m8 = _m8 * A._m0;
		out._m9 = _m9 * A._m5;
		out._m10 = _m10 * A._m10;
		out._m15 = 1.0f;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}

	Rot Rot::operator * (const Rot &A) const
	{
		Rot out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
		out._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
		out._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;

		out._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
		out._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
		out._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;

		out._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
		out._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
		out._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;

		out._m15 = 1.0f;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}

	Rot &Rot::operator *= (const Rot &A)
	{

		Rot out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
		out._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
		out._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;

		out._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
		out._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
		out._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;

		out._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
		out._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
		out._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;

		out._m15 = 1.0f;
		out.privSetNewHint(myHint, yourHint);
		*this = out;

		return *this;
	}

	Mat4 Rot::operator * (const Trans &A) const
	{
		Mat4 out = *this;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m12 = A._m12;
		out._m13 = A._m13;
		out._m14 = A._m14;
		out._m15 = 1.0f;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}


	void Rot::set(const Quat &q)
	{
		this->_m0 = 1 - 2 * (q._qy * q._qy + q._qz * q._qz);
		this->_m1 = 2 * (q._qx * q._qy + q._qw * q._qz);
		this->_m2 = 2 * (q._qx * q._qz - q._qw * q._qy);


		this->_m4 = 2 * (q._qx * q._qy - q._qw * q._qz);
		this->_m5 = 1 - 2 * (q._qx * q._qx + q._qz * q._qz);
		this->_m6 = 2 * (q._qy * q._qz + q._qw * q._qx);


		this->_m8 = 2 * (q._qx * q._qz + q._qw * q._qy);
		this->_m9 = 2 * (q._qy * q._qz - q._qw * q._qx);
		this->_m10 = 1 - 2 * (q._qx * q._qx + q._qy * q._qy);

		this->_m15 = 1.0f;
		this->privSetRotHint();
	}




}

// ---  End of File ---
