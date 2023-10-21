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
	_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(20.0f, X_AXIS);
	_orbit1 = glm::mat4(1.0f);
	_orbit2 = GET_SINGLE(TransformManager).GetRotateMatrix(45.0f, Z_AXIS);
	_orbit3 = GET_SINGLE(TransformManager).GetRotateMatrix(-45.0f, Z_AXIS);

	_parentMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(3.0f, 0.0f, 0.0f));
	_parentMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -3.0f));
	_parentMat3 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 3.0f));
	
	_childMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(4.0f, 0.0f, 0.0f));
	_childMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -4.0f));
	_childMat3 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 4.0f));
	
	_lastMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(1.0f, 0.0f, 0.0f));
	_lastMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -1.0f));
	_lastMat3 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 1.0f));

	_scaleMat1 = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.4f, 0.4f, 0.4f));
	_scaleMat2 = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.2f, 0.2f, 0.2f));

	_camera = new Camera(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -8.0f);
}

void Ex19::drawScene()
{
	_camera->Bind();
	_projection->Bind();
	
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * yRot1);
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
	if (_bigOrbit == nullptr)
	{
		SetOrbit();
		SetPlanet();
	}

	RenderOrbit();
	RenderPlanet();
	


	yRot1 = GET_SINGLE(TransformManager).GetRotateMatrix(yDeg1, Y_AXIS);
	yDeg1 += 0.05f;
	
	yRot2 = GET_SINGLE(TransformManager).GetRotateMatrix(yDeg2, Y_AXIS);
	yDeg2 += 0.03f;
	
	yRot3 = GET_SINGLE(TransformManager).GetRotateMatrix(yDeg3, Y_AXIS);
	yDeg3 += 0.07f;

}

void Ex19::SetOrbit()
{
	float degree = 0.0f;
	int idx = 0;
	while (degree <= 360.0f)
	{
		Coord pos = { 0.0f, 0.0f, 0.0f };
		pos.x = _bigOrbitRadius * glm::cos(glm::radians(degree));
		pos.z = _bigOrbitRadius * glm::sin(glm::radians(degree));
		
		_bigOrbitVBuf[idx] = pos.x;
		_bigOrbitVBuf[idx + 1] = pos.y;
		_bigOrbitVBuf[idx + 2] = pos.z;

		_bigOrbitCBuf[idx] = 0.0f;
		_bigOrbitCBuf[idx + 1] = 0.0f;
		_bigOrbitCBuf[idx + 2] = 0.0f;

		degree += 10.0f;
		idx += 3;
	}

	_bigOrbit = new VAO(_bigOrbitVBuf, _bigOrbitCBuf, idx);

	degree = 0.0f;
	idx = 0;
	while (degree <= 360.0f)
	{
		Coord pos = { 0.0f, 0.0f, 0.0f };
		pos.x = _smallOrbitRadius * glm::cos(glm::radians(degree));
		pos.z = _smallOrbitRadius * glm::sin(glm::radians(degree));

		_smallOrbitVBuf[idx] = pos.x;
		_smallOrbitVBuf[idx + 1] = pos.y;
		_smallOrbitVBuf[idx + 2] = pos.z;

		_smallOrbitCBuf[idx] = 0.0f;
		_smallOrbitCBuf[idx + 1] = 0.0f;
		_smallOrbitCBuf[idx + 2] = 0.0f;

		degree += 10.0f;
		idx += 3;
	}

	_smallOrbit = new VAO(_smallOrbitVBuf, _smallOrbitCBuf, idx);
}

void Ex19::SetPlanet()
{
	// 1. 조상: 중심점, 부모행성 3개를 자식으로 가짐
	_planet = new Objects(QOBJ_SPHERE, {0.0f, 0.0f, 0.0f}, 1.0f, GLU_LINE, {0.0f, 0.0f, 1.0f});

}

void Ex19::RenderOrbit()
{
	glBindVertexArray(_bigOrbit->GetVAOHandle());
	int bufSize = _bigOrbit->GetVertexCount();

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
	
	glBindVertexArray(_smallOrbit->GetVAOHandle());
	bufSize = _smallOrbit->GetVertexCount();

	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * yRot2 * _parentMat1);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}
	
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * (_orbit2 * yRot2) * _parentMat2);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}
	
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * (_orbit3 * yRot2) * _parentMat3);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}

}

void Ex19::RenderPlanet()
{
	glm::mat4 currMat = _worldMat * _ancestorMat * yRot1;
	GET_SINGLE(TransformManager).BindTransformMatrix(currMat);
	_planet->Render();
	
	// 부모;
	currMat = _worldMat * (_orbit1 * yRot2) * (_parentMat1 * yRot1) * _scaleMat1;
	GET_SINGLE(TransformManager).BindTransformMatrix(currMat);
	_planet->Render();

	currMat = _worldMat * (_orbit2 * yRot2) * (_parentMat2 * yRot1) * _scaleMat1;
	GET_SINGLE(TransformManager).BindTransformMatrix(currMat);
	_planet->Render();

	currMat = _worldMat * (_orbit3 * yRot2) * (_parentMat3 * yRot1) * _scaleMat1;
	GET_SINGLE(TransformManager).BindTransformMatrix(currMat);
	_planet->Render();
	
	// 자식
	currMat = _worldMat * (_orbit1 * yRot2) * _parentMat1 * (yRot3) * (_lastMat1 * yRot1) * _scaleMat2;
	GET_SINGLE(TransformManager).BindTransformMatrix(currMat);
	_planet->Render();

	currMat = _worldMat * (_orbit2 * yRot2) * _parentMat2 * (yRot3) * (_lastMat2 * yRot1) * _scaleMat2;
	GET_SINGLE(TransformManager).BindTransformMatrix(currMat);
	_planet->Render();

	currMat = _worldMat * (_orbit3 * yRot2) * _parentMat3 * (yRot3) * (_lastMat3 * yRot1) * _scaleMat2;
	GET_SINGLE(TransformManager).BindTransformMatrix(currMat);
	_planet->Render();



}
