#include "BallObject.h"
#include "./gl/glut.h"
#include "3dsLoader.h"
#include "Texture.h"
#include "Collision.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

BallObject::BallObject(Vector3D startPosition, string modelFileName, int texID)
{
	mScale = Vector3D(1.0f, 1.0f, 1.0f);

	scale = 1.0f;

	//3ds file to load
	strcpy_s(fileName, modelFileName.c_str());
	LoadModel();
	object.id_texture = texID;

	position.x = -100 * (float)rand() / (RAND_MAX)+ 40;
	position.y = 40 * (float)rand() / (RAND_MAX)+ 5;
	position.z = 50 * (float)rand() / (RAND_MAX) - 40;

	velocity.x = 50 * (float)rand() / ((RAND_MAX)* 1000) - .005;
	velocity.y = 50 * (float)rand() / ((RAND_MAX)* 1000) - .005;
	velocity.z = 50 * (float)rand() / ((RAND_MAX)* 1000) - .005;

	boundingSphere = new Sphere(position, scale*5.0f);

	acceleration = Vector3D(0.0f, -0.1f, 0.0f);

	bounceEffect = new SoundEffect();
	bounceEffect->Load("Music/Bounce.wav");
}

BallObject::~BallObject()
{
}

void BallObject::Render()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glColor3f(0.0, 0.0, 0.0);
		glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(position.x, position.y, position.z);
		glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
		glScalef(mScale.x, mScale.y, mScale.z);

		// Set the active texture.
		glBindTexture(GL_TEXTURE_2D, object.id_texture);

		glBegin(GL_TRIANGLES);
		for (int l_index = 0; l_index < object.polygons_qty; l_index++)
		{
			// ----------------- FIRST VERTEX ----------------------------------
			// Texture Coordinates
			glTexCoord2f(object.mapcoord[object.polygon[l_index].a].u, object.mapcoord[object.polygon[l_index].a].v);

			// Coordinates of the first Vertex
			glVertex3f(object.vertex[object.polygon[l_index].a].x, object.vertex[object.polygon[l_index].a].y, object.vertex[object.polygon[l_index].a].z);

			// ----------------- SECOND VERTEX ----------------------------------
			// Texture Coordinates 
			glTexCoord2f(object.mapcoord[object.polygon[l_index].b].u, object.mapcoord[object.polygon[l_index].b].v);

			// Coordinates of the second Vertex
			glVertex3f(object.vertex[object.polygon[l_index].b].x, object.vertex[object.polygon[l_index].b].y, object.vertex[object.polygon[l_index].b].z);

			// ----------------- THIRD VERTEX ----------------------------------
			// Texture Coordinates
			glTexCoord2f(object.mapcoord[object.polygon[l_index].c].u, object.mapcoord[object.polygon[l_index].c].v);

			// Coordinates of the third Vertex
			glVertex3f(object.vertex[object.polygon[l_index].c].x, object.vertex[object.polygon[l_index].c].y, object.vertex[object.polygon[l_index].c].z);
		}
		glEnd();
	glPopMatrix();
}

void BallObject::Update(float deltaTime)
{
	boundingSphere->SetCollided(false);
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	if (position.x > 70 || position.x < -90)
		velocity.x *= -1;

	if (position.y > 500 || position.y < -50)
		velocity.y *= -1;

	if (position.z > 50 || position.z < 20)
		velocity.z *= -1;

	position.x += velocity.x * deltaTime + 0.5f * acceleration.x * deltaTime * deltaTime;
	position.y += velocity.y * deltaTime + 0.5f * acceleration.y * deltaTime * deltaTime;
	position.z += velocity.z * deltaTime + 0.5f * acceleration.z * deltaTime * deltaTime;

	velocity.x += acceleration.x * deltaTime;
	velocity.y += acceleration.y * deltaTime;
	velocity.z += acceleration.z * deltaTime;

	velocity.x * 0.98f;
	velocity.y * 0.98f;
	velocity.z * 0.98f;

	boundingSphere->Update(position);

	if (position.y <= -50)
		bounceEffect->Play(0);
}

void BallObject::LoadModel()
{
	if (fileName[0] != '-')
		Load3DS(&object, fileName);
}

void BallObject::LoadTexture()
{
}

void BallObject::SetPosition(Vector3D mChangePosition)
{
	position = mChangePosition;
}

void BallObject::SetScale(Vector3D mChangeScale)
{
	mScale = mChangeScale;
}

void BallObject::SetVelocity(Vector3D mVelocity)
{
	velocity = mVelocity;
}

void BallObject::SetAcceleration(Vector3D mAcceleration)
{
	acceleration = mAcceleration;
}

Sphere * BallObject::GetBoundingSphere()
{
	return boundingSphere;
}
