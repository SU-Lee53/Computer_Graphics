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
	// 1�� ƨ��� ����
	ANIM_TYPE type;
	ANIM_DIR bounceDir;

	// 2�� ������� ����
	bool ZigZagGoDown;
	Dir ZigZagDir;
	Dir ZigZagDir2;
	int downCount = 0;

	// 3�� �簢 �����̷� ����
	Dir RSP_dir;
	int switchCount;
	int moveCount;
};

