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
	virtual void KeyboardUpdate() override {}
	virtual void MotionUpdate() override {}

private:
	RGB _Background = { 0.0f, 0.0f, 0.0f };
	Objects* _obj;
	m_State* _mouseState = nullptr;
};

