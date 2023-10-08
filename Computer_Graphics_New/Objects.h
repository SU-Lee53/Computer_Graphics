#pragma once
using namespace std;

enum OBJ_SHAPE
{
	OBJ_POINT = 0,
	OBJ_LINE,
	OBJ_TRIANGLE,
	OBJ_RECTANGLE,
	OBJ_PENTAGON
};

struct HITBOX
{
	Coord p1;
	Coord p2;
	Coord p3;
	Coord p4;
};

class Objects
{
public:
	Objects(OBJ_SHAPE shape, Coord pos, float size);
	~Objects();
	void CreateObject(OBJ_SHAPE shape, Coord pos, float size);
	void SetRGB(RGB rgb);
	void SetVertexPos(Coord pos, float size);
	void MoveVertex(float dx, float dy);
	void MoveObject(Dir d, float distance);
	void RenderObject();
	void InitBuffer();
	void MakeHitbox();
	void StoreBufferData();

	GLuint GetVAO() { return vao; }
	OBJ_SHAPE GetShape() { return shape; }

	Dir CheckOutOfScreen();
	Coord GetOutOfScreenVertex();
	bool ChangeTriangleDirection(Dir dir);

	bool CheckClicked(Coord pos);

	bool GetCollision(Objects* obj);
	int GetVertexCount();

	float GetVertex(int index) { return vertexStore[index]; }

	HITBOX GetHitbox() { return hBox; }
protected:

	GLfloat* vertexBuf;
	GLfloat* colorBuf;
	unsigned int* elementBuf;

	// 버퍼를 여기다 옮겨담음
	float vertexStore[15];
	float colorStore[15];
	unsigned int elementStore[9];

	OBJ_SHAPE shape;
	GLuint vao;
	GLuint vbo[2];
	GLuint ebo;

	float size;

	HITBOX hBox;
};

