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
	
	Ű���� ���
	h		�������� ����/����
	w/W		���̾� ��ü/ �ָ��� ��ü
	x/X		x���� �������� ��/�� �������� ȸ�� �ִϸ��̼�
	y/Y		y���� �������� ��/�� �������� ȸ�� �ִϸ��̼�
	����Ű	��/��/��/�Ϸ� ��ü�� �̵��Ѵ�(x��, y�� �̵�)
	s:		�ʱ� ��ġ�� ����

	*/

	bool cullMode = true;
	bool renderMode = true;

	// Switch -> �ִϸ��̼� On/Off, Mode -> ��/�� ���� ����
	bool rxSwitch = false;
	bool rxMode = true;
	bool rySwitch = false;
	bool ryMode = true;

};

