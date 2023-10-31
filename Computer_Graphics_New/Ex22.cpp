#include "pch.h"
#include "Ex22.h"

Ex22::Ex22()
{
	InitEx();
}

Ex22::~Ex22()
{
}

void Ex22::InitEx()
{
	srand(time(0));
	cout << "����ü�� ����Ͽ� ���븦 �׸���, Ű���带 ������ ������ �ո��� �¿�� �����̵��Ͽ� ������." << endl;
	cout << "����� ������ ������ �ִ�.���� �ٸ������� �����Ѵ�." << endl;
	cout << "	o / O: �ո��� �¿�� ������." << endl;
	cout << "�ٴڿ� ����ü�� ��ֹ��� ������ ��ġ�� 3�� �ִ�." << endl;
	cout << "���� ������ �κ��� ���� ���� �Ȱ� �ִ�." << endl;
	cout << "�κ��� �Ӹ�, ����, �� ��, �� �ٸ��� �ְ� ��, �ٸ��� ���� �ȴ´�." << endl;
	cout << "�Ӹ��� �ո鿡 �ڸ� ���̰�(�յ� ����), ���Ȱ� �� �ٸ��� �ٸ����� ����Ѵ�.(���� ����)" << endl;
	cout << "Ű���� ��ɾ ����Ͽ� �κ��� �̵� ������ �ٲ㼭 �����δ�." << endl;
	cout << "	w / a / s / d: �κ��� �� / �� / �� / �� �������� �̵� ������ �ٲ㼭 �ȴ´�.�����ڸ��� �����ϸ� �κ��� �ڷ� ���� �ٽ� �ȴ´�." << endl;
	cout << "	+ / -: �ȴ� �ӵ��� �������ų� / ��������.�ӵ��� �ٲ� �� �ȴ� �ٸ��� ������ �þ�ų� / �پ���." << endl;
	cout << "	j : �κ��� ���ڸ����� �����Ѵ�.��ֹ� ���� �����Ͽ� �ö󰡰� ������ �� �ִ�." << endl;
	cout << "	i : ��� ��ȯ�� �����ϰ� �ٽ� ����" << endl;
	cout << "ī�޶� ���� : Ű���� ������� ī�޶� �̵�" << endl;
	cout << "	z / Z : �յڷ� �̵�" << endl;
	cout << "	x / X : �¿�� �̵�" << endl;
	cout << "	y / Y : ī�޶� ���� ��ġ���� ȭ�� �߽� y���� �������� ����" << endl;

	for (int i = 0; i < 6; i++)
	{
		_stage[i] = nullptr;
	}

	_camera = new Camera(glm::vec3(0.0, 4.0, 10.0), glm::vec3(0.0, 4.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
	
}

void Ex22::drawScene()
{
	_shaderID = GET_SINGLE(Core).GetShaderID();
	glUseProgram(_shaderID);

	_camera->Bind(_shaderID);
	_projection->Bind(_shaderID);
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);

	KeyboardUpdate();

	if(_stage[0] != nullptr)
	{
		OpenStage();
		RobotJump();
		RobotWalk();
		RobotWalkAnim();
		PlayCameraAnim();
	}

	Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Ex22::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex22::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();
	if (ks == nullptr)
	{
		return;
	}

	switch (ks->key)
	{
	case 'o':
		if (!_doorAnim)
			_doorAnim = true;

		_doorOpen = true;
		break;

	case 'O':
		if (!_doorAnim)
			_doorAnim = true;

		_doorOpen = false;
		break;

	case 'w':
		walkPlay = true;
		_direction = DIR_FRONT;
		break;
		
	case 's':
		walkPlay = true;
		_direction = DIR_BACK;
		break;
		
	case 'd':
		walkPlay = true;
		_direction = DIR_RIGHT;
		break;
		
	case 'a':
		walkPlay = true;
		_direction = DIR_LEFT;
		break;	
	
	case 'r':
		walkPlay = true;
		_direction = DIR_NONE;
		break;

	case 'j':
		if(!isJumped)
		{
			isJumped = true;
			jump = true;
		}
		break;

	case '+':
		_mvSpeed += 0.005f;
		_maxWalkDeg += 3.0f;
		break;
		
	case '-':
		_mvSpeed -= 0.005f;
		_maxWalkDeg -= 3.0f;
		break;

	case 'z':
		_camera->CameraMove(glm::vec3(0.0f, 0.0f, _camMoveSpeed));
		_camMoveDistZ += _camMoveSpeed;
		break;
		
	case 'Z':
		_camera->CameraMove(glm::vec3(0.0f, 0.0f, -(_camMoveSpeed)));
		_camMoveDistZ -= _camMoveSpeed;
		break;
		
	case 'x':
		_camera->CameraMove(glm::vec3(_camMoveSpeed, 0.0f, 0.0f));
		_camMoveDistX += _camMoveSpeed;
		break;
		
	case 'X':
		_camera->CameraMove(glm::vec3(-(_camMoveSpeed), 0.0f, 0.0f));
		_camMoveDistX -= _camMoveSpeed;
		break;
		
	case 'y':
		if (!_camRotatePlay)
		{
			_camRotatePlay = true;
			_camRotateDir = true;
		}
		else
			_camRotatePlay = false;
		break;
		
	case 'Y':
		if (!_camRotatePlay)
		{
			_camRotatePlay = true;
			_camRotateDir = false;
		}
		else
			_camRotatePlay = false;
		break;

	case 'i':
		Reset();
		break;

	}





	delete ks;
}

void Ex22::Render()
{
	if (_stage[0] == nullptr)
	{
		MakeStage();
		MakeRobot();
		MakeObstacle();
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	RenderStage();
	RenderObstacle();
	RenderRobot();
	
}

void Ex22::Reset()
{
	for (int i = 0; i < 3; i++)
	{
		delete _obstacle[i];
	}
	MakeObstacle();

	_robotMoveX = glm::mat4(1.0f);
	_robotMoveY = glm::mat4(1.0f);
	_robotMoveZ = glm::mat4(1.0f);
	_robotFace = glm::mat4(1.0f);
	_direction = DIR_NONE;

	_xMoveDist = 0.0f;
	_yMoveDist = 0.0f;
	_zMoveDist = 0.0f;

	leftLeg = glm::mat4(1.0f);
	rightLeg = glm::mat4(1.0f);
	leftArm = glm::mat4(1.0f);
	rightArm = glm::mat4(1.0f);

	_camera->CameraMove(glm::vec3(-(_camMoveDistX), 0.0f, -(_camMoveDistZ)));
	_camMoveDistZ = 0.0f;
	_camMoveDistX = 0.0f;
	_camRotateDeg = 0.0f;

	
	_camera->CameraRevolution(-(_camRotateDeg), Y_AXIS);
	_camRotateDeg = 0.0f;
	_camRotatePlay = false;
}

void Ex22::MakeStage()
{
	glm::mat4 scale, rot, move;

	// ���� ����� ����� �������� ũ�⸦ ������ ���� ȸ���ؼ� ����
	_stage[0] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 1.0f, 1.0f));
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, X_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-2.0f, 4.0f, 4.0f));
	_stageMat[0] = move * rot * scale;
	_stage[0]->ChangeColor({ 1.0f,0.3f,0.0f });
	
	_stage[1] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 1.0f, 1.0f));
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, X_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(2.0f, 4.0f, 4.0f));
	_stageMat[1] = move * rot * scale;
	_stage[1]->ChangeColor({ 1.0f,0.3f,0.0f });

	_stage[2] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 8.0f, 0.0f));
	_stageMat[2] = move;
	_stage[2]->ChangeColor({ 1.0f,1.0f,0.0f });

	_stage[3] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(180.0f, Z_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
	_stageMat[3] = move * rot;
	_stage[3]->ChangeColor({ 0.0f,1.0f,1.0f });

	_stage[4] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, Z_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-4.0f, 4.0f, 0.0f));
	_stageMat[4] = move * rot;
	_stage[4]->ChangeColor({ 1.0f,0.0f,1.0f });

	_stage[5] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(-90.0f, Z_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(4.0f, 4.0f, 0.0f));
	_stageMat[5] = move * rot;
	_stage[5]->ChangeColor({ 0.0f,1.0f,0.0f });

	_stage[6] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(-90.0f, X_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 4.0f, -4.0f));
	_stageMat[6] = move * rot;
	_stage[6]->ChangeColor({ 0.0f,0.0f,1.0f });


}

void Ex22::MakeRobot()
{
	// �ٸ�
	_robot[0] = new Objects(0.1f, 0.1f, 0.3f, -0.1f, 0.0f, 0.5f);
	_robot[0]->ChangeColor({ 1.0f, 0.0f, 0.0f });
	_robot[1] = new Objects(-0.3f, 0.1f, -0.1f, -0.1f, 0.0f, 0.5f);
	_robot[1]->ChangeColor({ 1.0f, 1.0f, 0.5f });

	// ����
	_robot[2] = new Objects(-0.3f, 0.1f, 0.3f, -0.1f, 0.5f, 1.3f);
	_robot[2]->ChangeColor({ 0.0f, 0.3f, 0.5f });

	// ��
	_robot[3] = new Objects(-0.5f, 0.1f, -0.3f, -0.1f, 0.7f, 1.3f);
	_robot[3]->ChangeColor({ 1.0f, 0.0f, 0.0f });
	_robot[4] = new Objects(0.3f, 0.1f, 0.5f, -0.1f, 0.7f, 1.3f);
	_robot[4]->ChangeColor({ 1.0f, 1.0f, 0.0f });

	// �Ӹ�, ��
	_robot[5] = new Objects(-0.2f, 0.2f, 0.2f, -0.2f, 1.3f, 1.7f);
	_robot[5]->ChangeColor({ 0.0f, 0.6f, 0.5f });
	_robot[6] = new Objects(-0.05f, 0.2f, 0.05f, 0.3f, 1.4f, 1.45f);
	_robot[6]->ChangeColor({ 1.0f, 0.0f, 0.0f });
}

void Ex22::MakeObstacle()
{
	Coord pos1, pos2, pos3;

	pos1.x = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));
	pos1.y = 0.5f;
	pos1.z = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));
	
	pos2.x = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));
	pos2.y = 0.5f;
	pos2.z = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));
	
	pos3.x = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));
	pos3.y = 0.5f;
	pos3.z = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));


	_obstacle[0] = new Objects(OBJ_CUBE, pos1, 0.5f, INDEXED);
	_obstacle[1] = new Objects(OBJ_CUBE, pos2, 0.5f, INDEXED);
	_obstacle[2] = new Objects(OBJ_CUBE, pos3, 0.5f, INDEXED);


	// ��ֹ��� �浹���� �̸� ��������

	_oHitbox[0].left = _obstacle[0]->GetCenter().x - _obstacle[0]->GetSize();
	_oHitbox[0].top = _obstacle[0]->GetCenter().z + _obstacle[0]->GetSize();
	_oHitbox[0].right = _obstacle[0]->GetCenter().x + _obstacle[0]->GetSize();
	_oHitbox[0].bottom = _obstacle[0]->GetCenter().z - _obstacle[0]->GetSize();
	
	_oHitbox[1].left = _obstacle[1]->GetCenter().x - _obstacle[1]->GetSize();
	_oHitbox[1].top = _obstacle[1]->GetCenter().z + _obstacle[1]->GetSize();
	_oHitbox[1].right = _obstacle[1]->GetCenter().x + _obstacle[1]->GetSize();
	_oHitbox[1].bottom = _obstacle[1]->GetCenter().z - _obstacle[1]->GetSize();
	
	_oHitbox[2].left = _obstacle[2]->GetCenter().x - _obstacle[2]->GetSize();
	_oHitbox[2].top = _obstacle[2]->GetCenter().z + _obstacle[2]->GetSize();
	_oHitbox[2].right = _obstacle[2]->GetCenter().x + _obstacle[2]->GetSize();
	_oHitbox[2].bottom = _obstacle[2]->GetCenter().z - _obstacle[2]->GetSize();


}

void Ex22::RenderStage()
{
	// for (int i = 0; i < 6; i++)
	// {
	// 		GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[i], _shaderID);
	// 		_stage[i]->Render();
	// }

	GET_SINGLE(TransformManager).Bind(_worldMat * _openLeft * _stageMat[0], _shaderID);
	_stage[0]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _openRight * _stageMat[1], _shaderID);
	_stage[1]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[2], _shaderID);
	_stage[2]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[3], _shaderID);
	_stage[3]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[4], _shaderID);
	_stage[4]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[5], _shaderID);
	_stage[5]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[6], _shaderID);
	_stage[6]->Render();



}

void Ex22::RenderRobot()
{
	glm::mat4 move = _robotMoveX * _robotMoveY * _robotMoveZ;


	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace * leftLeg, _shaderID);
	_robot[0]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace * rightLeg, _shaderID);
	_robot[1]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace, _shaderID);
	_robot[2]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace * leftArm, _shaderID);
	_robot[3]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace * rightArm, _shaderID);
	_robot[4]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace, _shaderID);
	_robot[5]->Render();
	
	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace, _shaderID);
	_robot[6]->Render();

}

void Ex22::RenderObstacle()
{
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);
	_obstacle[0]->Render();
	_obstacle[1]->Render();
	_obstacle[2]->Render();

}

void Ex22::OpenStage()
{
	if (_doorAnim)
	{
		glm::mat4 move, rot, mvBack;

		// 1. ���� �� ����
		move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(4.0f, 0.0f, -4.0f));
		rot = GET_SINGLE(TransformManager).GetRotateMatrix(-_doorDeg, Y_AXIS);
		mvBack = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-4.0f, 0.0f, 4.0f));
		_openLeft = mvBack * rot * move;

		// 2. ������ �� ����
		move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-4.0f, 0.0f, -4.0f));
		rot = GET_SINGLE(TransformManager).GetRotateMatrix(_doorDeg, Y_AXIS);
		mvBack = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(4.0f, 0.0f, 4.0f));
		_openRight = mvBack * rot * move;

		if(_doorOpen)
		{
			if (_doorDeg <= 120.0f)
				_doorDeg += _doorSpeed;
			else
				_doorAnim = false;
		}
		else
		{
			if (_doorDeg >= 0.0f)
				_doorDeg -= _doorSpeed;
			else
				_doorAnim = false;
		}

	}

}

void Ex22::RobotJump()
{
	if (isJumped)
	{
		if (jump)
		{
			_yMoveDist += _jumpSpeed;
			_robotMoveY = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _yMoveDist, 0.0f));
			if (_yMoveDist >= 1.5f)
			{
				jump = false;
			}
		}
		else
		{
			bool isColide = false;
			int colidedIdx = 0;
			for (int i = 0; i < 3; i++)
			{
				if (CheckCollisionBtwHitbox(_rHitbox, _oHitbox[i]))
				{
					isColide = true;
					colidedIdx = i;
					break;
				}
			}

			_yMoveDist -= _jumpSpeed;
			_robotMoveY = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _yMoveDist, 0.0f));

			if (isColide && _yMoveDist <= _obstacle[colidedIdx]->GetCenter().y + _obstacle[colidedIdx]->GetSize() && _direction != DIR_NONE)	// DIR_NONE�̸� �ö󰡱����� ����� -> ���� ������ �÷��� �ʿ䰡 ����
			{
				_yMoveDist = _obstacle[colidedIdx]->GetCenter().y + _obstacle[colidedIdx]->GetSize();
				_robotMoveY = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _yMoveDist, 0.0f));
				return;
			}

			if (_yMoveDist <= 0.0f)
			{
				isJumped = false;
			}
		}
	}
}

void Ex22::RobotWalk()
{
	if (walkPlay)
	{
		
		switch (_direction)
		{
		case DIR_FRONT:
			_zMoveDist -= _mvSpeed;
			_robotMoveZ = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, _zMoveDist));
			_robotFace = GET_SINGLE(TransformManager).GetRotateMatrix(180.0f, Y_AXIS);
			
			if (_zMoveDist <= -3.5f || _zMoveDist >= 3.5f)
				_direction = DIR_BACK;

			break;

		case DIR_BACK:
			_zMoveDist += _mvSpeed;
			_robotMoveZ = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, _zMoveDist));
			_robotFace = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, Y_AXIS);

			if (_zMoveDist <= -3.5f || _zMoveDist >= 3.5f)
				_direction = DIR_FRONT;

			break;

		case DIR_RIGHT:
			_xMoveDist += _mvSpeed;
			_robotMoveX = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_xMoveDist, 0.0f, 0.0f));
			_robotFace = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, Y_AXIS);

			if (_xMoveDist <= -3.5f || _xMoveDist >= 3.5f)
				_direction = DIR_LEFT;

			break;

		case DIR_LEFT:
			_xMoveDist -= _mvSpeed;
			_robotMoveX = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_xMoveDist, 0.0f, 0.0f));
			_robotFace = GET_SINGLE(TransformManager).GetRotateMatrix(-90.0f, Y_AXIS);

			if (_xMoveDist <= -3.5f || _xMoveDist >= 3.5f)
				_direction = DIR_RIGHT;

			break;
		}

		if (CheckCollision())
		{
			_direction = DIR_NONE;
		}
	}
}

void Ex22::RobotWalkAnim()
{
	if(walkPlay && _direction != DIR_NONE)
	{
		glm::mat4 tMat, mvMat, rotMat, mvBackMat;

		// 1. �޴ٸ�
		mvMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-(_robot[0]->GetCenter().x), -0.5f, -(_robot[0]->GetCenter().z)));
		rotMat = GET_SINGLE(TransformManager).GetRotateMatrix(walkDeg, X_AXIS);
		mvBackMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3((_robot[0]->GetCenter().x), 0.5f, (_robot[0]->GetCenter().z)));
		leftLeg = mvBackMat * rotMat * mvMat;

		// 2. �����ٸ�
		mvMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-(_robot[1]->GetCenter().x), -0.5f, -(_robot[1]->GetCenter().z)));
		rotMat = GET_SINGLE(TransformManager).GetRotateMatrix(-walkDeg, X_AXIS);
		mvBackMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3((_robot[1]->GetCenter().x), 0.5f, (_robot[1]->GetCenter().z)));
		rightLeg = mvBackMat * rotMat * mvMat;

		// 1. ����
		mvMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-(_robot[3]->GetCenter().x), -1.3f, -(_robot[3]->GetCenter().z)));
		rotMat = GET_SINGLE(TransformManager).GetRotateMatrix(walkDeg, X_AXIS);
		mvBackMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3((_robot[3]->GetCenter().x), 1.3f, (_robot[3]->GetCenter().z)));
		leftArm = mvBackMat * rotMat * mvMat;

		// 2. ������
		mvMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-(_robot[4]->GetCenter().x), -1.3f, -(_robot[4]->GetCenter().z)));
		rotMat = GET_SINGLE(TransformManager).GetRotateMatrix(-walkDeg, X_AXIS);
		mvBackMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3((_robot[4]->GetCenter().x), 1.3f, (_robot[4]->GetCenter().z)));
		rightArm = mvBackMat * rotMat * mvMat;

		walk += swingSpeed;
		walkDeg = glm::sin(glm::radians(walk)) * _maxWalkDeg;
	}
	else
	{
		leftLeg = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
		rightLeg = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
		leftArm = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
		rightArm = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
		walk = 0.0f;
		walkDeg = 0.0f;
	}

}

void Ex22::PlayCameraAnim()
{
	if (_camRotatePlay)
	{
		if (_camRotateDir)
		{
			_camRotateDeg += _camRotateSpeed;
			_camera->CameraRevolution(_camRotateDeg, Y_AXIS);
		}
		else
		{
			_camRotateDeg -= _camRotateSpeed;
			_camera->CameraRevolution(_camRotateDeg, Y_AXIS);
		}
	}

}

bool Ex22::CheckCollision()
{
	_rHitbox = GetRobotHitboxXZ();	// ����
	
	for (int i = 0; i < 3; i++)
	{
		if (!CheckCollisionBtwHitbox(_rHitbox, _oHitbox[i]))
			continue;
		if (_yMoveDist >= _obstacle[i]->GetCenter().y + _obstacle[i]->GetSize())	// �����ؼ� ���̰� ��ֹ����� ������ �浹�ƴ�
			continue;
		
		return true;
	}

	return false;

	//	���� Objects�� GetCollosion, ������ HITBOX�� �� ���� ��ǥ��
	//	if (h1.p2.x > h2.p1.x && h2.p2.x > h1.p1.x && h1.p1.y > h2.p4.y && h2.p1.y > h1.p4.y)
	//		return true;
	//	else
	//		return false;

}

bool Ex22::CheckCollisionBtwHitbox(HITBOX h1, HITBOX h2)
{
	if (h1.right > h2.left && h2.right > h1.left && h1.top > h2.bottom && h2.top > h1.bottom)
	{
		return true;
	}
	else
		return false;
}

HITBOX Ex22::GetRobotHitboxXZ()
{
	switch (_direction)
	{
	case DIR_FRONT:
	case DIR_BACK:
		_rHitbox = { _xMoveDist - 0.5f, _zMoveDist + 0.1f, _xMoveDist + 0.5f, _zMoveDist - 0.1f };
		break;

	case DIR_LEFT:
	case DIR_RIGHT:
		_rHitbox = { _xMoveDist - 0.1f, _zMoveDist + 0.5f, _xMoveDist + 0.1f, _zMoveDist - 0.5f };
		break;
	}

	return _rHitbox;
}
