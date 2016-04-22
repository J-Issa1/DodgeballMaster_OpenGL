#ifndef _POOLBALLS_H
#define _POOLBALLS_H

#include "Commons.h"
#include "SoundEffect.h"
#include <string>
using std::string;

class Sphere;

class PoolBalls
{
public:
	PoolBalls(Vector3D startPosition, string modelFileName, int texID);
	~PoolBalls();

	void Update(float deltaTime);
	void Render();

	// Load 3DS File
	void LoadModel();

	// Load texture for model
	void LoadTexture();

	Vector3D GetPosition() { return position; }
	Vector3D GetOldPosition() const { return oldPosition; }

	Vector3D GetVelocity() { return velocity; }
	Vector3D GetAcceleration() { return acceleration; }

	float GetMass() const { return _mass; }

	void SetPosition(Vector3D mChangePosition);
	void SetScale(Vector3D mChangeScale);

	void SetVelocity(Vector3D velocity);
	void SetAcceleration(Vector3D acceleration);

	void MoveVelocity();
	void MoveAcceleration(float deltaTime);
	void UpdateAccel();

	void Drag();

	void ResolveCollision(PoolBalls* poolBall1, PoolBalls* poolBall2);

	void SetMaterial(material newMaterial);

	Sphere * GetBoundingSphere();

	bool collisionCompleted;

private:
	Vector3D position, mScale, oldPosition;

	float scale, _mass, dragFactor, gravity;

	Vector3D velocity;
	Vector3D acceleration;
	Vector3D dragForce;

	bool _useAcc;

	char fileName[20];
	char textureNme[20];

	obj_type object;

	Sphere * boundingSphere;

	SoundEffect* bounceEffect;
};

#endif




