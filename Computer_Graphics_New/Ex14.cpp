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
	tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(30.0f, X_AXIS);
	tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(30.0f, Y_AXIS);
}

void Ex14::drawScene()
{
	glClearColor(_Background.Red, _Background.Green, _Background.Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Update();

	unsigned int shaderID = Core::GetInstance().GetShaderID();
	glUseProgram(shaderID);

	tMatrix = tMatrix * TransformManager::GetInstance().GetRotateMatrix(0.03f, Y_AXIS);

	unsigned int uniformLocation = glGetUniformLocation(shaderID, "transform");
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(tMatrix));

	DrawAxis();

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

void Ex14::MouseUpdate()
{
	_mouseState = InputManager::GetInstance().DequeueMouseBuf();

	if (_mouseState == nullptr)
		return;
	else
	{
		if(_mouseState->button == GLUT_LEFT_BUTTON && _mouseState->state == GLUT_DOWN())
		_obj = new Objects(OBJ_TETRAHEDRON, { 0,0 }, 0.2);
		delete _mouseState;
	}
}
