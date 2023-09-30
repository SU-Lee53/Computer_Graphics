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

	void SetBounceDir();


private:
	Objects* obj;
	ANIM_TYPE type;
	ANIM_DIR bounceDir;
};

