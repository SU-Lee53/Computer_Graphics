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
	virtual void Update() override;

	void MouseUpdate();
	void KeyboardUpdate() {}
	void MotionUpdate() {}

private:
	RGB _Background = { 0.0f, 0.0f, 0.0f };
	Objects* _obj;
	m_State* _mouseState = nullptr;
};

