#include <windows.h>
#include <GL\gl.h>
#include <vector>
#include <string>
#include <sstream>
#include "GameScreenLevel2.h"
#include "Constants.h"
#include "Commons.h"
#include "GameScreenLevel1.h"

using namespace std;

GameScreenLevel2::GameScreenLevel2() : GameScreen()
{
	nextScreen = NOCHANGE;

	//mCurrentTime = 0;

	Texture* groundPlaneTexture = new Texture();
	Texture* whiteBallTexture = new Texture();
	Texture* yellowBallTexture = new Texture();
	Texture* blueBallTexture = new Texture();
	Texture* redBallTexture = new Texture();
	Texture* purpleBallTexture = new Texture();
	Texture* orangeBallTexture = new Texture();
	Texture* greenBallTexture = new Texture();
	Texture* maroonBallTexture = new Texture();
	Texture* blackBallTexture = new Texture();
	Texture* yellowStripeBallTexture = new Texture();
	Texture* blueStripeBallTexture = new Texture();
	Texture* redStripeBallTexture = new Texture();
	Texture* purpleStripeBallTexture = new Texture();
	Texture* orangeStripeBallTexture = new Texture();
	Texture* greenStripeBallTexture = new Texture();
	Texture* maroonStripeBallTexture = new Texture();

	// Pool Table
	groundPlaneTexture->Load("Images/Table.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, groundPlaneTexture->GetID());
	groundPlane = new Object3DS(Vector3D(0.0f, -1.0f, 0.0f), "Court.3ds", groundPlaneTexture->GetID());

	groundPlane2 = new Object3DS(Vector3D(0.0f, -1.0f, -20.0f), "Court.3ds", whiteBallTexture->GetID());

	whiteBallTexture->Load("Images/White-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, whiteBallTexture->GetID());

	yellowBallTexture->Load("Images/yellow-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, yellowBallTexture->GetID());
	
	blueBallTexture->Load("Images/blue-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, blueBallTexture->GetID());

	redBallTexture->Load("Images/red-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, redBallTexture->GetID());

	purpleBallTexture->Load("Images/purple-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, purpleBallTexture->GetID());

	orangeBallTexture->Load("Images/orange-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, orangeBallTexture->GetID());

	greenBallTexture->Load("Images/green-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, greenBallTexture->GetID());

	maroonBallTexture->Load("Images/maroon-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, maroonBallTexture->GetID());

	blackBallTexture->Load("Images/8-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, blackBallTexture->GetID());

	yellowStripeBallTexture->Load("Images/yellowStripe-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, yellowStripeBallTexture->GetID());

	blueStripeBallTexture->Load("Images/blueStripe-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, blueStripeBallTexture->GetID());

	redStripeBallTexture->Load("Images/redStripe-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, redStripeBallTexture->GetID());

	purpleStripeBallTexture->Load("Images/purpleStripe-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, purpleStripeBallTexture->GetID());

	orangeStripeBallTexture->Load("Images/orangeStripe-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, orangeStripeBallTexture->GetID());

	greenStripeBallTexture->Load("Images/greenStripe-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, greenStripeBallTexture->GetID());

	maroonStripeBallTexture->Load("Images/maroonStripe-Ball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, maroonStripeBallTexture->GetID());

	whiteBall = new PoolBalls(Vector3D(0.0f, -1.2f, -35.0f), "Sphere.3ds", whiteBallTexture->GetID());
	ball1 = new PoolBalls(Vector3D(1.2f, -1.2, 12.5f), "Sphere.3ds", blueBallTexture->GetID());
	ball2 = new PoolBalls(Vector3D(-1.2f, -1.2, 12.5f), "Sphere.3ds", redBallTexture->GetID());
	ball3 = new PoolBalls(Vector3D(0.0f, -1.2f, 10.0f), "Sphere.3ds", yellowBallTexture->GetID());
	ball4 =	new PoolBalls(Vector3D(2.4f, -1.2f, 15.0f), "Sphere.3ds", purpleBallTexture->GetID());
	ball5 = new PoolBalls(Vector3D(0.0f, -1.2f, 15.0f), "Sphere.3ds", blackBallTexture->GetID());
	ball6 = new PoolBalls(Vector3D(-2.4f, -1.2f, 15.0f), "Sphere.3ds", greenBallTexture->GetID());
	ball7 = new PoolBalls(Vector3D(3.6f, -1.2f, 17.5f), "Sphere.3ds", maroonBallTexture->GetID());
	ball8 = new PoolBalls(Vector3D(0.8f, -1.2f, 17.5f), "Sphere.3ds", orangeBallTexture->GetID());
	ball9 = new PoolBalls(Vector3D(-1.8f, -1.2f, 17.5f), "Sphere.3ds", yellowStripeBallTexture->GetID());
	ball10 = new PoolBalls(Vector3D(-4.5f, -1.2f, 17.5f), "Sphere.3ds", blueStripeBallTexture->GetID());
	ball11 = new PoolBalls(Vector3D(4.8f, -1.2f, 20.0f), "Sphere.3ds", redStripeBallTexture->GetID());
	ball12 = new PoolBalls(Vector3D(2.2f, -1.2f, 20.0f), "Sphere.3ds", purpleStripeBallTexture->GetID());
	ball13 = new PoolBalls(Vector3D(-0.6f, -1.2f, 20.0f), "Sphere.3ds", orangeStripeBallTexture->GetID());
	ball14 = new PoolBalls(Vector3D(-3.2f, -1.2f, 20.0f), "Sphere.3ds", greenStripeBallTexture->GetID());
	ball15 = new PoolBalls(Vector3D(-6.0f, -1.2f, 20.0f), "Sphere.3ds", maroonStripeBallTexture->GetID());

	vecPoolBalls.push_back(ball1);
	vecPoolBalls.push_back(ball2);
	vecPoolBalls.push_back(ball3);
	vecPoolBalls.push_back(ball4);
	vecPoolBalls.push_back(ball5);
	vecPoolBalls.push_back(ball6);
	vecPoolBalls.push_back(ball7);
	vecPoolBalls.push_back(ball8);
	vecPoolBalls.push_back(ball9);
	vecPoolBalls.push_back(ball10);
	vecPoolBalls.push_back(ball11);
	vecPoolBalls.push_back(ball12);
	vecPoolBalls.push_back(ball13);
	vecPoolBalls.push_back(ball14);
	vecPoolBalls.push_back(ball15);

	shotEffect = new SoundEffect();
	shotEffect->Load("Music/Pool_Shot1.wav");

	hitEffect = new SoundEffect();
	hitEffect->Load("Music/Pool_Hit.wav");

	//l2Timer = new Timer();
}

GameScreenLevel2::~GameScreenLevel2()
{
}

void GameScreenLevel2::Render()
{
	//Parent class deals with camera.
	GameScreen::Render();

	glPushMatrix();
	RenderText();
	glPopMatrix();

	DrawObjects();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	//Call parent update for camera functionality.
	GameScreen::Update(deltaTime, e);

	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_u:
					whiteBall->SetVelocity(Vector3D(-50.0f, 0.0f, 20.0f));
					shotEffect->Play(0);
				break;

				case SDLK_o:
					whiteBall->SetVelocity(Vector3D(50.0f, 0.0f, 20.0f));
					shotEffect->Play(0);
					break;

				case SDLK_i:
					whiteBall->SetVelocity(Vector3D(0.0f, 0.0f, 50.0f));
					shotEffect->Play(0);
				break;

				case SDLK_j:
					whiteBall->SetVelocity(Vector3D(-50.0f, 0.0f, -20.0f));
					shotEffect->Play(0);
					break;

				case SDLK_l:
					whiteBall->SetVelocity(Vector3D(50.0f, 0.0f, -20.0f));
					shotEffect->Play(0);
					break;

				case SDLK_k:
					whiteBall->SetVelocity(Vector3D(0.0f, 0.0f, -50.0f));
					shotEffect->Play(0);
					break;

			}
		break;
	}

	for (unsigned int i = 0; i < vecPoolBalls.size(); i++)
	{
		if (Collision::SphereSphereCollision(whiteBall->GetBoundingSphere(), vecPoolBalls[i]->GetBoundingSphere()) == true)
		{
			whiteBall->ResolveCollision(whiteBall, vecPoolBalls[i]);

			hitEffect->Play(0);
				
			if (whiteBall->collisionCompleted)
			{
				//whiteBall->SetVelocity(Vector3D(0.0f, 0.0f, 0.0f));

				whiteBall->SetVelocity(Vector3D(whiteBall->GetVelocity().x * 0.98f, whiteBall->GetVelocity().y * 0.98f, whiteBall->GetVelocity().z * 0.98f));

				whiteBall->collisionCompleted = false;
			}
		}

		for (unsigned int j = 0; j < vecPoolBalls.size(); j++)
		{
			if (j != i)
			{
				if (Collision::SphereSphereCollision(vecPoolBalls[i]->GetBoundingSphere(), vecPoolBalls[j]->GetBoundingSphere()) == true)
				{
					vecPoolBalls[j]->ResolveCollision(vecPoolBalls[j], vecPoolBalls[i]);

					hitEffect->Play(0);

					if (vecPoolBalls[i]->collisionCompleted)
					{
						vecPoolBalls[i]->SetVelocity(Vector3D(0.0f, 0.0f, 0.0f));
						//vecPoolBalls[i]->SetVelocity(Vector3D(vecPoolBalls[i]->GetVelocity().x * 0.98f, vecPoolBalls[i]->GetVelocity().y * 0.98f, vecPoolBalls[i]->GetVelocity().z * 0.98f));
						
						vecPoolBalls[i]->collisionCompleted = false;
					}
				}
			}
		}

		vecPoolBalls[i]->Update(deltaTime);
	}

	whiteBall->Update(deltaTime);

	//l2Timer->Update(deltaTime);
}

void GameScreenLevel2::OutputLine(float x, float y, string text)
{
	glRasterPos2f(x, y);  // where to start drawing
	for (unsigned int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}

void GameScreenLevel2::RenderText()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);

		int time = static_cast<int> (myTimer->GetTimer());
		string timepassed = static_cast<ostringstream*>(&(ostringstream() << time))->str();
		stringstream timePassed;
		timePassed << "Time: " << timepassed;

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(0.0f, 0.0f, 0.0f);
			OutputLine(2, 95, timePassed.str());
		glPopMatrix();

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(0.0f, 0.0f, 1.0f);
			OutputLine(80, 95, "Pool Collision");
		glPopMatrix();

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(1.0f, 0.0f, 0.0f);
			OutputLine(2, 55, "Press i to fire forward.");
		glPopMatrix();

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(1.0f, 0.0f, 0.0f);
			OutputLine(2, 50, "Press u to fire up left.");
		glPopMatrix();

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(1.0f, 0.0f, 0.0f);
			OutputLine(2, 45, "Press o to fire up right.");
		glPopMatrix();

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(1.0f, 0.0f, 0.0f);
			OutputLine(2, 40, "Press j to fire down left.");
		glPopMatrix();

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(1.0f, 0.0f, 0.0f);
			OutputLine(2, 35, "Press l to fire down right.");
		glPopMatrix();

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(1.0f, 0.0f, 0.0f);
			OutputLine(2, 30, "Press k to fire down.");
		glPopMatrix();

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(1.0f, 0.0f, 0.0f);
			OutputLine(35, 95, "Press Esc to quit game.");
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GameScreenLevel2::DrawObjects()
{
	glPushMatrix();
		glTranslatef(0.0f, -20.0f, 0.0f);
		groundPlane->SetScale(Vector3D(1.5f, 0.5f, 0.1f));
		glRotatef(270.0f, 0.0f, 0.0f, 1.0f);
		groundPlane->Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -20.0f, 0.0f);
	groundPlane2->SetScale(Vector3D(10.0f, 10.0f, 10.0f));
	glRotatef(270.0f, 0.0f, 0.0f, 1.0f);
	groundPlane2->Render();
	glPopMatrix();

	// ------------------------------------------------------------ Balls ----------------------------------------------------------------------------------- //

	glPushMatrix();
		whiteBall->SetScale(Vector3D(0.1f, 0.1f, 0.1f));
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		whiteBall->Render();
	glPopMatrix();

	for (unsigned int i = 0; i < vecPoolBalls.size(); i++)
	{
		glPushMatrix();
			vecPoolBalls[i]->SetScale(Vector3D(0.1f, 0.1f, 0.1f));
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			vecPoolBalls[i]->Render();
		glPopMatrix();
	}
}