#include "pch.h"
#include "Objects.h"

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
		GLfloat vertex[] = {
			_centerPos.x, _centerPos.y + (_size * 2), 0.0f,
			_centerPos.x - _size, _centerPos.y - _size, 0.0f,
			_centerPos.x + _size, _centerPos.y - _size, 0.0f
		};
		GLfloat color[] = {
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
		};
		_vao = new VAO(vertex, color, 9);
		break;
	}
}

void Objects::Render()
{
	int vCount = _vao->GetVertexCount() / 3;

	glBindVertexArray(_vao->GetVAOHandle());
	glDrawArrays(GL_TRIANGLES, 0, vCount);

	glutPostRedisplay();
}


