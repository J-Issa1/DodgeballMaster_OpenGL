#include <windows.h>
#include <GL\gl.h>
#include <vector>
#include <string>
#include <sstream>
#include "GameScreenLevel1.h"
#include "Constants.h"
#include "Commons.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	nextScreen = NOCHANGE;

	myTimer->SetTimer(0.0f);

	lightingOn = true;

	hits = 0;
	denzilHit = false;

	win = false;

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	sunEmmisiveMaterial = {
							{ 1.0f, 1.0f, 1.0f, 1.0f },
							{ 0.4f, 0.4f, 0.4f, 1.0f },
							{ 1.0f, 1.0f, 1.0f, 1.0f },
							0.0f,
							{ 0.4f, 0.2f, 0.0f }
					   };

	// ------------------------------------------------------------------------------------ TEXTURES ----------------------------------------------------------------------------------- //

	// Skybox Texture 
	Texture* skyFront = new Texture();
	Texture* skyBack  = new Texture();
	Texture* skyLeft  = new Texture();
	Texture* skyRight = new Texture();
	Texture* skyUp	  = new Texture();
	Texture* skyDown  = new Texture();
	skyboxTexture[0]  = skyFront;
	skyboxTexture[1]  = skyBack;
	skyboxTexture[2]  = skyLeft;
	skyboxTexture[3]  = skyRight;
	skyboxTexture[4]  = skyUp;
	skyboxTexture[5]  = skyDown;

	skyFront->Load("sky-front.raw", 512, 512);
	skyBack->Load("sky-back.raw", 512, 512);
	skyLeft->Load("sky-left.raw", 512, 512);
	skyRight->Load("sky-right.raw", 512, 512);
	skyUp->Load("sky-up.raw", 512, 512);
	skyDown->Load("sky-down.raw", 512, 512);

	Texture* denzilTexture = new Texture();
	Texture* dodgeballsTexture = new Texture();
	Texture* groundPlaneTexture = new Texture();
	Texture* winTexture = new Texture();

	// Denzil
	denzilTexture->Load("Denzil.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, denzilTexture->GetID());
	DenzilChar = new Denzil(Vector3D(70.0f, -43.0f, 0.0f), "Cube.3ds", denzilTexture->GetID());

	// Dodgeballs
	dodgeballsTexture->Load("Pokeball.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, dodgeballsTexture->GetID());
	for (int i = 0; i < 10; i++)
	{
		dodgeballs.push_back(new BallObject(Vector3D(0.0f, -1.0f, 0.0f), "Sphere.3ds", dodgeballsTexture->GetID()));
	}

	// Court
	groundPlaneTexture->Load("Court.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, groundPlaneTexture->GetID());
	groundPlane = new Object3DS(Vector3D(0.0f, -1.0f, 0.0f), "Court.3ds", groundPlaneTexture->GetID());
	groundPlane2 = new Object3DS(Vector3D(0.0f, -1.0f, 0.0f), "Court.3ds", groundPlaneTexture->GetID());

	// Win Screen
	winTexture->Load("Images/winScreen.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, winTexture->GetID());
	winPlane = new Object3DS(Vector3D(0.0f, 400.0f, 0.0f), "Court.3ds", winTexture->GetID());

	// End Point
	groundPlaneTexture->Load("Court.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, groundPlaneTexture->GetID());
	endZone = new EndPoint(Vector3D(-90.0f, -43.0f, -21.0f), "Cube.3ds", groundPlaneTexture->GetID());

	// ------------------------------------------------------------------------------------ Sound Effects ----------------------------------------------------------------------------------- //

	hitEffect = new SoundEffect();
	hitEffect->Load("Music/pop.wav");

	deathEffect = new SoundEffect();
	deathEffect->Load("Music/Scream.wav");

	winEffect = new SoundEffect();
	winEffect->Load("Music/victory.wav");
}

GameScreenLevel1::~GameScreenLevel1()
{	
	dodgeballs.clear();
	delete[] &skyboxTexture;
}

void setLight()
{
	lighting light = {
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
	};

	// position of the light in homogeneous coordinates (x, y, z, w)
	// w should be 0 for directional lights, and 1 for spotlights
	float light_pos[] = { 20.0f, 0.0f, 1.0f, 0.0f };

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenLevel1::Render()
{
	//Parent class deals with camera.
	GameScreen::Render();

	RenderText();

	//DrawSkybox();

	DrawObjects();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Call parent update for camera functionality.
	GameScreen::Update(deltaTime, e);

	//groundPlane->Update(deltaTime, e);
	//groundPlane2->Update(deltaTime, e);

	if (Collision::SphereSphereCollision(endZone->GetBoundingSphere(), DenzilChar->GetBoundingSphere()) == true)
	{
		endZone->SetPosition(Vector3D(-200.0f, -43.0f, -53.0f));

		completed = true;
		//myTimer->StopTimer();

		winEffect->Play(0);
		cout << "You Win" << endl;
	}

	if (completed)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_RETURN:
				nextScreen = LEVEL2;
				break;
			}
			break;
		}
	}

	for (unsigned int i = 0; i < dodgeballs.size(); i++)
	{
		Collision::SphereSphereCollision(DenzilChar->GetBoundingSphere(), dodgeballs[i]->GetBoundingSphere());

		if (completed)
		{
			// Complete the level
			dodgeballs[i]->SetAcceleration(Vector3D(0.0f, 0.0f, 0.0f));
			dodgeballs[i]->SetVelocity(Vector3D(0.0f, 0.0f, 0.0f));
			dodgeballs[i]->SetPosition(Vector3D(0.0f, 200.0f, 0.0f));
		}

		// && dodgeballs[i]->GetBoundingSphere()->GetCollided() == true
		if (DenzilChar->GetBoundingSphere()->GetCollided() == true)
		{
			denzilHit = true;
			hits = hits + 1;

			cout << "Denzil Hit " << hits << " times" << endl;

			dodgeballs[i]->SetVelocity(Vector3D(0.0f, 0.0f, 0.0f));
			dodgeballs[i]->SetAcceleration(Vector3D(0.0f, 0.0f, 0.0f));

			// Follow Denzil
			//dodgeballs[i]->SetOldPos(dodgeballs[i]->GetPosition());

			dodgeballs[i]->SetPosition(Vector3D(DenzilChar->GetPosition().x + 20.0f + (i * 20.0f), DenzilChar->GetPosition().y, DenzilChar->GetPosition().z));

			Vector3D oldPos = dodgeballs[i]->GetPosition();

			dodgeballs[i]->position.x = DenzilChar->GetPosition().x + oldPos.x;


			if (hits < 4)
			{
				hitEffect->Play(0);
			}
			else if (hits = 4)
			{
				deathEffect->Play(0);

				nextScreen = GAMEOVER;
			}
			else if (hits > 4)
			{
				deathEffect->Stop();

				cout << "Denzil dead" << endl;
			}
		}
		else
		{
			denzilHit = false;
		}

		for (unsigned int j = 0; j < dodgeballs.size(); j++)
		{
			if (j != i)
			{
				// For Dodgeball - Dodgeball Collision

				/*Collision::SphereSphereCollision(dodgeballs[i]->GetBoundingSphere(), dodgeballs[j]->GetBoundingSphere());

				if (dodgeballs[i]->GetBoundingSphere()->GetCollided() == true && dodgeballs[j]->GetBoundingSphere()->GetCollided() == true)
				{
					//hitEffect->Play(0);
					//cout << "Hit" << endl;
				}
				else
				{
					//cout << "Not Hit" << endl;
				}*/
			}
		}
	}

	DenzilChar->Update(deltaTime, e);
	endZone->Update(deltaTime);

	if (completed)
	{
		winPlane->SetScale(Vector3D(1000.0f, 1000.0f, 1000.0f));
		winPlane->SetPosition(Vector3D(0.0f, 0.0f, 50.0f));

		newText();
	}

	winPlane->Update(deltaTime, e);

	for (unsigned int i = 0; i < dodgeballs.size(); i++)
	{
		dodgeballs[i]->Update(deltaTime);
	}

	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_m:
					if (myTimer->StartTimer())
						myTimer->StopTimer();

					if (myTimer->StopTimer())
						myTimer->StartTimer();
				break;

				case SDLK_SPACE:
					if (lightingOn)
					{
						glDisable(GL_LIGHT0);
						glDisable(GL_LIGHTING);

						lightingOn = false;
					}
					else
					{
						glEnable(GL_LIGHT0);
						glEnable(GL_LIGHTING);

						lightingOn = true;
					}
					break;
			}
		break;
	}

	//mCurrentTime += deltaTime;+

	// Update Clock
	//if (running == true)
	//{
	//	mCurrentTime += deltaTime;
	//}
	//else
	//{
	//}
}

void GameScreenLevel1::OutputLine(float x, float y, string text)
{
	glRasterPos2f(x, y);  // where to start drawing
	for (unsigned int i = 0; i < text.size(); i++) 
	{
		if (completed == false)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
		}
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
		}
	}
}

void GameScreenLevel1::RenderText()
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

			if (completed == false)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				OutputLine(2, 95, timePassed.str());
			}
			else
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				OutputLine(45, 50, timePassed.str());
				OutputLine(45, 60, "You Win");
				OutputLine(20, 20, "Press Enter to go to Level 2");
			}
		glPopMatrix();

		string hitsNumber = static_cast<ostringstream*>(&(ostringstream() << hits))->str();
		stringstream ssHits;
		ssHits << "Hits: " << hitsNumber;

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);

			if (completed == false)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				OutputLine(55, 95, ssHits.str());
			}
			else
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				OutputLine(45, 40, ssHits.str());

			}
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GameScreenLevel1::newText()
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
			OutputLine(45, 55, timePassed.str());
		glPopMatrix();

		string hitsNumber = static_cast<ostringstream*>(&(ostringstream() << hits))->str();
		stringstream ssHits;
		ssHits << "Hits: " << hitsNumber;

		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glColor3f(0.0f, 0.0f, 0.0f);
			OutputLine(45, 35, ssHits.str());
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GameScreenLevel1::DrawSkybox()
{
	// Skybox 
	// White vertices to allow different coloured text.
	glPushMatrix();
		glScalef(600.0f, 600.0f, 600.0f);
		glBindTexture(GL_TEXTURE_2D, skyboxTexture[0]->GetID());
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Top)	
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Top)
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, skyboxTexture[1]->GetID());
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f,  1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Bottom)
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f,  1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Bottom)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, skyboxTexture[2]->GetID());
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f,  -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f,  -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Front)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, skyboxTexture[3]->GetID());
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, 1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Back)
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Back)
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, 1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Back)
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Back)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, skyboxTexture[4]->GetID());
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
			glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f,  1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Left)
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,  1.0f,  1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Left)
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,  1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, skyboxTexture[5]->GetID());
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Right)
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	glColor3f(1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Right)
		glEnd();
		glPopMatrix();
}

void GameScreenLevel1::DrawObjects()
{
	// Denzil
	glPushMatrix();
		DenzilChar->SetScale(Vector3D(0.7f, 0.7f, 0.7f));
		DenzilChar->Render();
	glPopMatrix();

	//glPushMatrix();
	//	setLight();
	//glPopMatrix();

	glPushMatrix();
		endZone->SetScale(Vector3D(0.01f, 0.01f, 0.01f));
		endZone->Render();
	glPopMatrix();

	// Dodgeballs
	for (unsigned int i = 0; i < dodgeballs.size(); i++)
	{
		glPushMatrix();
			dodgeballs[i]->SetScale(Vector3D(0.2f, 0.2f, 0.2f));
			dodgeballs[i]->Render();
		glPopMatrix();
	}

	// Ground Plane
	glPushMatrix();
		groundPlane->SetScale(Vector3D(1.5f, 0.5f, 0.1f));
		glRotatef(-90, 90.0f, 0.0f, 0.0f);
		glTranslatef(-40.0f, 1.0f, -50.0f);
		//groundPlane->SetPosition(Vector3D(0.0f, 0.0f, 0.0f));
		groundPlane->Render();

		glPushMatrix();
			groundPlane2->SetScale(Vector3D(1.5f, 0.5f, 0.1f));
			glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(-60.0f, 0.0f, 0.0f);
			groundPlane2->Render();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		//winPlane->SetScale(Vector3D(0.01f, 0.01f, 0.01f));
		winPlane->Render();
	glPopMatrix();
	
}