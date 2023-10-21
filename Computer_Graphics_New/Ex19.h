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

	VAO* _orbit = nullptr;
	float _orbitRadius = 3.0f;
	float _orbitVBuf[1000];
	float _orbitCBuf[1000];

	// 경로에 종속될 변환행렬
	glm::mat4 _orbit1;
	glm::mat4 _orbit2;
	glm::mat4 _orbit3;


	// 행성들: 조상1, 부모3, 자식3(트리처럼)
	Objects* _ancestor;
	Objects* _parent1;
	Objects* _parent2;
	Objects* _parent3;
	Objects* _child1;
	Objects* _child2;
	Objects* _child3;

	// 헹성 변환행렬
	glm::mat4 _ancestorMat = glm::mat4(1.0f);
	glm::mat4 _parentMat1 = glm::mat4(1.0f);
	glm::mat4 _parentMat2 = glm::mat4(1.0f);
	glm::mat4 _parentMat3 = glm::mat4(1.0f);
	glm::mat4 _chlidMat1 = glm::mat4(1.0f);
	glm::mat4 _chlidMat2 = glm::mat4(1.0f);
	glm::mat4 _chlidMat3 = glm::mat4(1.0f);


	glm::mat4 yRot = glm::mat4(1.0f);
	float yDeg = 0.0f;
};

