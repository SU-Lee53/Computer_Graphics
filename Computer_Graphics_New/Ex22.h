#pragma once
#include "pch.h"

struct HITBOX
{
	float left;
	float top;
	float right;
	float bottom;
};

class Ex22 : protected Examples
{
public:
	Ex22();
	virtual ~Ex22() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

private:
	void Render();
	
	
	// 물체 생성 함수
	void MakeStage();
	void MakeRobot();
	void MakeObstacle();

	// 물체 렌더 함수
	void RenderStage();
	void RenderRobot();
	void RenderObstacle();

	// 애니매이션
	void OpenStage();
	void RobotJump();
	void RobotWalk();
	void RobotWalkAnim();

	// 충돌 -> 바닥 평면에서의 단순 겹침 판정만 하는 함수를 분리
	// 이유 -> 바닥에 있을때랑 점프해서 공중에 있을때 판정이 다름
	bool CheckCollision();
	bool CheckCollisionBtwHitbox(HITBOX h1, HITBOX h2);
	HITBOX GetRobotHitboxXZ();


private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;

	// 무대-> 0,1: 앞문 왼쪽, 오른쪽, 2: 위, 3: 아래, 4: 왼쪽, 5: 오른쪽, 6: 뒷면
	Objects* _stage[7];
	glm::mat4 _stageMat[7];
	float _stageOpenDeg = 0.0f;

	// 로봇-> 0,1: 다리 왼쪽 오른쪽, 2: 몸통, 3,4: 팔 왼쪽, 오른쪽, 5: 머리, 6: 코
	Objects* _robot[7];
	HITBOX _rHitbox;

	// 장애물
	Objects* _obstacle[3];
	HITBOX _oHitbox[3];

	// 문을 열고 닫을때 쓸 변수들
	glm::mat4 _openLeft = glm::mat4(1.0f);
	glm::mat4 _openRight = glm::mat4(1.0f);
	float _doorDeg = 0.0f;
	float _doorSpeed = 0.03f;
	bool _doorAnim = false;
	bool _doorOpen = false;

	// 로봇의 이동 행렬
	glm::mat4 _robotMoveX = glm::mat4(1.0f);
	glm::mat4 _robotMoveY = glm::mat4(1.0f);
	glm::mat4 _robotMoveZ = glm::mat4(1.0f);
	glm::mat4 _robotFace = glm::mat4(1.0f);
	DIR _direction = DIR_NONE;
	bool walkPlay = false;
	float _xMoveDist = 0.0f;
	float _yMoveDist = 0.0f;
	float _zMoveDist = 0.0f;
	float _mvSpeed = 0.02f;
	float _jumpSpeed = 0.05f;
	bool isJumped = false;
	bool jump = false;

	// 로봇 애니매이션 행렬
	glm::mat4 leftLeg = glm::mat4(1.0f);
	glm::mat4 rightLeg = glm::mat4(1.0f);
	glm::mat4 leftArm = glm::mat4(1.0f);
	glm::mat4 rightArm = glm::mat4(1.0f);
	float swingSpeed = 3.0f;
	float walk = 0.0f;
	float walkDeg = 0.0f;
	float _maxWalkDeg = 40.0f;

	
};

