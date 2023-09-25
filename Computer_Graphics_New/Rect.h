#pragma once
#include "pch.h"
using namespace std;

class Rect : public Object
{
public:
	// �»��, ���ϴ��� ��ǥ�� �ް� �簢���� �����մϴ�.
	Rect(float x1, float y1, float x2, float y2, float Red, float Green, float Blue);
	// �߽� ��ǥ�� ũ�⸦ �ް� �簢���� �����մϴ�. 
	Rect(float x, float y, float size, float Red, float Green, float Blue);
	// �»��, ���ϴ��� ��ǥ�� �ް� ���������� �簢���� �����մϴ�.
	Rect(float x1, float y1, float x2, float y2);
	// �߽� ��ǥ�� ũ�⸦ �ް� ���������� �簢���� �����մϴ�.
	Rect(float x, float y, float size);

	virtual ~Rect();
	
	virtual void SizeChange(float dx, float dy) override;
	virtual void SizeRandomize() override;


	void SetSplitType(SPLIT_TYPE st);
	SPLIT_TYPE GetSplitType() { return splitType; }
	Coord GetCoord1() { return coord1; }
	Coord GetCoord2() { return coord2; }
	void SetCoord1(Coord coord) { this->coord1 = coord; }
	void SetCoord2(Coord coord) { this->coord2 = coord; }
	vector<Rect*> SplitRect();
	Coord GetCenter() { return center; }

public:
	Coord* GetPoint() { return point; }
	void DrawRect();
	float GetSize();
	bool CollitionCheck(Rect* r1, Rect* r2);
	bool MouseClickCheck(Coord Clicked);

private:
	virtual void SetPoint() override;
	virtual void SetCenter() override;

protected:
	// coord1�� �簢���� �»�� ��ǥ�Դϴ�.
	Coord coord1;

	// coord1�� �簢���� ���ϴ� ��ǥ�Դϴ�.
	Coord coord2;

	// �簢���� �������Դϴ�. 0���� �»�, ���, ����, ���� �Դϴ�.
	Coord point[4];

	SPLIT_TYPE splitType;

	bool AnimSwitch;

};

