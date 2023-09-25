#include "pch.h"
#include "Rect.h"

Rect::Rect(float x1, float y1, float x2, float y2, float Red, float Green, float Blue)
{
	this->coord1.x = x1;
	this->coord1.y = y1;
	this->coord2.x = x2;
	this->coord2.y = y2;

	this->color.Red = Red;
	this->color.Green = Green;
	this->color.Blue = Blue;
	this->isValid = true;

	SetSplitType(static_cast<SPLIT_TYPE>(rand() % 3));
	SetCenter();
	SetPoint();
}

Rect::Rect(float x, float y, float size, float Red, float Green, float Blue)
{
	this->coord1.x = x - (size / 2);
	this->coord1.y = y + (size / 2);
	this->coord2.x = x + (size / 2);
	this->coord2.y = y - (size / 2);

	this->color.Red = Red;
	this->color.Green = Green;
	this->color.Blue = Blue;
	this->isValid = true;

	SetSplitType(static_cast<SPLIT_TYPE>(rand() % 3));
	SetCenter();
	SetPoint();
}

Rect::Rect(float x1, float y1, float x2, float y2)
{
	this->coord1.x = x1;
	this->coord1.y = y1;
	this->coord2.x = x2;
	this->coord2.y = y2;

	this->ColorRandomize();
	this->isValid = true;

	SetSplitType(static_cast<SPLIT_TYPE>(rand() % 3));
	SetCenter();
	SetPoint();
}

Rect::Rect(float x, float y, float size)
{
	this->coord1.x = x - (size / 2);
	this->coord1.y = y + (size / 2);
	this->coord2.x = x + (size / 2);
	this->coord2.y = y - (size / 2);

	this->ColorRandomize();
	this->isValid = true;

	SetSplitType(static_cast<SPLIT_TYPE>(rand() % 3));
	SetCenter();
	SetPoint();
}

Rect::~Rect()
{
}

void Rect::SizeChange(float dx, float dy)
{
	coord1.x -= dx;
	coord1.y += dy;
	coord2.x += dx;
	coord2.y -= dy;

	point[0] = coord1;
	point[1] = { coord2.x, coord1.y };
	point[2] = { coord1.x, coord2.y };
	point[3] = coord2;

}

void Rect::SizeRandomize()
{
	Coord before1 = { coord1.x, coord1.y };
	Coord before2 = { coord2.x, coord2.y };

	float change = (((static_cast<float>(rand()) / RAND_MAX) - 0.5) * 0.1f);
	coord1.x -= change;
	change = (((static_cast<float>(rand()) / RAND_MAX) - 0.5) * 0.1f);
	coord1.y += change;
	change = (((static_cast<float>(rand()) / RAND_MAX) - 0.5) * 0.1f);
	coord2.x += change;
	change = (((static_cast<float>(rand()) / RAND_MAX) - 0.5) * 0.1f);
	coord2.y -= change;

	// 사이즈가 음수 or 0이 되면 원상복구
	if (coord1.x >= coord2.x || coord1.y <= coord2.y)
	{
		coord1.x = before1.x;
		coord1.y = before1.y;
		coord2.x = before2.x;
		coord2.y = before2.y;
	}

	SetPoint();
}

void Rect::SetSplitType(SPLIT_TYPE st)
{
	splitType = st;
}

vector<Rect*> Rect::SplitRect()
{
	vector<Rect*> splitList;

	Rect* r1 = new Rect(coord1.x, coord1.y, (coord1.x + coord2.x) / 2, (coord1.y + coord2.y) / 2, color.Red, color.Green, color.Blue);
	Rect* r2 = new Rect((coord1.x + coord2.x) / 2, coord1.y, coord2.x, (coord1.y + coord2.y) / 2, color.Red, color.Green, color.Blue);
	Rect* r3 = new Rect(coord1.x, (coord1.y + coord2.y) / 2, (coord1.x + coord2.x) / 2, coord2.y, color.Red, color.Green, color.Blue);
	Rect* r4 = new Rect((coord1.x + coord2.x) / 2, (coord1.y + coord2.y) / 2, coord2.x, coord2.y, color.Red, color.Green, color.Blue);
	
	splitList.push_back(r1);
	splitList.push_back(r2);
	splitList.push_back(r3);
	splitList.push_back(r4);

	return splitList;
}

void Rect::DrawRect()
{
	glColor3f(color.Red, color.Green, color.Blue);
	glRectf(coord1.x, coord1.y, coord2.x, coord2.y);
}

float Rect::GetSize()
{
	GLfloat x = coord2.x - coord1.x;
	GLfloat y = coord1.y - coord2.y;

	return x * y;
}

bool Rect::CollitionCheck(Rect* r1, Rect* r2)
{
	// 충돌체크
	GLboolean Collition = false;

	if (r1->GetSize() >= r2->GetSize())
	{
		// r1이 더 크므로 r2의 포인트가 r1안에 들어있다면 충돌임
		Coord* pointList = r2->GetPoint();
		if ((pointList[0].x >= r1->coord1.x && pointList[0].x <= r1->coord2.x && pointList[0].y <= r1->coord1.y && pointList[0].y >= r1->coord2.y)
			|| (pointList[1].x >= r1->coord1.x && pointList[1].x <= r1->coord2.x && pointList[1].y <= r1->coord1.y && pointList[1].y >= r1->coord2.y)
			|| (pointList[2].x >= r1->coord1.x && pointList[2].x <= r1->coord2.x && pointList[2].y <= r1->coord1.y && pointList[2].y >= r1->coord2.y)
			|| (pointList[3].x >= r1->coord1.x && pointList[3].x <= r1->coord2.x && pointList[3].y <= r1->coord1.y && pointList[3].y >= r1->coord2.y))
		{
			Collition = true;
		}
	}
	else
	{
		// r1이 더 크므로 r2의 포인트가 r1안에 들어있다면 충돌임
		Coord* pointList = r1->GetPoint();
		if ((pointList[0].x >= r2->coord1.x && pointList[0].x <= r2->coord2.x && pointList[0].y <= r2->coord1.y && pointList[0].y >= r2->coord2.y)
			|| (pointList[1].x >= r2->coord1.x && pointList[1].x <= r2->coord2.x && pointList[1].y <= r2->coord1.y && pointList[1].y >= r2->coord2.y)
			|| (pointList[2].x >= r2->coord1.x && pointList[2].x <= r2->coord2.x && pointList[2].y <= r2->coord1.y && pointList[2].y >= r2->coord2.y)
			|| (pointList[3].x >= r2->coord1.x && pointList[3].x <= r2->coord2.x && pointList[3].y <= r2->coord1.y && pointList[3].y >= r2->coord2.y))
		{
			Collition = true;
		}
	}

	return Collition;
}

bool Rect::MouseClickCheck(Coord Clicked)
{
	bool isClicked = false;
	
	if ((Clicked.x >= coord1.x && Clicked.x <= coord2.x)
		&& (Clicked.y <= coord1.y && Clicked.y >= coord2.y))
	{
		isClicked = true;
	}

	return isClicked;

}

void Rect::SetPoint()
{
	point[0] = coord1;
	point[1] = { coord2.x, coord1.y };
	point[2] = { coord1.x, coord2.y };
	point[3] = coord2;
}

void Rect::SetCenter()
{
	center.x = (coord1.x + coord2.x) / 2;
	center.y = (coord1.y + coord2.y) / 2;
}
