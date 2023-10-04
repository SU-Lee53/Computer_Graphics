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

class Objects
{
public:
	Objects(OBJ_SHAPE shape, Coord pos, float size);
	~Objects();
	void CreateObject(OBJ_SHAPE shape, Coord pos, float size);
	void SetRGB(RGB rgb);
	void SetVertexPos(Coord pos, float size);
	void ModifyVertex(float dx, float dy);
	void MoveObject(Dir d, float distance);
	void RenderObject();
	void InitBuffer();
	
	GLuint GetVAO() { return vao; }
	OBJ_SHAPE GetShape() { return shape; }

	void StoreBufferData();
	void LoadBufferData();

	Dir CheckOutOfScreen();
	Coord GetOutOfScreenVertex();
	bool ChangeTriangleDirection(Dir dir);

protected:

	GLfloat* vertexBuf;
	GLfloat* colorBuf;
	unsigned int* elementBuf;

	// ���۸� ����� �Űܴ�Ƽ� �����ϰ� �ʿ��Ҷ� ������
	float vertexStore[15];
	float colorStore[15];
	unsigned int elementStore[9];

	OBJ_SHAPE shape;
	GLuint vao;
	GLuint vbo[2];
	GLuint ebo;

	float size;
};

