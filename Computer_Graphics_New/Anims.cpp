#include "pch.h"
#include "Anims.h"

Anims::Anims(Objects* obj) : obj(obj)
{
	SetBounce();
	SetZigZag();
	SetRSpiral();
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

		obj->ChangeTriangleDirection(UP);
		break;
	}

	case DOWN:
	{
		if (bounceDir == SW)
			bounceDir = NW;
		else if (bounceDir == SE)
			bounceDir = NE;

		obj->ChangeTriangleDirection(DOWN);
		break;
	}

	case RIGHT:
	{
		if (bounceDir == NE)
			bounceDir = NW;
		if (bounceDir == SE)
			bounceDir = SW;

		obj->ChangeTriangleDirection(RIGHT);
		break;
	}

	case LEFT:
	{
		if (bounceDir == NW)
			bounceDir = NE;
		if (bounceDir == SW)
			bounceDir = SE;

		obj->ChangeTriangleDirection(LEFT);
		break;
	}

	case NONE:
		break;
	}

	
}

void Anims::Zigzag()
{
	if (downCount == 10)
	{
		ZigZagGoDown = false;
		downCount = 0;
		if (ZigZagDir == LEFT)
			ZigZagDir = RIGHT;
		else
			ZigZagDir = LEFT;
	}

	if (ZigZagGoDown == false)
	{
		switch (ZigZagDir)
		{
		case LEFT:
			obj->MoveObject(LEFT, 0.02f);
			break;

		case RIGHT:
			obj->MoveObject(RIGHT, 0.02f);
			break;
		}
	}
	else
	{
		switch (ZigZagDir2)
		{
		case UP:
			obj->MoveObject(UP, 0.02f);
			break;

		case DOWN:
			obj->MoveObject(DOWN, 0.02f);
			break;
		}

		downCount++;

	}

	Dir outDir = obj->CheckOutOfScreen();
	bool isSwitched = false;

	switch (outDir)
	{
	case LEFT:
		isSwitched = obj->ChangeTriangleDirection(LEFT);
		break;

	case RIGHT:
		isSwitched = obj->ChangeTriangleDirection(RIGHT);
	}

	if (isSwitched == true)
	{
		ZigZagGoDown = true;
		downCount = 0;
	}
	
	if (outDir == UP)
	{
		obj->ChangeTriangleDirection(UP);
		ZigZagDir2 = DOWN;
		ZigZagGoDown = false;
		if (ZigZagDir == LEFT)
			ZigZagDir = RIGHT;
		else
			ZigZagDir = LEFT;
	}
	else if(outDir == DOWN)
	{
		obj->ChangeTriangleDirection(DOWN);
		ZigZagDir2 = UP;
		ZigZagGoDown = false;
		if (ZigZagDir == LEFT)
			ZigZagDir = RIGHT;
		else
			ZigZagDir = LEFT;
	}

}

void Anims::RSpiral()
{
	if (switchCount * 3 <= moveCount)
	{
		ChangeRSprialDirection();

		moveCount = 0;
		switchCount++;
	}

	switch (RSP_dir)
	{
	case UP:
		obj->MoveObject(UP, 0.02f);
		break;

	case DOWN:
		obj->MoveObject(DOWN, 0.02f);
		break;

	case LEFT:
		obj->MoveObject(LEFT, 0.02f);
		break;

	case RIGHT:
		obj->MoveObject(RIGHT, 0.02f);
		break;
	}
	moveCount++;


	Dir isOut = obj->CheckOutOfScreen();
	switch (isOut)
	{
	case UP:
	{
		obj->ChangeTriangleDirection(UP);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case DOWN:
	{
		obj->ChangeTriangleDirection(DOWN);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case RIGHT:
	{
		obj->ChangeTriangleDirection(RIGHT);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case LEFT:
	{
		obj->ChangeTriangleDirection(LEFT);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case NONE:
		break;
	}


}


//////////////// 이하 애니메이션 셋업 함수 ////////////////

void Anims::SetBounce()
{
	srand(time(0));

	int temp = rand() % 4;
	bounceDir = static_cast<ANIM_DIR>(temp);

}

void Anims::SetZigZag()
{
	srand(time(0));
	int temp = rand() % 2;
	if (temp == 0)
		ZigZagDir = LEFT;
	else
		ZigZagDir = RIGHT;

	ZigZagDir2 = DOWN;
	ZigZagGoDown = false;
	downCount = 0;
}

void Anims::SetRSpiral()
{
	srand(time(0));
	int temp = rand() % 4;
	RSP_dir = static_cast<Dir>(temp);
	switchCount = 1;
	moveCount = 0;
}

void Anims::ChangeRSprialDirection()
{
	switch (RSP_dir)
	{
	case UP:
		RSP_dir = RIGHT;
		break;

	case RIGHT:
		RSP_dir = DOWN;
		break;

	case DOWN:
		RSP_dir = LEFT;
		break;

	case LEFT:
		RSP_dir = UP;
		break;
	}
}
