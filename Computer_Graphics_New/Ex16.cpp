#include "pch.h"
#include "Ex16.h"

Ex16::Ex16()
{
	InitEx();
}

Ex16::~Ex16()
{
}

void Ex16::InitEx()
{
	_worldMat = TransformManager::GetInstance().GetRotateMatrix(30.0f, X_AXIS)
		* TransformManager::GetInstance().GetRotateMatrix(30.0f, Y_AXIS);

	_objMat1 = TransformManager::GetInstance().GetTranslateMatrix({ 0.0f, 0.f, 0.5f });
	_objMat2 = TransformManager::GetInstance().GetTranslateMatrix({ 0.0f, 0.0f, -0.5f });
	_objPos1 = _objPos1 * glm::vec3(0.0f, 0.0f, 0.5f);
	_objPos2 = _objPos2 * glm::vec3(0.0f, 0.0f, -0.5f);

	projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0));

	
}

void Ex16::drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	KeyboardUpdate();
	SpecialKeyUpdate();
	AnimationUpdate();

	unsigned int projectionLocation = glGetUniformLocation(Core::GetInstance().GetShaderID(), "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	TransformManager::GetInstance().BindTransformMatrix(&_worldMat);
	DrawAxis();

	RenderWorld();

	glutSwapBuffers();
}

void Ex16::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex16::KeyboardUpdate()
{
	KeyboardState* kState = InputManager::GetInstance().DequeueKeyboardBuf();
	if (kState == nullptr)
		return;

	switch (kState->key)
	{
	case 'x':
		if (!rotateSwitch)
			rotateSwitch = true;
		else
			rotateSwitch = false;

		rotateDirection = true;
		rotateAxis = X_AXIS;
		break;

	case 'X':
		if (!rotateSwitch)
			rotateSwitch = true;
		else
			rotateSwitch = false;

		rotateDirection = false;
		rotateAxis = X_AXIS;
		break;

	case 'y':
		if (!rotateSwitch)
			rotateSwitch = true;
		else
			rotateSwitch = false;

		rotateDirection = true;
		rotateAxis = Y_AXIS;
		break;

	case 'Y':
		if (!rotateSwitch)
			rotateSwitch = true;
		else
			rotateSwitch = false;

		rotateDirection = false;
		rotateAxis = Y_AXIS;
		break;

	case '1':
		rotateMode = MODE1;
		break;

	case '2':
		rotateMode = MODE2;
		break;

	case '3':
		rotateMode = BOTH;


	case 'r':
		if (!revolutionSwitch)
			revolutionSwitch = true;
		else
			revolutionSwitch = false;

		revolutionDirection = true;
		break;

	case 'R':
		if (!revolutionSwitch)
			revolutionSwitch = true;
		else
			revolutionSwitch = false;

		revolutionDirection = false;
		break;
	}



	delete kState;
}


void Ex16::AnimationUpdate()
{
	glm::mat4 rotation = glm::mat4(1.0f);
	

	if (rotateSwitch == true)
	{
		if (rotateAxis == X_AXIS)
		{
			if (rotateDirection == true)
			{
				rotation = rotation * TransformManager::GetInstance().GetRotateMatrix(0.5f, X_AXIS);
			}
			else
			{
				rotation = rotation * TransformManager::GetInstance().GetRotateMatrix(-0.5f, X_AXIS);
			}
		}
		else if (rotateAxis == Y_AXIS)
		{
			if (rotateDirection == true)
			{
				rotation = rotation * TransformManager::GetInstance().GetRotateMatrix(0.5f, Y_AXIS);
			}
			else
			{
				rotation = rotation * TransformManager::GetInstance().GetRotateMatrix(-0.5f, Y_AXIS);
			}
		}
		switch (rotateMode)
		{
		case MODE1:
			_objMat1 = _objMat1 * rotation;
			break;

		case MODE2:
			_objMat2 = _objMat2 * rotation;
			break;

		case BOTH:
			_objMat1 = _objMat1 * rotation;
			_objMat2 = _objMat2 * rotation;
			break;
		}
	
	}

	glm::mat4 revolution1 = glm::mat4(1.0f);
	glm::mat4 revolution2 = glm::mat4(1.0f);
	glm::vec3 axis = TransformManager::GetInstance().GetRotateMatrix(30.0f, Y_AXIS) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	if (revolutionSwitch)
	{
		if (revolutionDirection)
		{
			revolution1 = TransformManager::GetInstance().GetRotateMatrix(0.5f, Y_AXIS);
			_objPos1 = TransformManager::GetInstance().GetRotateMatrix(0.5f, Y_AXIS) * glm::vec4(_objPos1, 1.0f);
			_objPos2 = TransformManager::GetInstance().GetRotateMatrix(0.5f, Y_AXIS) * glm::vec4(_objPos2, 1.0f);
		}
		else
		{
			revolution1 = TransformManager::GetInstance().GetRotateMatrix(-0.5f, Y_AXIS);
			_objPos1 = glm::vec3(radius * glm::cos(glm::radians(-0.5f)), 0.0, radius * glm::sin(glm::radians(-0.05f)));
			_objPos2 = glm::vec3(radius * glm::cos(glm::radians(-0.5f)), 0.0, radius * glm::sin(glm::radians(-0.05f)));
		}
		
		glm::mat4 Tm1 = TransformManager::GetInstance().GetTranslateMatrix(_objPos1);
		glm::mat4 Tm2 = TransformManager::GetInstance().GetTranslateMatrix(_objPos2);

		_objMat1 = revolution1 * _objMat1;
		_objMat2 = revolution1 * _objMat2;

		

	}




	/*
	�̵���ķ� ���� -> ������ �Բ� ���� ����
	if (revolutionSwitch)
	{
		if (revolutionDirection)
		{
			float sin1 = glm::sin(glm::radians(revolutionDegree1));
			float cos1 = glm::cos(glm::radians(revolutionDegree1));
			glm::vec3 position1 = glm::vec3(radius * cos1, 0.0, radius * sin1);
			revolution1 = TransformManager::GetInstance().GetTranslateMatrix(position1);

			float sin2 = glm::sin(glm::radians(revolutionDegree2));
			float cos2 = glm::cos(glm::radians(revolutionDegree2));
			glm::vec3 position2 = glm::vec3(radius * cos2, 0.0, radius * sin2);
			revolution2 = TransformManager::GetInstance().GetTranslateMatrix(position2);	
			revolutionDegree1 += 0.04f;
			revolutionDegree2 += 0.04f;
		}
		else
		{
			float sin1 = glm::sin(glm::radians(revolutionDegree1));
			float cos1 = glm::cos(glm::radians(revolutionDegree1));
			glm::vec3 position1 = glm::vec3(radius * cos1, 0.0, radius * sin1);
			revolution1 = TransformManager::GetInstance().GetTranslateMatrix(position1);

			float sin2 = glm::sin(glm::radians(revolutionDegree2));
			float cos2 = glm::cos(glm::radians(revolutionDegree2));
			glm::vec3 position2 = glm::vec3(radius * cos2, 0.0, radius * sin2);
			revolution2 = TransformManager::GetInstance().GetTranslateMatrix(position2);
			revolutionDegree1 -= 0.04f;
			revolutionDegree2 -= 0.04f;
		}

		_objMat1 = _worldMat * revolution1;
		_objMat2 = _worldMat * revolution2;
	}

	*/
}

void Ex16::RenderWorld()
{
	if (_obj1 == nullptr)
	{
		_obj1 = new Objects(OBJ_CUBE, { 0.0f, 0.0f , 0.0f }, 0.15);
	}

	if (_obj2 == nullptr)
	{
		_obj2 = new Objects(QOBJ_SPHERE, { 0.0f, 0.0f, 0.0f }, 0.3);
	}

	glEnable(GL_CULL_FACE);

	glm::mat4 objMatUse1 = _worldMat * _objMat1;
	glm::mat4 objMatUse2 = _worldMat * _objMat2;

	if(_obj1 != nullptr)
	{
		
		TransformManager::GetInstance().BindTransformMatrix(&objMatUse1);
		_obj1->Render();
	}
	
	if(_obj2 != nullptr)
	{
		TransformManager::GetInstance().BindTransformMatrix(&objMatUse2);
		_obj2->Render();
	}

}
