#include "MathEngine.h"

namespace Azul
{

	Quat::Quat(void)
		:_qx(0.0f), _qy(0.0f), _qz(0.0f), _qw(1.0f)
	{
	}

	Quat::Quat(const Quat &qIn)
		:_qx(qIn._qx), _qy(qIn._qy), _qz(qIn._qz), _qw(qIn._qw)
	{
	}

	Quat &Quat::operator=(const Quat &q)
	{
		_qx = q._qx;
		_qy = q._qy;
		_qz = q._qz;
		_qw = q._qw;

		return *this;
	}

	Quat::Quat(const Vec3 &vect, const float real)
		:_qx(vect._vx), _qy(vect._vy), _qz(vect._vz), _qw(real)
	{

	}

	Quat::Quat(const float vx, const float vy, const float vz, const float real)
		:_qx(vx), _qy(vy), _qz(vz), _qw(real)
	{

	}

	Quat::Quat(const Rot &M)
		:Quat()
	{
		//needs to be ROT no?
		this->set(M);
	}

	Quat::Quat(const Special  value)
		:Quat()
	{
		this->set(value);
	}

	Quat::Quat(const Rot1 type, const float angle)
		:Quat()
	{
		this->set(type, angle);
	}

	Quat::Quat(const Rot3 type, const float angle_x, const float angle_y, const float angle_z)
		:Quat()
	{
		this->set(type, angle_x, angle_y, angle_z);
	}

	Quat::Quat(const Axis type, const Vec3 &vAxis, const float angle_radians)
		:Quat()
	{
		this->set(type, vAxis, angle_radians);
	}

	Quat::Quat(const Orient type, const Vec3 &dof, const Vec3 &up)
		:Quat()
	{
		this->set(type, dof, up);
	}

	Quat::~Quat(void)
	{

	}



	Quat &Quat::operator=(const Rot &M)
	{
		this->set(M);
		return *this;
	}

	void Quat::set(const Special type)
	{
		switch(type)
		{
		case Special::Zero:
			_qx = 0.0f;
			_qy = 0.0f;
			_qz = 0.0f;
			_qw = 0.0f;
			break;
		case Special::Identity:
			_qx = 0.0f;
			_qy = 0.0f;
			_qz = 0.0f;
			_qw = 1.0f;
			break;
		default:
			assert(false);
		}
	}

	void Quat::set(const Rot1 type, const float angle)
	{

		float halfangle = angle * 0.5f;
		float sin_halfangle = Trig::sin(halfangle);
		float cos_halfangle = Trig::cos(halfangle);
		switch(type)
		{
		case Rot1::X:
			_qx = sin_halfangle;
			_qy = 0.0f;
			_qz = 0.0f;
			_qw = cos_halfangle;
			break;
		case Rot1::Y:
			_qx = 0.0f;
			_qy = sin_halfangle;
			_qz = 0.0f;
			_qw = cos_halfangle;
			break;
		case Rot1::Z:
			_qx = 0.0f;
			_qy = 0.0f;
			_qz = sin_halfangle;
			_qw = cos_halfangle;
			break;
		default:
			assert(false);
		}
	}
	void Quat::set(const Rot3 type, const float angle_x, const float angle_y, const float angle_z)
	{

		float cx = Trig::cos(angle_x);
		float cy = Trig::cos(angle_y);
		float cz = Trig::cos(angle_z);

		float sx = Trig::sin(angle_x);
		float sy = Trig::sin(angle_y);
		float sz = Trig::sin(angle_z);

		float m0, m1, m2, m4, m5, m6, m8, m9, m10;


		switch(type)
		{
		case Rot3::XYZ:
			m0 = cy * cz;
			m1 = cy * sz;
			m2 = -sy;

			m4 = sx * sy * cz + cx * -sz;
			m5 = sx * sy * sz + cx * cz;
			m6 = sx * cy;

			m8 = cx * sy * cz + sx * sz;
			m9 = cx * sy * sz + -sx * cz;
			m10 = cx * cy;

			this->privSetFromMatFloats(m0, m1, m2, m4, m5, m6, m8, m9, m10);
			break;
		case Rot3::XZY:
			// Rotation matrix for XZY order
			m0 = cz * cy;
			m1 = sz;
			m2 = cz * -sy;

			m4 = cx * -sz * cy + sx * sy;
			m5 = cx * cz;
			m6 = cx * -sz * -sy + sx * cy;

			m8 = -sx * -sz * cy + cx * sy;
			m9 = -sx * cz;
			m10 = -sx * -sz * -sy + cx * cy;

			this->privSetFromMatFloats(m0, m1, m2, m4, m5, m6, m8, m9, m10);
			break;
		case Rot3::YXZ:
			m0 = cy * cz + -sy * -sx * -sz;
			m1 = cy * sz + -sy * -sx * cz;
			m2 = -sy * cx;

			m4 = cx * -sz;
			m5 = cx * cz;
			m6 = sx;

			m8 = sy * cz + cy * -sx * -sz;
			m9 = sy * sz + cy * -sx * cz;
			m10 = cy * cx;

			this->privSetFromMatFloats(m0, m1, m2, m4, m5, m6, m8, m9, m10);
			break;
		case Rot3::YZX:
			m0 = cy * cz;
			m1 = cy * sz * cx + -sy * -sx;
			m2 = cy * sz * sx + -sy * cx;

			m4 = -sz;
			m5 = cz * cx;
			m6 = cz * sx;

			m8 = sy * cz;
			m9 = sy * sz * cx + cy * -sx;
			m10 = sy * sz * sx + cy * cx;

			this->privSetFromMatFloats(m0, m1, m2, m4, m5, m6, m8, m9, m10);
			break;
		case Rot3::ZXY:
			m0 = cz * cy + sz * sx * sy;
			m1 = sz * cx;
			m2 = cz * -sy + sz * sx * cy;

			m4 = -sz * cy + cz * sx * sy;
			m5 = cz * cx;
			m6 = -sz * -sy + cz * sx * cy;

			m8 = cx * sy;
			m9 = -sx;
			m10 = cx * cy;

			this->privSetFromMatFloats(m0, m1, m2, m4, m5, m6, m8, m9, m10);
			break;
		case Rot3::ZYX:
			m0 = cz * cy;
			m1 = sz * cx + cz * -sy * -sx;
			m2 = sz * sx + cz * -sy * cx;

			m4 = -sz * cy;
			m5 = cz * cx + -sz * -sy * -sx;
			m6 = cz * sx + -sz * -sy * cx;

			m8 = sy;
			m9 = cy * -sx;
			m10 = cy * cx;

			this->privSetFromMatFloats(m0, m1, m2, m4, m5, m6, m8, m9, m10);
			break;
		default:
			assert(false);
			break;
		}

	}

	void Quat::privSetFromMatFloats(float m0, float m1, float m2, float m4, float m5, float m6, float m8, float m9, float m10)
	{
		float tr;
		float S;
		tr = m0 + m5 + m10;
		if(tr > 0.0f)
		{
			S = 2 * Trig::sqrt(tr + 1.0f);
			this->_qw = 0.25f * S;
			this->_qx = -(m9 - m6) / S;
			this->_qy = -(m2 - m8) / S;
			this->_qz = -(m4 - m1) / S;
		}
		else if((m0 > m5) && (m0 > m10))
		{
			S = 2 * Trig::sqrt(1.0f + m0 - m5 - m10);
			this->_qw = -(m9 - m6) / S;
			this->_qx = 0.25f * S;
			this->_qy = (m1 + m4) / S;
			this->_qz = (m2 + m8) / S;
		}
		else if(m5 > m10)
		{
			S = 2 * Trig::sqrt(1.0f + m5 - m0 - m10);
			this->_qw = -(m2 - m8) / S;
			this->_qx = (m1 + m4) / S;
			this->_qy = 0.25f * S;
			this->_qz = (m6 + m9) / S;
		}
		else
		{
			S = 2 * Trig::sqrt(1.0f + m10 - m0 - m5);
			this->_qw = -(m4 - m1) / S;
			this->_qx = (m2 + m8) / S;
			this->_qy = (m6 + m9) / S;
			this->_qz = 0.25f * S;
		}
	}



	void Quat::set(const Axis type, const Vec3 &vAxis, const float angle_radians)
	{
		// Calculate the sin and cos of the angle
		float halfangle = angle_radians * 0.5f;
		float s = Trig::sin(halfangle);
		float c = Trig::cos(halfangle);

		switch(type)
		{
		case Axis::AxisAngle:
		{
			// Normalize the axis vector
			this->_qV3 = vAxis.getNorm();

			this->_qV3 *= s;
			this->_qw = c;

			break;
		}
		case Axis::UnitAxisAngle:
		{

			this->_qV3 = vAxis;
			this->_qV3 *= s;
			this->_qw = c;

			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void Quat::set(const Orient type, const Vec3 &dof, const Vec3 &up)
	{
		Vec3 vDof = dof.getNorm();
		Vec3 vUp = up.getNorm();
		Vec3 vRight = vUp.cross(vDof);
		vUp = vDof.cross(vRight);

		//NEEDS OPTIMIZING

		switch(type)
		{
		case Orient::LocalToWorld: {
			// Calculate quaternion components for LocalToWorld
			float m0 = vRight[x];
			float m1 = vRight[y];
			float m2 = vRight[z];

			float m4 = vUp[x];
			float m5 = vUp[y];
			float m6 = vUp[z];

			float m8 = vDof[x];
			float m9 = vDof[y];
			float m10 = vDof[z];

			this->privSetFromMatFloats(m0, m1, m2, m4, m5, m6, m8, m9, m10);
			break;
		}
		case Orient::WorldToLocal: {

			float m0 = vRight[x];
			float m4 = vRight[y];
			float m8 = vRight[z];
			float m1 = vUp[x];
			float m5 = vUp[y];
			float m9 = vUp[z];
			float m2 = vDof[x];
			float m6 = vDof[y];
			float m10 = vDof[z];

			this->privSetFromMatFloats(m0, m1, m2, m4, m5, m6, m8, m9, m10);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void Quat::set(const float vx, const float vy, const float vz, const float real)
	{
		_qx = vx;
		_qy = vy;
		_qz = vz;
		_qw = real;
	}

	void Quat::setVec3(const Vec3 &vect)
	{
		_qx = vect._vx;
		_qy = vect._vy;
		_qz = vect._vz;
	}

	void Quat::set(const Vec3 &vect, const float real)
	{
		_qx = vect._vx;
		_qy = vect._vy;
		_qz = vect._vz;
		_qw = real;
	}


	void Quat::set(const Rot &M)
	{
		//needs to be ROT no?
		float tr = M._m0 + M._m5 + M._m10;
		float S;
		if(tr > 0.0f)
		{
			S = 2 * Trig::sqrt(tr + 1.0f);
			this->_qw = 0.25f * S;
			this->_qx = -(M._m9 - M._m6) / S;
			this->_qy = -(M._m2 - M._m8) / S;
			this->_qz = -(M._m4 - M._m1) / S;
		}
		else if((M._m0 > M._m5) && (M._m0 > M._m10))
		{
			S = 2 * Trig::sqrt(1.0f + M._m0 - M._m5 - M._m10);
			this->_qw = -(M._m9 - M._m6) / S;
			this->_qx = 0.25f * S;
			this->_qy = (M._m1 + M._m4) / S;
			this->_qz = (M._m2 + M._m8) / S;
		}
		else if(M._m5 > M._m10)
		{
			S = 2 * Trig::sqrt(1.0f + M._m5 - M._m0 - M._m10);
			this->_qw = -(M._m2 - M._m8) / S;
			this->_qx = (M._m1 + M._m4) / S;
			this->_qy = 0.25f * S;
			this->_qz = (M._m6 + M._m9) / S;
		}
		else
		{
			S = 2 * Trig::sqrt(1.0f + M._m10 - M._m0 - M._m5);
			this->_qw = -(M._m4 - M._m1) / S;
			this->_qx = (M._m2 + M._m8) / S;
			this->_qy = (M._m6 + M._m9) / S;
			this->_qz = 0.25f * S;
		}
	}

	float &Quat::operator[](const enum x_enum) { return _qx; }
	float &Quat::operator[](const enum y_enum) { return _qy; }
	float &Quat::operator[](const enum z_enum) { return _qz; }
	float &Quat::operator[](const enum w_enum) { return _qw; }

	float Quat::operator[](const enum x_enum)const { return _qx; }
	float Quat::operator[](const enum y_enum)const { return _qy; }
	float Quat::operator[](const enum z_enum)const { return _qz; }
	float Quat::operator[](const enum w_enum)const { return _qw; }

	void Quat::qx(const float f) { _qx = f; }
	void Quat::qy(const float f) { _qy = f; }
	void Quat::qz(const float f) { _qz = f; }
	void Quat::real(const float f) { _qw = f; }

	float Quat::qx()const { return _qx; }
	float Quat::qy()const { return _qy; }
	float Quat::qz()const { return _qz; }
	float Quat::real()const { return _qw; }

	float Quat::getAngle(void) const { return 2 * (Trig::acos(_qw)); }
	void Quat::getVec3(Vec3 &vOut) const { vOut.set(_qx, _qy, _qz); }
	void Quat::getAxis(Vec3 &vOut) const
	{
		float angle = 2 * (Trig::acos(_qw));
		float factor = 1 / Trig::sin(angle / 2);
		vOut.set(_qx * factor, _qy * factor, _qz * factor);
	}


	// Conjugate Quat in place
	Quat &Quat::conj(void)
	{
		_qx = -_qx;
		_qy = -_qy;
		_qz = -_qz;

		return *this;
	}

	// Return conjuate Quat
	Quat Quat::getConj(void) const
	{
		return Quat(-_qx, -_qy, -_qz, _qw);
	}

	float Quat::dot(const Quat &qIn) const
	{
		return (_qx * qIn._qx) + (_qy * qIn._qy) + (_qz * qIn._qz) + (_qw * qIn._qw);
	}

	float Quat::mag(void) const
	{
		return Trig::sqrt((_qx * _qx) + (_qy * _qy) + (_qz * _qz) + (_qw * _qw));
	}

	float Quat::invMag(void) const
	{
		return 1 / this->mag();
	}

	float Quat::magSquared(void) const
	{
		return ((_qx * _qx) + (_qy * _qy) + (_qz * _qz) + (_qw * _qw));
	}

	// Inverse Quat in place
	Quat &Quat::inv(void)
	{
		float magnitude;
		magnitude = this->dot(*this);
		if(magnitude > MATH_TOLERANCE)
		{
			magnitude = 1.0f / (magnitude);
		}
		else
		{
			assert(0);
			magnitude = 1.0f;
		}
		this->_qx = -_qx * magnitude;
		this->_qy = -_qy * magnitude;
		this->_qz = -_qz * magnitude;
		this->_qw = _qw * magnitude;

		return *this;
	}

	// Return inverse Quat
	Quat Quat::getInv(void) const
	{
		float magnitude;
		magnitude = this->dot(*this);
		if(magnitude > MATH_TOLERANCE)
		{
			magnitude = 1.0f / (magnitude);
		}
		else
		{
			assert(0);
			magnitude = 1.0f;
		}
		return Quat(-_qx * magnitude, -_qy * magnitude, -_qz * magnitude, _qw * magnitude);
	}


	// Normalize Quat in place
	Quat &Quat::norm(void)
	{
		float invmagnitude;
		invmagnitude = Trig::rsqrt(this->dot(*this));

		this->_qx *= invmagnitude;
		this->_qy *= invmagnitude;
		this->_qz *= invmagnitude;
		this->_qw *= invmagnitude;

		return *this;
	}

	// Return Normalize Quat
	Quat Quat::getNorm(void) const
	{

		float invmagnitude;
		invmagnitude = Trig::rsqrt(this->dot(*this));

		return Quat(_qx * invmagnitude, _qy * invmagnitude, _qz * invmagnitude, _qw * invmagnitude);
	}


	// Linear Operator vout = Quat * Vector * Quat(conjugate)
// vOut = Quat * vIn * Quat.conj()
	void Quat::Lqvqc(const Vec3 &vIn, Vec3 &vOut) const
	{
		vOut = ((2 * _qw) * vIn.cross(_qV3)) + (((_qw * _qw) - _qV3.dot(_qV3)) * vIn) + ((2 * _qV3.dot(vIn)) * _qV3);
	}

	// Linear Operator  vOut = Quat(conjugate) * Vector * Quat
	// vOut = Quat.conj() * vIn * Quat		
	void Quat::Lqcvq(const Vec3 &vIn, Vec3 &vOut) const
	{
		vOut = ((2 * _qw) * _qV3.cross(vIn)) + (((_qw * _qw) - _qV3.dot(_qV3)) * vIn) + ((2 * _qV3.dot(vIn)) * _qV3);
	}


	Quat Quat::operator+(void) const
	{
		return Quat(*this);
	}

	Quat Quat::operator+(const Quat &inQ) const
	{
		return Quat(_qx + inQ._qx, _qy + inQ._qy, _qz + inQ._qz, _qw + inQ._qw);
	}

	Quat &Quat::operator+=(const Quat &inQ)
	{
		this->_qx += inQ._qx;
		this->_qy += inQ._qy;
		this->_qz += inQ._qz;
		this->_qw += inQ._qw;

		return *this;
	}

	Quat Quat::operator+(const float a) const
	{
		return Quat(_qx + a, _qy + a, _qz + a, _qw + a);
	}

	Quat &Quat::operator+=(const float a)
	{
		this->_qx += a;
		this->_qy += a;
		this->_qz += a;
		this->_qw += a;

		return *this;
	}


	Quat operator+(const float a, const Quat &inQ)
	{
		Quat result;
		result._qx = inQ._qx + a;
		result._qy = inQ._qy + a;
		result._qz = inQ._qz + a;
		result._qw = inQ._qw + a;
		return result;

	}

	Quat Quat::operator-(void) const
	{
		return Quat(-_qx, -_qy, -_qz, -_qw);
	}

	Quat Quat::operator-(const Quat &q) const
	{
		return Quat(_qx - q._qx, _qy - q._qy, _qz - q._qz, _qw - q._qw);
	}

	Quat &Quat::operator-=(const Quat &q)
	{
		this->_qx -= q._qx;
		this->_qy -= q._qy;
		this->_qz -= q._qz;
		this->_qw -= q._qw;

		return *this;
	}

	Quat Quat::operator-(const float a) const
	{
		return Quat(_qx - a, _qy - a, _qz - a, _qw - a);
	}

	Quat &Quat::operator-=(const float a)
	{
		this->_qx -= a;
		this->_qy -= a;
		this->_qz -= a;
		this->_qw -= a;

		return *this;
	}


	Quat operator-(const float a, const Quat &inQ)
	{
		Quat result;
		result._qx = a - inQ._qx;
		result._qy = a - inQ._qy;
		result._qz = a - inQ._qz;
		result._qw = a - inQ._qw;
		return result;
	}



	Quat Quat::operator*(const float a) const
	{
		return Quat(_qx * a, _qy * a, _qz * a, _qw * a);
	}

	Quat &Quat::operator*=(const float a)
	{
		this->_qx *= a;
		this->_qy *= a;
		this->_qz *= a;
		this->_qw *= a;

		return *this;
	}

	Quat operator*(const float a, const Quat &inQ)
	{
		Quat result;
		result._qx = inQ._qx * a;
		result._qy = inQ._qy * a;
		result._qz = inQ._qz * a;
		result._qw = inQ._qw * a;
		return result;
	}



	Mat4 Quat::operator*(const Mat4 &m) const
	{
		Mat4 qm(*this);
		return qm * m;

	}


	Quat Quat::operator*(const Quat &q) const
	{
		float real = (this->_qw * q._qw) - (this->_qV3.dot(q._qV3));
		Vec3 res = (q._qV3.cross(this->_qV3)) + (q._qw * this->_qV3) + (this->_qw * q._qV3);
		return Quat(res, real);
	}

	Quat &Quat::operator*=(const Quat &q)
	{
		float real = (this->_qw * q._qw) - (this->_qV3.dot(q._qV3));
		Vec3 res = (q._qV3.cross(this->_qV3)) + (q._qw * this->_qV3) + (this->_qw * q._qV3);
		this->_qV3 = res;
		this->_qw = real;
		return *this;
	}


	Mat4 Quat::operator*(const Scale &m) const
	{
		Rot qm(*this);
		return qm * m;
	}


	Quat &Quat::operator*=(const Rot &m)
	{
		Quat quatRot(m);
		*this = *this * quatRot;
		return *this;
	}

	Rot Quat::operator*(const Rot &m) const
	{
		Rot qm(*this);
		return qm * m;
	}



	Mat4 Quat::operator*(const Trans &m) const
	{
		Rot qm(*this);
		return qm * m;
	}


	Quat Quat::operator/(const Quat &q) const
	{
		Quat res;
		res._qx = this->_qx / q._qx;
		res._qy = this->_qy / q._qy;
		res._qz = this->_qz / q._qz;
		res._qw = this->_qw / q._qw;
		return res;
	}

	Quat &Quat::operator/=(const Quat &q)
	{
		this->_qx /= q._qx;
		this->_qy /= q._qy;
		this->_qz /= q._qz;
		this->_qw /= q._qw;

		return *this;
	}

	Quat Quat::operator/(const float a) const
	{
		float aInv;
		aInv = 1 / a;
		return Quat(_qx * aInv, _qy * aInv, _qz * aInv, _qw * aInv);
	}

	Quat &Quat::operator/=(const float a)
	{
		float aInv;
		aInv = 1 / a;
		this->_qx *= aInv;
		this->_qy *= aInv;
		this->_qz *= aInv;
		this->_qw *= aInv;

		return *this;
	}

	Quat operator/(const float a, const Quat &inQ)
	{
		Quat result;
		result._qx = a / inQ._qx;
		result._qy = a / inQ._qy;
		result._qz = a / inQ._qz;
		result._qw = a / inQ._qw;
		return result;
	}

	void Quat::Print(const char *pName) const
	{
		size_t pSize = strnlen_s(pName, 10);
		Trace::out("[Quat] %-*s  [x]:%-8f   [y]:%-8f   [z]:%-8f   [w]:%-8f   \n", pSize, pName, this->_qx, this->_qy, this->_qz);
	}


	bool Quat::isEqual(const Quat &qin, const float epsilon) const
	{
		return (Util::isEqual(_qx, qin._qx, epsilon) && Util::isEqual(_qy, qin._qy, epsilon) && Util::isEqual(_qz, qin._qz, epsilon) && Util::isEqual(_qw, qin._qw, epsilon));
	}

	bool Quat::isEquivalent(const Quat &qin, const float epsilon) const
	{
		if(this->isEqual(qin, epsilon))
		{
			return true;
		}
		return this->isNegEqual(qin, epsilon);
	}


	bool Quat::isNegEqual(const Quat &qin, const float epsilon) const
	{
		return (Util::isEqual(-_qx, qin._qx, epsilon) && Util::isEqual(-_qy, qin._qy, epsilon) && Util::isEqual(-_qz, qin._qz, epsilon) && Util::isEqual(-_qw, qin._qw, epsilon));
	}

	bool Quat::isConjugateEqual(const Quat &qin, const float epsilon) const
	{
		return (this->getConj().isEqual(qin, epsilon));
	}


	bool Quat::isIdentity(const float epsilon) const
	{
		return (Util::isEqual(_qx, 0.0f, epsilon) && Util::isEqual(_qy, 0.0f, epsilon) && Util::isEqual(_qz, 0.0f, epsilon) && Util::isEqual(_qw, 1.0f, epsilon));
	}

	bool Quat::isNormalized(const float epsilon) const
	{
		float dot_sqr;
		dot_sqr = this->dot(*this);
		return(Util::isEqual(1.0f, dot_sqr, epsilon));
	}

	bool Quat::isZero(const float epsilon) const
	{
		return (Util::isEqual(_qx, 0.0f, epsilon) && Util::isEqual(_qy, 0.0f, epsilon) && Util::isEqual(_qz, 0.0f, epsilon) && Util::isEqual(_qw, 0.0f, epsilon));
	}



}

//--- End of File ---
