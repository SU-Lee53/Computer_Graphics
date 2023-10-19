#include "pch.h"
#include "Ex14.h"
// inputManager와 VAO, VBO에서 메모리가 세고있는것으로 추정됨

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

	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	_projection = glm::translate(_projection, glm::vec3(0.0, 0.0, -2.0));
}

void Ex14::drawScene()
{
	glClearColor(_Background.Red, _Background.Green, _Background.Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MouseUpdate();
	KeyboardUpdate();

	unsigned int projectionLocation = glGetUniformLocation(Core::GetInstance().GetShaderID(), "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &_projection[0][0]);

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
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
		renderMode = static_cast<int>(_keyState->key) - 48;
		renderMode2 = __NONE;
		modeSwitch = true;
		break;

	case 'a':
		tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(3.0f, Y_AXIS);
		break;

	case 'd':
		tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(-3.0f, Y_AXIS);
		break;

	case 'c':
		if (_obj != nullptr)
			delete _obj;

		_obj = new Objects(OBJ_CUBE, { 0,0 }, 0.3f);

		SetRandomFace(CUBE);
		renderMode = -1;
		renderMode2 = CUBE;
		modeSwitch = false;
		break;

	case 't':
	{
		if (_obj != nullptr)
			delete _obj;

		_obj = new Objects(OBJ_TETRAHEDRON, { 0,0 }, 0.3f);

		SetRandomFace(TETRAHEDRON);
		renderMode = -1;
		renderMode2 = TETRAHEDRON;
		modeSwitch = false;
		break;
	}

	default:
		return;

	
	}

	delete _keyState;
	glutPostRedisplay();
}

void Ex14::RenderWorld()
{

	if(modeSwitch){
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

			_obj = new Objects(OBJ_CUBE, { 0,0 }, 0.3f);
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
		{
			if (_obj != nullptr)
				delete _obj;

			int faceNum = renderMode;
			if (faceNum > 0)
				faceNum -= 5;
			else
				faceNum += 1;

			_obj = new Objects(OBJ_TETRAHEDRON, { 0,0 }, 0.3f);
			unsigned int start = faceNum * 3 - 3;
			unsigned int elementBuf[3];
			memcpy(elementBuf, &_obj->GetVAO().GetElementBuffer()[start], sizeof(unsigned int) * 3);
			_obj->GetVAO().ChangeElementBuffer(elementBuf, 3);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

			break;
		}

		default:
			return;
		}
	}
	else
	{
		switch (renderMode2)
		{
		case TETRAHEDRON:
		{
			_obj->GetVAO().ChangeElementBuffer(elementBuf1, 3);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			
			_obj->GetVAO().ChangeElementBuffer(elementBuf2, 3);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			break;
		}

		case CUBE:
		{
			if (_obj != nullptr)
				delete _obj;

			_obj = new Objects(OBJ_CUBE, { 0,0 }, 0.3f);

			_obj->GetVAO().ChangeElementBuffer(elementBuf1, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			_obj->GetVAO().ChangeElementBuffer(elementBuf2, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		}

		case __NONE:
			return;
		}
	}

}

void Ex14::SetRandomFace(RenderMode2 mode)
{
	if(mode == TETRAHEDRON)
	{
		int face1 = ((rand() % 4) + 1) * 3 - 3;
		int face2;
		while (true)
		{
			face2 = ((rand() % 4) + 1) * 3 - 3;
			if (face2 != face1)
				break;
		}

		memcpy(elementBuf1, &_obj->GetVAO().GetElementBuffer()[face1], sizeof(unsigned int) * 3);
		memcpy(elementBuf2, &_obj->GetVAO().GetElementBuffer()[face2], sizeof(unsigned int) * 3);
	}
	else if (mode == CUBE)
	{
		int face1 = ((rand() % 6) + 1) * 6 - 6;
		int face2;
		while (true)
		{
			face2 = ((rand() % 6) + 1) * 6 - 6;
			if (face2 != face1)
				break;
		}

		memcpy(elementBuf1, &_obj->GetVAO().GetElementBuffer()[face1], sizeof(unsigned int) * 6);
		memcpy(elementBuf2, &_obj->GetVAO().GetElementBuffer()[face2], sizeof(unsigned int) * 6);
	}
}


