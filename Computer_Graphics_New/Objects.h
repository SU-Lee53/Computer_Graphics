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
	Objects(OBJ_SHAPE shape, Coord pos);
	~Objects();
	void CreateObject(OBJ_SHAPE shape, Coord pos);
	void MoveObject(Dir d);
	void RenderObject();
	void InitBuffer();
	
	GLuint GetVAO() { return vao; }
	OBJ_SHAPE GetShape() { return shape; }

	void StoreBufferData();
	void LoadBufferData();

protected:

	GLfloat* vertexBuf;
	GLfloat* colorBuf;
	unsigned int* elementBuf;

	// ���۸� ����� �Űܴ�Ƽ� �����ϰ� �ʿ��Ҷ� ������
	vector<float> vertexStore;
	vector<float> colorStore;
	vector<unsigned int> elementStore;

	OBJ_SHAPE shape;
	GLuint vao;
	GLuint vbo[2];
	GLuint ebo;
};

