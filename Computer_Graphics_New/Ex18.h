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
	void RenderPyramid();

private:
	Objects* _cube;
	Objects* _pyramid;
	float _objSize = 0.5f;

	glm::mat4 _worldMat = glm::mat4(1.0);
	
	// ���� -> 0: �� 1: ���� 2: �� 3: ������ 4: �� 5: �Ʒ�
	glm::mat4 _cubeMat[6];

	// ���� -> 0: ���� 1: �� 2: ������ 3: �� 4: ��
	glm::mat4 _pyramidMat[5];

	Projection* _projection;
	Camera* _camera;
	
	bool _perspective = true;

	bool _depthTestMode = true;
	bool _yRotate = false;

	// ����ü �ִϸ��̼� �÷���
	bool _TopRotate = false;
	bool _frontOpen = false;
	bool _sideOpen = false;
	bool _backOpen = false;

	// �簢�� �ִϸ��̼� �÷���
	bool _playOpen = false;
	bool _openAll = false;
	bool _playReverse = false;
	bool _reverseOpen = false;

	bool objType = false;

	// y�� ȸ���� ���
	glm::mat4 _yrotateMat = glm::mat4(1.0);
	float _yRotateDegree = 0.0f;

	// ����ü �ִϸ��̼ǽ� ���
	float _topRotateDegree = 0.0f;
	float _cubeFrontOpenDegree = 0.0f;
	float _sideSlideDistance = 0.0f;
	float _backScaleSize = 1.0f;

	// �簢�� �ִϸ��̼ǽ� ���
	float _leftOpenDegree = 0.0f;
	float _frontOpenDegree = 0.0f;
	float _rightOpenDegree = 0.0f;
	float _backOpenDegree = 0.0f;
	float _openSpeed = 0.08f;
	int _openOrder = 0;

	unsigned int shaderID;
};
