#pragma once
#include "pch.h"

enum RenderMode2
{
	TETRAHEDRON = 0,
	CUBE,
	__NONE
};

class Ex14 : private Examples
{
public:
	Ex14();
	virtual ~Ex14() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override;
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}

	void RenderWorld();
	void SetRandomFace(RenderMode2 mode);
private:
	RGB _Background = { 1.0f, 1.0f, 1.0f };
	Objects* _obj;
	MouseState* _mouseState = nullptr;
	KeyboardState* _keyState = nullptr;
	
	// �� 1�� ������ ��� ����
	int renderMode = 1;

	// �� 2�� ������ ��� ����
	RenderMode2 renderMode2 = __NONE;
	bool modeSwitch = true;

	// ��ȯ����� ������ķ� �ʱ�ȭ
	glm::mat4 tMatrix = glm::mat4(1.0f);

	// ������ �鸸 �׸��� ����� �ε��� ����
	unsigned int elementBuf1[6];
	unsigned int elementBuf2[6];
};

