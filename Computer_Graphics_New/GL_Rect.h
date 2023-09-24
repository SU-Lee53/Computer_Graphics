#pragma once
#include "pch.h"
using namespace std;

class GL_Rect : public Object
{
public:
	// �»��, ���ϴ��� ��ǥ�� �ް� �簢���� �����մϴ�.
	GL_Rect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLclampf Red, GLclampf Green, GLclampf Blue);
	// �߽� ��ǥ�� ũ�⸦ �ް� �簢���� �����մϴ�. 
	GL_Rect(GLfloat x, GLfloat y, GLfloat size, GLclampf Red, GLclampf Green, GLclampf Blue);
	// �»��, ���ϴ��� ��ǥ�� �ް� ���������� �簢���� �����մϴ�.
	GL_Rect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	// �߽� ��ǥ�� ũ�⸦ �ް� ���������� �簢���� �����մϴ�.
	GL_Rect(GLfloat x, GLfloat y, GLfloat size);

	virtual ~GL_Rect();
	
	virtual GLvoid SizeChange(GLfloat dx, GLfloat dy) override;
	virtual GLvoid SizeRandomize() override;


	GLvoid SetSplitType(SPLIT_TYPE st);
	SPLIT_TYPE GetSplitType() { return splitType; }
	GL_Coord GetCoord1() { return coord1; }
	GL_Coord GetCoord2() { return coord2; }
	GLvoid SetCoord1(GL_Coord coord) { this->coord1 = coord; }
	GLvoid SetCoord2(GL_Coord coord) { this->coord2 = coord; }
	GLvoid SplitRect();
	GL_Coord GetCenter() { return center; }

public:
	GL_Coord* GetPoint() { return point; }
	GLvoid DrawRect();
	GLfloat GetSize();
	vector<GL_Rect*> GetSplitList() { return splitList; }
	GLvoid ClearSplitList() { splitList.clear(); }
	GLvoid PushSplitList(GL_Rect* r) { splitList.push_back(r); }
	GLboolean CollitionCheck(GL_Rect* r1, GL_Rect* r2);
	GLboolean MouseClickCheck(GL_Coord Clicked);

	GLvoid AnimStraight();
	GLvoid AnimDiagnoal();
	GLvoid AnimBoth();
	GLvoid SetAnimSwitch(GLboolean flag) { AnimSwitch = flag; }
private:
	GLvoid SetPoint();
	GLvoid SetCenter();

protected:
	// coord1�� �簢���� �»�� ��ǥ�Դϴ�.
	GL_Coord coord1;

	// coord1�� �簢���� ���ϴ� ��ǥ�Դϴ�.
	GL_Coord coord2;

	// �簢���� �������Դϴ�. 0���� �»�, ���, ����, ���� �Դϴ�.
	GL_Coord point[4];

	SPLIT_TYPE splitType;
	vector <GL_Rect*> splitList;

	GLboolean AnimSwitch;

};

