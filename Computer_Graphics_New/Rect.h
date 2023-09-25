#pragma once
#include "pch.h"
using namespace std;

class Rect : public Object
{
public:
	// 좌상단, 우하단의 좌표를 받고 사각형을 생성합니다.
	Rect(float x1, float y1, float x2, float y2, float Red, float Green, float Blue);
	// 중심 좌표와 크기를 받고 사각형을 생성합니다. 
	Rect(float x, float y, float size, float Red, float Green, float Blue);
	// 좌상단, 우하단의 좌표를 받고 랜덤색상의 사각형을 생성합니다.
	Rect(float x1, float y1, float x2, float y2);
	// 중심 좌표와 크기를 받고 랜덤색상의 사각형을 생성합니다.
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
	// coord1은 사각형의 좌상단 좌표입니다.
	Coord coord1;

	// coord1은 사각형의 우하단 좌표입니다.
	Coord coord2;

	// 사각형의 꼭짓점입니다. 0부터 좌상, 우상, 좌하, 우하 입니다.
	Coord point[4];

	SPLIT_TYPE splitType;

	bool AnimSwitch;

};

