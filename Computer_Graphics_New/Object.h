#pragma once
#include "pch.h"
using namespace std;

class Object
{
public:
	virtual ~Object();

	virtual RGB GetColor() { return color; };

	// 지정된 색상으로 변경합니다. 
	virtual GLvoid ColorChange(GLclampf Red, GLclampf Green, GLclampf Blue);

	// 색상을 랜덤으로 변경합니다.
	virtual GLvoid ColorRandomize();

	// 지정된 크기만큼 사이즈를 변경합니다.
	virtual GLvoid SizeChange(GLfloat dx, GLfloat dy) = 0;

	// 사이즈를 랜덤으로 변경합니다.
	virtual GLvoid SizeRandomize() = 0;

protected:
	RGB color;
	GL_Coord center;
};

