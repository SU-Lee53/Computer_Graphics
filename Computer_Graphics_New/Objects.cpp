#include "pch.h"
#include "Objects.h"


Objects::Objects(OBJ_SHAPE shape, Coord pos, float size) : shape(shape)
{
	CreateObject(this->shape, pos, size);
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
		float vertex[] = {pos.x, pos.y, 0.0};
		GLfloat color[] = { 0.0f, 0.0f, 1.0f };
		vertexBuf = vertex;
		colorBuf = color;
		break;
	}
	case OBJ_LINE:
	{
		srand(time(0));
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

	}

	StoreBufferData();
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
}

void Objects::MoveObject(Dir d)
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

	switch (d)
	{
	case UP:
		for (int i = 1; i < vertexCount; i += 3)
		{
			vertexBuf[i] += 0.1f;
		}
		break;

	case DOWN:
		for (int i = 1; i < vertexCount; i += 3)
		{
			vertexBuf[i] -= 0.1f;
		}
		break;

	case LEFT:
		for (int i = 0; i < vertexCount; i += 3)
		{
			vertexBuf[i] -= 0.1f;
		}
		break;

	case RIGHT:
		for (int i = 0; i < vertexCount; i += 3)
		{
			vertexBuf[i] += 0.1f;
		}
		break;

	}

}

void Objects::RenderObject()
{
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
	}

}

void Objects::InitBuffer()
{
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(GLuint), elementBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colorBuf, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}
	}
}

void Objects::StoreBufferData()
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
	}

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

}

void Objects::LoadBufferData()
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
	}

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

void Objects::CheckOutOfScreen()
{
	if (shape != OBJ_TRIANGLE)
		return;

	int index;
	for (index = 0; index < 9; index++)
	{
		if (vertexBuf[index] >= 1.0f || vertexBuf[index] <= 1.0f)
			break;
	}

	

}
