#include "pch.h"
#include "Ex14.h"


Ex14::Ex14()
{
	InitEx();
}

Ex14::~Ex14()
{

}

void Ex14::InitEx()
{
	tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(20.0f, X_AXIS);
	tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(20.0f, Y_AXIS);
}

void Ex14::drawScene()
{
	glClearColor(_Background.Red, _Background.Green, _Background.Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MouseUpdate();
	KeyboardUpdate();

	TransformManager::GetInstance().BindTransformMatrix(&tMatrix);

	DrawAxis();

	RenderWorld();

	glutSwapBuffers();
}

void Ex14::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex14::MouseUpdate()
{
	_mouseState = InputManager::GetInstance().DequeueMouseBuf();

	if (_mouseState == nullptr)
		return;
}

void Ex14::KeyboardUpdate()
{
	_keyState = InputManager::GetInstance().DequeueKeyboardBuf();

	if (_keyState == nullptr)
		return;
	
	switch (_keyState->key)
	{
	case '1':
		renderMode = 1;
		break;

	case '2':
		renderMode = 2;
		break;

	case '3':
		renderMode = 3;
		break;

	case '4':
		renderMode = 4;
		break;

	case '5':
		renderMode = 5;
		break;

	case '6':
		renderMode = 6;
		break;

	case '7':
		renderMode = 7;
		break;

	case '8':
		renderMode = 8;
		break;

	case '9':
		renderMode = 9;
		break;

	case '0':
		renderMode = 0;
		break;

	case 'a':
		tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(3.0f, Y_AXIS);
		break;

	case 'd':
		tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(-3.0f, Y_AXIS);
		break;
	default:
		return;

	
	}

	delete _keyState;
	glutPostRedisplay();
}

void Ex14::RenderWorld()
{
	switch (renderMode)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	{
		if (_obj != nullptr)
			delete _obj;

		_obj = new Objects(OBJ_CUBE, { 0,0 }, 0.2);
		unsigned int start = renderMode * 6 - 6;
		unsigned int elementBuf[6];
		memcpy(elementBuf, &_obj->GetVAO().GetElementBuffer()[start], sizeof(unsigned int) * 6);
		_obj->GetVAO().ChangeElementBuffer(elementBuf, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		break;
	}

	case 7:
	case 8:
	case 9:
	case 0:
		if (_obj != nullptr)
			delete _obj;

		int faceNum = renderMode;
		if (faceNum > 0)
			faceNum -= 5;
		else
			faceNum += 1;

		_obj = new Objects(OBJ_TETRAHEDRON, { 0,0 }, 0.2);
		unsigned int start = faceNum * 3 - 3;
		unsigned int elementBuf[3];
		memcpy(elementBuf, &_obj->GetVAO().GetElementBuffer()[start], sizeof(unsigned int) * 3);
		_obj->GetVAO().ChangeElementBuffer(elementBuf, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		break;
	}

}


