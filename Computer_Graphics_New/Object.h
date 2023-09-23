#pragma once
#include "pch.h"
using namespace std;

class Object
{
public:
	virtual ~Object();

	virtual RGB GetColor() { return color; };

	// ������ �������� �����մϴ�. 
	virtual GLvoid ColorChange(GLclampf Red, GLclampf Green, GLclampf Blue);

	// ������ �������� �����մϴ�.
	virtual GLvoid ColorRandomize();

	// ������ ũ�⸸ŭ ����� �����մϴ�.
	virtual GLvoid SizeChange(GLfloat dx, GLfloat dy) = 0;

	// ����� �������� �����մϴ�.
	virtual GLvoid SizeRandomize() = 0;

protected:
	RGB color;
	GL_Coord center;
};

