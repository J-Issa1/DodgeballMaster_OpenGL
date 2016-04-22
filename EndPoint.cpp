#include "EndPoint.h"
#include "./gl/glut.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

EndPoint::EndPoint(Vector3D startPosition, string modelFileName, int texID)
{
	position = startPosition;

	mScale = Vector3D(1.0f, 1.0f, 1.0f);

	scale = 1.0f;

	//3ds file to load
	strcpy_s(fileName, modelFileName.c_str());
	LoadModel();
	object.id_texture = texID;

	boundingSphere = new Sphere(position, scale*3.0f);

}

EndPoint::~EndPoint()
{
}

void EndPoint::Render()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glScalef(mScale.x, mScale.y, mScale.z);
		//glScalef(scale*3.0f, scale*3.0f, scale*3.0f);
		glColor3f(1.0f, 0.0f, 1.0f);

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

void EndPoint::Update(float deltaTime)
{
	boundingSphere->SetCollided(false);

	boundingSphere->Update(position);
}

void EndPoint::LoadModel()
{
	if (fileName[0] != '-')
		Load3DS(&object, fileName);
}

void EndPoint::LoadTexture()
{
}

void EndPoint::SetPosition(Vector3D mChangePosition)
{
	position = mChangePosition;
}

void EndPoint::SetScale(Vector3D mChangeScale)
{
	mScale = mChangeScale;
}

Sphere * EndPoint::GetBoundingSphere()
{
	return boundingSphere;
}
