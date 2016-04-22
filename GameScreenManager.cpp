#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel2.h"

//--------------------------------------------------------------------------------------------------
SCREEN_STATE nextScreen;

GameScreenManager::GameScreenManager(SCREENS startScreen)
{
	nextScreen = NOCHANGE;
	mCurrentScreen = NULL;

	//Ensure the first screen is set up.
	ChangeScreen(startScreen);
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);

	if (nextScreen != NOCHANGE)
	{
		switch (nextScreen)
		{
			case NOCHANGE:
				break;

			case MENU:
				ChangeScreen(SCREEN_MENU);
				break;

			case LEVEL1:
				ChangeScreen(SCREEN_LEVEL1);
				break;

			case LEVEL2:
				ChangeScreen(SCREEN_LEVEL2);
				break;

			case GAMEOVER:
				ChangeScreen(SCREEN_GAMEOVER);
				break;

			case SCORES:
				ChangeScreen(SCREEN_HIGHSCORES);
				break;

			default:
				break;
		}

	}
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen1;
	GameScreenMenu* tempScreen2;
	GameScreenLevel2* tempScreen3;
	//GameScreenGameOver* tempScreen4;

	//Initialise the new screen.
	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;

	case SCREEN_MENU:
		tempScreen2 = new GameScreenMenu();
		mCurrentScreen = (GameScreen*)tempScreen2;
		tempScreen2 = NULL;
		break;

	case SCREEN_LEVEL1:
		tempScreen1 = new GameScreenLevel1();
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;

	case SCREEN_LEVEL2:
		tempScreen3 = new GameScreenLevel2();
		mCurrentScreen = (GameScreen*)tempScreen3;
		tempScreen3 = NULL;
		break;

	// Need to Implement

	/*case SCREEN_GAMEOVER:
		tempScreen4 = new GameScreenGameOver();
		mCurrentScreen = (GameScreen*)tempScreen4;
		tempScreen4 = NULL;
		break;
	
	case SCREEN_HIGHSCORES:
		tempScreen5 = new GameScreenScores();
		mCurrentScreen = (GameScreen*)tempScreen5;
		tempScreen5 = NULL;
		break;
	*/

	default:
		break;
	}
}