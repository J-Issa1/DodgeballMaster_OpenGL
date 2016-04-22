#ifndef _BALLOBJECT_H
#define _BALLOBJECT_H

#include "Commons.h"
#include "SoundEffect.h"
#include <string>
using std::string;

class Sphere;

class BallObject
{
public:
	BallObject(Vector3D startPosition, string modelFileName, int texID);
	virtual ~BallObject();

	virtual void Update(float deltaTime);
	virtual void Render();

	// Load 3DS File
	void LoadModel();

	// Load texture for model
	void LoadTexture();

	Vector3D GetPosition() { return position; }

	//void SetRotation(Vector3D mChangeRotation, float angle);
	void SetPosition(Vector3D mChangePosition);
	void SetScale(Vector3D mChangeScale);

	void SetVelocity(Vector3D mVelocity);
	void SetAcceleration(Vector3D mAcceleration);

	void SetMaterial(material newMaterial);

	Sphere * GetBoundingSphere();

	Vector3D position;

private:
	char fileName[20];
	char textureNme[20];

	obj_type object;

	SoundEffect* bounceEffect;

protected:
	Vector3D mScale;

	float scale;

	Vector3D velocity;
	Vector3D acceleration;

	Sphere * boundingSphere;

};

#endif

