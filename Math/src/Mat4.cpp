#include "MathEngine.h"
#include "Trig.h"


namespace Azul
{
	// Do your magic here
	Mat4::Mat4()
		:_m0(0), _m1(0), _m2(0), _m3(0),
		_m4(0), _m5(0), _m6(0), _m7(0),
		_m8(0), _m9(0), _m10(0), _m11(0),
		_m12(0), _m13(0), _m14(0), _m15(1.0f)
	{
		this->privSetGeneralHint();
	}

	Mat4 &Mat4::operator = (const Mat4 &A)
	{
		_m0 = A._m0; _m1 = A._m1; _m2 = A._m2; _m3 = A._m3;
		_m4 = A._m4; _m5 = A._m5; _m6 = A._m6; _m7 = A._m7;
		_m8 = A._m8; _m9 = A._m9; _m10 = A._m10; _m11 = A._m11;
		_m12 = A._m12; _m13 = A._m13; _m14 = A._m14; _m15 = A._m15;
		return *this;
	}

	Mat4 &Mat4::operator = (const Quat &q)
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

		return *this;
	}

	Mat4::Mat4(const Mat4 &tM)
		:_m0(tM._m0), _m1(tM._m1), _m2(tM._m2), _m3(tM._m3),
		_m4(tM._m4), _m5(tM._m5), _m6(tM._m6), _m7(tM._m7),
		_m8(tM._m8), _m9(tM._m9), _m10(tM._m10), _m11(tM._m11),
		_m12(tM._m12), _m13(tM._m13), _m14(tM._m14), _m15(tM._m15)
	{
		this->privSetGeneralHint();
	}

	Mat4::~Mat4()
	{

	}


	Mat4::Mat4(const Vec4 &tV0, const Vec4 &tV1, const Vec4 &tV2, const Vec4 &tV3)
		:_m0(tV0._vx), _m1(tV0._vy), _m2(tV0._vz), _m3(tV0._vw),
		_m4(tV1._vx), _m5(tV1._vy), _m6(tV1._vz), _m7(tV1._vw),
		_m8(tV2._vx), _m9(tV2._vy), _m10(tV2._vz), _m11(tV2._vw),
		_m12(tV3._vx), _m13(tV3._vy), _m14(tV3._vz), _m15(tV3._vw)
	{
		this->privSetGeneralHint();
	}



	Mat4::Mat4(const Special type)
	{
		this->set(type);
	}

	Mat4::Mat4(const Quat &q)
		:_m0(1 - 2 * (q._qy * q._qy + q._qz * q._qz)), _m1(2 * (q._qx * q._qy + q._qw * q._qz)), _m2(2 * (q._qx * q._qz - q._qw * q._qy)), _m3(0),
		_m4(2 * (q._qx * q._qy - q._qw * q._qz)), _m5(1 - 2 * (q._qx * q._qx + q._qz * q._qz)), _m6(2 * (q._qy * q._qz + q._qw * q._qx)), _m7(0),
		_m8(2 * (q._qx * q._qz + q._qw * q._qy)), _m9(2 * (q._qy * q._qz - q._qw * q._qx)), _m10(1 - 2 * (q._qx * q._qx + q._qy * q._qy)), _m11(0.0f),
		_m12(0.0f), _m13(0.0f), _m14(0.0f), _m15(1.0f)
	{
		privSetRotHint();
	}

	void Mat4::set(const Mat4 &tM)
	{
		_m0 = tM._m0;  _m1 = tM._m1;  _m2 = tM._m2;  _m3 = tM._m3;
		_m4 = tM._m4;  _m5 = tM._m5;  _m6 = tM._m6;  _m7 = tM._m7;
		_m8 = tM._m8;  _m9 = tM._m9;  _m10 = tM._m10; _m11 = tM._m11;
		_m12 = tM._m12; _m13 = tM._m13; _m14 = tM._m14; _m15 = tM._m15;
		this->privSetGeneralHint();
	}

	void Mat4::set(const Vec4 &V0, const Vec4 &V1, const Vec4 &V2, const Vec4 &V3)
	{
		_m0 = V0._vx;  _m1 = V0._vy;  _m2 = V0._vz;  _m3 = V0._vw;
		_m4 = V1._vx;  _m5 = V1._vy;  _m6 = V1._vz;  _m7 = V1._vw;
		_m8 = V2._vx;  _m9 = V2._vy;  _m10 = V2._vz; _m11 = V2._vw;
		_m12 = V3._vx; _m13 = V3._vy; _m14 = V3._vz; _m15 = V3._vw;
		this->privSetGeneralHint();
	}



	void Mat4::set(const Special type)
	{
		switch(type)
		{
		case Special::Zero:
			_m0 = 0; _m1 = 0; _m2 = 0; _m3 = 0;
			_m4 = 0; _m5 = 0; _m6 = 0; _m7 = 0;
			_m8 = 0; _m9 = 0; _m10 = 0; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 0;
			this->privSetGeneralHint();
			break;
		case Special::Identity:
			_m0 = 1; _m1 = 0; _m2 = 0; _m3 = 0;
			_m4 = 0; _m5 = 1; _m6 = 0; _m7 = 0;
			_m8 = 0; _m9 = 0; _m10 = 1; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
			this->privSetScaleHint();
			break;
		default:
			assert(false);
		}
	}

	void Mat4::set(const Row4 type, const Vec4 &V)
	{
		switch(type)
		{
		case Row4::i0:
			_m0 = V._vx; _m1 = V._vy; _m2 = V._vz; _m3 = V._vw;
			break;
		case Row4::i1:
			_m4 = V._vx; _m5 = V._vy; _m6 = V._vz; _m7 = V._vw;
			break;
		case Row4::i2:
			_m8 = V._vx; _m9 = V._vy; _m10 = V._vz; _m11 = V._vw;
			break;
		case Row4::i3:
			_m12 = V._vx; _m13 = V._vy; _m14 = V._vz; _m15 = V._vw;
			break;
		default:
			assert(false);
		}
		this->privSetGeneralHint();
	}

	Vec4 Mat4::get(const Row4 type) const
	{
		float x;
		float y;
		float z;
		float w;
		switch(type)
		{
		case Row4::i0:
			x = _m0; y = _m1; z = _m2; w = _m3;
			break;
		case Row4::i1:
			x = _m4; y = _m5; z = _m6; w = _m7;
			break;
		case Row4::i2:
			x = _m8; y = _m9; z = _m10; w = _m11;
			break;
		case Row4::i3:
			x = _m12; y = _m13; z = _m14; w = _m15;
			break;
		default:
			x = 0; y = 0; z = 0; w = 0; //surpess warning
			assert(false);
		}
		return Vec4(x, y, z, w);
	}

	void Mat4::set(const Quat &qIn)
	{
		Quat q = qIn.getNorm();
		assert(q.isNormalized());

		_m0 = 1 - 2 * (q._qy * q._qy + q._qz * q._qz);
		_m1 = 2 * (q._qx * q._qy + q._qw * q._qz);
		_m2 = 2 * (q._qx * q._qz - q._qw * q._qy);
		_m3 = 0.0f;
		_m4 = 2 * (q._qx * q._qy - q._qw * q._qz);
		_m5 = 1 - 2 * (q._qx * q._qx + q._qz * q._qz);
		_m6 = 2 * (q._qy * q._qz + q._qw * q._qx);
		_m7 = 0.0f;
		_m8 = 2 * (q._qx * q._qz + q._qw * q._qy);
		_m9 = 2 * (q._qy * q._qz - q._qw * q._qx);
		_m10 = 1 - 2 * (q._qx * q._qx + q._qy * q._qy);
		_m11 = 0.0f;

		_m12 = 0.0f;
		_m13 = 0.0f;
		_m14 = 0.0f;
		_m15 = 1.0f;
		privSetRotHint();

	}

	Mat4Proxy Mat4::operator[] (const enum m0_enum) { return Mat4Proxy(*this, this->_m0); }
	Mat4Proxy Mat4::operator[] (const enum m1_enum) { return  Mat4Proxy(*this, this->_m1); }
	Mat4Proxy Mat4::operator[] (const enum m2_enum) { return  Mat4Proxy(*this, this->_m2); }
	Mat4Proxy Mat4::operator[] (const enum m3_enum) { return  Mat4Proxy(*this, this->_m3); }
	Mat4Proxy Mat4::operator[] (const enum m4_enum) { return  Mat4Proxy(*this, this->_m4); }
	Mat4Proxy Mat4::operator[] (const enum m5_enum) { return  Mat4Proxy(*this, this->_m5); }
	Mat4Proxy Mat4::operator[] (const enum m6_enum) { return  Mat4Proxy(*this, this->_m6); }
	Mat4Proxy Mat4::operator[] (const enum m7_enum) { return  Mat4Proxy(*this, this->_m7); }
	Mat4Proxy Mat4::operator[] (const enum m8_enum) { return  Mat4Proxy(*this, this->_m8); }
	Mat4Proxy Mat4::operator[] (const enum m9_enum) { return  Mat4Proxy(*this, this->_m9); }
	Mat4Proxy Mat4::operator[] (const enum m10_enum) { return  Mat4Proxy(*this, this->_m10); }
	Mat4Proxy Mat4::operator[] (const enum m11_enum) { return  Mat4Proxy(*this, this->_m11); }
	Mat4Proxy Mat4::operator[] (const enum m12_enum) { return  Mat4Proxy(*this, this->_m12); }
	Mat4Proxy Mat4::operator[] (const enum m13_enum) { return  Mat4Proxy(*this, this->_m13); }
	Mat4Proxy Mat4::operator[] (const enum m14_enum) { return  Mat4Proxy(*this, this->_m14); }
	Mat4Proxy Mat4::operator[] (const enum m15_enum) { return  Mat4Proxy(*this, this->_m15); }

	float Mat4::operator[] (const enum m0_enum) const { return _m0; }
	float Mat4::operator[] (const enum m1_enum) const { return _m1; }
	float Mat4::operator[] (const enum m2_enum) const { return _m2; }
	float Mat4::operator[] (const enum m3_enum) const { return _m3; }
	float Mat4::operator[] (const enum m4_enum) const { return _m4; }
	float Mat4::operator[] (const enum m5_enum) const { return _m5; }
	float Mat4::operator[] (const enum m6_enum) const { return _m6; }
	float Mat4::operator[] (const enum m7_enum) const { return _m7; }
	float Mat4::operator[] (const enum m8_enum) const { return _m8; }
	float Mat4::operator[] (const enum m9_enum) const { return _m9; }
	float Mat4::operator[] (const enum m10_enum) const { return _m10; }
	float Mat4::operator[] (const enum m11_enum) const { return _m11; }
	float Mat4::operator[] (const enum m12_enum) const { return _m12; }
	float Mat4::operator[] (const enum m13_enum) const { return _m13; }
	float Mat4::operator[] (const enum m14_enum) const { return _m14; }
	float Mat4::operator[] (const enum m15_enum) const { return _m15; }

	void Mat4::m0(const float v) { _m0 = v; }
	void Mat4::m1(const float v) { _m1 = v; }
	void Mat4::m2(const float v) { _m2 = v; }
	void Mat4::m3(const float v) { _m3 = v; }
	void Mat4::m4(const float v) { _m4 = v; }
	void Mat4::m5(const float v) { _m5 = v; }
	void Mat4::m6(const float v) { _m6 = v; }
	void Mat4::m7(const float v) { _m7 = v; }
	void Mat4::m8(const float v) { _m8 = v; }
	void Mat4::m9(const float v) { _m9 = v; }
	void Mat4::m10(const float v) { _m10 = v; }
	void Mat4::m11(const float v) { _m11 = v; }
	void Mat4::m12(const float v) { _m12 = v; }
	void Mat4::m13(const float v) { _m13 = v; }
	void Mat4::m14(const float v) { _m14 = v; }
	void Mat4::m15(const float v) { _m15 = v; }

	float Mat4::m0() const { return _m0; }
	float Mat4::m1() const { return _m1; }
	float Mat4::m2() const { return _m2; }
	float Mat4::m3() const { return _m3; }
	float Mat4::m4() const { return _m4; }
	float Mat4::m5() const { return _m5; }
	float Mat4::m6() const { return _m6; }
	float Mat4::m7() const { return _m7; }
	float Mat4::m8() const { return _m8; }
	float Mat4::m9() const { return _m9; }
	float Mat4::m10() const { return _m10; }
	float Mat4::m11() const { return _m11; }
	float Mat4::m12() const { return _m12; }
	float Mat4::m13() const { return _m13; }
	float Mat4::m14() const { return _m14; }
	float Mat4::m15() const { return _m15; }

	float Mat4::det() const
	{

		return _m0 * (_m5 * (_m10 * _m15 - _m14 * _m11) - _m9 * (_m6 * _m15 - _m14 * _m7) + _m13 * (_m6 * _m11 - _m10 * _m7))
			- _m1 * (_m4 * (_m10 * _m15 - _m14 * _m11) - _m8 * (_m6 * _m15 - _m14 * _m7) + _m12 * (_m6 * _m11 - _m10 * _m7))
			+ _m2 * (_m4 * (_m9 * _m15 - _m13 * _m11) - _m8 * (_m5 * _m15 - _m13 * _m7) + _m12 * (_m5 * _m11 - _m9 * _m7))
			- _m3 * (_m4 * (_m9 * _m14 - _m13 * _m10) - _m8 * (_m5 * _m14 - _m13 * _m6) + _m12 * (_m5 * _m10 - _m9 * _m6));
	}

	// Transpose (non-const)
	Mat4 &Mat4::T()
	{
		float m1 = _m4; float m2 = _m8; float m3 = _m12;
		float m4 = _m1; float m6 = _m9; float m7 = _m13;
		float m8 = _m2; float m9 = _m6; float m11 = _m14;
		float m12 = _m3; float m13 = _m7; float m14 = _m11;

		_m1 = m1;
		_m2 = m2;
		_m3 = m3;
		_m4 = m4;
		_m6 = m6;
		_m7 = m7;
		_m8 = m8;
		_m9 = m9;
		_m11 = m11;
		_m12 = m12;
		_m13 = m13;
		_m14 = m14;

		return *this;
	}

	// Transpose (const)
	Mat4 Mat4::getT() const
	{
		return Mat4(Vec4(_m0, _m4, _m8, _m12),
					Vec4(_m1, _m5, _m9, _m13),
					Vec4(_m2, _m6, _m10, _m14),
					Vec4(_m3, _m7, _m11, _m15));
	}

	Mat4 Mat4::getInv() const
	{
		Mat4 invMat = *this;
		float invDet;

		switch(privGetHint())
		{
		case Hint::Generalize:
			invMat = getInvGeneralize();
			break;

		case Hint::Rot:
			invMat._m1 = _m4;
			invMat._m2 = _m8;
			invMat._m4 = _m1;
			invMat._m6 = _m9;
			invMat._m8 = _m2;
			invMat._m9 = _m6;
			break;

		case Hint::Trans:
			invMat._m12 = -_m12;
			invMat._m13 = -_m13;
			invMat._m14 = -_m14;
			break;

		case Hint::RotTrans:
			invMat._m1 = _m4;
			invMat._m2 = _m8;
			invMat._m4 = _m1;
			invMat._m6 = _m9;
			invMat._m8 = _m2;
			invMat._m9 = _m6;
			invMat._m12 = (-_m12 * invMat._m0) + (-_m13 * invMat._m4) + (-_m14 * invMat._m8);
			invMat._m13 = (-_m12 * invMat._m1) + (-_m13 * invMat._m5) + (-_m14 * invMat._m9);
			invMat._m14 = (-_m12 * invMat._m2) + (-_m13 * invMat._m6) + (-_m14 * invMat._m10);
			break;

		case Hint::Scale:
			invMat._m0 = 1 / invMat._m0;
			invMat._m5 = 1 / invMat._m5;
			invMat._m10 = 1 / invMat._m10;
			break;

		case Hint::RotScale:
			invDet = 1.0f / (_m0 * (_m5 * _m10 - _m6 * _m9) - _m1 * (_m4 * _m10 - _m6 * _m8) + _m2 * (_m4 * _m9 - _m5 * _m8));
			invMat._m0 = (_m5 * _m10 - _m6 * _m9) * invDet;
			invMat._m1 = (_m2 * _m9 - _m1 * _m10) * invDet;
			invMat._m2 = (_m1 * _m6 - _m2 * _m5) * invDet;
			invMat._m4 = (_m6 * _m8 - _m4 * _m10) * invDet;
			invMat._m5 = (_m0 * _m10 - _m2 * _m8) * invDet;
			invMat._m6 = (_m2 * _m4 - _m0 * _m6) * invDet;
			invMat._m8 = (_m4 * _m9 - _m5 * _m8) * invDet;
			invMat._m9 = (_m1 * _m8 - _m0 * _m9) * invDet;
			invMat._m10 = (_m0 * _m5 - _m1 * _m4) * invDet;


			break;
		case Hint::TransScale:
			invMat._m0 = 1 / invMat._m0;
			invMat._m5 = 1 / invMat._m5;
			invMat._m10 = 1 / invMat._m10;
			invMat._m12 = (-_m12 * invMat._m0);
			invMat._m13 = (-_m13 * invMat._m5);
			invMat._m14 = (-_m14 * invMat._m10);
			break;

		case Hint::Affine:
			invDet = 1.0f / (_m0 * (_m5 * _m10 - _m6 * _m9) - _m1 * (_m4 * _m10 - _m6 * _m8) + _m2 * (_m4 * _m9 - _m5 * _m8));

			invMat._m0 = (_m5 * _m10 - _m6 * _m9) * invDet;
			invMat._m1 = (_m2 * _m9 - _m1 * _m10) * invDet;
			invMat._m2 = (_m1 * _m6 - _m2 * _m5) * invDet;
			invMat._m4 = (_m6 * _m8 - _m4 * _m10) * invDet;
			invMat._m5 = (_m0 * _m10 - _m2 * _m8) * invDet;
			invMat._m6 = (_m2 * _m4 - _m0 * _m6) * invDet;
			invMat._m8 = (_m4 * _m9 - _m5 * _m8) * invDet;
			invMat._m9 = (_m1 * _m8 - _m0 * _m9) * invDet;
			invMat._m10 = (_m0 * _m5 - _m1 * _m4) * invDet;
			invMat._m12 = (-_m12 * invMat._m0) + (-_m13 * invMat._m4) + (-_m14 * invMat._m8);
			invMat._m13 = (-_m12 * invMat._m1) + (-_m13 * invMat._m5) + (-_m14 * invMat._m9);
			invMat._m14 = (-_m12 * invMat._m2) + (-_m13 * invMat._m6) + (-_m14 * invMat._m10);
			break;

		default:

			assert(false);
		}
		return invMat;
	}


	Mat4 Mat4::getInvGeneralize() const
	{
		Mat4 invMat;

		invMat._m0 = _m5 * _m10 * _m15 -
			_m5 * _m11 * _m14 -
			_m9 * _m6 * _m15 +
			_m9 * _m7 * _m14 +
			_m13 * _m6 * _m11 -
			_m13 * _m7 * _m10;

		invMat._m4 = -_m4 * _m10 * _m15 +
			_m4 * _m11 * _m14 +
			_m8 * _m6 * _m15 -
			_m8 * _m7 * _m14 -
			_m12 * _m6 * _m11 +
			_m12 * _m7 * _m10;

		invMat._m8 = _m4 * _m9 * _m15 -
			_m4 * _m11 * _m13 -
			_m8 * _m5 * _m15 +
			_m8 * _m7 * _m13 +
			_m12 * _m5 * _m11 -
			_m12 * _m7 * _m9;

		invMat._m12 = -_m4 * _m9 * _m14 +
			_m4 * _m10 * _m13 +
			_m8 * _m5 * _m14 -
			_m8 * _m6 * _m13 -
			_m12 * _m5 * _m10 +
			_m12 * _m6 * _m9;

		invMat._m1 = -_m1 * _m10 * _m15 +
			_m1 * _m11 * _m14 +
			_m9 * _m2 * _m15 -
			_m9 * _m3 * _m14 -
			_m13 * _m2 * _m11 +
			_m13 * _m3 * _m10;

		invMat._m5 = _m0 * _m10 * _m15 -
			_m0 * _m11 * _m14 -
			_m8 * _m2 * _m15 +
			_m8 * _m3 * _m14 +
			_m12 * _m2 * _m11 -
			_m12 * _m3 * _m10;

		invMat._m9 = -_m0 * _m9 * _m15 +
			_m0 * _m11 * _m13 +
			_m8 * _m1 * _m15 -
			_m8 * _m3 * _m13 -
			_m12 * _m1 * _m11 +
			_m12 * _m3 * _m9;

		invMat._m13 = _m0 * _m9 * _m14 -
			_m0 * _m10 * _m13 -
			_m8 * _m1 * _m14 +
			_m8 * _m2 * _m13 +
			_m12 * _m1 * _m10 -
			_m12 * _m2 * _m9;

		invMat._m2 = _m1 * _m6 * _m15 -
			_m1 * _m7 * _m14 -
			_m5 * _m2 * _m15 +
			_m5 * _m3 * _m14 +
			_m13 * _m2 * _m7 -
			_m13 * _m3 * _m6;

		invMat._m6 = -_m0 * _m6 * _m15 +
			_m0 * _m7 * _m14 +
			_m4 * _m2 * _m15 -
			_m4 * _m3 * _m14 -
			_m12 * _m2 * _m7 +
			_m12 * _m3 * _m6;

		invMat._m10 = _m0 * _m5 * _m15 -
			_m0 * _m7 * _m13 -
			_m4 * _m1 * _m15 +
			_m4 * _m3 * _m13 +
			_m12 * _m1 * _m7 -
			_m12 * _m3 * _m5;

		invMat._m14 = -_m0 * _m5 * _m14 +
			_m0 * _m6 * _m13 +
			_m4 * _m1 * _m14 -
			_m4 * _m2 * _m13 -
			_m12 * _m1 * _m6 +
			_m12 * _m2 * _m5;

		invMat._m3 = -_m1 * _m6 * _m11 +
			_m1 * _m7 * _m10 +
			_m5 * _m2 * _m11 -
			_m5 * _m3 * _m10 -
			_m9 * _m2 * _m7 +
			_m9 * _m3 * _m6;

		invMat._m7 = _m0 * _m6 * _m11 -
			_m0 * _m7 * _m10 -
			_m4 * _m2 * _m11 +
			_m4 * _m3 * _m10 +
			_m8 * _m2 * _m7 -
			_m8 * _m3 * _m6;

		invMat._m11 = -_m0 * _m5 * _m11 +
			_m0 * _m7 * _m9 +
			_m4 * _m1 * _m11 -
			_m4 * _m3 * _m9 -
			_m8 * _m1 * _m7 +
			_m8 * _m3 * _m5;

		invMat._m15 = _m0 * _m5 * _m10 -
			_m0 * _m6 * _m9 -
			_m4 * _m1 * _m10 +
			_m4 * _m2 * _m9 +
			_m8 * _m1 * _m6 -
			_m8 * _m2 * _m5;

		float det = _m0 * invMat._m0 + _m1 * invMat._m4 + _m2 * invMat._m8 + _m3 * invMat._m12;

		if(det == 0)
		{

			assert(false);
			return Mat4();
		}

		det = 1.0f / det;


		invMat._m0 *= det;

		invMat._m4 *= det;

		invMat._m8 *= det;

		invMat._m12 *= det;

		invMat._m1 *= det;

		invMat._m5 *= det;

		invMat._m9 *= det;

		invMat._m13 *= det;

		invMat._m2 *= det;

		invMat._m6 *= det;

		invMat._m10 *= det;

		invMat._m14 *= det;

		invMat._m3 *= det;

		invMat._m7 *= det;

		invMat._m11 *= det;

		invMat._m15 *= det;

		return invMat;
	}





	Mat4 &Mat4::inv()
	{
		*this = this->getInv();
		return *this;
	}

	bool Mat4::isEqual(const Mat4 &A, const float epsilon) const
	{
		if(_v0.isEqual(A._v0, epsilon) && _v1.isEqual(A._v1, epsilon) && _v2.isEqual(A._v2, epsilon) && _v3.isEqual(A._v3, epsilon))
		{
			return true;
		}
		return false;
	}

	bool Mat4::isIdentity(const float epsilon) const
	{
		Mat4 identity;
		Mat4 copy;

		identity.set(Special::Identity);
		copy.set(*this);

		if(copy.isEqual(identity, epsilon))
		{
			return true;
		}
		return false;
	}

	bool Mat4::isRotation(const float epsilon) const
	{
		// Extract the 3x3 rotation matrix from the 4x4 matrix
		Mat3 rotMat(*this);
		// Check if the matrix is orthogonal
		Mat3 transposeMat = rotMat.getT();
		Mat3 productMat = rotMat * transposeMat;

		// Check if the product is an identity matrix
		bool isId = productMat.isIdentity(epsilon);

		// Check if the determinant of the rotation matrix is 1
		float det = rotMat.det();
		bool detOne = Util::isEqual(det, 1.0f, epsilon);

		return isId && detOne;
	}

	Mat4 Mat4::operator + (void) const
	{
		return *this;
	}

	Mat4 Mat4::operator + (const Mat4 &A) const
	{
		Mat4 ret = Mat4(_v0 + A._v0, _v1 + A._v1, _v2 + A._v2, _v3 + A._v3);
		ret.privSetGeneralHint();
		return ret;
	}

	Mat4 &Mat4::operator += (const Mat4 &A)
	{
		_v0 += A._v0;
		_v1 += A._v1;
		_v2 += A._v2;
		_v3 += A._v3;
		this->privSetGeneralHint();
		return *this;
	}

	Mat4 Mat4::operator - (void) const
	{
		Mat4 ret = Mat4(-_v0, -_v1, -_v2, -_v3);
		ret.privSetGeneralHint();
		return ret;
	}

	Mat4 Mat4::operator - (const Mat4 &A) const
	{
		Mat4 ret = Mat4(_v0 - A._v0, _v1 - A._v1, _v2 - A._v2, _v3 - A._v3);
		ret.privSetGeneralHint();
		return ret;
	}

	Mat4 &Mat4::operator -= (const Mat4 &A)
	{
		_v0 -= A._v0;
		_v1 -= A._v1;
		_v2 -= A._v2;
		_v3 -= A._v3;
		this->privSetGeneralHint();
		return *this;
	}


	Mat4 Mat4::operator * (const float s) const
	{
		Mat4 ret = Mat4(_v0 * s, _v1 * s, _v2 * s, _v3 * s);
		ret.privSetGeneralHint();
		return ret;
	}


	Mat4 operator * (const float scale, const Mat4 &A)
	{
		Mat4 ret = A * scale;
		ret.privSetGeneralHint();
		return ret;
	}


	Mat4 &Mat4::operator *= (const float scale)
	{
		_v0 *= scale;
		_v1 *= scale;
		_v2 *= scale;
		_v3 *= scale;
		this->privSetGeneralHint();
		return *this;
	}

	Mat4 Mat4::operator*(const Mat4 &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8 + _m3 * A._m12;
		out._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9 + _m3 * A._m13;
		out._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10 + _m3 * A._m14;
		out._m3 = _m0 * A._m3 + _m1 * A._m7 + _m2 * A._m11 + _m3 * A._m15;

		out._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8 + _m7 * A._m12;
		out._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9 + _m7 * A._m13;
		out._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10 + _m7 * A._m14;
		out._m7 = _m4 * A._m3 + _m5 * A._m7 + _m6 * A._m11 + _m7 * A._m15;

		out._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8 + _m11 * A._m12;
		out._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9 + _m11 * A._m13;
		out._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10 + _m11 * A._m14;
		out._m11 = _m8 * A._m3 + _m9 * A._m7 + _m10 * A._m11 + _m11 * A._m15;

		out._m12 = _m12 * A._m0 + _m13 * A._m4 + _m14 * A._m8 + _m15 * A._m12;
		out._m13 = _m12 * A._m1 + _m13 * A._m5 + _m14 * A._m9 + _m15 * A._m13;
		out._m14 = _m12 * A._m2 + _m13 * A._m6 + _m14 * A._m10 + _m15 * A._m14;
		out._m15 = _m12 * A._m3 + _m13 * A._m7 + _m14 * A._m11 + _m15 * A._m15;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}

	Mat4 &Mat4::operator*=(const Mat4 &A)
	{
		Mat4 temp = (*this) * A;
		(*this) = temp;
		return *this;
	}



	void Mat4::Print(const char *pName) const
	{
		size_t pSize = strnlen_s(pName, 10);
		const char *blank = " ";
		Trace::out("[Mat4] %-*s  [m0]:%-8f  [m1]:%-8f  [m2]:%-8f  [m3]:%-8f	  \n", pSize, pName, this->_m0, this->_m1, this->_m2, this->_m3);
		Trace::out("       %-*s  [m4]:%-8f  [m5]:%-8f  [m6]:%-8f  [m7]:%-8f	  \n", pSize, blank, this->_m4, this->_m5, this->_m6, this->_m7);
		Trace::out("       %-*s  [m8]:%-8f  [m9]:%-8f [m10]:%-8f [m11]:%-8f	  \n", pSize, blank, this->_m8, this->_m9, this->_m10, this->_m11);
		Trace::out("       %-*s [m12]:%-8f [m13]:%-8f [m14]:%-8f [m15]:%-8f	  \n", pSize, blank, this->_m12, this->_m13, this->_m14, this->_m15);
	}





	Mat4 Mat4::operator * (const Quat &q) const
	{
		Mat4 qM(q);
		Hint myHint = this->privGetHint();
		Mat4 res = *this * qM;
		res.privSetNewHint(myHint, Hint::Rot);
		return res;

	}
	Mat4 &Mat4::operator *= (const Quat &q)
	{
		Mat4 qM(q);
		Hint myHint = this->privGetHint();
		*this *= qM;
		privSetNewHint(myHint, Hint::Rot);
		return *this;
	}

	Mat4 Mat4::operator * (const Scale &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();


		out._m0 = _m0 * A._m0;
		out._m1 = _m1 * A._m5;
		out._m2 = _m2 * A._m10;
		out._m3 = _m3;

		out._m4 = _m4 * A._m0;
		out._m5 = _m5 * A._m5;
		out._m6 = _m6 * A._m10;
		out._m7 = _m7;

		out._m8 = _m8 * A._m0;
		out._m9 = _m9 * A._m5;
		out._m10 = _m10 * A._m10;
		out._m11 = _m11;

		out._m12 = _m12 * A._m0;
		out._m13 = _m13 * A._m5;
		out._m14 = _m14 * A._m10;
		out._m15 = _m15;



		out.privSetNewHint(myHint, yourHint);

		return out;
	}
	Mat4 &Mat4::operator *= (const Scale &A)
	{

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();



		this->_m0 = _m0 * A._m0;
		this->_m1 = _m1 * A._m5;
		this->_m2 = _m2 * A._m10;
		//this->_m3 = _m3;

		this->_m4 = _m4 * A._m0;
		this->_m5 = _m5 * A._m5;
		this->_m6 = _m6 * A._m10;
		//this->_m7 = _m7;

		this->_m8 = _m8 * A._m0;
		this->_m9 = _m9 * A._m5;
		this->_m10 = _m10 * A._m10;
		//this->_m11 = _m11;

		this->_m12 = _m12 * A._m0;
		this->_m13 = _m13 * A._m5;
		this->_m14 = _m14 * A._m10;
		this->_m15 = _m15;



		this->privSetNewHint(myHint, yourHint);

		return *this;
	}

	Mat4 Mat4::operator * (const Rot &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
		out._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
		out._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;
		out._m3 = _m3;

		out._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
		out._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
		out._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;
		out._m7 = _m7;

		out._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
		out._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
		out._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;
		out._m11 = _m11;

		out._m12 = _m12 * A._m0 + _m13 * A._m4 + _m14 * A._m8;
		out._m13 = _m12 * A._m1 + _m13 * A._m5 + _m14 * A._m9;
		out._m14 = _m12 * A._m2 + _m13 * A._m6 + _m14 * A._m10;
		out._m15 = _m15;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}
	Mat4 &Mat4::operator *= (const Rot &A)
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
		out._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
		out._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;
		out._m3 = _m3;

		out._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
		out._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
		out._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;
		out._m7 = _m7;

		out._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
		out._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
		out._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;
		out._m11 = _m11;

		out._m12 = _m12 * A._m0 + _m13 * A._m4 + _m14 * A._m8;
		out._m13 = _m12 * A._m1 + _m13 * A._m5 + _m14 * A._m9;
		out._m14 = _m12 * A._m2 + _m13 * A._m6 + _m14 * A._m10;
		out._m15 = _m15;
		out.privSetNewHint(myHint, yourHint);
		*this = out;

		return *this;
	}

	Mat4 Mat4::operator * (const Trans &A) const
	{
		Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		out._m0 = _m0 + _m3 * A._m12;
		out._m1 = _m1 + _m3 * A._m13;
		out._m2 = _m2 + _m3 * A._m14;
		out._m3 = _m3;

		out._m4 = _m4 + _m7 * A._m12;
		out._m5 = _m5 + _m7 * A._m13;
		out._m6 = _m6 + _m7 * A._m14;
		out._m7 = _m7;

		out._m8 = _m8 + _m11 * A._m12;
		out._m9 = _m9 + _m11 * A._m13;
		out._m10 = _m10 + _m11 * A._m14;
		out._m11 = _m11;

		out._m12 = _m12 + _m15 * A._m12;
		out._m13 = _m13 + _m15 * A._m13;
		out._m14 = _m14 + _m15 * A._m14;
		out._m15 = _m15;
		out.privSetNewHint(myHint, yourHint);

		return out;
	}
	Mat4 &Mat4::operator *= (const Trans &A)
	{
		//Mat4 out;

		Hint myHint = this->privGetHint();
		Hint yourHint = A.privGetHint();

		this->_m0 = _m0 + _m3 * A._m12;
		this->_m1 = _m1 + _m3 * A._m13;
		this->_m2 = _m2 + _m3 * A._m14;
		//this->_m3 = _m3;
		this->_m4 = _m4 + _m7 * A._m12;
		this->_m5 = _m5 + _m7 * A._m13;
		this->_m6 = _m6 + _m7 * A._m14;
		//this->_m7 = _m7;
		this->_m8 = _m8 + _m11 * A._m12;
		this->_m9 = _m9 + _m11 * A._m13;
		this->_m10 = _m10 + _m11 * A._m14;
		//this->_m11 = _m11;
		this->_m12 = _m12 + _m15 * A._m12;
		this->_m13 = _m13 + _m15 * A._m13;
		this->_m14 = _m14 + _m15 * A._m14;
		//this->_m15 = _m15;
		privSetNewHint(myHint, yourHint);

		return *this;
	}
}

// ---  End of File ---
