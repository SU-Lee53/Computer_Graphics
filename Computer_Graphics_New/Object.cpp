#include "pch.h"
#include "Object.h"

Object::~Object()
{
}

void Object::ColorChange(GLclampf Red, GLclampf Green, GLclampf Blue)
{
	color.Red = Red;
	color.Green = Green;
	color.Blue = Blue;
}

void Object::ColorRandomize()
{
	srand(time(0));

	color.Red = static_cast<GLfloat>(rand()) / RAND_MAX;
	color.Green = static_cast<GLfloat>(rand()) / RAND_MAX;
	color.Blue = static_cast<GLfloat>(rand()) / RAND_MAX;
}
