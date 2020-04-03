#include "timer.h"

std::chrono::duration<double> Timer::timeDifference(int start, int end)
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(timers[end]-timers[start]);
}
