#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include "Timer.h"

class Camera;

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

protected:
	Camera* mCamera;
	Timer* myTimer;

	bool completed;

private:
	float aAspect;
	float aNear;
	float aFar;
	float aFieldOfView;

	float aLeft;
	float aRight;
	float aBottom;
	float aTop;
};

#endif //_GAMESCREEN_H