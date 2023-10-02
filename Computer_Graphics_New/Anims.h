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
	// 실습 9번용 생성자
	Anims(Objects* obj);
	// 실습 10번용 생성자
	Anims(Coord pos);
	~Anims();

	// 실습 9번 애니매이션
	void Bounce();
	void Zigzag();
	void RSpiral();
	void CSpiral();

	void SetBounce();
	void SetZigZag();
	void SetRSpiral();
	void SetCSpiral();
	void ChangeRSprialDirection();
	
	// 실습 10번 스파이럴 애니매이션
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
	// 9-1번 튕기기 전용
	ANIM_TYPE type;
	ANIM_DIR bounceDir;

	// 9-2번 지그재그 전용
	bool ZigZagGoDown;
	Dir ZigZagDir;
	Dir ZigZagDir2;
	int downCount = 0;

	// 9-3번 사각 스파이럴 전용
	Dir RSP_dir;
	int switchCount;
	int moveCount;

	// 9-4번 원스파이럴 전용
	float radius;
	float radian;
	float beforeX;
	float beforeY;
	float vertexOrigin[9];

	// 10번 스파이럴 전용
	
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

