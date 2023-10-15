#pragma once

enum OBJ_TYPE_2D
{
	OBJ_POINT = 0,
	OBJ_LINE,
	OBJ_TRIANGLE,
	OBJ_RECTANGLE,
	OBJ_PENTAGON,
};

enum OBJ_TYPE_3D
{
	OBJ_TETRAHEDRON = 0,
	OBJ_CUBE,
	OBJ_CONE
};

enum QOBJ_TYPE	// Quadric Objects
{
	QOBJ_SPHERE = 0,
	QOBJ_CYLINDER,
	QOBJ_DISK
};

enum AXIS
{
	X_AXIS = 0,
	Y_AXIS,
	Z_AXIS
};

class Objects
{
public:
	// 2D���� ������
	Objects(OBJ_TYPE_2D type, Coord pos, float size);
	Objects(OBJ_TYPE_3D type, Coord pos, float size);
	~Objects();

private:
	void CreateObject2D(OBJ_TYPE_2D type);
	void CreateObject3D(OBJ_TYPE_3D type);
	void CreateQuadricObject(QOBJ_TYPE type) {}

public:
	// ��ƿ�Լ�
	VAO& GetVAO() { return *_vao; }

	// ������
	void Render();

private:
	VAO* _vao;
	Coord _centerPos;
	float _size;


	bool indexed = false;
};

