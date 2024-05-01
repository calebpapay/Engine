#include <math.h>    // <--- ONLY location for <math.h> allowed
#include "Trig.h"

namespace Azul
{

	// Do your magic here
	float Trig::cos(const float  angle_radians)
	{
		return cosf(angle_radians);
	}

	float Trig::sin(const float  angle_radians)
	{
		return sinf(angle_radians);
	}

	float Trig::tan(const float  val)
	{
		return tanf(val);
	}

	float Trig::atan(const float val)
	{
		return atanf(val);
	}

	float Trig::atan2(const float x, const float y)
	{
		return atan2f(x, y);
	}

	float Trig::acos(const float val)
	{
		return acosf(val);
	}

	float Trig::asin(const float val)
	{
		return asinf(val);
	}

	void Trig::cossin(float &cos, float &sin, const float angle_radians)
	{
		cos = cosf(angle_radians);
		sin = sinf(angle_radians);
	}

	float Trig::sqrt(const float val)
	{
		return sqrtf(val);
	}

	float Trig::rsqrt(const float val)
	{
		return 1.0f / sqrtf(val);
	}

}

//--- End of File ---
