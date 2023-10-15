#include "pch.h"
#include "Ex15.h"

Ex15::Ex15()
{
	InitEx();
}

Ex15::~Ex15()
{
}

void Ex15::InitEx()
{
	tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(30.0f, X_AXIS) 
			* TransformManager::GetInstance().GetRotateMatrix(30.0f, Y_AXIS);

	Reset();
}

void Ex15::drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MouseUpdate();
	KeyboardUpdate();
	SpecialKeyUpdate();

	TransformManager::GetInstance().BindTransformMatrix(&tMatrix);
	DrawAxis();
	RenderWorld();

	glutSwapBuffers();
}

void Ex15::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex15::KeyboardUpdate()
{
	KeyboardState* kState = InputManager::GetInstance().DequeueKeyboardBuf();

	if (kState == nullptr)
		return;

	switch (kState->key)
	{
	case'c':
		if (_obj != nullptr)
			delete _obj;

		_obj = new Objects(OBJ_CUBE, { 0,0 }, 0.3f);
		break;

	case 'p':
		if (_obj != nullptr)
			delete _obj;

		_obj = new Objects(OBJ_PYRAMID, { 0,0 }, 0.3f);
		break;

	case 'h':
		if (cullMode == true)
		{
			cout << "CULL_MODE OFF" << endl;
			cullMode = false;
		}
		else
		{
			cout << "CULL_MODE ON" << endl;
			cullMode = true;
		}
		break;

	case 'w':
		if (renderMode == true)
		{
			cout << "Wireframe Mode ON" << endl;
			renderMode = false;
		}
		break;

	case 'W':
		if(renderMode == false)
		{
			cout << "Wireframe Mode OFF" << endl;
			renderMode = true;
		}
		break;
	
	case 'x':
		if (rxSwitch == false)
		{
			rxSwitch = true;
		}
		else
		{
			rxSwitch = false;
		}

		if (rxMode == false)
		{
			rxMode = true;
		}
		break;

	case 'X':
		if (rxSwitch == false)
		{
			rxSwitch = true;
		}
		else
		{
			rxSwitch = false;
		}

		if (rxMode == true)
		{
			rxMode = false;
		}
		break;

	case 'y':
		if (rySwitch == false)
		{
			rySwitch = true;
		}
		else
		{
			rySwitch = false;
		}

		if (ryMode == false)
		{
			ryMode = true;
		}
		break;

	case 'Y':
		if (rySwitch == false)
		{
			rySwitch = true;
		}
		else
		{
			rySwitch = false;
		}

		if (ryMode == true)
		{
			ryMode = false;
		}
		break;

	case 's':
		Reset();
		break;
	}
	delete kState;
	
	

}

void Ex15::SpecialKeyUpdate()
{
	SpecialState* sState = InputManager::GetInstance().DequeueSpecialKeyBuf();
	if (sState == nullptr)
		return;

	switch (sState->key)
	{
	case GLUT_KEY_UP:
	{
		glm::vec3 dir = glm::vec3(0.f, 0.02f, 0.f);
		tMatrix = tMatrix * TransformManager::GetInstance().GetTranslateMatrix(dir);
		break;
	}

	case GLUT_KEY_DOWN:
	{
		glm::vec3 dir = glm::vec3(0.f, -0.02f, 0.f);
		tMatrix = tMatrix * TransformManager::GetInstance().GetTranslateMatrix(dir);
		break;
	}
	case GLUT_KEY_LEFT:
	{
		glm::vec3 dir = glm::vec3(0.02f, 0.f, 0.f);
		tMatrix = tMatrix * TransformManager::GetInstance().GetTranslateMatrix(dir);
		break;
	}

	case GLUT_KEY_RIGHT:
	{
		glm::vec3 dir = glm::vec3(-0.02f, -0.f, 0.f);
		tMatrix = tMatrix * TransformManager::GetInstance().GetTranslateMatrix(dir);
		break;
	}
	}
	delete sState;
}

void Ex15::RenderWorld()
{
	if (cullMode == true)
	{
		glEnable(GL_CULL_FACE);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	if (renderMode == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	if (rxSwitch == true)
	{
		if (rxMode == true)
		{
			tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(0.04f, X_AXIS);
		}
		else
		{
			tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(-0.04f, X_AXIS);
		}
	}

	if (rySwitch == true)
	{
		if (ryMode == true)
		{
			tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(0.04f, Y_AXIS);
		}
		else
		{
			tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(-0.04f, Y_AXIS);
		}
	}

	_obj->Render();
}

void Ex15::Reset()
{
	tMatrix = unit * TransformManager::GetInstance().GetRotateMatrix(30.0f, X_AXIS)
		* TransformManager::GetInstance().GetRotateMatrix(30.0f, Y_AXIS);

	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	rxSwitch = false;
	rySwitch = false;
	rxMode = true;
	ryMode = true;
}

