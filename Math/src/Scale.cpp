#include "MathEngine.h"

namespace Azul
{
	// Do your magic here

	Scale::Scale()
		:Mat4()
	{

	}

	// Constructors
	Scale::Scale(const float sx, const float sy, const float sz)
	{
		this->set(sx, sy, sz);
	}
	Scale::Scale(const Vec3 &vScale)
	{
		this->set(vScale);
	}

	// Set 
	void Scale::set(const float sx, const float sy, const float sz)
	{
		_m0 = sx; _m1 = 0; _m2 = 0; _m3 = 0;
		_m4 = 0; _m5 = sy; _m6 = 0; _m7 = 0;
		_m8 = 0; _m9 = 0; _m10 = sz; _m11 = 0;
		_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
		this->privSetScaleHint();
	}
	void Scale::set(const Vec3 &vScale)
	{
		_m0 = vScale[x]; _m1 = 0; _m2 = 0; _m3 = 0;
		_m4 = 0; _m5 = vScale[y]; _m6 = 0; _m7 = 0;
		_m8 = 0; _m9 = 0; _m10 = vScale[z]; _m11 = 0;
		_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
		this->privSetScaleHint();
	}

	Mat4 Scale::operator * (const Mat4 &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0;
		out._m1 = _m0 * A._m1;
		out._m2 = _m0 * A._m2;
		out._m3 = _m0 * A._m3;

		out._m4 = _m5 * A._m4;
		out._m5 = _m5 * A._m5;
		out._m6 = _m5 * A._m6;
		out._m7 = _m5 * A._m7;

		out._m8 = _m10 * A._m8;
		out._m9 = _m10 * A._m9;
		out._m10 = _m10 * A._m10;
		out._m11 = _m10 * A._m11;

		out._m12 = A._m12;
		out._m13 = A._m13;
		out._m14 = A._m14;
		out._m15 = A._m15;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}


	Mat4 Scale::operator * (const Quat &q) const
	{
		Mat4 qM(q);
		return *this * qM;
	}


	Scale Scale::operator * (const Scale &A) const
	{
		Scale out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0;

		out._m5 = _m5 * A._m5;

		out._m10 = _m10 * A._m10;

		out._m15 = 1.0f;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}

	Scale &Scale::operator *= (const Scale &A)
	{

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		_m0 = _m0 * A._m0;

		_m5 = _m5 * A._m5;

		_m10 = _m10 * A._m10;

		_m15 = 1.0f;
		privSetNewHint(myHint, yourHint);

		return *this;
	}


	Mat4 Scale::operator * (const Rot &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0;
		out._m1 = _m0 * A._m1;
		out._m2 = _m0 * A._m2;

		out._m4 = _m5 * A._m4;
		out._m5 = _m5 * A._m5;
		out._m6 = _m5 * A._m6;


		out._m8 = _m10 * A._m8;
		out._m9 = _m10 * A._m9;
		out._m10 = _m10 * A._m10;

		out._m15 = 1.0f;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}


	Mat4 Scale::operator * (const Trans &A) const
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

}

// ---  End of File ---
