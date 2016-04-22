#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

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
#include "BallObject.h"
#include "Collision.h"
#include "SoundEffect.h"
#include "Denzil.h"
#include "EndPoint.h"
#include "Timer.h"

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void OutputLine(float x, float y, string text);

	void RenderText();
	void newText();

	void DrawSkybox();

	void DrawObjects();

private:
	string text;
	
	Texture* skyboxTexture[6];

	material sunEmmisiveMaterial;

	Denzil* DenzilChar;
	Object3DS* groundPlane;
	Object3DS* groundPlane2;
	Object3DS* winPlane;
	EndPoint* endZone;

	std::vector<BallObject*> dodgeballs;

	SoundEffect* hitEffect;
	SoundEffect* deathEffect;
	SoundEffect* winEffect;
	bool win;

	//Timer* myTimer;

	string timepassed;

	int hits;
	bool denzilHit;

	bool lightingOn;
};


#endif //_GAMESCREENLEVEL1_H