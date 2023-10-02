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
	Anims(Objects* obj);
	~Anims();

	void Bounce();
	void Zigzag();
	void RSpiral();
	void CSpiral();


	void SetBounce();
	void SetZigZag();
	void SetRSpiral();
	void ChangeRSprialDirection();


private:
	Objects* obj;
	// 1번 튕기기 전용
	ANIM_TYPE type;
	ANIM_DIR bounceDir;

	// 2번 지그재그 전용
	bool ZigZagGoDown;
	Dir ZigZagDir;
	Dir ZigZagDir2;
	int downCount = 0;

	// 3번 사각 스파이럴 전용
	Dir RSP_dir;
	int switchCount;
	int moveCount;
};

