#pragma once
#include "pch.h"


class Ex20 : protected Examples
{
public:
	Ex20();
	virtual ~Ex20() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override {};
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	void Render();

	void MakeCrane();


private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;

	Objects* _floor = nullptr;
	// 0: �Ʒ���, 1: ����, 2: ���ϴ� ����, 3: ���ϴ� ����
	// 4: �»�� ����, 5: ���� ����
	Objects* _crane[6];

	glm::mat4 _upper;
	glm::mat4 _lower;
	glm::mat4 _upperBarrelLeft;
	glm::mat4 _upperBarrelRight;
	glm::mat4 _lowerBarrelLeft;
	glm::mat4 _lowerBarrelRight;




};

