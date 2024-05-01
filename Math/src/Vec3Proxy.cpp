#include "MathEngine.h"

namespace Azul
{
	// Add Proxy here
	Vec3Proxy::Vec3Proxy(float a, float b, float c)
		:x(a), y(b), z(c)
	{
	}

	Vec3Proxy::operator float() const
	{
		return (float)Trig::sqrt((x * x) + (y * y) + (z * z));
	}

	float Vec3Proxy::operator *(const Vec3Proxy &r) const
	{
		float a = (float)*this;
		float b = (float)r;
		return a * b;
	}

	bool Vec3Proxy::operator >(const Vec3Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z)) > ((r.x * r.x) + (r.y * r.y) + (r.z * r.z))) return true;
		else return false;
	}

	bool Vec3Proxy::operator <(const Vec3Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z)) < ((r.x * r.x) + (r.y * r.y) + (r.z * r.z))) return true;
		else return false;
	}

	bool Vec3Proxy::operator ==(const Vec3Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z)) == ((r.x * r.x) + (r.y * r.y) + (r.z * r.z))) return true;
		else return false;
	}

	bool Vec3Proxy::operator >=(const Vec3Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z)) >= ((r.x * r.x) + (r.y * r.y) + (r.z * r.z))) return true;
		else return false;
	}

	bool Vec3Proxy::operator <=(const Vec3Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z)) <= ((r.x * r.x) + (r.y * r.y) + (r.z * r.z))) return true;
		else return false;
	}

	bool Vec3Proxy::operator !=(const Vec3Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z)) != ((r.x * r.x) + (r.y * r.y) + (r.z * r.z))) return true;
		else return false;
	}



}

//--- End of File ---
