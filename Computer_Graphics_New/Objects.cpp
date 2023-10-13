#include "pch.h"
#include "Objects.h"
#include <cmath>

Objects::Objects(OBJ_TYPE_2D type, Coord pos, float size) : _centerPos(pos), _size(size)
{
	CreateObject2D(type);
}

Objects::Objects(OBJ_TYPE_3D type, Coord pos, float size) : _centerPos(pos), _size(size)
{
	CreateObject3D(type);
}

Objects::~Objects()
{
}

void Objects::CreateObject2D(OBJ_TYPE_2D type)
{
	switch (type)
	{
	case OBJ_TRIANGLE:
	{
		float vertex[] = {
			_centerPos.x, _centerPos.y + (_size * 2), 0.0f,
			_centerPos.x - _size, _centerPos.y - _size, 0.0f,
			_centerPos.x + _size, _centerPos.y - _size, 0.0f
		};
		float color[] = {
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
		};
		_vao = new VAO(vertex, color, 9);
		indexed = false;
	}
		break;
	}
}

void Objects::CreateObject3D(OBJ_TYPE_3D type)
{
	switch (type)
	{
	case OBJ_TETRAHEDRON:
	{
		float vertex[] = {		// 사면체의 정점: 4*3 = 12, 위에 꼭짓점 하나 찍고 zx평면에 삼각형 하나 그려서 정점 이어주면 됨
			_centerPos.x, _centerPos.y + (_size * sqrt(2)), _centerPos.z,	// 위쪽 꼭짓점
			_centerPos.x, _centerPos.y - _size, _centerPos.z - (_size * sqrt(2)),
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
		};
		float color[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f
		};
		unsigned int element[] = {
			0, 2, 1,
			0, 3, 2,
			0, 1, 3,
			1, 2, 3
		};
		_vao = new VAO(vertex, color, element, 12, 12);
		indexed = true;
		break;
	}
	case OBJ_CUBE:
		float vertex[] = {
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size
		};
		float color[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f
		};
		unsigned int element[] = {
			0, 2, 1,	// 면 1
			1, 2, 3,
			0, 4, 2,	// 면 2
			2, 4, 6,
			2, 6, 3,	// 면 3
			3, 6, 7,
			1, 3, 5,	// 면 4
			3, 7, 5,
			0, 1, 4,	// 면 5
			1, 5, 4,
			6, 4, 5,	// 면 6
			6, 5, 7
		};
		_vao = new VAO(vertex, color, element, 24, 36);
		indexed = true;
		break;

	}

}

void Objects::Render()
{
	glBindVertexArray(_vao->GetVAOHandle());
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);

	if(!indexed)
	{
		glDrawArrays(GL_TRIANGLES, 0, _vao->GetVertexCount());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, _vao->GetElementCount(), GL_UNSIGNED_INT, 0);
	}
	glutPostRedisplay();
}


