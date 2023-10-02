#pragma once

enum ANIM_TYPE
{
	ANIM_BOUNCE = 0,
	ANIM_ZIGZAG,
	ANIM_RSPIRAL,
	ANIM_CSPIRAL
};

enum ANIM_DIR
{
	NW = 0,
	NE,
	SE,
	SW,
	N,
	E,
	S,
	W
};

class Anims
{
public:
	// �ǽ� 9���� ������
	Anims(Objects* obj);
	// �ǽ� 10���� ������
	Anims(Coord pos);
	~Anims();

	// �ǽ� 9�� �ִϸ��̼�
	void Bounce();
	void Zigzag();
	void RSpiral();
	void CSpiral();

	void SetBounce();
	void SetZigZag();
	void SetRSpiral();
	void SetCSpiral();
	void ChangeRSprialDirection();
	
	// �ǽ� 10�� �����̷� �ִϸ��̼�
	void SymSpiral();
	void InitSpiral();
	void SetSpiral();
	unsigned int GetSpiralVAO() { return vao; }
	int GetSpiralVertexCount() { return bufIndex / 3; }
	float GetSpiralRadian() { return radian; }
	bool GetSpiralEndFlag() { return isEnd; }
	bool GetSpiralDirection() { return spiralDirection; }

private:
	Objects* obj;
	// 9-1�� ƨ��� ����
	ANIM_TYPE type;
	ANIM_DIR bounceDir;

	// 9-2�� ������� ����
	bool ZigZagGoDown;
	Dir ZigZagDir;
	Dir ZigZagDir2;
	int downCount = 0;

	// 9-3�� �簢 �����̷� ����
	Dir RSP_dir;
	int switchCount;
	int moveCount;

	// 9-4�� �������̷� ����
	float radius;
	float radian;
	float beforeX;
	float beforeY;
	float vertexOrigin[9];

	// 10�� �����̷� ����
	
	unsigned int vao;
	unsigned int vbo[2];
	float* colorBuf;
	float* spiralBuf;
	float vBuf[2000];
	float cBuf[2000];
	int bufIndex;
	Coord pos;
	Coord newPos;
	bool SpiralSwitch = true;
	bool isEnd;
	bool spiralDirection;
	
};

