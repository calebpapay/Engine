#include "MathEngine.h"

namespace Azul
{
	// Add Proxy here
	Vec4Proxy::Vec4Proxy(float a, float b, float c, float d)
		:x(a), y(b), z(c), w(d)
	{
	}

	Vec4Proxy::operator float() const
	{
		return Trig::sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	float Vec4Proxy::operator *(const Vec4Proxy &r) const
	{
		float a = (float)*this;
		float b = (float)r;
		return a * b;
	}

	bool Vec4Proxy::operator >(const Vec4Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z) + (w * w)) > ((r.x * r.x) + (r.y * r.y) + (r.z * r.z) + (r.w * r.w))) return true;
		else return false;
	}

	bool Vec4Proxy::operator <(const Vec4Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z) + (w * w)) < ((r.x * r.x) + (r.y * r.y) + (r.z * r.z) + (r.w * r.w))) return true;
		else return false;
	}

	bool Vec4Proxy::operator ==(const Vec4Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z) + (w * w)) == ((r.x * r.x) + (r.y * r.y) + (r.z * r.z) + (r.w * r.w))) return true;
		else return false;
	}

	bool Vec4Proxy::operator >=(const Vec4Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z) + (w * w)) >= ((r.x * r.x) + (r.y * r.y) + (r.z * r.z) + (r.w * r.w))) return true;
		else return false;
	}

	bool Vec4Proxy::operator <=(const Vec4Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z) + (w * w)) <= ((r.x * r.x) + (r.y * r.y) + (r.z * r.z) + (r.w * r.w))) return true;
		else return false;
	}

	bool Vec4Proxy::operator !=(const Vec4Proxy &r) const
	{
		if(((x * x) + (y * y) + (z * z) + (w * w)) != ((r.x * r.x) + (r.y * r.y) + (r.z * r.z) + (r.w * r.w))) return true;
		else return false;
	}

}

//--- End of File ---
