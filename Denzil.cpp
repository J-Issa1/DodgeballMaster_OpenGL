#include "Denzil.h"
#include "Collision.h"

Denzil::Denzil(Vector3D startPosition, string modelFileName, int texID) : Object3DS(startPosition, modelFileName, texID)
{
	scale = 1.0f;

	// Move bounding sphere down
	newPos = Vector3D(mPosition.x, mPosition.y, mPosition.z + 15.0f);

	boundingSphere = new Sphere(newPos, scale*10.0f);

	//velocity = Vector3D(0.0f, 0.0f, 0.0f);
	//acceleration = Vector3D(0.0f, 0.0f, 0.0f);
}

Denzil::~Denzil()
{
}

void Denzil::Render()
{
	glPushMatrix();
		glTranslatef(newPos.x, newPos.y, newPos.z);
		//glTranslatef(mPosition.x, mPosition.y, mPosition.z);
		// z  + 20.0f
		glScalef(mScale.x, mScale.y, mScale.z);
		glColor3f(0.0f, 0.0f, 1.0f);
		glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();

	Object3DS::Render();
}

void Denzil::Update(float deltaTime, SDL_Event e)
{
	boundingSphere->SetCollided(false);

	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_i:
					MoveDenzilForward(1.0f);
				break;

				case SDLK_k:
					MoveDenzilForward(-1.0f);
					break;

				case SDLK_j:
					MoveDenzilLeft(-1.0f);
					break;

				case SDLK_l:
					MoveDenzilLeft(1.0f);
					break;
			}
				break;
	}

	if (newPos.x && mPosition.x < -90.0f)
	{
		newPos.x = -90.0f; 
		mPosition.x = -90.0f;
	}
	else if (newPos.x && mPosition.x > 71.0f)
	{
		newPos.x = 71.0f;
		mPosition.x = 71.0f;
	}
	//if (newPos.z && mPosition.z < -15.0f)
	//{
	//	newPos.z = -15.0f;
	//	mPosition.z = -15.0f;
	//}
	//else if (newPos.z && mPosition.z > 15.0f)
	//{
	//	newPos.z = 15.0f;
	//	mPosition.z = 15.0f;
	//}

	boundingSphere->Update(newPos);
}

void Denzil::MoveDenzilForward(float amount)
{
	newPos.x -= amount;
	mPosition.x -= amount;
}

void Denzil::MoveDenzilLeft(float amount)
{
	newPos.z -= amount;
	mPosition.z -= amount;
}

Sphere * Denzil::GetBoundingSphere()
{
	return boundingSphere;
}

