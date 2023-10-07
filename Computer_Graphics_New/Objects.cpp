#include "pch.h"
#include "Objects.h"
#include <cmath>

Objects::Objects(OBJ_SHAPE shape, Coord pos, float size) : shape(shape), size(size)
{
	CreateObject(this->shape, pos, size);
	MakeHitbox();
}

Objects::~Objects()
{
}

void Objects::CreateObject(OBJ_SHAPE shape, Coord pos, float size)
{
	// 정점 데이터를 쉐입에 따라서 다르게 넣는다.
	switch (shape)
	{
	case OBJ_POINT:
	{
		float vertex[] = { pos.x, pos.y, 0.0 };
		GLfloat color[] = { 0.0f, 0.0f, 1.0f };
		vertexBuf = vertex;
		colorBuf = color;
		break;
	}

	case OBJ_LINE:
	{
		float randf1 = 1 - static_cast<float>(rand()) / (RAND_MAX / 2);
		float randf2 = 1 - static_cast<float>(rand()) / (RAND_MAX / 2);
		GLfloat vertex[] = {
			pos.x, pos.y, 0.0,
			pos.x + randf1, pos.y + randf2, 0.0
		};
		GLfloat color[] = {
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};
		vertexBuf = vertex;
		colorBuf = color;
		break;
	}

	case OBJ_TRIANGLE:
	{
		GLfloat vertex[] = {
			pos.x, pos.y + (size * 2), 0.0f,
			pos.x - size, pos.y - size, 0.0f,
			pos.x + size, pos.y - size, 0.0f
		};
		GLfloat color[] = {
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
		};
		vertexBuf = vertex;
		colorBuf = color;
		break;
	}

	case OBJ_RECTANGLE:
	{
		float vertex[] = {
			pos.x - 0.2, pos.y + 0.2, 0.0f,
			pos.x + 0.2, pos.y + 0.2, 0.0f,
			pos.x - 0.2, pos.y - 0.2, 0.0f,
			pos.x + 0.2, pos.y - 0.2, 0.0f
		};
		float color[] =
		{
			1.0, 1.0, 0.0,
			1.0, 1.0, 0.0,
			1.0, 1.0, 0.0,
			1.0, 1.0, 0.0
		};
		unsigned int index[] = {
			0, 2, 1,
			1, 2, 3

		};
		vertexBuf = vertex;
		colorBuf = color;
		elementBuf = index;
		break;
	}

	case OBJ_PENTAGON:
	{
		float vertex[] = {
			pos.x,					pos.y + (size * 1.8f),	0.0f,
			pos.x - (size * 1.5f),	pos.y + (size / 1.5f),	0.0f,
			pos.x + (size * 1.5f),	pos.y + (size / 1.5f),	0.0f,
			pos.x - size,			pos.y - size,			0.0f,
			pos.x + size,			pos.y - size,			0.0f
		};
		float color[] = {
			0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f
		};
		unsigned int index[] = {
			0, 1, 2,
			1, 3, 2,
			2, 3, 4
		};
		vertexBuf = vertex;
		colorBuf = color;
		elementBuf = index;
		break;
	}

	}

	StoreBufferData();
	MakeHitbox();

}

void Objects::SetRGB(RGB rgb)
{
	int vertexCount;
	switch (shape)
	{
	case OBJ_POINT:
		vertexCount = 3;
		break;
	case OBJ_LINE:
		vertexCount = 6;
		break;
	case OBJ_TRIANGLE:
		vertexCount = 9;
		break;
	case OBJ_RECTANGLE:
		vertexCount = 12;
		break;
	}

	for (int i = 0; i < vertexCount; i++)
	{
		if (i % 3 == 0)
			colorBuf[i] = rgb.Red;
		else if (i % 3 == 1)
			colorBuf[i] = rgb.Green;
		else if (i % 3 == 2)
			colorBuf[i] = rgb.Blue;
	}


}

void Objects::SetVertexPos(Coord pos, float size)
{
	switch (shape)
	{
	case OBJ_POINT:
	{
		float vertex[] = { pos.x, pos.y, 0.0f };
		vertexBuf = vertex;
		break;
	}

	case OBJ_LINE:
	{
		float vertex[] = {
			pos.x, pos.y, 0.0f,
			pos.x + size, pos.y + size, 0.0f
		};
		vertexBuf = vertex;
		break;
	}

	case OBJ_TRIANGLE:
	{
		float vertex[] = {
			pos.x, pos.y + (size * 2), 0.0f,
			pos.x - size, pos.y - size, 0.0f,
			pos.x + size, pos.y - size, 0.0f
		};
		vertexBuf = vertex;
		break;
	}

	case OBJ_RECTANGLE:
	{
		float vertex[] = {
			pos.x - size, pos.y + size, 0.0f,
			pos.x + size, pos.y + size, 0.0f,
			pos.x - size, pos.y - size, 0.0f,
			pos.x + size, pos.y - size, 0.0f
		};
		vertexBuf = vertex;
		break;
	}
	}

	StoreBufferData();
	MakeHitbox();

}

void Objects::MoveVertex(float dx, float dy)
{
	int vertexCount = GetVertexCount();

	for (int i = 0; i < vertexCount; i++)
	{
		// x좌표 -> 0, 3, 6
		if (i % 3 == 0)
		{
			vertexBuf[i] += dx;
		}
		// y좌표 -> 1, 4, 7
		else if (i % 3 == 1)
		{
			vertexBuf[i] += dy;
		}
		// z좌표 -> 2, 5, 8 : 현재 안쓰므로 스킵
		else if (i % 3 == 2)
		{
			continue;
		}
	}

	MakeHitbox();

}

void Objects::MoveObject(Dir d, float distance)
{
	int vertexCount = GetVertexCount();


	switch (d)
	{
	case UP:
		for (int i = 1; i < vertexCount; i += 3)
		{
			vertexBuf[i] += distance;
		}
		break;

	case DOWN:
		for (int i = 1; i < vertexCount; i += 3)
		{
			vertexBuf[i] -= distance;
		}
		break;

	case LEFT:
		for (int i = 0; i < vertexCount; i += 3)
		{
			vertexBuf[i] -= distance;
		}
		break;

	case RIGHT:
		for (int i = 0; i < vertexCount; i += 3)
		{
			vertexBuf[i] += distance;
		}
		break;

	}

	MakeHitbox();

}

void Objects::RenderObject()
{
	InitBuffer();

	glBindVertexArray(vao);
	switch (shape)
	{
	case OBJ_POINT:
		glPointSize(5.0);
		glDrawArrays(GL_POINTS, 0, 1);
		break;

	case OBJ_LINE:
		glLineWidth(3.0);
		glDrawArrays(GL_LINES, 0, 2);
		break;

	case OBJ_TRIANGLE:
		glDrawArrays(GL_TRIANGLES, 0, 3);
		break;

	case OBJ_RECTANGLE:
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		break;

	case OBJ_PENTAGON:
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		break;
	}

}

void Objects::InitBuffer()
{
	if(!vao)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(2, vbo);
	}

	glBindVertexArray(vao);

	// 정점 데이터를 쉐입에 따라서 다르게 넣는다.
	switch (shape)
	{
	case OBJ_POINT:
	{
		// vbo[0]에 정점 데이터 복사
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), vertexBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		// vbo[1]에 색상 데이터 복사
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),	0);
		glEnableVertexAttribArray(1);
		break;
	}
	case OBJ_LINE:
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertexBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		break;
	}
	case OBJ_TRIANGLE:
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertexBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		break;
	}
	case OBJ_RECTANGLE:
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertexBuf, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), elementBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}
	case OBJ_PENTAGON:
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), vertexBuf, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(GLuint), elementBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}
	}
}

void Objects::MakeHitbox()
{
	int vertexCount = GetVertexCount();

	switch (shape)
	{
	case OBJ_POINT:
	{
		hBox.p1 = { vertexBuf[0] - 0.02f, vertexBuf[1] + 0.02f };
		hBox.p4 = { vertexBuf[0] + 0.02f, vertexBuf[1] - 0.02f };

		hBox.p2 = { hBox.p4.x, hBox.p1.y };
		hBox.p3 = { hBox.p1.x, hBox.p4.y };

		break;
	}

	case OBJ_LINE:
	case OBJ_TRIANGLE:
	case OBJ_RECTANGLE:
	case OBJ_PENTAGON:
	{
		Coord min = { 1.0f, 1.0f };
		Coord max = { -1.0f, -1.0f };

		for (int i = 0; i < vertexCount; i++)
		{
			if (i % 3 == 0)
			{
				if (vertexBuf[i] > max.x)
					max.x = vertexBuf[i];
				if (vertexBuf[i] < min.x)
					min.x = vertexBuf[i];
			}
			if (i % 3 == 1)
			{
				if (vertexBuf[i] > max.y)
					max.y = vertexBuf[i];
				if (vertexBuf[i] < min.y)
					min.y = vertexBuf[i];
			}
			if (i % 3 == 2)
				continue;
		}

		hBox.p1 = { min.x, max.y };
		hBox.p2 = { max.x, max.y };
		hBox.p3 = { min.x, min.y };
		hBox.p4 = { max.x, min.y };

		break;
	}
	}

}

void Objects::StoreBufferData()
{
	int count = GetVertexCount();

	for (int i = 0; i < count; i++)
	{
		vertexStore[i] = vertexBuf[i];
		colorStore[i] = colorBuf[i];
	}

	vertexBuf = vertexStore;
	colorBuf = colorStore;

	if (shape == OBJ_RECTANGLE)
	{
		for(int i = 0; i < 6; i++)
			elementStore[i] = elementBuf[i];

		elementBuf = elementStore;
	}
	else if (shape == OBJ_PENTAGON)
	{
		for (int i = 0; i < 9; i++)
			elementStore[i] = elementBuf[i];

		elementBuf = elementStore;
	}

	
}

void Objects::LoadBufferData()
{
	int count = GetVertexCount();

	for (int i = 0; i < count; i++)
	{
		vertexBuf[i] = vertexStore[i];
		colorBuf[i] = colorStore[i];
		if (shape == OBJ_RECTANGLE)
		{
			elementBuf[i] = elementStore[i];
		}
	}
}

Dir Objects::CheckOutOfScreen()
{
	int count = GetVertexCount();


	for (int i = 0; i < count; i++)
	{
		// 필요없는 z좌표는 스킵
		if (i % 3 == 2)
		{
			continue;
		}
		else if (i % 3 == 0)
		{
			if (vertexBuf[i] > 1.0f)
				return RIGHT;
			else if (vertexBuf[i] < -1.0f)
				return LEFT;
		}
		else if (i % 3 == 1)
		{
			if (vertexBuf[i] > 1.0f)
				return	UP;
			else if (vertexBuf[i] < -1.0f)
				return DOWN;
		}
	}

	return NONE;
	

}

Coord Objects::GetOutOfScreenVertex()
{
	if (CheckOutOfScreen() == NONE)
		return{ -1.0f, -1.0f };

	int count;
	switch (shape)
	{
	case OBJ_POINT:
		count = 3;
		break;

	case OBJ_LINE:
		count = 6;
		break;

	case OBJ_TRIANGLE:
		count = 9;
		break;

	case OBJ_RECTANGLE:
		count = 12;
		break;
	}

	int index;
	for (index = 0; index < count; index++)
	{
		// 필요없는 z좌표는 스킵
		if (vertexBuf[index] <= -1.0 || vertexBuf[index] >= 1.0)
			break;
	}

	Coord pos;
	if (index % 3 == 0)
	{
		pos = { vertexBuf[index], vertexBuf[index + 1] };
	}
	else if (index % 3 == 1)
	{
		pos = { vertexBuf[index - 1], vertexBuf[index] };
	}

	return pos;
}

bool Objects::ChangeTriangleDirection(Dir dir)
{
	if (dir == NONE)
		return false;

	Coord standard = GetOutOfScreenVertex();
	Coord pos1, pos2, pos3;

	switch (dir)
	{
	case UP:
	{
		if (standard.x + size >= 1.0f)
		{
			pos1 = { 1.0f, 1.0f };
			pos2 = { 1.0f - (size * 2), 1.0f };
			pos3 = { 1.0f - (size), 1.0f - sqrt(static_cast<float>(pow(size, 2)) * 2) - (size * 2) };
		}
		else if (standard.x - size <= -1.0f)
		{
			pos1 = { -1.0f, 1.0f };
			pos2 = { -1.0f + (size * 2), 1.0f };
			pos3 = { -1.0f + (size), 1.0f - sqrt(static_cast<float>(pow(size, 2)) * 2) - (size * 2) };
		}
		else
		{
			pos1 = { standard.x - size, 1.0f };
			pos2 = { standard.x + size, 1.0f };
			pos3 = { standard.x, 1.0f - sqrt(static_cast<float>(pow(size, 2)) * 2) - (size * 2) };
		}
		
		break;
	}

	case DOWN:
	{
		if (standard.x + size >= 1.0f)
		{
			pos1 = { 1.0f, -1.0f };
			pos2 = { 1.0f - (size * 2), -1.0f };
			pos3 = { 1.0f - (size), -1.0f + sqrt(static_cast<float>(pow(size, 2)) * 2) + (size * 2) };
		}
		else if (standard.x - size <= -1.0f)
		{
			pos1 = { -1.0f, -1.0f };
			pos2 = { -1.0f + (size * 2), -1.0f };
			pos3 = { -1.0f + (size), -1.0f + sqrt(static_cast<float>(pow(size, 2)) * 2) + (size * 2) };
		}
		else
		{
			pos1 = { standard.x - size, -1.0f };
			pos2 = { standard.x + size, -1.0f };
			pos3 = { standard.x, -1.0f + sqrt(static_cast<float>(pow(size, 2)) * 2) + (size * 2) };
		}

		break;
	}

	case RIGHT:
	{
		if (standard.y + size >= 1.0f)
		{
			pos1 = { 1.0f, 1.0f };
			pos2 = { 1.0f, 1.0f - (size * 2) };
			pos3 = { 1.0f - sqrt(static_cast<float>(pow(size, 2)) * 2) - (size * 2), 1.0f - (size) };
		}
		else if (standard.y - size <= -1.0f)
		{
			pos1 = { 1.0f, -1.0f };
			pos2 = { 1.0f, -1.0f + (size * 2) };
			pos3 = { 1.0f - sqrt(static_cast<float>(pow(size, 2)) * 2) - (size * 2), -1.0f - (size) };
		}
		else
		{
			pos1 = { 1.0f, standard.y + size };
			pos2 = { 1.0f, standard.y - size };
			pos3 = { 1.0f - sqrt(static_cast<float>(pow(size, 2)) * 2) - (size * 2), standard.y };
		}

		break;
	}

	case LEFT:
	{
		if (standard.y + size >= 1.0f)
		{
			pos1 = { -1.0f, 1.0f };
			pos2 = { -1.0f, 1.0f - (size * 2) };
			pos3 = { -1.0f + sqrt(static_cast<float>(pow(size, 2)) * 2) + (size * 2), 1.0f - (size) };
		}
		else if (standard.y - size <= -1.0f)
		{
			pos1 = { -1.0f, -1.0f };
			pos2 = { -1.0f, -1.0f + (size * 2) };
			pos3 = { -1.0f + sqrt(static_cast<float>(pow(size, 2)) * 2) + (size * 2), -1.0f + (size) };
		}
		else
		{
			pos1 = { -1.0f, standard.y + size };
			pos2 = { -1.0f, standard.y - size };
			pos3 = { -1.0f + sqrt(static_cast<float>(pow(size, 2)) * 2) + (size * 2), standard.y };
		}

		break;
	}

	}
	
	vertexBuf[0] = pos1.x;
	vertexBuf[1] = pos1.y;

	vertexBuf[3] = pos2.x;
	vertexBuf[4] = pos2.y;

	vertexBuf[6] = pos3.x;
	vertexBuf[7] = pos3.y;
	
	MakeHitbox();

	return true;
}

bool Objects::CheckClicked(Coord pos)
{

	if ((pos.x >= hBox.p1.x && pos.x <= hBox.p4.x) && (pos.y <= hBox.p1.y && pos.y >= hBox.p4.y))
		return true;
	else
		return false;

}

bool Objects::GetCollision(Objects* obj)
{
	HITBOX h1 = GetHitbox();
	HITBOX h2 = obj->GetHitbox();

	if ((h1.p1.x >= h2.p1.x && h1.p1.x <= h2.p2.x && h1.p1.y <= h2.p1.y && h1.p1.y >= h2.p4.y)
		|| (h1.p2.x >= h2.p1.x && h1.p2.x <= h2.p2.x && h1.p2.y <= h2.p1.y && h1.p2.y >= h2.p4.y)
		|| (h1.p3.x >= h2.p1.x && h1.p3.x <= h2.p2.x && h1.p3.y <= h2.p1.y && h1.p3.y >= h2.p4.y)
		|| (h1.p4.x >= h2.p1.x && h1.p4.x <= h2.p2.x && h1.p4.y <= h2.p1.y && h1.p4.y >= h2.p4.y))
	{
		return true;
	}
	else
		return false;


}

int Objects::GetVertexCount()
{
	int count = 0;

	switch (shape)
	{
	case OBJ_POINT:
		count = 3;
		break;

	case OBJ_LINE:
		count = 6;
		break;

	case OBJ_TRIANGLE:
		count = 9;
		break;

	case OBJ_RECTANGLE:
		count = 12;
		break;

	case OBJ_PENTAGON:
		count = 15;
		break;
	}

	return count;
}
