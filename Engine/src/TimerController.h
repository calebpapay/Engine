//2024. Caleb Papay

#ifndef TIMER_CONTROLLER_H
#define TIMER_CONTROLLER_H

#include "AnimTimer.h"

namespace Azul
{
	class TimerController
	{
	public:
		//TimerController(AnimTime Delta, AnimTime Min, AnimTime Max);

		TimerController();
		TimerController(const TimerController &) = delete;
		TimerController &operator = (const TimerController &) = delete;
		~TimerController() = default;

		void Set(AnimTime Delta, AnimTime Min, AnimTime Max);

		void Update();

		void SetCurrTime(const AnimTime time);
		AnimTime GetCurrTime() const;

		void SetDeltaTime(const AnimTime time);
		AnimTime GetDeltaTime() const;

		void SetMaxTime(const AnimTime time);
		AnimTime GetMaxTime() const;

		void SetMinTime(const AnimTime time);
		AnimTime GetMinTime() const;

	private:
		AnimTime tCurr;
		AnimTime tDelta;
		AnimTime tMax;
		AnimTime tMin;
	};
}

#endif

// --- End of File ---

