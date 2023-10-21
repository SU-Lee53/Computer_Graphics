#include "pch.h"
#include "Ex20.h"

Ex20::Ex20()
{
	InitEx();
}

Ex20::~Ex20()
{
}

void Ex20::InitEx()
{
	_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(30.0f, X_AXIS) * GET_SINGLE(TransformManager).GetRotateMatrix(30.0f, Y_AXIS);


	_camera = new Camera(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
}

void Ex20::drawScene()
{
	_shaderID = GET_SINGLE(Core).GetShaderID();
	glUseProgram(_shaderID);

	_projection->Bind(_shaderID);
	_camera->Bind(_shaderID);
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat, _shaderID);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Ex20::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex20::Render()
{
	if (_floor == nullptr)
	{
		_floor = new Objects(OBJ_PLANE_RECT, { 0, 0, 0 }, 3.0f);
		MakeCrane();
	}

	glEnable(GL_DEPTH_TEST);

	_floor->Render();
	_crane[0]->Render();
	_crane[1]->Render();
	_crane[2]->Render();
	_crane[3]->Render();
	_crane[4]->Render();
	_crane[5]->Render();

}

void Ex20::MakeCrane()
{
	_crane[0] = new Objects(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.7f);
	_crane[1] = new Objects(-0.5f, 0.5f, 0.5f, -0.5f, 0.7f, 1.1f);
	_crane[2] = new Objects(-0.8f, 1.0f, -0.5f, 2.0f, 0.1f, 0.4f);
	_crane[3] = new Objects(0.5f, 1.0f, 0.8f, 2.0f, 0.1f, 0.4f);
	_crane[4] = new Objects(-0.4f, -0.1f, -0.2f, 0.1f, 1.1f, 2.0f);
	_crane[5] = new Objects(0.2f, -0.1f, 0.4f, 0.1f, 1.1f, 2.0f);

}
