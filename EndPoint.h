#ifndef _ENDPOINT_H
#define _ENDPOINT_H

#include "Commons.h"
#include "3dsLoader.h"
#include "Texture.h"
#include "Collision.h"
#include <string>
using std::string;

class Sphere;

class EndPoint
{
public:
	EndPoint(Vector3D startPosition, string modelFileName, int texID);
	~EndPoint();

	void Update(float deltaTime);
	void Render();

	// Load 3DS File
	void LoadModel();

	// Load texture for model
	void LoadTexture();

	Vector3D GetPosition() { return position; }

	//void SetRotation(Vector3D mChangeRotation, float angle);
	void SetPosition(Vector3D mChangePosition);
	void SetScale(Vector3D mChangeScale);

	void SetMaterial(material newMaterial);

	Sphere * GetBoundingSphere();

	Vector3D position;
	float scale;

private:
	Vector3D mScale;

	char fileName[20];
	char textureNme[20];

	obj_type object;

	//Vector3D position;
	//float scale;

	Sphere * boundingSphere;
};

#endif


