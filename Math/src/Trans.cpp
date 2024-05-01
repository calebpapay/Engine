
//2024. Caleb Papay
//-------------

#include "MathEngine.h"

namespace Azul
{
	// Do your magic here

	Trans::Trans()
		:Mat4()
	{

	}


	Trans::Trans(const float tx, const float ty, const float tz)
	{
		this->set(tx, ty, tz);
	}

	Trans::Trans(const Vec3 &vTrans)
	{
		this->set(vTrans);
	}


	// Set 
	void Trans::set(const float tx, const float ty, const float tz)
	{
		_m0 = 1; _m1 = 0; _m2 = 0; _m3 = 0;
		_m4 = 0; _m5 = 1; _m6 = 0; _m7 = 0;
		_m8 = 0; _m9 = 0; _m10 = 1; _m11 = 0;
		_m12 = tx; _m13 = ty; _m14 = tz; _m15 = 1;
		this->privSetTransHint();
	}

	void Trans::set(const Vec3 &vTrans)
	{
		_m0 = 1; _m1 = 0; _m2 = 0; _m3 = 0;
		_m4 = 0; _m5 = 1; _m6 = 0; _m7 = 0;
		_m8 = 0; _m9 = 0; _m10 = 1; _m11 = 0;
		_m12 = vTrans[x]; _m13 = vTrans[y]; _m14 = vTrans[z]; _m15 = 1;
		this->privSetTransHint();
	}




	Mat4 Trans::operator * (const Mat4 &A) const
	{
		Mat4 out = A;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = 1 * A._m0;
		out._m1 = 1 * A._m1;
		out._m2 = 1 * A._m2;
		out._m3 = 1 * A._m3;

		out._m4 = 1 * A._m4;
		out._m5 = 1 * A._m5;
		out._m6 = 1 * A._m6;
		out._m7 = 1 * A._m7;

		out._m8 = 1 * A._m8;
		out._m9 = 1 * A._m9;
		out._m10 = 1 * A._m10;
		out._m11 = 1 * A._m11;

		out._m12 = _m12 * A._m0 + _m13 * A._m4 + _m14 * A._m8 + A._m12;
		out._m13 = _m12 * A._m1 + _m13 * A._m5 + _m14 * A._m9 + A._m13;
		out._m14 = _m12 * A._m2 + _m13 * A._m6 + _m14 * A._m10 + A._m14;
		out._m15 = _m12 * A._m3 + _m13 * A._m7 + _m14 * A._m11 + A._m15;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}

	Mat4 Trans::operator * (const Quat &q) const
	{
		Mat4 qM(q);
		return *this * qM;

	}

	Mat4 Trans::operator * (const Scale &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = A._m0;

		out._m5 = A._m5;

		out._m10 = A._m10;


		out._m12 = _m12 * A._m0 + _m13 * A._m4 + _m14 * A._m8 + A._m12;
		out._m13 = _m12 * A._m1 + _m13 * A._m5 + _m14 * A._m9 + A._m13;
		out._m14 = _m12 * A._m2 + _m13 * A._m6 + _m14 * A._m10 + A._m14;
		out._m15 = _m12 * A._m3 + _m13 * A._m7 + _m14 * A._m11 + A._m15;
		out.privSetNewHint(myHint, yourHint);

		return out;

	}

	Mat4 Trans::operator * (const Rot &A) const
	{
		Mat4 out = A;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();


		out._m12 = _m12 * A._m0 + _m13 * A._m4 + _m14 * A._m8;
		out._m13 = _m12 * A._m1 + _m13 * A._m5 + _m14 * A._m9;
		out._m14 = _m12 * A._m2 + _m13 * A._m6 + _m14 * A._m10;
		out._m15 = 1.0f;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}

	Trans Trans::operator * (const Trans &A) const
	{
		Trans out = A;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m12 = _m12 + A._m12;
		out._m13 = _m13 + A._m13;
		out._m14 = _m14 + A._m14;
		out._m15 = 1.0f;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}

	Trans &Trans::operator *= (const Trans &A)
	{
		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		_m12 = _m12 + A._m12;
		_m13 = _m13 + A._m13;
		_m14 = _m14 + A._m14;
		_m15 = 1.0f;
		privSetNewHint(myHint, yourHint);

		return *this;
	}


}

// ---  End of File ---
