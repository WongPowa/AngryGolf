#pragma once
#include <Windows.h>

class FrameTimer {
public:
	void init(int);
	int framesToUpdate();
private:
	LARGE_INTEGER timer_freq;
	LARGE_INTEGER time_now;
	LARGE_INTEGER time_previous;
	int Requested_FPS;
	float intervalsPerFrame;
	float intervalsSinceLastUpdate;
};

