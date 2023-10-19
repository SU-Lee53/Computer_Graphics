#include "pch.h"
#include "Ex18.h"

Ex18::Ex18()
{
	InitEx();
}

Ex18::~Ex18()
{
}

void Ex18::InitEx()
{
	_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS)
		* GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, Y_AXIS);

	for (int i = 0; i < 6; i++)
	{
		_cube[i] = nullptr;
		_cubeMat[i] = glm::mat4(1.0f);

		if (i < 4)
		{
			_tetra[i] = nullptr;
			_tetraMat[i] = glm::mat4(1.0f);
		}
	}

	_camera = new Camera(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -2.0f);
}

void Ex18::drawScene()
{
	_camera->Bind();
	_projection->Bind();
	SetBackground({1.0f, 1.0f, 1.0f});

	KeyboardUpdate();
	
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat);
	DrawAxis();

	Render();


	glutSwapBuffers();
	glutPostRedisplay();
}

void Ex18::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex18::Render()
{
	Objects* t1 = new Objects(OBJ_PLANE_TRIANGLE, { 0.f, 0.f, 0.f }, 0.5);
	Objects* t2 = new Objects(OBJ_PLANE_RECT, { 0.f, 0.f, 0.f }, 0.5);



	t2->Render();

	glm::mat4 tm = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.5f ,0.5f)) * GET_SINGLE(TransformManager).GetRotateMatrix(60.0f, X_AXIS);
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * tm);
	t1->Render();
	degTest += 0.5f;

	delete t1;
	delete t2;

}
