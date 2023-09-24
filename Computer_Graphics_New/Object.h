#pragma once
#include "pch.h"
using namespace std;

class Object
{
public:
	virtual ~Object();

	RGB GetColor() { return color; };

	// ������ �������� �����մϴ�. 
	GLvoid ColorChange(GLclampf Red, GLclampf Green, GLclampf Blue);

	// ������ �������� �����մϴ�.
	GLvoid ColorRandomize();

	// ������ ũ�⸸ŭ ����� �����մϴ�.
	virtual GLvoid SizeChange(GLfloat dx, GLfloat dy) = 0;

	// ����� �������� �����մϴ�.
	virtual GLvoid SizeRandomize() = 0;

	GLvoid SetValidFlag(GLboolean flag) { isValid = flag; }
	GLboolean GetValidFlag() { return isValid; }

protected:
	RGB color;
	GL_Coord center;
	GLboolean isValid;
};

