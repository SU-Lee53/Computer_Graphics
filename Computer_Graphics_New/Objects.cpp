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

Objects::Objects(OBJ_TYPE_3D type, Coord pos, float size, VAO_TYPE indexType) : _centerPos(pos), _size(size), _indexType(indexType)
{
	if(_indexType == NON_INDEXED)
		CreateNonIndexedObject3D(type);
	else
		CreateObject3D(type);
}

Objects::Objects(QOBJ_TYPE type, Coord pos, float size) : _qType(type), _centerPos(pos), _size(size)
{
	CreateQuadricObject();
}

Objects::~Objects()
{
	if (isQuadric() == false)
		_vao->~VAO();
}

void Objects::CreateObject2D(OBJ_TYPE_2D type)
{
	switch (type)
	{
	case OBJ_LINE:


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
		_indexType = INDEXED;
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
		float vertex[] = 
		{		// ���ü�� ����: 4*3 = 12, ���� ������ �ϳ� ��� zx��鿡 �ﰢ�� �ϳ� �׷��� ���� �̾��ָ� ��
			_centerPos.x, _centerPos.y + (_size * sqrt(2)), _centerPos.z,	// ���� ������
			_centerPos.x, _centerPos.y - _size, _centerPos.z - (_size * sqrt(2)),
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
		};
		float color[] = 
		{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f
		};
		unsigned int element[] = 
		{
			0, 2, 1,
			0, 3, 2,
			0, 1, 3,
			1, 2, 3
		};
		_vao = new VAO(vertex, color, element, 12, 12);
		_indexType = INDEXED;
		break;
	}
	case OBJ_CUBE:
	{
		float vertex[] = 
		{
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size
		};
		float color[] = 
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f
		};
		unsigned int element[] = 
		{
			0, 2, 1,	// �� 1
			1, 2, 3,
			0, 4, 2,	// �� 2
			2, 4, 6,
			2, 6, 3,	// �� 3
			3, 6, 7,
			1, 3, 5,	// �� 4
			3, 7, 5,
			0, 1, 4,	// �� 5
			1, 5, 4,
			6, 4, 5,	// �� 6
			6, 5, 7
		};
		_vao = new VAO(vertex, color, element, 24, 36);
		_indexType = INDEXED;
		break;
	}

	case OBJ_PYRAMID:
	{
		float vertex[] = 
		{
			_centerPos.x, _centerPos.y + _size, _centerPos.z,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size
		};
		float color[] = 
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f
		};
		unsigned int element[] = 
		{
			0, 2, 1,
			0, 1, 3,
			0, 3, 4,
			0, 4, 2,
			1, 2, 3,
			2, 4, 3
		};
		_vao = new VAO(vertex, color, element, 15, 18);
		_indexType = INDEXED;
		break;
	}

	case OBJ_PLANE_RECT:	// �⺻������ zx������� ����
	{
		float vertex[] =
		{
			_centerPos.x - _size, _centerPos.y, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y, _centerPos.z + _size
		};
		float color[] =
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
		};
		unsigned int element[] =
		{
			0, 2, 1,
			1, 2, 3
		};
		_vao = new VAO(vertex, color, element, 12, 6);
		_indexType = INDEXED;
		break;
	}

	case OBJ_PLANE_TRIANGLE:	// �⺻������ zx������� ����
	{
		float vertex[] = // �� ���� ���̰� 2 * _size�� ���ﰢ��
		{
			_centerPos.x, _centerPos.y, _centerPos.z - _size,	// ���
			_centerPos.x - _size, _centerPos.y, _centerPos.z + _size,	// ���ϴ�
			_centerPos.x + _size, _centerPos.y, _centerPos.z + _size	// ���ϴ�
		};
		float color[] =
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
		};
		_vao = new VAO(vertex, color, 9);
		_indexType = NON_INDEXED;
		break;
	}


	}

}

void Objects::CreateNonIndexedObject3D(OBJ_TYPE_3D type)
{
	switch (type)
	{
	case OBJ_CUBE:
	{
		float vertex[] =
		{
			// _centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,	0
			// _centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,	1
			// _centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,	2
			// _centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,	3
			// _centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,	4
			// _centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,	5
			// _centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,	6
			// _centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size		7

			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,	// ����		0, 2, 1 / 1, 2, 3 
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,

			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,	// ���ʸ�	0, 4, 2 / 2, 4, 6
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,	
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,

			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,	// �ո�		2, 6, 3 / 3, 6, 7
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,

			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,	// �����ʸ�	1, 3, 5 / 5, 3, 7
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,

			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,	// �޸�		0, 1, 4 / 1, 5, 4
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,

			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,	// �Ʒ���	4, 5, 6	/ 5, 7, 6
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size
		};

		glm::vec3 c0 = glm::vec3 (1.0f, 0.0f, 0.0f);
		glm::vec3 c1 = glm::vec3 (0.0f, 1.0f, 0.0f);
		glm::vec3 c2 = glm::vec3 (0.0f, 0.0f, 1.0f);
		glm::vec3 c3 = glm::vec3 (1.0f, 1.0f, 0.0f);

		glm::vec3 c4 = glm::vec3 (0.0f, 1.0f, 1.0f);
		glm::vec3 c5 = glm::vec3 (1.0f, 0.0f, 1.0f);
		glm::vec3 c6 = glm::vec3 (0.0f, 0.0f, 0.0f);
		glm::vec3 c7 = glm::vec3 (1.0f, 1.0f, 1.0f);

		float color[] =
		{
			// 1.0f, 0.0f, 0.0f,	0
			// 0.0f, 1.0f, 0.0f,	1
			// 0.0f, 0.0f, 1.0f,	2
			// 1.0f, 1.0f, 0.0f,	3

			// 0.0f, 1.0f, 1.0f,	4
			// 1.0f, 0.0f, 1.0f,	5
			// 0.0f, 0.0f, 0.0f,	6
			// 1.0f, 1.0f, 1.0f		7

			c0[0], c0[1], c0[2],	// ����		0, 2, 1 / 1, 2, 3 
			c2[0], c2[1], c2[2],
			c1[0], c1[1], c1[2],
			c1[0], c1[1], c1[2],
			c2[0], c2[1], c2[2],
			c3[0], c3[1], c3[2],

			c0[0], c0[1], c0[2],	// ���ʸ�	0, 4, 2 / 2, 4, 6
			c4[0], c4[1], c4[2],
			c2[0], c2[1], c2[2],
			c2[0], c2[1], c2[2],
			c4[0], c4[1], c4[2],
			c6[0], c6[1], c6[2],
			
			c2[0], c2[1], c2[2],	// �ո�		2, 6, 3 / 3, 6, 7
			c6[0], c6[1], c6[2],
			c3[0], c3[1], c3[2],
			c3[0], c3[1], c3[2],
			c6[0], c6[1], c6[2],
			c7[0], c7[1], c7[2],

			c1[0], c1[1], c1[2],	// �����ʸ�	1, 3, 5 / 5, 3, 7
			c3[0], c3[1], c3[2],
			c5[0], c5[1], c5[2],
			c5[0], c5[1], c5[2],
			c3[0], c3[1], c3[2],
			c7[0], c7[1], c7[2],
			
			c0[0], c0[1], c0[2],	// �޸�		0, 1, 4 / 1, 5, 4
			c1[0], c1[1], c1[2],
			c4[0], c4[1], c4[2],
			c1[0], c1[1], c1[2],
			c5[0], c5[1], c5[2],
			c4[0], c4[1], c4[2],

			c4[0], c4[1], c4[2],	// �Ʒ���	4, 5, 6	/ 5, 7, 6
			c5[0], c5[1], c5[2],
			c6[0], c6[1], c6[2],
			c5[0], c5[1], c5[2],
			c7[0], c7[1], c7[2],
			c6[0], c6[1], c6[2],
		};
		_vao = new VAO(vertex, color, 108);
		_indexType = NON_INDEXED;
	}
	}
}

void Objects::CreateQuadricObject()
{
	_qObj = gluNewQuadric();
	gluQuadricDrawStyle(_qObj, GLU_LINE);
}

void Objects::Render()
{
	if (this == nullptr)
		return;

	
	if(_qType == NONE)
	{
		glBindVertexArray(_vao->GetVAOHandle());
		if (_indexType == NON_INDEXED)
		{
			glDrawArrays(GL_TRIANGLES, 0, _vao->GetVertexCount());
		}
		else
		{
			glDrawElements(GL_TRIANGLES, _vao->GetElementCount(), GL_UNSIGNED_INT, 0);
		}
	}
	else
	{
		switch (_qType)
		{
		case QOBJ_SPHERE:
			gluSphere(_qObj, 0.2, 20, 20);
			break;

		case QOBJ_CYLINDER:
			gluCylinder(_qObj, 0.2, 0.2, 0.5, 20, 8);
			break;

		case QOBJ_CONE:
			gluCylinder(_qObj, 0.2, 0.0, 0.5, 20, 8);
			break;

		case QOBJ_DISK:
			gluDisk(_qObj, 0.2, 0.4, 20, 3);
			break;
		}
	}

	glutPostRedisplay();
}


