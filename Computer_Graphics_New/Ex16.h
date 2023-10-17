#pragma once
#include "pch.h"

enum RotateMode
{
	MODE1 = 0,
	MODE2,
	BOTH,
	_NONE
};

class Ex16 : protected Examples
{
public:
	Ex16();
	virtual ~Ex16() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	void AnimationUpdate();
	void RenderWorld();

	void ChangeObjects();
	void Reset();

private:
	Objects* _obj1;
	Objects* _obj2;
	glm::mat4 _unit = glm::mat4(1.0f);
	glm::mat4 _worldMat = glm::mat4(1.0f);
	glm::mat4 _objMat1 = glm::mat4(1.0f);
	glm::mat4 _objMat2 = glm::mat4(1.0f);

	glm::mat4 projection = glm::mat4(1.0f);

	// ���� ���
	RotateMode rotateMode = BOTH;

	// ���� ����
	bool rotateDirection = false;

	// ���� On/Off
	bool rotateSwitch = false;

	// ������
	AXIS rotateAxis = X_AXIS;

	// ���� ����
	bool revolutionDirection = true;

	// ���� On/Off
	bool revolutionSwitch = false;



	// ������ -> �̵���� �������� ����Ͽ����� ���
	// float revolutionDegree1 = 90.0f;
	// float revolutionDegree2 = 270.0f;
	// float radius = 0.5f;

};

