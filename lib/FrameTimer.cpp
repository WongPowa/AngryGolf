//FrameTimer.cpp
#include "FrameTimer.h"

void FrameTimer::init(int fps) {
    QueryPerformanceFrequency(&timer_freq);
    QueryPerformanceCounter(&time_now);
    QueryPerformanceCounter(&time_previous);
    //init fps time info
    Requested_FPS = fps;
    //The number of intervals in the given
    //timer, per frame at the requested rate.
    intervalsPerFrame = ((float)timer_freq.QuadPart / Requested_FPS);
}

int FrameTimer::framesToUpdate() {
    int framesToUpdate = 0;
    QueryPerformanceCounter(&time_now);
    //getting the delta time
    intervalsSinceLastUpdate = (float)time_now.QuadPart - (float)time_previous.QuadPart;
    framesToUpdate = (int)( intervalsSinceLastUpdate / intervalsPerFrame );
    //If we are not updating any frames, 
   //keep the old previous timer count
    if (framesToUpdate != 0) {
        QueryPerformanceCounter(&time_previous);
    }
    
    return framesToUpdate;
}