#include "pch.h"
#include "Anims.h"

Anims::Anims(Objects* obj) : obj(obj)
{
}

Anims::~Anims()
{
}

void Anims::Bounce()
{
	switch (bounceDir)
	{
	case NW:
		obj->MoveObject(UP, 0.01f);
		obj->MoveObject(LEFT, 0.01f);
		break;
	case NE:
		obj->MoveObject(UP, 0.01f);
		obj->MoveObject(RIGHT, 0.01f);
		break;
	case SE:
		obj->MoveObject(DOWN, 0.01f);
		obj->MoveObject(RIGHT, 0.01f);
		break;
	case SW:
		obj->MoveObject(DOWN, 0.01f);
		obj->MoveObject(LEFT, 0.01f);
		break;

	}

	Dir isOut = obj->CheckOutOfScreen();

	switch (isOut)
	{
	case UP:
	{
		if (bounceDir == NW)
			bounceDir = SW;
		else if (bounceDir == NE)
			bounceDir = SE;

		break;
	}

	case DOWN:
	{
		if (bounceDir == SW)
			bounceDir = NW;
		else if (bounceDir == SE)
			bounceDir = NE;

		break;
	}

	case RIGHT:
	{
		if (bounceDir == NE)
			bounceDir = NW;
		if (bounceDir == SE)
			bounceDir = SW;

		break;
	}

	case LEFT:
	{
		if (bounceDir == NW)
			bounceDir = NE;
		if (bounceDir == SW)
			bounceDir = SE;

		break;
	}

	case NONE:
		break;
	}

}

void Anims::SetBounceDir()
{
	srand(time(0));

	int temp = rand() % 4;
	bounceDir = static_cast<ANIM_DIR>(temp);

}
