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
	OBJ_PYRAMID,
};

enum QOBJ_TYPE	// Quadric Objects
{
	QOBJ_SPHERE = 0,
	QOBJ_CYLINDER,
	QOBJ_CONE,
	QOBJ_DISK,
	NONE
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
	// 2D전용 생성자
	Objects(OBJ_TYPE_2D type, Coord pos, float size);
	// 3D전용 생성자
	Objects(OBJ_TYPE_3D type, Coord pos, float size);
	// Quadric Objects 전용 생성자
	Objects(QOBJ_TYPE type, Coord pos, float size);
	~Objects();

private:
	void CreateObject2D(OBJ_TYPE_2D type);
	void CreateObject3D(OBJ_TYPE_3D type);
	void CreateQuadricObject();

public:
	// 유틸함수
	VAO& GetVAO() { return *_vao; }

	// 렌더링
	void Render();
	
private:
	VAO* _vao;
	Coord _centerPos;
	float _size;
	QOBJ_TYPE _qType = NONE;
	GLUquadricObj* _qObj = nullptr;

	bool indexed = false;
};

