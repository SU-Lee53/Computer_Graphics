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

class Objects
{
public:
	// 2D전용 생성자
	Objects(OBJ_TYPE_2D type, Coord pos, float size);
	Objects(OBJ_TYPE_3D type, Coord pos, float size);
	~Objects();

private:
	void CreateObject2D(OBJ_TYPE_2D type);
	void CreateObject3D(OBJ_TYPE_3D type) {} ;

public:
	// 변환 함수
	void Translate() {};
	void Rotate() {};
	void Scale() {};


	// 렌더링
	void Render();

private:
	VAO* _vao;
	Coord _centerPos;
	float _size;
};

