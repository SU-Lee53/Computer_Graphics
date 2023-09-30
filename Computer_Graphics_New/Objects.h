#pragma once
using namespace std;

enum OBJ_SHAPE
{
	OBJ_POINT = 0,
	OBJ_LINE,
	OBJ_TRIANGLE,
	OBJ_RECTANGLE
};

class Objects
{
public:
	Objects(OBJ_SHAPE shape, Coord pos, float size);
	~Objects();
	void CreateObject(OBJ_SHAPE shape, Coord pos, float size);
	void SetRGB(RGB rgb);
	void SetVertexPos(Coord pos, float size);
	void MoveObject(Dir d);
	void RenderObject();
	void InitBuffer();
	
	GLuint GetVAO() { return vao; }
	OBJ_SHAPE GetShape() { return shape; }

	void StoreBufferData();
	void LoadBufferData();

	void CheckOutOfScreen();

protected:

	GLfloat* vertexBuf;
	GLfloat* colorBuf;
	unsigned int* elementBuf;

	// 버퍼를 여기다 옮겨담아서 저장하고 필요할때 꺼내씀
	float vertexStore[12];
	float colorStore[12];
	unsigned int elementStore[6];

	OBJ_SHAPE shape;
	GLuint vao;
	GLuint vbo[2];
	GLuint ebo;
};

