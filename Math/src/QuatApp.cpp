#include "MathEngine.h"
#include "MathApp.h"

//-------------
// Mutates result to be a slerp between the source and target by the
// specified factor.
// For a factor of 0.0, result == source.
// For a factor of 1.0, result == target.
//-------------

namespace Azul
{
	void QuatApp::Slerp(Quat &result, const Quat &source, const Quat &target, const float t)
	{
		if(target.isEqual(source))
		{
			result = target;
		}
		else
		{
			float tmpCos = source.dot(target);
			Quat tmpTarget = target;
			if(tmpCos < 0)
			{
				tmpCos = -tmpCos;
				tmpTarget = -tmpTarget;
			}
			float angle = Trig::acos(tmpCos);


			float tmpSinDiv = 1 / Trig::sin(angle);
			float tmpSinTime = Trig::sin(t * angle);
			float tmpSinTimeDiff = Trig::sin((1.0f - t) * angle);

			result = (source * tmpSinTimeDiff * tmpSinDiv) + (tmpTarget * tmpSinTime * tmpSinDiv);
		}

	}

	void QuatApp::SlerpArray(Quat *result, const Quat *source, const Quat *target, const float t, const int numQuats)
	{
		for(int i = 0; i < numQuats; i++)
		{
			Slerp(result[i], source[i], target[i], t);
		}
	}
}

// ---  End of File 
