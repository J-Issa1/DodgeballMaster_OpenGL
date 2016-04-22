#include "Timer.h"
#include <windows.h>
#include <GL\gl.h>
#include "Constants.h"
#include "Commons.h"

Timer::Timer()
{
	mCurrentTime = 0;

	running = false;
}

Timer::~Timer()
{
}

void Timer::Update(float deltaTime)
{
	if (running)
	mCurrentTime += deltaTime;
}

void Timer::SetTimer(float newTime)
{
	mCurrentTime = newTime;
}

bool Timer::StartTimer()
{
	if (running == false)
	{
		running = true;

		return true;
	}
	else
	{
		return false;
	}
}

bool Timer::StopTimer()
{
	if (running)
	{
		running = false;

		return false;
	}
	else
	{
		return true;
	}
}

