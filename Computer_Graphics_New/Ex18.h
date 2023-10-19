#pragma once
#include "pch.h"

class Ex18 : protected Examples
{
public:
	Ex18();
	virtual ~Ex18() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override {};
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	void Render();


private:
	Objects* _cube[6];
	Objects* _tetra[4];

	glm::mat4 _worldMat = glm::mat4(1.0);
	glm::mat4 _cubeMat[6];
	glm::mat4 _tetraMat[4];
	Projection* _projection;
	Camera* _camera;
	
	float degTest = 0.0f;
};
