#pragma once
using namespace std;

enum OBJ_SHAPE
{
	OBJ_POINT = 0,
	OBJ_LINE,
	OBJ_TRIANGLE,
	OBJ_RECTANGLE,
	OBJ_PENTAGON,
	OBJ_RECT13	// 13�� ���� �ﰢ���� �ƴ� ������ ������� �簢��
};

struct HITBOX
{
	Coord p1;
	Coord p2;
	Coord p3;
	Coord p4;
};

class Objects_Unused
{
public:
	Objects_Unused(OBJ_SHAPE shape, Coord pos, float size);
	~Objects_Unused();
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

	bool GetCollision(Objects_Unused* obj);
	int GetVertexCount();

	float GetVertex(int index) { return vertexStore[index]; }

	HITBOX GetHitbox() { return hBox; }

	void SetValid(bool flag) { isValid = flag; }
	bool GetValid() { return isValid; }


	// �ǽ� 13
	void ModifySpecificVertex(int vNum, float dx, float dy);
	Coord GetSpecificVertex(int vNum);
	int CheckSpecificVertexClicked(Coord pos);
	// x,y�� �� ����, Mode == true -> x��, �ƴϸ� y��
	void SetAxis(bool Mode);

protected:

	GLfloat* vertexBuf;
	GLfloat* colorBuf;
	unsigned int* elementBuf;

	// ���۸� ����� �Űܴ���
	float vertexStore[15];
	float colorStore[15];
	unsigned int elementStore[9];

	OBJ_SHAPE shape;
	GLuint vao;
	GLuint vbo[2];
	GLuint ebo;

	float size;

	HITBOX hBox;

	bool isValid;
};

