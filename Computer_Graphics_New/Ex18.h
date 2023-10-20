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
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	void AnimUpdate();

	void Render();
	void RenderCube();

private:
	Objects* _cube;
	Objects* _tetra;

	glm::mat4 _worldMat = glm::mat4(1.0);
	
	// 순서: 0: 위 1: 왼 2: 앞 3: 오른쪽 4: 뒤 5: 아래
	glm::mat4 _cubeMat[6];
	glm::mat4 _tetraMat[4];
	Projection* _projection;
	Camera* _camera;
	
	bool _depthTestMode = true;
	bool _yRotate = false;
	bool _TopRotate = false;
	bool _frontOpen = false;
	bool _sideOpen = false;
	bool _backOpen = false;

	glm::mat4 _yrotateMat = glm::mat4(1.0);
	float _yRotateDegree = 0.0f;
	float _topRotateDegree = 0.0f;
	float _frontOpenDegree = 0.0f;
	float _sideSlideDistance = 0.0f;
	float _backScaleSize = 1.0f;

};
