#pragma once
#include "pch.h"

enum ANIMTYPE
{
	ANIM_SPIRAL = 0,
	ANIM_GOTOCENTER,
	ANIM_CROSS,
	ANIM_ROTATE,
	ANIM_UPDOWN,
	ANIM_NONE
};

class Ex17 : protected Examples
{
public:
	Ex17();
	virtual ~Ex17() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	void SpiralAnim();
	void GotoCenterAnim();
	void CrossAnim();
	void RotateAnim();
	void UpDownAnim();

	void AnimPlayer();

	void RenderWorld();
	void MakeSpiral2D();

	void Reset();

private:
	Objects* _obj1;
	Objects* _obj2;
	glm::mat4 _unit = glm::mat4(1.0f);
	glm::mat4 _worldMat = glm::mat4(1.0f);
	glm::mat4 _objMat1 = glm::mat4(1.0f);
	glm::mat4 _objMat2 = glm::mat4(1.0f);
	glm::mat4 _projection = glm::mat4(1.0f);

	VAO* _spiralVAO;
	float _spiralVBuf[256];
	float _spiralCBuf[256];

	// 2개의 도형이 도는 타이밍을 다르게 하기 위해서 인덱스 2개 생성
	int _spiralMoveIdx1 = 0;
	int _spiralMoveIdx2 = 0;

	ANIMTYPE _animType = ANIM_NONE;

	glm::vec3 _objPos1 = glm::vec3(0.0f, 0.0f, 0.8f);
	glm::vec3 _objPos2 = glm::vec3(0.0f, 0.0f, -0.8f);

	bool _CenterSwitch = false;

	float _rotateDegree = 0.0f;

	bool UpDownSwitch = false;

	bool positionSwitched = false;
};

