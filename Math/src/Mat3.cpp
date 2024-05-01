#include "MathEngine.h"

namespace Azul
{
	// Do your magic here
	Mat3::Mat3()
		:_m0(0), _m1(0), _m2(0), _m3(0),
		_m4(0), _m5(0), _m6(0), _m7(0),
		_m8(0), _m9(0), _m10(0), _m11(0),
		_m12(0), _m13(0), _m14(0), _m15(0)
	{

	}

	Mat3 &Mat3::operator = (const Mat3 &A)
	{
		_m0 = A._m0; _m1 = A._m1; _m2 = A._m2; _m3 = 0;
		_m4 = A._m4; _m5 = A._m5; _m6 = A._m6; _m7 = 0;
		_m8 = A._m8; _m9 = A._m9; _m10 = A._m10; _m11 = 0;
		_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
		return *this;
	}

	Mat3::Mat3(const Mat3 &tM)
		:_m0(tM._m0), _m1(tM._m1), _m2(tM._m2), _m3(0),
		_m4(tM._m4), _m5(tM._m5), _m6(tM._m6), _m7(0),
		_m8(tM._m8), _m9(tM._m9), _m10(tM._m10), _m11(0),
		_m12(0), _m13(0), _m14(0), _m15(1)
	{

	}

	Mat3::~Mat3()
	{

	}

	Mat3::Mat3(const Vec3 &tV0, const Vec3 &tV1, const Vec3 &tV2)
		:_m0(tV0._vx), _m1(tV0._vy), _m2(tV0._vz), _m3(0),
		_m4(tV1._vx), _m5(tV1._vy), _m6(tV1._vz), _m7(0),
		_m8(tV2._vx), _m9(tV2._vy), _m10(tV2._vz), _m11(0),
		_m12(0), _m13(0), _m14(0), _m15(1)
	{

	}

	Mat3::Mat3(const Mat4 &m)
		:_m0(m._m0), _m1(m._m1), _m2(m._m2), _m3(0),
		_m4(m._m4), _m5(m._m5), _m6(m._m6), _m7(0),
		_m8(m._m8), _m9(m._m9), _m10(m._m10), _m11(0),
		_m12(0), _m13(0), _m14(0), _m15(1)
	{

	}

	Mat3::Mat3(const Special type)
	{
		switch(type)
		{
		case Special::Zero:
			_m0 = 0; _m1 = 0; _m2 = 0; _m3 = 0;
			_m4 = 0; _m5 = 0; _m6 = 0; _m7 = 0;
			_m8 = 0; _m9 = 0; _m10 = 0; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
			break;
		case Special::Identity:
			_m0 = 1; _m1 = 0; _m2 = 0; _m3 = 0;
			_m4 = 0; _m5 = 1; _m6 = 0; _m7 = 0;
			_m8 = 0; _m9 = 0; _m10 = 1; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
			break;
		default:
			assert(false);
		}
	}

	Vec3 Mat3::get(const Row3 type) const
	{
		float x;
		float y;
		float z;
		switch(type)
		{
		case Row3::i0:
			x = _m0; y = _m1; z = _m2;
			break;
		case Row3::i1:
			x = _m4; y = _m5; z = _m6;
			break;
		case Row3::i2:
			x = _m8; y = _m9; z = _m10;
			break;
		default:
			x = 0; y = 0; z = 0; //surpess warning
			assert(false);
		}
		return Vec3(x, y, z);
	}

	void Mat3::set(const Mat3 &mIn)
	{
		_m0 = mIn._m0; _m1 = mIn._m1; _m2 = mIn._m2;
		_m4 = mIn._m4; _m5 = mIn._m5; _m6 = mIn._m6;
		_m8 = mIn._m8; _m9 = mIn._m9; _m10 = mIn._m10;

	}
	void Mat3::set(const Special type)
	{
		switch(type)
		{
		case Special::Zero:
			_m0 = 0; _m1 = 0; _m2 = 0; _m3 = 0;
			_m4 = 0; _m5 = 0; _m6 = 0; _m7 = 0;
			_m8 = 0; _m9 = 0; _m10 = 0; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
			break;
		case Special::Identity:
			_m0 = 1; _m1 = 0; _m2 = 0; _m3 = 0;
			_m4 = 0; _m5 = 1; _m6 = 0; _m7 = 0;
			_m8 = 0; _m9 = 0; _m10 = 1; _m11 = 0;
			_m12 = 0; _m13 = 0; _m14 = 0; _m15 = 1;
			break;
		default:
			assert(false);
		}
	}
	void Mat3::set(const Row3 type, const Vec3 &V)
	{
		switch(type)
		{
		case Row3::i0:
			_m0 = V._vx; _m1 = V._vy; _m2 = V._vz;
			break;
		case Row3::i1:
			_m4 = V._vx; _m5 = V._vy; _m6 = V._vz;
			break;
		case Row3::i2:
			_m8 = V._vx; _m9 = V._vy; _m10 = V._vz;
			break;
		default:
			assert(false);
		}
	}
	void Mat3::set(const Vec3 &V0, const Vec3 &V1, const Vec3 &V2)
	{
		_m0 = V0._vx; _m1 = V0._vy; _m2 = V0._vz;
		_m4 = V1._vx; _m5 = V1._vy; _m6 = V1._vz;
		_m8 = V2._vx; _m9 = V2._vy; _m10 = V2._vz;
	}

	float &Mat3::operator[](const enum m0_enum) { return _m0; }
	float &Mat3::operator[](const enum m1_enum) { return _m1; }
	float &Mat3::operator[](const enum m2_enum) { return _m2; }
	float &Mat3::operator[](const enum m4_enum) { return _m4; }
	float &Mat3::operator[](const enum m5_enum) { return _m5; }
	float &Mat3::operator[](const enum m6_enum) { return _m6; }
	float &Mat3::operator[](const enum m8_enum) { return _m8; }
	float &Mat3::operator[](const enum m9_enum) { return _m9; }
	float &Mat3::operator[](const enum m10_enum) { return _m10; }

	float Mat3::operator[](const enum m0_enum) const { return _m0; }
	float Mat3::operator[](const enum m1_enum) const { return _m1; }
	float Mat3::operator[](const enum m2_enum) const { return _m2; }
	float Mat3::operator[](const enum m4_enum) const { return _m4; }
	float Mat3::operator[](const enum m5_enum) const { return _m5; }
	float Mat3::operator[](const enum m6_enum) const { return _m6; }
	float Mat3::operator[](const enum m8_enum) const { return _m8; }
	float Mat3::operator[](const enum m9_enum) const { return _m9; }
	float Mat3::operator[](const enum m10_enum) const { return _m10; }

	void Mat3::m0(const float v) { _m0 = v; }
	void Mat3::m1(const float v) { _m1 = v; }
	void Mat3::m2(const float v) { _m2 = v; }
	void Mat3::m4(const float v) { _m4 = v; }
	void Mat3::m5(const float v) { _m5 = v; }
	void Mat3::m6(const float v) { _m6 = v; }
	void Mat3::m8(const float v) { _m8 = v; }
	void Mat3::m9(const float v) { _m9 = v; }
	void Mat3::m10(const float v) { _m10 = v; }

	float Mat3::m0() const { return _m0; }
	float Mat3::m1() const { return _m1; }
	float Mat3::m2() const { return _m2; }
	float Mat3::m4() const { return _m4; }
	float Mat3::m5() const { return _m5; }
	float Mat3::m6() const { return _m6; }
	float Mat3::m8() const { return _m8; }
	float Mat3::m9() const { return _m9; }
	float Mat3::m10() const { return _m10; }


	Mat3 Mat3::operator + (void) const
	{
		return Mat3(*this);
	}
	Mat3 Mat3::operator + (const Mat3 &A) const
	{
		return Mat3(Vec3(_m0 + A._m0, _m1 + A._m1, _m2 + A._m2),
					Vec3(_m4 + A._m4, _m5 + A._m5, _m6 + A._m6),
					Vec3(_m8 + A._m8, _m9 + A._m9, _m10 + A._m10));
	}
	Mat3 &Mat3::operator += (const Mat3 &A)
	{
		_m0 = _m0 + A._m0; _m1 = _m1 + A._m1; _m2 = _m2 + A._m2;
		_m4 = _m4 + A._m4; _m5 = _m5 + A._m5; _m6 = _m6 + A._m6;
		_m8 = _m8 + A._m8; _m9 = _m9 + A._m9; _m10 = _m10 + A._m10;
		return *this;
	}

	Mat3 Mat3::operator - (void) const
	{
		return Mat3(Vec3(-_m0, -_m1, -_m2),
					Vec3(-_m4, -_m5, -_m6),
					Vec3(-_m8, -_m9, -_m10));
	}
	Mat3 Mat3::operator - (const Mat3 &A) const
	{
		return Mat3(Vec3(_m0 - A._m0, _m1 - A._m1, _m2 - A._m2),
					Vec3(_m4 - A._m4, _m5 - A._m5, _m6 - A._m6),
					Vec3(_m8 - A._m8, _m9 - A._m9, _m10 - A._m10));
	}
	Mat3 &Mat3::operator -= (const Mat3 &A)
	{
		_m0 = _m0 - A._m0; _m1 = _m1 - A._m1; _m2 = _m2 - A._m2;
		_m4 = _m4 - A._m4; _m5 = _m5 - A._m5; _m6 = _m6 - A._m6;
		_m8 = _m8 - A._m8; _m9 = _m9 - A._m9; _m10 = _m10 - A._m10;
		return *this;
	}

	float Mat3::det() const
	{
		return _m0 * (_m5 * _m10 - _m6 * _m9) - _m1 * (_m4 * _m10 - _m6 * _m8) + _m2 * (_m4 * _m9 - _m5 * _m8);
	}

	Mat3 &Mat3::T()
	{
		float m1 = _m4; float m2 = _m8;
		float m4 = _m1; float m6 = _m9;
		float m8 = _m2; float m9 = _m6;

		_m1 = m1;
		_m2 = m2;
		_m4 = m4;
		_m6 = m6;
		_m8 = m8;
		_m9 = m9;
		return *this;
	}

	// Transpose (const)
	Mat3 Mat3::getT() const
	{
		return Mat3(Vec3(_m0, _m4, _m8),
					Vec3(_m1, _m5, _m9),
					Vec3(_m2, _m6, _m10));
	}

	Mat3 Mat3::getInv() const
	{
		float det = this->det();
		if(Util::isZero(det, MATH_TOLERANCE))
		{
			assert(false);
			return Mat3();
		}

		float invDet = 1.0f / det;

		Mat3 invMat;

		invMat._m0 = (_m5 * _m10 - _m6 * _m9) * invDet;
		invMat._m1 = (_m2 * _m9 - _m1 * _m10) * invDet;
		invMat._m2 = (_m1 * _m6 - _m2 * _m5) * invDet;
		invMat._m4 = (_m6 * _m8 - _m4 * _m10) * invDet;
		invMat._m5 = (_m0 * _m10 - _m2 * _m8) * invDet;
		invMat._m6 = (_m2 * _m4 - _m0 * _m6) * invDet;
		invMat._m8 = (_m4 * _m9 - _m5 * _m8) * invDet;
		invMat._m9 = (_m1 * _m8 - _m0 * _m9) * invDet;
		invMat._m10 = (_m0 * _m5 - _m1 * _m4) * invDet;

		return invMat;
	}

	Mat3 &Mat3::inv()
	{
		*this = this->getInv();
		return *this;
	}

	bool Mat3::isEqual(const Mat3 &A, const float epsilon) const
	{
		return (_v0.isEqual(A._v0, epsilon) && _v1.isEqual(A._v1, epsilon) && _v2.isEqual(A._v2, epsilon));
	}

	bool Mat3::isIdentity(const float epsilon) const
	{
		Mat3 identity;
		Mat3 copy;

		identity.set(Special::Identity);
		copy.set(*this);

		return (copy.isEqual(identity, epsilon));
	}

	Mat3 Mat3::operator*(const float s) const
	{
		Mat3 result;
		result._m0 = _m0 * s;
		result._m1 = _m1 * s;
		result._m2 = _m2 * s;
		result._m4 = _m4 * s;
		result._m5 = _m5 * s;
		result._m6 = _m6 * s;
		result._m8 = _m8 * s;
		result._m9 = _m9 * s;
		result._m10 = _m10 * s;
		return result;
	}

	Mat3 operator*(const float scale, const Mat3 &A)
	{
		Mat3 result;
		result._m0 = A._m0 * scale;
		result._m1 = A._m1 * scale;
		result._m2 = A._m2 * scale;
		result._m4 = A._m4 * scale;
		result._m5 = A._m5 * scale;
		result._m6 = A._m6 * scale;
		result._m8 = A._m8 * scale;
		result._m9 = A._m9 * scale;
		result._m10 = A._m10 * scale;
		return result;
	}

	Mat3 &Mat3::operator*=(const float scale)
	{
		_m0 *= scale;
		_m1 *= scale;
		_m2 *= scale;
		_m4 *= scale;
		_m5 *= scale;
		_m6 *= scale;
		_m8 *= scale;
		_m9 *= scale;
		_m10 *= scale;
		return *this;
	}


	Mat3 Mat3::operator*(const Mat3 &A) const
	{
		Mat3 result;

		result._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
		result._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
		result._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;

		result._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
		result._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
		result._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;

		result._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
		result._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
		result._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;

		return result;
	}


	Mat3 &Mat3::operator*=(const Mat3 &A)
	{
		Mat3 temp = *this;

		_m0 = temp._m0 * A._m0 + temp._m1 * A._m4 + temp._m2 * A._m8;
		_m1 = temp._m0 * A._m1 + temp._m1 * A._m5 + temp._m2 * A._m9;
		_m2 = temp._m0 * A._m2 + temp._m1 * A._m6 + temp._m2 * A._m10;

		_m4 = temp._m4 * A._m0 + temp._m5 * A._m4 + temp._m6 * A._m8;
		_m5 = temp._m4 * A._m1 + temp._m5 * A._m5 + temp._m6 * A._m9;
		_m6 = temp._m4 * A._m2 + temp._m5 * A._m6 + temp._m6 * A._m10;

		_m8 = temp._m8 * A._m0 + temp._m9 * A._m4 + temp._m10 * A._m8;
		_m9 = temp._m8 * A._m1 + temp._m9 * A._m5 + temp._m10 * A._m9;
		_m10 = temp._m8 * A._m2 + temp._m9 * A._m6 + temp._m10 * A._m10;
		return *this;
	}

	void Mat3::Print(const char *pName) const
	{
		size_t pSize = strnlen_s(pName, 10);
		const char *blank = " ";
		Trace::out("[Mat3] %-*s  [m0]:%-8f  [m1]:%-8f  [m2]:%-8f	  \n", pSize, pName, this->_m0, this->_m1, this->_m2);
		Trace::out("       %-*s  [m4]:%-8f  [m5]:%-8f  [m6]:%-8f	  \n", pSize, blank, this->_m4, this->_m5, this->_m6);
		Trace::out("       %-*s  [m8]:%-8f  [m9]:%-8f [m10]:%-8f	  \n", pSize, blank, this->_m8, this->_m9, this->_m10);
	}

}

// ---  End of File ---
