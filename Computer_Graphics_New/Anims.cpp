#include "pch.h"
#include "Anims.h"
#include <cmath>

Anims::Anims(Objects* obj) : obj(obj)
{
	SetBounce();
	SetZigZag();
	SetRSpiral();
}

Anims::Anims(Coord _pos)
{
	this->pos = _pos;
	SetSpiral();
}

Anims::~Anims()
{
}

void Anims::Bounce()
{
	switch (bounceDir)
	{
	case NW:
		obj->MoveObject(DIR_UP, 0.01f);
		obj->MoveObject(DIR_LEFT, 0.01f);
		break;
	case NE:
		obj->MoveObject(DIR_UP, 0.01f);
		obj->MoveObject(DIR_RIGHT, 0.01f);
		break;
	case SE:
		obj->MoveObject(DIR_DOWN, 0.01f);
		obj->MoveObject(DIR_RIGHT, 0.01f);
		break;
	case SW:
		obj->MoveObject(DIR_DOWN, 0.01f);
		obj->MoveObject(DIR_LEFT, 0.01f);
		break;

	}

	Dir isOut = obj->CheckOutOfScreen();

	switch (isOut)
	{
	case DIR_UP:
	{
		if (bounceDir == NW)
			bounceDir = SW;
		else if (bounceDir == NE)
			bounceDir = SE;

		// obj->ChangeTriangleDirection(UP);
		break;
	}

	case DIR_DOWN:
	{
		if (bounceDir == SW)
			bounceDir = NW;
		else if (bounceDir == SE)
			bounceDir = NE;

		// obj->ChangeTriangleDirection(DOWN);
		break;
	}

	case DIR_RIGHT:
	{
		if (bounceDir == NE)
			bounceDir = NW;
		if (bounceDir == SE)
			bounceDir = SW;

		// obj->ChangeTriangleDirection(RIGHT);
		break;
	}

	case DIR_LEFT:
	{
		if (bounceDir == NW)
			bounceDir = NE;
		if (bounceDir == SW)
			bounceDir = SE;

		// obj->ChangeTriangleDirection(LEFT);
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
		if (ZigZagDir == DIR_LEFT)
			ZigZagDir = DIR_RIGHT;
		else
			ZigZagDir = DIR_LEFT;
	}

	if (ZigZagGoDown == false)
	{
		switch (ZigZagDir)
		{
		case DIR_LEFT:
			obj->MoveObject(DIR_LEFT, 0.02f);
			break;

		case DIR_RIGHT:
			obj->MoveObject(DIR_RIGHT, 0.02f);
			break;
		}
	}
	else
	{
		switch (ZigZagDir2)
		{
		case DIR_UP:
			obj->MoveObject(DIR_UP, 0.02f);
			break;

		case DIR_DOWN:
			obj->MoveObject(DIR_DOWN, 0.02f);
			break;
		}

		downCount++;

	}

	Dir outDir = obj->CheckOutOfScreen();
	bool isSwitched = false;

	switch (outDir)
	{
	case DIR_LEFT:
		isSwitched = obj->ChangeTriangleDirection(DIR_LEFT);
		break;

	case DIR_RIGHT:
		isSwitched = obj->ChangeTriangleDirection(DIR_RIGHT);
	}

	if (isSwitched == true)
	{
		ZigZagGoDown = true;
		downCount = 0;
	}
	
	if (outDir == DIR_UP)
	{
		obj->ChangeTriangleDirection(DIR_UP);
		ZigZagDir2 = DIR_DOWN;
		ZigZagGoDown = false;
		if (ZigZagDir == DIR_LEFT)
			ZigZagDir = DIR_RIGHT;
		else
			ZigZagDir = DIR_LEFT;
	}
	else if(outDir == DIR_DOWN)
	{
		obj->ChangeTriangleDirection(DIR_DOWN);
		ZigZagDir2 = DIR_UP;
		ZigZagGoDown = false;
		if (ZigZagDir == DIR_LEFT)
			ZigZagDir = DIR_RIGHT;
		else
			ZigZagDir = DIR_LEFT;
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
	case DIR_UP:
		obj->MoveObject(DIR_UP, 0.02f);
		break;

	case DIR_DOWN:
		obj->MoveObject(DIR_DOWN, 0.02f);
		break;

	case DIR_LEFT:
		obj->MoveObject(DIR_LEFT, 0.02f);
		break;

	case DIR_RIGHT:
		obj->MoveObject(DIR_RIGHT, 0.02f);
		break;
	}
	moveCount++;


	Dir isOut = obj->CheckOutOfScreen();
	switch (isOut)
	{
	case DIR_UP:
	{
		obj->ChangeTriangleDirection(DIR_UP);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case DIR_DOWN:
	{
		obj->ChangeTriangleDirection(DIR_DOWN);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case DIR_RIGHT:
	{
		obj->ChangeTriangleDirection(DIR_RIGHT);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case DIR_LEFT:
	{
		obj->ChangeTriangleDirection(DIR_LEFT);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case NONE:
		break;
	}


}

void Anims::CSpiral()
{
	obj->MoveVertex(radius * cos(radian) - beforeX, radius * sin(radian) - beforeY);

	beforeX = radius * cos(radian);
	beforeY = radius * sin(radian);

	radius += 0.003;
	radian += 0.1;

	Dir isOut = obj->CheckOutOfScreen();
	switch (isOut)
	{
	case DIR_UP:
	{
		obj->ChangeTriangleDirection(DIR_UP);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case DIR_DOWN:
	{
		obj->ChangeTriangleDirection(DIR_DOWN);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case DIR_RIGHT:
	{
		obj->ChangeTriangleDirection(DIR_RIGHT);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case DIR_LEFT:
	{
		obj->ChangeTriangleDirection(DIR_LEFT);
		ChangeRSprialDirection();
		moveCount = 0;
		switchCount++;
		break;
	}

	case NONE:
		break;
	}

}


//////////////// 이하 애니메이션 셋업, 유틸 함수 ////////////////

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
		ZigZagDir = DIR_LEFT;
	else
		ZigZagDir = DIR_RIGHT;

	ZigZagDir2 = DIR_DOWN;
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

void Anims::SetCSpiral()
{
	radian = 0;
	radius = 0;
	beforeX = 0;
	beforeY = 0;
}

void Anims::ChangeRSprialDirection()
{
	switch (RSP_dir)
	{
	case DIR_UP:
		RSP_dir = DIR_RIGHT;
		break;

	case DIR_RIGHT:
		RSP_dir = DIR_DOWN;
		break;

	case DIR_DOWN:
		RSP_dir = DIR_LEFT;
		break;

	case DIR_LEFT:
		RSP_dir = DIR_UP;
		break;
	}
}

void Anims::SymSpiral()
{
	if (isEnd == true)
		return;

	if(spiralDirection == true) {
		if (SpiralSwitch == true) {
			if (radian < 5.5 * L_pi)
			{
				spiralBuf[bufIndex] = pos.x + radius * cos(radian) - beforeX;
				spiralBuf[bufIndex + 1] = pos.y + radius * sin(radian) - beforeY;
				spiralBuf[bufIndex + 2] = 0.0f;

				colorBuf[bufIndex] = 1.0f;
				colorBuf[bufIndex + 1] = 1.0f;
				colorBuf[bufIndex + 2] = 1.0f;

				beforeX = radius * cos(radian);
				beforeY = radius * sin(radian);

				radius += 0.015;
				radian += 0.07;
			}
			else
			{
				spiralBuf[bufIndex] = pos.x + radius * cos(radian) - beforeX;
				spiralBuf[bufIndex + 1] = pos.y + radius * sin(radian) - beforeY;
				spiralBuf[bufIndex + 2] = 0.0f;

				colorBuf[bufIndex] = 1.0f;
				colorBuf[bufIndex + 1] = 1.0f;
				colorBuf[bufIndex + 2] = 1.0f;

				SpiralSwitch = false;
				float temp = (spiralBuf[bufIndex] - spiralBuf[0]);

				newPos.x = spiralBuf[bufIndex] + temp;
				newPos.y = pos.y;

				beforeX = radius * cos(radian) + temp;
				beforeY = radius * sin(radian);

			}
		}
		else
		{
			if (radian > 0.0f)
			{
				spiralBuf[bufIndex] = newPos.x + radius * cos(radian) - beforeX;
				spiralBuf[bufIndex + 1] = newPos.y + radius * sin(radian) - beforeY;
				spiralBuf[bufIndex + 2] = 0.0f;

				colorBuf[bufIndex] = 1.0f;
				colorBuf[bufIndex + 1] = 1.0f;
				colorBuf[bufIndex + 2] = 1.0f;

				beforeX = radius * cos(radian);
				beforeY = radius * sin(radian);

				radius -= 0.015;
				radian -= 0.07;
			}
			else
			{
				isEnd = true;
			}
		}
	}
	else
	{
		if (SpiralSwitch == true) {
			if (radian > -4.52 * L_pi)
			{
				spiralBuf[bufIndex] = pos.x + radius * cos(radian) - beforeX;
				spiralBuf[bufIndex + 1] = pos.y + radius * sin(radian) - beforeY;
				spiralBuf[bufIndex + 2] = 0.0f;

				colorBuf[bufIndex] = 1.0f;
				colorBuf[bufIndex + 1] = 1.0f;
				colorBuf[bufIndex + 2] = 1.0f;

				beforeX = radius * cos(radian);
				beforeY = radius * sin(radian);

				radius -= 0.015;
				radian -= 0.07;
			}
			else
			{
				spiralBuf[bufIndex] = pos.x + radius * cos(radian) - beforeX;
				spiralBuf[bufIndex + 1] = pos.y + radius * sin(radian) - beforeY;
				spiralBuf[bufIndex + 2] = 0.0f;

				colorBuf[bufIndex] = 1.0f;
				colorBuf[bufIndex + 1] = 1.0f;
				colorBuf[bufIndex + 2] = 1.0f;

				SpiralSwitch = false;
				float temp = (spiralBuf[bufIndex] - spiralBuf[0]);

				newPos.x = spiralBuf[bufIndex] + temp;
				newPos.y = pos.y;

				beforeX = radius * cos(radian) + temp;
				beforeY = radius * sin(radian);

			}
		}
		else
		{
			if (radian < 0.0f)
			{
				spiralBuf[bufIndex] = newPos.x + radius * cos(radian) - beforeX;
				spiralBuf[bufIndex + 1] = newPos.y + radius * sin(radian) - beforeY;
				spiralBuf[bufIndex + 2] = 0.0f;

				colorBuf[bufIndex] = 1.0f;
				colorBuf[bufIndex + 1] = 1.0f;
				colorBuf[bufIndex + 2] = 1.0f;

				beforeX = radius * cos(radian);
				beforeY = radius * sin(radian);

				radius += 0.015;
				radian += 0.07;
			}
			else
			{
				isEnd = true;
			}
		}
	}

	bufIndex += 3;

	InitSpiral();
}

void Anims::InitSpiral()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, bufIndex * sizeof(float), spiralBuf, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, bufIndex  * sizeof(float), colorBuf, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

}

void Anims::SetSpiral()
{
	
	radian = 0;
	radius = 0;
	beforeX = 0;
	beforeY = 0;
	bufIndex = 0;

	spiralBuf = vBuf;
	colorBuf = cBuf;
	isEnd = false;

	if (rand() % 2 == 0)
		spiralDirection = true;
	else
		spiralDirection = false;
}


