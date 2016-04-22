#pragma once
#include <time.h>

class Timer
{
public:
	Timer();
	~Timer();

	void Update(float deltaTime);

	float GetTimer() { return mCurrentTime; }
	void SetTimer(float newTime);
	bool StartTimer();
	bool StopTimer();

private:
	float mCurrentTime;

	bool running;
};

