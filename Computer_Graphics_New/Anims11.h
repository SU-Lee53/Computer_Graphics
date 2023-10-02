#pragma once

enum TF_TYPE
{
	L2T = 0,
	T2R,
	R2P,
	P2P
};

class Anims11
{
public:
	Anims11(Coord pos, float Size, TF_TYPE type);
	void PlayAnim();
	void SetAnim();

	void Line2Tri();
	void Tri2Rect();
	void Rect2Pent();
	void Pent2Point();

	void SetLine2Tri();
	void SetTri2Rect();
	void SetRect2Pent();
	void SetPent2Point();

	void InitBuffer();

	void Render();

	unsigned int GetVAO() { return vao; }
	bool GetEndFlag() {return isEnd;}

private:
	unsigned int vao;
	unsigned int vbo[3];

	float* vertexBuf;
	float* colorBuf;
	unsigned int* elementBuf;

	float vertex[15];
	float color[15];
	unsigned int element[15];

	Coord center;
	float size;
	TF_TYPE type;

	bool isEnd = false;
};

