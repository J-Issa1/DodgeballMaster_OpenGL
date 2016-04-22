#include "GameScreenMenu.h"
#include "GameScreenManager.h"
#include "SoundEffect.h"
#include "Texture2D.h" 
#include <iostream>

using namespace std;

extern SCREEN_STATE nextScreen;

GameScreenMenu::GameScreenMenu() : GameScreen()
{
	nextScreen = NOCHANGE;
	
	selectLevel1 = true;
	selectLevel2 = false;
	selectHowToPlay = false;
	selectQuit = false;
}

GameScreenMenu::~GameScreenMenu()
{
}

void GameScreenMenu::Render()
{
	GameScreen::Render();

	RenderText();
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_RETURN:
				if (selectLevel1)
					nextScreen = LEVEL1;

				if (selectLevel2)
					nextScreen = LEVEL2;

				if (selectQuit == true)
				{
					SDL_Quit();
					exit(0);
				}
				break;

			case SDLK_DOWN:
				if (selectLevel1 == true)
				{
					selectLevel1 = false;
					selectLevel2 = true;
					selectHowToPlay = false;
					selectQuit = false;
				}
				else if (selectLevel2 == true)
				{
					selectLevel1 = false;
					selectLevel2 = false;
					selectHowToPlay = true;
					selectQuit = false;
				}
				else if (selectHowToPlay == true)
				{
					selectLevel1 = false;
					selectLevel2 = false;
					selectHowToPlay = false;
					selectQuit = true;
				}
				else if (selectQuit == true)
				{
					selectLevel1 = true;
					selectLevel2 = false;
					selectHowToPlay = false;
					selectQuit = false;
				}
			break;

			case SDLK_UP:
				if (selectLevel1 == true)
				{
					selectLevel1 = false;
					selectLevel2 = false;
					selectHowToPlay = false;
					selectQuit = true;
				}
				else if (selectQuit == true)
				{
					selectLevel1 = false;
					selectLevel2 = false;
					selectHowToPlay = true;
					selectQuit = false;
				}
				else if (selectHowToPlay == true)
				{
					selectLevel1 = false;
					selectLevel2 = true;
					selectHowToPlay = false;
					selectQuit = false;
				}
				else if (selectLevel2 == true)
				{
					selectLevel1 = true;
					selectLevel2 = false;
					selectHowToPlay = false;
					selectQuit = false;
				}				
				break;

			}
		break;
	}
}

void GameScreenMenu::OutputLine(float x, float y, string text)
{
	glRasterPos2f(x, y);  // where to start drawing
	for (unsigned int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}

}

void GameScreenMenu::RenderText()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);

			if (selectLevel1 == true)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				OutputLine(45, 70, "Go to Level 1.");

				glColor3f(1.0f, 1.0f, 1.0f);
				OutputLine(45, 60, "Go to Level 2.");
				OutputLine(45, 50, "How to Play.");
				OutputLine(45, 40, "Quit.");
			}
			if (selectLevel2 == true)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				OutputLine(45, 60, "Go to Level 2.");

				glColor3f(1.0f, 1.0f, 1.0f);
				OutputLine(45, 70, "Go to Level 1.");
				OutputLine(45, 50, "How to Play.");
				OutputLine(45, 40, "Quit.");
			}
			if (selectHowToPlay == true)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				OutputLine(45, 50, "How to Play.");

				glColor3f(1.0f, 1.0f, 1.0f);
				OutputLine(45, 70, "Go to Level 1.");
				OutputLine(45, 60, "Go to Level 2.");
				OutputLine(45, 40, "Quit.");
			}
			if (selectQuit == true)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				OutputLine(45, 40, "Quit.");

				glColor3f(1.0f, 1.0f, 1.0f);
				OutputLine(45, 70, "Go to Level 1.");
				OutputLine(45, 60, "Go to Level 2.");
				OutputLine(45, 50, "How to Play.");
			}
		glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}