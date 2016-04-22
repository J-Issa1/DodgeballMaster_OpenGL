#ifndef _DENZIL_H
#define _DENZIL_H

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL\gl.h>
#include "./gl/glut.h"
#include "Object3ds.h"

class Sphere;

class Denzil : public Object3DS
{
public:
	Denzil(Vector3D startPosition, string modelFileName, int texID);
	~Denzil();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void MoveDenzilForward(float amount);
	void MoveDenzilLeft(float amount);

	Sphere * GetBoundingSphere();

private:
	Vector3D newPos;

	float scale;

	Sphere * boundingSphere;
};

#endif