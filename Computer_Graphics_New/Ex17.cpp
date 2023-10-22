#include "pch.h"
#include "Ex17.h"


Ex17::Ex17()
{
	InitEx();
}

Ex17::~Ex17()
{
}

void Ex17::InitEx()
{
	srand(time(0));
	_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(30.0f, X_AXIS)
		* GET_SINGLE(TransformManager).GetRotateMatrix(30.0f, Y_AXIS);

	_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix({ 0.0f, 0.f, 0.8f });
	_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix({ 0.0f, 0.0f, -0.8f });

	_camera = new Camera(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -2.0f);

	cout << "����, �̵� ����Ű" << endl;
	cout << "* : ���� Ȯ��" << endl;
	cout << "/ : ���� ���" << endl;
	cout << "+ : ���ڸ� Ȯ��" << endl;
	cout << "- : ���ڸ� ���" << endl;

	cout << endl;

	cout << "s : 1�� ���� + y" << endl;
	cout << "x : 1�� ���� - y" << endl;
	cout << "c : 1�� ���� + x" << endl;
	cout << "z : 1�� ���� - x" << endl;
	cout << "d : 1�� ���� + z" << endl;
	cout << "a : 1�� ���� - z" << endl;

	cout << endl;

	cout << "i : 2�� ���� + y" << endl;
	cout << "k : 2�� ���� - y" << endl;
	cout << "l : 2�� ���� + x" << endl;
	cout << "j : 2�� ���� - x" << endl;
	cout << "o : 2�� ���� + z" << endl;
	cout << "u : 2�� ���� - z" << endl;

	cout << endl;

	cout << "8 : ��ü ���� - z" << endl;
	cout << "5 : ��ü ���� + z" << endl;
	cout << "6 : ��ü ���� + x" << endl;
	cout << "4 : ��ü ���� - x" << endl;


}

void Ex17::drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_camera->Bind(GET_SINGLE(Core).GetuShaderID());
	_projection->Bind(GET_SINGLE(Core).GetuShaderID());

	KeyboardUpdate();
	AnimPlayer();

	GET_SINGLE(TransformManager).Bind(_worldMat);
	DrawAxis(1.0f);

	RenderWorld();

	glutSwapBuffers();
}

void Ex17::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex17::KeyboardUpdate()
{
	KeyboardState* kState = InputManager::GetInstance().DequeueKeyboardBuf();
	if (kState == nullptr)
		return;

	switch (kState->key)
	{
	case 'r':
		_animType = ANIM_SPIRAL;
		Reset();
		break;
		
	case 't':
		_animType = ANIM_GOTOCENTER;
		Reset();
		break;
		
	case '1':
		_animType = ANIM_CROSS;
		Reset();
		break;
		
	case '2':
		_animType = ANIM_ROTATE;
		Reset();
		break;
		
	case '3':
		_animType = ANIM_UPDOWN;
		Reset();
		break;

	case '`':
		_animType = ANIM_NONE;
		Reset();
		break;

	// ���� ����
	case '*':
		_objMat1 = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(1.2f, 1.2f, 1.2f)) * _objMat1;
		_objMat2 = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(1.2f, 1.2f, 1.2f)) * _objMat2;
		break;

	case '/':
		_objMat1 = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.8f, 0.8f, 0.8f)) * _objMat1;
		_objMat2 = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.8f, 0.8f, 0.8f)) * _objMat2;
		break;

	case '+':
		_objMat1 = _objMat1 * GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(1.2f, 1.2f, 1.2f));
		_objMat2 = _objMat2 * GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(1.2f, 1.2f, 1.2f));
		break;

	case '-':
		_objMat1 = _objMat1 * GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.8f, 0.8f, 0.8f));
		_objMat2 = _objMat2 * GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.8f, 0.8f, 0.8f));
		break;
	// ���� ��


	// 1�� ���� �̵�
	case 's':
		_objPos1 += glm::vec3(0.0f, 0.1f, 0.0f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		break;
		
	case 'x':
		_objPos1 += glm::vec3(0.0f, -0.1f, 0.0f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		break;
		
	case 'c':
		_objPos1 += glm::vec3(0.1f, 0.0f, 0.0f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		break;
		
	case 'z':
		_objPos1 += glm::vec3(-0.1f, 0.0f, 0.0f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		break;
		
	case 'd':
		_objPos1 += glm::vec3(0.0f, 0.0f, 0.1f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		break;

	case 'a':
		_objPos1 += glm::vec3(0.0f, 0.0f, -0.1f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		break;
	// 1�� ���� �̵� ��


	// 2�� ���� �̵�
	case 'i':
		_objPos2 += glm::vec3(0.0f, 0.1f, 0.0f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;

	case 'k':
		_objPos2 += glm::vec3(0.0f, -0.1f, 0.0f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;

	case 'l':
		_objPos2 += glm::vec3(0.1f, 0.0f, 0.0f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;

	case 'j':
		_objPos2 += glm::vec3(-0.1f, 0.0f, 0.0f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;

	case 'o':
		_objPos2 += glm::vec3(0.0f, 0.0f, 0.1f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;

	case 'u':
		_objPos2 += glm::vec3(0.0f, 0.0f, -0.1f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;
	// 2�� ���� �̵� ��


	// ��ü ���� �̵�
	case '8':
		_objPos1 += glm::vec3(0.0f, 0.0f, -0.1f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		_objPos2 += glm::vec3(0.0f, 0.0f, -0.1f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;

	case '5':
		_objPos1 += glm::vec3(0.0f, 0.0f, 0.1f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		_objPos2 += glm::vec3(0.0f, 0.0f, 0.1f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;

	case '6':
		_objPos1 += glm::vec3(0.1f, 0.0f, 0.0f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		_objPos2 += glm::vec3(0.1f, 0.0f, 0.0f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;

	case '4':
		_objPos1 += glm::vec3(-0.1f, 0.0f, 0.0f);
		_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
		_objPos2 += glm::vec3(-0.1f, 0.0f, 0.0f);
		_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);
		break;
	// ��ü ���� �̵� ��
	}

	delete kState;
}

void Ex17::AnimPlayer()
{
	SetOrigin();

	switch (_animType)
	{
	case ANIM_SPIRAL:
		SpiralAnim();
		break;

	case ANIM_GOTOCENTER:
		GotoCenterAnim();
		break;

	case ANIM_CROSS:
		CrossAnim();
		break;

	case ANIM_ROTATE:
		RotateAnim();
		break;

	case ANIM_UPDOWN:
		UpDownAnim();
		break;
	}

}

void Ex17::SpiralAnim()
{
	// ���� 1ȸ �����̷� ����
	if(_spiralVAO == nullptr)
		MakeSpiral2D();

	// �����̷��� ���븦 ���� ��ȯ����� ��������.

	if(_spiralMoveIdx1 < 256) 
	{
		glm::vec3 move = glm::vec3(_spiralVBuf[_spiralMoveIdx1], _spiralVBuf[_spiralMoveIdx1 + 1], _spiralVBuf[_spiralMoveIdx1 + 2]);
		glm::mat4 Tmat = GET_SINGLE(TransformManager).GetTranslateMatrix(move);
		_spiralMoveIdx1 += 3;
		_objMat1 = Tmat;
	}

	if (_spiralMoveIdx1 > 256 / 3)
	{
		glm::vec3 move = glm::vec3(_spiralVBuf[_spiralMoveIdx2], _spiralVBuf[_spiralMoveIdx2 + 1], _spiralVBuf[_spiralMoveIdx2 + 2]);
		glm::mat4 Tmat = GET_SINGLE(TransformManager).GetTranslateMatrix(move);
		_spiralMoveIdx2 += 3;
		_objMat2 = Tmat;
	}

	Sleep(20);

	if (_spiralMoveIdx2 >= 256)
	{
		_spiralMoveIdx1 = 0;
		_spiralMoveIdx2 = 0;
		_animType = ANIM_NONE;
		
	}
}

void Ex17::GotoCenterAnim()
{

	if(_CenterSwitch == false)
	{
		_objPos1[2] -= 0.001f;
		_objPos2[2] += 0.001f;
		if (_objPos1[2] <= 0.0f)
		{
			_CenterSwitch = true;
		}
	}
	else
	{
		_objPos1[2] += 0.001f;
		_objPos2[2] -= 0.001f;
		if (_objPos1[2] >= 0.8f)
		{
			_CenterSwitch = false;
			_objPos1[2] = 0.8f;
			_objPos2[2] = -0.8f;
			_animType = ANIM_NONE;
		}
	}
	

	_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
	_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);

}

void Ex17::CrossAnim()
{
	_objPos1[2] -= 0.001f;
	_objPos2[2] += 0.001f;

	_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
	_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);

	if (_objPos1[2] <= -0.8f)
	{
		_objPos1[2] = 0.8f;
		_objPos2[2] = -0.8f;
		_animType = ANIM_NONE;
	}

}

void Ex17::RotateAnim()
{
	glm::mat4 rotateMatrix = GET_SINGLE(TransformManager).GetRotateMatrix(0.2f, Y_AXIS);

	_rotateDegree += 0.2f;

	_objMat1 = rotateMatrix * _objMat1;
	_objMat2 = rotateMatrix * _objMat2;

	if (_rotateDegree >= 180.0f)
	{
		_objPos1[2] = 0.8f;
		_objPos2[2] = -0.8f;
		_rotateDegree = 0.0f;
		_animType = ANIM_NONE;
	}

}

void Ex17::UpDownAnim()
{
	if(UpDownSwitch == false)
	{
		_objPos1 += glm::vec3(0.0f, 0.001f, -0.001f);
		_objPos2 += glm::vec3(0.0f, -0.001f, 0.001f);
		if (_objPos1[2] <= 0.0)
		{
			UpDownSwitch = true;
		}
	}
	else
	{
		_objPos1 += glm::vec3(0.0f, -0.001f, -0.001f);
		_objPos2 += glm::vec3(0.0f, 0.001f, 0.001f);
	}

	_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos1);
	_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(_objPos2);

	if (_objPos1[2] <= -0.8f)
	{
		UpDownSwitch = false;
		_objPos1[2] = 0.8f;
		_objPos2[2] = -0.8f;
		_animType = ANIM_NONE;
	}

}

void Ex17::RenderWorld()
{
	if (_obj1 == nullptr)
	{
		_obj1 = new Objects(OBJ_CUBE, { 0.0f, 0.0f , 0.0f }, 0.15);
	}

	if (_obj2 == nullptr)
	{
		_obj2 = new Objects(QOBJ_SPHERE, { 0.0f, 0.0f, 0.0f }, 0.3, GL_LINES, {0.0f, 0.0f, 0.0f});
	}

	glEnable(GL_CULL_FACE);

	glm::mat4 objMatUse1 = _worldMat * _objMat1;
	glm::mat4 objMatUse2 = _worldMat * _objMat2;

	if (_obj1 != nullptr)
	{
		GET_SINGLE(TransformManager).Bind(objMatUse1);
		_obj1->Render();
	}

	if (_obj2 != nullptr)
	{
		GET_SINGLE(TransformManager).Bind(objMatUse2);
		_obj2->Render();
	}

	
	if (_animType == ANIM_SPIRAL)
	{
		GET_SINGLE(TransformManager).Bind(_worldMat);
		glBindVertexArray(_spiralVAO->GetVAOHandle());
		glLineWidth(1.0);
		for (int i = 0; i < (256 / 3) - 1; i++)
		{
			glDrawArrays(GL_LINES, i, 2);
		}
	}
}

void Ex17::MakeSpiral2D()
{
	Coord SpiralPoint = { 0.0f, 0.0f, 0.0f };
	float radius = 0.0f;
	float SpiralDegree = 0.0f;

	for(int i = 0; i < 256; i += 3)
	{
		SpiralPoint = { radius * glm::cos(SpiralDegree), 0.0f, radius * glm::sin(SpiralDegree) };
		_spiralVBuf[i] = SpiralPoint.x;
		_spiralVBuf[i+1] = SpiralPoint.y;
		_spiralVBuf[i+2] = SpiralPoint.z;
		radius += 0.013f;
		SpiralDegree += 0.3;
	}
	memset(_spiralCBuf, 0.0f, sizeof(float) * 256);

	_spiralVAO = new VAO(_spiralVBuf, _spiralCBuf, 256);
	
}

void Ex17::Reset()
{
	_objMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix({ 0.0f, 0.f, 0.8f });
	_objMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix({ 0.0f, 0.0f, -0.8f });

	delete _obj1;
	delete _obj2;

	_obj1 = new Objects(OBJ_CUBE, { 0.0f, 0.0f , 0.0f }, 0.15);


	_objPos1 = _originPos1;
	_objPos2 = _originPos2;

	_rotateDegree = 0.0f;

	UpDownSwitch = false;
	_CenterSwitch = false;
}

void Ex17::SetOrigin()
{
	_originPos1 = _objPos1;
	_originPos2 = _objPos2;
	

}
