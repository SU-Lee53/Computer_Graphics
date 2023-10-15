#pragma once
#include "pch.h"

class Ex15 : protected Examples
{
public:
	Ex15();
	virtual ~Ex15() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override;

	void RenderWorld();
	void Reset();


private:
	Objects* _obj;
	glm::mat4 unit = glm::mat4(1.0f);
	glm::mat4 tMatrix = glm::mat4(1.0f);

	/*
	
	키보드 명령
	h		은면제거 적용/해제
	w/W		와이어 객체/ 솔리드 객체
	x/X		x축을 기준으로 양/음 방향으로 회전 애니매이션
	y/Y		y축을 기준으로 양/음 방향으로 회전 애니매이션
	방향키	좌/우/상/하로 객체를 이동한다(x축, y축 이동)
	s:		초기 위치로 리셋

	*/

	bool cullMode = true;
	bool renderMode = true;

	// Switch -> 애니매이션 On/Off, Mode -> 양/음 방향 결정
	bool rxSwitch = false;
	bool rxMode = true;
	bool rySwitch = false;
	bool ryMode = true;

};

