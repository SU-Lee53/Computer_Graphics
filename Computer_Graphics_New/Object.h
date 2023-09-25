#pragma once
#include "pch.h"
using namespace std;

class Object
{
public:
	virtual ~Object();

	RGB GetColor() { return color; };

	// ������ �������� �����մϴ�. 
	void ColorChange(GLclampf Red, GLclampf Green, GLclampf Blue);

	// ������ �������� �����մϴ�.
	void ColorRandomize();

	// ������ ũ�⸸ŭ ����� �����մϴ�.
	virtual void SizeChange(GLfloat dx, GLfloat dy) = 0;

	// ����� �������� �����մϴ�.
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

