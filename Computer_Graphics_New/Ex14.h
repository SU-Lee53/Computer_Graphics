#pragma once
#include "pch.h"

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
private:
	RGB _Background = { 1.0f, 1.0f, 1.0f };
	Objects* _obj;
	MouseState* _mouseState = nullptr;
	KeyboardState* _keyState = nullptr;
	int renderMode = 1;


	// 변환행렬은 단위행렬로 초기화
	glm::mat4 tMatrix = glm::mat4(1.0f);
};

