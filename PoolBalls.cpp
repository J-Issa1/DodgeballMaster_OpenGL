#include "PoolBalls.h"
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

PoolBalls::PoolBalls(Vector3D startPosition, string modelFileName, int texID)
{
	position = startPosition;

	mScale = Vector3D(1.0f, 1.0f, 1.0f);

	scale = 1.0f;
	_mass = 1.0f;
	dragFactor = 1.0f;
	gravity = -9.81;

	_useAcc = true;
	collisionCompleted = false;

	velocity = Vector3D(0.0f, 0.0f, 0.0f);
	acceleration = Vector3D(0.0f, 0.0f, 0.0f);

	//3ds file to load
	strcpy_s(fileName, modelFileName.c_str());
	LoadModel();
	object.id_texture = texID;

	boundingSphere = new Sphere(position, scale*1.2f);

	bounceEffect = new SoundEffect();
	bounceEffect->Load("Music/Bounce.wav");
}

PoolBalls::~PoolBalls()
{
}

void PoolBalls::Render()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glColor3f(1.0, 1.0, 1.0);
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

void PoolBalls::Update(float deltaTime)
{
	boundingSphere->SetCollided(false);

	if (position.x > 22 || position.x < -25)
		velocity.x *= -1;
	
	if (position.y > 80 || position.y < -50)
		velocity.y *= -1;
	
	if (position.z > 40 || position.z < -50)
		velocity.z *= -1;

	//if (velocity.x < -50)
	//{
	//	velocity.x * 0.98f;
	//	//velocity.x = 0.0f;
	//}
	//else if (velocity.x > 50)
	//{
	//	//velocity.x = 0.0f;
	//	velocity.x * 0.98f;
	//}
	//if (velocity.z < -20)
	//{
	//	velocity.z * 0.98f;
	//	//velocity.z = 0.0f;
	//}
	//else if (velocity.z > 20)
	//{
	//	//velocity.z = 0.0f;
	//	velocity.z * 0.98f;
	//}

	if (_useAcc)
	{	
		Drag();

		UpdateAccel();
		MoveAcceleration(deltaTime);
	}
	else
	{
		MoveVelocity();
	}

	//if (position.y <= -50)
	//	bounceEffect->Play(0);
}

void PoolBalls::LoadModel()
{
	if (fileName[0] != '-')
		Load3DS(&object, fileName);
}

void PoolBalls::LoadTexture()
{
}

void PoolBalls::SetPosition(Vector3D mChangePosition)
{
	position = mChangePosition;
	oldPosition = position;
}

void PoolBalls::SetScale(Vector3D mChangeScale)
{
	mScale = mChangeScale;
}

void PoolBalls::SetVelocity(Vector3D mVelocity)
{
	velocity = mVelocity;
}

void PoolBalls::SetAcceleration(Vector3D mAcceleration)
{
	acceleration = mAcceleration;
}

Sphere * PoolBalls::GetBoundingSphere()
{
	return boundingSphere;
}

void PoolBalls::MoveVelocity()
{
	Vector3D _position = GetPosition();

	_position.x += velocity.x;
	_position.y += velocity.y;
	_position.z += velocity.z;

	this->SetPosition(Vector3D(_position));
	boundingSphere->Update(_position);
}

void PoolBalls::MoveAcceleration(float deltaTime)
{
	Vector3D _position = GetPosition();

	// s = ut + 0.5 at^2
	_position.x += velocity.x * deltaTime + 0.5f * acceleration.x * deltaTime * deltaTime;
	_position.y += velocity.y * deltaTime + 0.5f * acceleration.y * deltaTime * deltaTime;
	_position.z += velocity.z * deltaTime + 0.5f * acceleration.z * deltaTime * deltaTime;

	velocity.x += acceleration.x * deltaTime;
	velocity.y += acceleration.y * deltaTime;
	velocity.z += acceleration.z * deltaTime;

	SetPosition(Vector3D(_position));
	boundingSphere->Update(_position);
}

void PoolBalls::Drag()
{
	// calculate components of drag
	dragForce.x = -dragFactor * velocity.x;
	dragForce.y = -dragFactor * velocity.y;
	dragForce.z = -dragFactor * velocity.z;
}

void::PoolBalls::UpdateAccel()
{
	acceleration.x = dragForce.x / _mass;
	acceleration.y = dragForce.y / _mass;
	acceleration.z = dragForce.z / _mass;
}

void PoolBalls::ResolveCollision(PoolBalls* poolBall1, PoolBalls* poolBall2)
{
	// coefficient of resitution
	float rCoef = 0.8f;

	Vector3D prevPos1 = poolBall1->GetOldPosition();
	Vector3D prevPos2 = poolBall2->GetOldPosition();

	float mass1 = poolBall1->GetMass();
	float mass2 = poolBall2->GetMass();

	Vector3D initialVelocity1 = poolBall1->GetVelocity();
	Vector3D initialVelocity2 = poolBall2->GetVelocity();

	poolBall1->SetPosition(prevPos1);
	poolBall2->SetPosition(prevPos2);

	Vector3D velocity1;
	Vector3D velocity2;

	velocity1.x = (mass1 * initialVelocity1.x) + (mass2 * initialVelocity2.x) + ((mass2 * rCoef) * (initialVelocity2.x - initialVelocity1.x)) / (mass1 + mass2);
	velocity1.y = 0.0f;
	velocity1.z = (mass1 * initialVelocity1.z) + (mass2 * initialVelocity2.z) + ((mass2 * rCoef) * (initialVelocity2.z - initialVelocity1.z)) / (mass1 + mass2);

	velocity2.x = (mass1 * initialVelocity1.x) + (mass2 * initialVelocity2.x) + ((mass1 * rCoef) * (initialVelocity1.x - initialVelocity2.x)) / (mass1 + mass2);
	velocity2.y = 0.0f;
	velocity2.z = (mass1 * initialVelocity1.z) + (mass2 * initialVelocity2.z) + ((mass1 * rCoef) * (initialVelocity1.z - initialVelocity2.z)) / (mass1 + mass2);

	poolBall1->SetVelocity(velocity1);
	poolBall2->SetVelocity(velocity2);

	collisionCompleted = true;
}