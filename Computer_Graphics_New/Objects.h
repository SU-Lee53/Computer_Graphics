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
	OBJ_PLANE_RECT,
	OBJ_PLANE_TRIANGLE
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
	// 3D전용 생성자, 되도록 아래 생성자를 사용, 이전 실습과 호환성 문제로 레거시로 남겨둠
	Objects(OBJ_TYPE_3D type, Coord pos, float size);
	// 3D NON-INDEXED 생성자, INDEXED로도 생성 가능하므로 가능하면 이걸 사용
	Objects(OBJ_TYPE_3D type, Coord pos, float size, VAO_TYPE indexType);
	// Quadric Objects 전용 생성자
	Objects(QOBJ_TYPE type, Coord pos, float size);
	~Objects();

private:
	void CreateObject2D(OBJ_TYPE_2D type);
	void CreateObject3D(OBJ_TYPE_3D type);
	void CreateNonIndexedObject3D(OBJ_TYPE_3D type);
	void CreateQuadricObject();

public:
	// 유틸함수
	VAO& GetVAO() { return *_vao; }

	// 렌더링
	void Render();
	
	// Quadric Object인지 확인하는 flag 반환
	bool isQuadric()
	{
		if (_qType == NONE)
			return false;
		else
			return true;
	}

private:
	VAO* _vao;
	Coord _centerPos;
	float _size;
	QOBJ_TYPE _qType = NONE;
	GLUquadricObj* _qObj = nullptr;

	VAO_TYPE _indexType = NON_INDEXED;

};

