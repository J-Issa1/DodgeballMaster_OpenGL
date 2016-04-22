#ifndef _OBJECT3DS_H
#define _OBJECT3DS_H

#include "SDL.h"
#include "Commons.h"
#include "3dsLoader.h"
#include "Texture.h"
#include <string>

using std::string;

class Object3DS
{
public:
	Object3DS(Vector3D startPosition, string modelFileName, int texID);
	virtual ~Object3DS();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	// Load 3DS File
	void LoadModel();

	// Load texture for model
	void LoadTexture();

	Vector3D GetPosition() { return mPosition; }

	void SetRotation(Vector3D mChangeRotation, float angle);
	void SetPosition(Vector3D mChangePosition);
	void SetScale(Vector3D mChangeScale);

	void SetMaterial(material newMaterial);

protected:
	Vector3D mPosition, mScale, mRotation;

	char fileName[20];
	char textureNme[20];

	obj_type object;

	float mRotVelocity, rotateAngle;
};

#endif