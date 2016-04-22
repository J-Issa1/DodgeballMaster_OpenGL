#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL\gl.h>
#include <gl\GLU.h>
#include "./gl/glut.h"
#include "GameScreen.h"
#include "Commons.h"
#include "Constants.h"
#include "SoundEffect.h"
#include <vector>

using namespace std;

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu();
	~GameScreenMenu();

	//bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void OutputLine(float x, float y, string text);
	void RenderText();

	bool selectLevel1, selectLevel2, selectHowToPlay, selectQuit;
};

#endif 