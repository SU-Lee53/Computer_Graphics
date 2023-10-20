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
	_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(30.0f, X_AXIS)
		* GET_SINGLE(TransformManager).GetRotateMatrix(30.0f, Y_AXIS);

	for (int i = 0; i < 6; i++)
	{
		_cubeMat[i] = glm::mat4(1.0f);

		if (i < 4)
		{
			_tetraMat[i] = glm::mat4(1.0f);
		}
	}

	_camera = new Camera(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -2.0f);
}

void Ex18::drawScene()
{
	// 월드 좌표, 카메라, 투영 바인드
	_camera->Bind();
	_projection->Bind();
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat);

	// 화면 리셋
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 업데이트
	KeyboardUpdate();
	AnimUpdate();

	// 렌더링
	DrawAxis();
	Render();


	// 스왑
	glutSwapBuffers();

}

void Ex18::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex18::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();

	if (ks == nullptr)
		return;

	switch (ks->key)
	{
	case 'h':
		if (!_depthTestMode)
			_depthTestMode = true;
		else
			_depthTestMode = false;


		break;
		
	case 'y':
		if (!_yRotate)
			_yRotate = true;
		else
			_yRotate = false;

		break;
		
	case 't':
		if (!_TopRotate)
			_TopRotate = true;
		else
			_TopRotate = false;

		break;
		
	case 'f':
		if (!_frontOpen)
			_frontOpen = true;
		else
			_frontOpen = false;

		break;
		
	case 's':
		if (!_sideOpen)
			_sideOpen = true;
		else
			_sideOpen = false;

		break;
		
	case 'b':
		if (!_backOpen)
			_backOpen = true;
		else
			_backOpen = false;

		break;

	}

	delete ks;
}

void Ex18::AnimUpdate()
{
	if (_depthTestMode)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	if (_yRotate)
	{
		_yrotateMat = GET_SINGLE(TransformManager).GetRotateMatrix(_yRotateDegree, Y_AXIS);
		_yRotateDegree += 0.05;
	}

	if (_TopRotate)
	{
		_cubeMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, -0.5, 0.0));
		_cubeMat[0] = GET_SINGLE(TransformManager).GetRotateMatrix(_topRotateDegree, X_AXIS) * _cubeMat[0];
		_cubeMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, 0.5, 0.0)) * _cubeMat[0];
		_topRotateDegree += 0.05;
	}

	if (_frontOpen)
	{
		if (_frontOpenDegree <= 90.0f)
		{
			_frontOpenDegree += 0.05;
			_cubeMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, 0.5, -0.5));
			_cubeMat[2] = GET_SINGLE(TransformManager).GetRotateMatrix(_frontOpenDegree, X_AXIS) * _cubeMat[2];
			_cubeMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, -0.5, 0.5)) * _cubeMat[2];
		}
	}
	else
	{
		if (_frontOpenDegree >= 0.0f)
		{
			_frontOpenDegree -= 0.05;
			_cubeMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, 0.5, -0.5));
			_cubeMat[2] = GET_SINGLE(TransformManager).GetRotateMatrix(_frontOpenDegree, X_AXIS) * _cubeMat[2];
			_cubeMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, -0.5, 0.5)) * _cubeMat[2];
		}
	}

	if (_sideOpen)
	{
		if (_sideSlideDistance <= 1.0f)
		{
			_sideSlideDistance += 0.001;
			_cubeMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _sideSlideDistance, 0.0f));
			_cubeMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _sideSlideDistance, 0.0f));
		}
	}
	else
	{
		if (_sideSlideDistance >= 0.0f)
		{
			_cubeMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _sideSlideDistance, 0.0f));
			_cubeMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _sideSlideDistance, 0.0f));
			_sideSlideDistance -= 0.001;
		}
	}
	
	if (_backOpen)
	{
		if (_backScaleSize >= 0.0f)
		{
			_backScaleSize -= 0.001;
			_cubeMat[4] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.f, -0.5f)) *
				GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(_backScaleSize, _backScaleSize, _backScaleSize))
					* GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.f, 0.5f));
		}
	}
	else
	{
		if (_backScaleSize <= 1.0f)
		{
			_cubeMat[4] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.f, -0.5f)) *
				GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(_backScaleSize, _backScaleSize, _backScaleSize))
				* GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.f, 0.5f));
			_backScaleSize += 0.001;
		}
	}


	glutPostRedisplay();
}

void Ex18::Render()
{
	if (_cube == nullptr)
	{
		_cube = new Objects(OBJ_CUBE, { 0,0,0 }, 0.5f, NON_INDEXED);
	}

	RenderCube();
}

void Ex18::RenderCube()
{
	glBindVertexArray(_cube->GetVAO().GetVAOHandle());

	int start;

	// 0. 윗면
	start = 0;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _cubeMat[0]);
	glDrawArrays(GL_TRIANGLES, start, 6);

	// 1. 왼쪽면
	start += 6;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _cubeMat[1]);
	glDrawArrays(GL_TRIANGLES, start, 6);

	// 2. 앞면
	start += 6;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _cubeMat[2]);
	glDrawArrays(GL_TRIANGLES, start, 6);

	// 3. 오른쪽면
	start += 6;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _cubeMat[3]);
	glDrawArrays(GL_TRIANGLES, start, 6);

	// 4. 뒷면
	start += 6;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _cubeMat[4]);
	glDrawArrays(GL_TRIANGLES, start, 6);

	// 5. 바닥면
	start += 6;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _cubeMat[5]);
	glDrawArrays(GL_TRIANGLES, start, 6);





}
