#pragma once
#include "pch.h"
using namespace std;

class Object
{
public:
	virtual ~Object();

	RGB GetColor() { return color; };

	// 지정된 색상으로 변경합니다. 
	void ColorChange(GLclampf Red, GLclampf Green, GLclampf Blue);

	// 색상을 랜덤으로 변경합니다.
	void ColorRandomize();

	// 지정된 크기만큼 사이즈를 변경합니다.
	virtual void SizeChange(GLfloat dx, GLfloat dy) = 0;

	// 사이즈를 랜덤으로 변경합니다.
	virtual void SizeRandomize() = 0;

	void SetValidFlag(bool flag) { isValid = flag; }
	bool GetValidFlag() { return isValid; }

private:
	virtual void SetPoint() = 0;
	virtual void SetCenter() = 0;

protected:
	RGB color;
	Coord center;
	bool isValid;
};

