//2024. Caleb Papay

#include "TimerController.h"

namespace Azul
{

	TimerController::TimerController()
		: tCurr(AnimTime(AnimTime::Duration::ZERO)),
		tDelta(AnimTime(AnimTime::Duration::ZERO)),
		tMax(AnimTime(AnimTime::Duration::ZERO)),
		tMin(AnimTime(AnimTime::Duration::ZERO))
	{
	}

	void TimerController::Set(AnimTime Delta, AnimTime Min, AnimTime Max)
	{
		tCurr = AnimTime(AnimTime::Duration::ZERO);
		tDelta = Delta;
		tMax = Max;
		tMin = Min;
	}

	void TimerController::Update()
	{
		tCurr += tDelta;

		// protection for time values for looping
		if (tCurr < tMin)
		{
			tCurr = tMax;
		}
		else if (tCurr > tMax)
		{
			tCurr = tMin;
		}
		else
		{
			// do nothing
		}
	}

	void TimerController::SetCurrTime(const AnimTime time)
	{
		this->tCurr = time;
	}

	AnimTime TimerController::GetCurrTime() const
	{
		return this->tCurr;
	}

	void TimerController::SetDeltaTime(const AnimTime time)
	{
		this->tDelta = time;
	}

	AnimTime TimerController::GetDeltaTime() const
	{
		return this->tDelta;
	}

	void TimerController::SetMaxTime(const AnimTime time)
	{
		this->tMax = time;
	}

	AnimTime TimerController::GetMaxTime() const
	{
		return this->tMax;
	}

	void TimerController::SetMinTime(const AnimTime time)
	{
		this->tMin = time;
	}

	AnimTime TimerController::GetMinTime() const
	{
		return this->tMin;
	}

}

// --- End of File ---
