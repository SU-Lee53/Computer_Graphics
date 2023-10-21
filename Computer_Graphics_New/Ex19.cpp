#include "pch.h"
#include "Ex19.h"

Ex19::Ex19()
{
	InitEx();
}

Ex19::~Ex19()
{
}

void Ex19::InitEx()
{
	_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(10.0f, X_AXIS);
	_orbit1 = glm::mat4(1.0f);
	_orbit2 = GET_SINGLE(TransformManager).GetRotateMatrix(45.0f, Z_AXIS);
	_orbit3 = GET_SINGLE(TransformManager).GetRotateMatrix(-45.0f, Z_AXIS);

	_parentMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(3.0f, 0.0f, 0.0f));
	_parentMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -3.0f));
	_parentMat3 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 3.0f));

	_camera = new Camera(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
}

void Ex19::drawScene()
{
	_camera->Bind();
	_projection->Bind();
	yRot = GET_SINGLE(TransformManager).GetRotateMatrix(yDeg, Y_AXIS);
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * yRot);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	DrawAxis(1.0f);

	Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Ex19::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex19::Render()
{
	if (_orbit == nullptr)
	{
		SetOrbit();
		SetPlanet();
	}

	RenderOrbit();
	RenderPlanet();
	



	yDeg += 0.05f;
}

void Ex19::SetOrbit()
{
	float degree = 0.0f;
	int idx = 0;
	while (degree <= 360.0f)
	{
		Coord pos = { 0.0f, 0.0f, 0.0f };
		pos.x = _orbitRadius * glm::cos(glm::radians(degree));
		pos.z = _orbitRadius * glm::sin(glm::radians(degree));
		
		_orbitVBuf[idx] = pos.x;
		_orbitVBuf[idx + 1] = pos.y;
		_orbitVBuf[idx + 2] = pos.z;

		_orbitCBuf[idx] = 0.0f;
		_orbitCBuf[idx + 1] = 0.0f;
		_orbitCBuf[idx + 2] = 0.0f;

		degree += 5.0f;
		idx += 3;
	}

	_orbit = new VAO(_orbitVBuf, _orbitCBuf, idx);

}

void Ex19::SetPlanet()
{
	// 1. 조상: 중심점, 부모행성 3개를 자식으로 가짐
	_ancestor = new Objects(QOBJ_SPHERE, {0.0f, 0.0f, 0.0f}, 1.0f, GLU_LINE, {0.0f, 0.0f, 1.0f});

	// 2. 부모: 조상 주변을 돌고, 자식 행성을 하나씩 가짐
	_parent1 = new Objects(QOBJ_SPHERE, { 0.0f, 0.0f, 0.0f }, 0.3f, GLU_LINE, { 0.0f, 0.0f, 1.0f });
	_parent2 = new Objects(QOBJ_SPHERE, { 0.0f, 0.0f, 0.0f }, 0.3f, GLU_LINE, { 0.0f, 0.0f, 1.0f });
	_parent3 = new Objects(QOBJ_SPHERE, { 0.0f, 0.0f, 0.0f }, 0.3f, GLU_LINE, { 0.0f, 0.0f, 1.0f });


}

void Ex19::RenderOrbit()
{
	glBindVertexArray(_orbit->GetVAOHandle());
	int bufSize = _orbit->GetVertexCount();

	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _orbit1);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}
	
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _orbit2);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}
	
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _orbit3);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}


}

void Ex19::RenderPlanet()
{
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _ancestorMat * yRot);
	_ancestor->Render();
	
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * yRot * _parentMat1 * yRot);
	_parent1->Render();											 

	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * (_orbit2 * yRot) * _parentMat2 * yRot);
	_parent2->Render();											 

	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * (_orbit3 * yRot) * _parentMat3 * yRot);
	_parent3->Render();



}
