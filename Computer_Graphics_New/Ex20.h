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
	// 0: ¾Æ·§¸ö, 1: À­¸ö, 2: ÁÂÇÏ´Ü Æ÷½Å, 3: ¿ìÇÏ´Ü Æ÷½Å
	// 4: ÁÂ»ó´Ü Æ÷½Å, 5: ¿ì»ó´Ü Æ÷½Å
	Objects* _crane[6];

	glm::mat4 _upper;
	glm::mat4 _lower;
	glm::mat4 _upperBarrelLeft;
	glm::mat4 _upperBarrelRight;
	glm::mat4 _lowerBarrelLeft;
	glm::mat4 _lowerBarrelRight;




};

