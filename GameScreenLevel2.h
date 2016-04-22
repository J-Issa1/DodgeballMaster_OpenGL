#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include <SDL.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <time.h>
#include "GameScreen.h"
#include "Terrain.h"
#include "Object3ds.h"
#include "Texture.h"
#include "Collision.h"
#include "SoundEffect.h"
#include "PoolBalls.h"
#include "Timer.h"

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2();
	~GameScreenLevel2();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void OutputLine(float x, float y, string text);

	void RenderText();

	void DrawSkybox();

	void DrawObjects();

private:

	string text;

	Object3DS* groundPlane;
	Object3DS* groundPlane2;
	PoolBalls* whiteBall;
	PoolBalls* ball1;
	PoolBalls* ball2;
	PoolBalls* ball3;
	PoolBalls* ball4;
	PoolBalls* ball5;
	PoolBalls* ball6;
	PoolBalls* ball7;
	PoolBalls* ball8;
	PoolBalls* ball9; 
	PoolBalls* ball10;
	PoolBalls* ball11;
	PoolBalls* ball12;
	PoolBalls* ball13;
	PoolBalls* ball14; 
	PoolBalls* ball15;

	std::vector<PoolBalls*> vecPoolBalls;

	std::vector<PoolBalls*> vecPockets;

	//Timer* l2Timer;

	SoundEffect* shotEffect;
	SoundEffect* hitEffect;
};


#endif //_GAMESCREENLEVEL2_H
