#pragma once
#include "pch.h"

class Ex19 : protected Examples
{
public:
	Ex19();
	virtual ~Ex19() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override {};
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}


	void Render();
	void SetOrbit();
	void SetPlanet();


	void RenderOrbit();
	void RenderPlanet();


private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);

	// 큰 궤도 -> 부모 행성들이 도는 경로
	VAO* _bigOrbit = nullptr;
	float _bigOrbitRadius = 3.0f;
	float _bigOrbitVBuf[150];
	float _bigOrbitCBuf[150];

	// 작은 궤도 -> 자식 행성들이 도는 경로
	VAO* _smallOrbit = nullptr;
	float _smallOrbitRadius = 1.0f;
	float _smallOrbitVBuf[400];
	float _smallOrbitCBuf[400];

	// 경로에 대한 변환행렬
	glm::mat4 _orbit1;
	glm::mat4 _orbit2;
	glm::mat4 _orbit3;

	// 행성: 조상1, 부모3, 자식3(트리처럼)
	// 조상 하나 만들고 나머지는 신축해서 만듬
	Objects* _planet;
	glm::mat4 _scaleMat1 = glm::mat4(1.0f);
	glm::mat4 _scaleMat2 = glm::mat4(1.0f);


	// 헹성 변환행렬
	glm::mat4 _ancestorMat = glm::mat4(1.0f);

	glm::mat4 _parentMat1 = glm::mat4(1.0f);
	glm::mat4 _parentMat2 = glm::mat4(1.0f);
	glm::mat4 _parentMat3 = glm::mat4(1.0f);

	glm::mat4 _childMat1 = glm::mat4(1.0f);
	glm::mat4 _childMat2 = glm::mat4(1.0f);
	glm::mat4 _childMat3 = glm::mat4(1.0f);
	
	// 공전의 공전 -> 궤도만큼 더 이동
	glm::mat4 _lastMat1 = glm::mat4(1.0f);
	glm::mat4 _lastMat2 = glm::mat4(1.0f);
	glm::mat4 _lastMat3 = glm::mat4(1.0f);


	glm::mat4 yRot1 = glm::mat4(1.0f);
	float yDeg1 = 0.0f;

	glm::mat4 yRot2 = glm::mat4(1.0f);
	float yDeg2 = 0.0f;
	
	glm::mat4 yRot3 = glm::mat4(1.0f);
	float yDeg3 = 0.0f;


};

