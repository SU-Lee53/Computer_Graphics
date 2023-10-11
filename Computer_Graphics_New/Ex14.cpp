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
	
}

void Ex14::drawScene()
{
	glClearColor(_Background.Red, _Background.Green, _Background.Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(Core::GetInstance().GetShaderID());
	
	Update();

	if (_obj != nullptr)
	{
		_obj->Render();
	}

	glutSwapBuffers();
}

void Ex14::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex14::Update()
{
	MouseUpdate();
}

void Ex14::MouseUpdate()
{
	_mouseState = InputManager::GetInstance().DequeueMouseBuf();

	if (_mouseState == nullptr)
		return;
	else
	{
		if(_mouseState->button == GLUT_LEFT_BUTTON && _mouseState->state == GLUT_DOWN())
		_obj = new Objects(OBJ_TRIANGLE, { _mouseState->pos.x, _mouseState->pos.y }, 0.2);
		delete _mouseState;
	}
}
