#ifndef TIMER_H
#define TIMER_H

#include <vector>
#include <chrono>
class Timer
{
    public:
    Timer(){timers.push_back(std::chrono::steady_clock::now());}

    void newTime(){timers.push_back(std::chrono::steady_clock::now());}
    
    std::chrono::duration<double> timeDifference(int start, int end);

    private:
    std::vector<std::chrono::steady_clock::time_point> timers;
};
#endif//TIMER_H
