#pragma once
#include "pch.h"
using namespace std;

class Object
{
public:
	virtual ~Object();

	RGB GetColor() { return color; };

	// 지정된 색상으로 변경합니다. 
	GLvoid ColorChange(GLclampf Red, GLclampf Green, GLclampf Blue);

	// 색상을 랜덤으로 변경합니다.
	GLvoid ColorRandomize();

	// 지정된 크기만큼 사이즈를 변경합니다.
	virtual GLvoid SizeChange(GLfloat dx, GLfloat dy) = 0;

	// 사이즈를 랜덤으로 변경합니다.
	virtual GLvoid SizeRandomize() = 0;

	GLvoid SetValidFlag(GLboolean flag) { isValid = flag; }
	GLboolean GetValidFlag() { return isValid; }

protected:
	RGB color;
	GL_Coord center;
	GLboolean isValid;
};

