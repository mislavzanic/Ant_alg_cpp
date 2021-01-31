#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <cassert>
#include <chrono>

namespace mh {

    class StopWatch
    {
    public:
        using clock_t = std::chrono::high_resolution_clock;
        using duration_t = std::chrono::duration<float>;

        StopWatch() 
            : mStartTime{clock_t::now()} {}

        duration_t getElapsedTime() const { return clock_t::now() - mStartTime; }
        void reset() { mStartTime = clock_t::now(); }

    private:
        clock_t::time_point mStartTime;
    };

}


#endif // STOP_WATCH_H