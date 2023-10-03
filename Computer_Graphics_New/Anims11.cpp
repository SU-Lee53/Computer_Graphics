#include "pch.h"
#include "Anims11.h"

Anims11::Anims11(Coord pos, float _size, TF_TYPE _type, float _speed) : center(pos), size(_size), type(_type), speed(_speed)
{
	vertexBuf = vertex;
	colorBuf = color;
	elementBuf = element;

	SetAnim();
}

void Anims11::PlayAnim()
{
	switch (type)
	{
	case L2T:
		Line2Tri();
		break;

	case T2R:
		Tri2Rect();
		break;

	case R2P:
		Rect2Pent();
		break;

	case P2P:
		Pent2Point();
		break;
	}
}

void Anims11::SetAnim()
{
	isEnd = false;

	switch (type)
	{
	case L2T:
		SetLine2Tri();
		break;

	case T2R:
		SetTri2Rect();
		break;

	case R2P:
		SetRect2Pent();
		break;

	case P2P:
		SetPent2Point();
		break;
	}

	
}

void Anims11::Line2Tri()
{
	if (isEnd == true)
		return;

	vertex[4] += speed * 2;
	if (vertex[4] >= center.y + size)
		isEnd = true;

	InitBuffer();
	
}

void Anims11::Tri2Rect()
{
	if (isEnd == true)
		return;

	vertex[0] -= speed;
	vertex[3] += speed;
	if (vertex[0] <= center.x - (size))
		isEnd = true;

	InitBuffer();
}

void Anims11::Rect2Pent()
{
	if (isEnd == true)
		return;

	vertex[1] += speed * 1.8f;

	vertex[3] -= speed * 1.5f;
	vertex[4] -= speed / 1.5f;
	
	vertex[6] += speed * 1.5f;
	vertex[7] -= speed / 1.5f;


	if (vertex[1] >= center.y + (size * 1.8))
		isEnd = true;

	InitBuffer();
}

void Anims11::Pent2Point()
{
	if (isEnd == true)
		return;

	vertex[1] -= speed * 1.8f;

	vertex[3] += speed * 1.5f;
	vertex[4] -= speed / 1.5f;

	vertex[6] -= speed * 1.5f;
	vertex[7] -= speed / 1.5f;

	vertex[9] += speed;
	vertex[10] += speed;

	vertex[12] -= speed;
	vertex[13] += speed;

	if (vertex[6] - vertex[3] <= 0.01f)
		isEnd = true;

	InitBuffer();
}

void Anims11::SetLine2Tri()
{
	// 좌하단
	vertex[0] = center.x - (size * 1.5);
	vertex[1] = center.y - size;
	vertex[2] = 0.0f;
	// 중심
	vertex[3] = center.x;
	vertex[4] = center.y - size;
	vertex[5] = 0.0f;

	// 우하단
	vertex[6] = center.x + (size * 1.5);
	vertex[7] = center.y - size;
	vertex[8] = 0.0f;

	for (int i = 0; i < 9; i++)
	{
		if (i % 3 == 0)
			color[i] = 0.0f;
		else if (i % 3 == 1)
			color[i] = 0.0f;
		else if (i % 3 == 2)
			color[i] = 1.0f;
	}

	element[0] = 0;
	element[1] = 1;
	element[2] = 2;

	InitBuffer();
}

void Anims11::SetTri2Rect()
{
	// 좌상단
	vertex[0] = center.x;
	vertex[1] = center.y + size;
	vertex[2] = 0.0f;

	// 우상단
	vertex[3] = center.x;
	vertex[4] = center.y + size;
	vertex[5] = 0.0f;

	// 좌하단
	vertex[6] = center.x - (size);
	vertex[7] = center.y - size;
	vertex[8] = 0.0f;

	// 우하단
	vertex[9] = center.x + (size);
	vertex[10] = center.y - size;
	vertex[11] = 0.0f;

	for (int i = 0; i < 12; i++)
	{
		if (i % 3 == 0)
			color[i] = 1.0f;
		else if (i % 3 == 1)
			color[i] = 1.0f;
		else if (i % 3 == 2)
			color[i] = 0.0f;
	}

	element[0] = 0;
	element[1] = 2;
	element[2] = 1;
	element[3] = 1;
	element[4] = 2;
	element[5] = 3;

	InitBuffer();
}

void Anims11::SetRect2Pent()
{
	// 최상단
	vertex[0] = center.x;
	vertex[1] = center.y + size;
	vertex[2] = 0.0f;

	// 좌상단
	vertex[3] = center.x - size;
	vertex[4] = center.y + size;
	vertex[5] = 0.0f;

	// 우상단
	vertex[6] = center.x + size;
	vertex[7] = center.y + size;
	vertex[8] = 0.0f;

	// 좌하단
	vertex[9] = center.x - size;
	vertex[10] = center.y - size;
	vertex[11] = 0.0f;

	// 우하단
	vertex[12] = center.x + size;
	vertex[13] = center.y - size;
	vertex[14] = 0.0f;

	for (int i = 0; i < 15; i++)
	{
		if (i % 3 == 0)
			color[i] = 0.0f;
		else if (i % 3 == 1)
			color[i] = 1.0f;
		else if (i % 3 == 2)
			color[i] = 0.0f;
	}

	element[0] = 0;
	element[1] = 1;
	element[2] = 2;
	element[3] = 1;
	element[4] = 3;
	element[5] = 2;
	element[6] = 2;
	element[7] = 3;
	element[8] = 4;

	InitBuffer();
}

void Anims11::SetPent2Point()
{
	// 최상단
	vertex[0] = center.x;
	vertex[1] = center.y + (size * 1.8);
	vertex[2] = 0.0f;

	// 좌상단
	vertex[3] = center.x - (size * 1.5);
	vertex[4] = center.y + (size / 1.5);
	vertex[5] = 0.0f;

	// 우상단
	vertex[6] = center.x + (size * 1.5);
	vertex[7] = center.y + (size / 1.5);
	vertex[8] = 0.0f;

	// 좌하단
	vertex[9] = center.x - size;
	vertex[10] = center.y - size;
	vertex[11] = 0.0f;

	// 우하단
	vertex[12] = center.x + size;
	vertex[13] = center.y - size;
	vertex[14] = 0.0f;

	for (int i = 0; i < 15; i++)
	{
		if (i % 3 == 0)
			color[i] = 1.0f;
		else if (i % 3 == 1)
			color[i] = 0.0f;
		else if (i % 3 == 2)
			color[i] = 0.0f;
	}

	element[0] = 0;
	element[1] = 1;
	element[2] = 2;
	element[3] = 1;
	element[4] = 3;
	element[5] = 2;
	element[6] = 2;
	element[7] = 3;
	element[8] = 4;

	InitBuffer();

}

void Anims11::InitBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(3, vbo);

	switch (type)
	{
	case L2T:
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexBuf, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), elementBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		break;

	case T2R:
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertexBuf, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), elementBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		break;

	case R2P:
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), vertexBuf, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(GLuint), elementBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		break;

	case P2P:
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), vertexBuf, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(GLuint), elementBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		break;
	}
}

void Anims11::Render()
{
	glBindVertexArray(vao);
	switch (type)
	{
	case L2T:
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		break;

	case T2R:
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		break;

	case R2P:
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		break;

	case P2P:
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		break;
	}
}
