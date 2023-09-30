#include "pch.h"
#include "Objects.h"

Objects::Objects(OBJ_SHAPE s, Coord pos) : shape(s)
{
	CreateObject(shape, pos);
}

void Objects::CreateObject(OBJ_SHAPE shape, Coord pos)
{
	// 정점 데이터를 쉐입에 따라서 다르게 넣는다.
	switch (shape)
	{
	case OBJ_POINT:
	{
		GLfloat vertex[] = { pos.x, pos.y, 0.0 };
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
			pos.x, pos.y + 0.2, 0.0f,
			pos.x - 0.1, pos.y - 0.1, 0.0f,
			pos.x + 0.1, pos.y - 0.1, 0.0f
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

	InitBuffer();

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

void Objects::renderObject(unsigned int ShaderID)
{

	glUseProgram(ShaderID);

	glBindVertexArray(vao);
	switch (shape)
	{
	case OBJ_POINT:
		glPointSize(5.0);
		glDrawArrays(GL_POINTS, 0, 1);
		break;

	case OBJ_LINE:
		glDrawArrays(GL_LINE, 0, 2);
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

	glGenBuffers(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);


	// 정점 데이터를 쉐입에 따라서 다르게 넣는다.
	switch (shape)
	{
	case OBJ_POINT:
	{
		// vboPosition에 정점 데이터 복사
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), vertexBuf, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		// vboColor에 색상 데이터 복사
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), colorBuf, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),	0);
		glEnableVertexAttribArray(1);
		break;
	}
	case OBJ_LINE:
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertexBuf, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), colorBuf, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		break;
	}
	case OBJ_TRIANGLE:
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertexBuf, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colorBuf, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		break;
	}
	case OBJ_RECTANGLE:
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertexBuf, GL_STATIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(GLuint), elementBuf, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colorBuf, GL_STATIC_DRAW);
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

	vertexStore.clear();
	colorStore.clear();
	elementStore.clear();


	for (int i = 0; i < count; i++)
	{
		vertexStore.push_back(vertexBuf[i]);
		colorStore.push_back(colorBuf[i]);
		if (shape == OBJ_RECTANGLE)
		{
			elementStore.push_back(elementBuf[i]);
		}
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
		vertexBuf[i] = vertexStore.at(i);
		colorBuf[i] = colorStore.at(i);
		if (shape == OBJ_RECTANGLE)
		{
			elementBuf[i] = elementStore.at(i);
		}
	}
}
