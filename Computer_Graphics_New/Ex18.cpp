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

		if (i < 5)
		{
			_pyramidMat[i] = glm::mat4(1.0f);
		}
	}

	_camera = new Camera(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
}

void Ex18::drawScene()
{
	// 월드 좌표, 카메라, 투영 바인드
	_camera->Bind();
	if (_perspective)
	{
		_projection->SetPerspectiveProjection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
		_projection->Bind();
	}
	else
	{
		_projection->SetOrthoProjection(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
		_projection->Bind();
	}
	
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat);

	// 화면 리셋
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 업데이트
	KeyboardUpdate();
	AnimUpdate();

	// 렌더링
	DrawAxis(2.0f);
	Render();


	// 스왑
	glutSwapBuffers();
	glutPostRedisplay();
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
	
	case 'c':
		if (!objType)
			objType = true;
		else
			objType = false;

		break;

	case 'o':
		_playReverse = false;
		_playOpen = true;
		if (!_openAll)
		{
			_openAll = true;
			_openOrder = 0;
		}
		else
		{
			_openAll = false;
			_openOrder = 3;
		}

		break;

	case 'r':
		_playOpen = false;
		_playReverse = true;
		if (!_reverseOpen)
			_reverseOpen = true;
		else
			_reverseOpen = false;

		break;

	case 'p':
		if (!_perspective)
			_perspective = true;
		else
			_perspective = false;
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
		_cubeMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, -_objSize, 0.0));
		_cubeMat[0] = GET_SINGLE(TransformManager).GetRotateMatrix(_topRotateDegree, X_AXIS) * _cubeMat[0];
		_cubeMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, _objSize, 0.0)) * _cubeMat[0];
		_topRotateDegree += 0.05;
	}

	if (_frontOpen)
	{
		if (_cubeFrontOpenDegree <= 90.0f)
		{
			_cubeFrontOpenDegree += 0.05;
			_cubeMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, _objSize, -_objSize));
			_cubeMat[2] = GET_SINGLE(TransformManager).GetRotateMatrix(_cubeFrontOpenDegree, X_AXIS) * _cubeMat[2];
			_cubeMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, -_objSize, _objSize)) * _cubeMat[2];
		}
	}
	else
	{
		if (_cubeFrontOpenDegree >= 0.0f)
		{
			_cubeFrontOpenDegree -= 0.05;
			_cubeMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, _objSize, -_objSize));
			_cubeMat[2] = GET_SINGLE(TransformManager).GetRotateMatrix(_cubeFrontOpenDegree, X_AXIS) * _cubeMat[2];
			_cubeMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0, -_objSize, _objSize)) * _cubeMat[2];
		}
	}

	if (_sideOpen)
	{
		if (_sideSlideDistance <= _objSize * 2)
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
			_cubeMat[4] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.f, -_objSize)) *
				GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(_backScaleSize, _backScaleSize, _backScaleSize))
					* GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.f, _objSize));
		}
	}
	else
	{
		if (_backScaleSize <= 1.0f)
		{
			_cubeMat[4] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.f, -_objSize)) *
				GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(_backScaleSize, _backScaleSize, _backScaleSize))
				* GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.f, 0.f, _objSize));
			_backScaleSize += 0.001;
		}
	}


	if (_playOpen && !_playReverse)
	{
		if(_openAll)
		{
			if(_openOrder == 0)
			{
				if (_leftOpenDegree <= 120.0f)
				{
					_leftOpenDegree += _openSpeed;
					_pyramidMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_objSize, (sqrt(3) * _objSize) / 2, 0.0f));
					_pyramidMat[0] = GET_SINGLE(TransformManager).GetRotateMatrix(_leftOpenDegree, Z_AXIS) * _pyramidMat[0];
					_pyramidMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-_objSize, -(sqrt(3) * _objSize) / 2, 0.0f)) * _pyramidMat[0];
				}
				else
					_openOrder++;
			}

			if (_openOrder == 1)
			{
				if (_frontOpenDegree <= 120.0f)
				{
					_frontOpenDegree += _openSpeed;
					_pyramidMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, (sqrt(3) * _objSize) / 2, -_objSize));
					_pyramidMat[1] = GET_SINGLE(TransformManager).GetRotateMatrix(_frontOpenDegree, X_AXIS) * _pyramidMat[1];
					_pyramidMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -(sqrt(3) * _objSize) / 2, _objSize)) * _pyramidMat[1];
				}
				else
					_openOrder++;
			}

			if (_openOrder == 2)
			{
				if (_rightOpenDegree >= -120.0f)
				{
					_rightOpenDegree -= _openSpeed;
					_pyramidMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-_objSize, (sqrt(3) * _objSize) / 2, 0.0f));
					_pyramidMat[2] = GET_SINGLE(TransformManager).GetRotateMatrix(_rightOpenDegree, Z_AXIS) * _pyramidMat[2];
					_pyramidMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_objSize, -(sqrt(3) * _objSize) / 2, 0.0f)) * _pyramidMat[2];
				}
				else
					_openOrder++;
			}

			if (_openOrder == 3)
			{
				if (_backOpenDegree >= -120.0f)
				{
					_backOpenDegree -= _openSpeed;
					_pyramidMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, (sqrt(3) * _objSize) / 2, _objSize));
					_pyramidMat[3] = GET_SINGLE(TransformManager).GetRotateMatrix(_backOpenDegree, X_AXIS) * _pyramidMat[3];
					_pyramidMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -(sqrt(3) * _objSize) / 2, -_objSize)) * _pyramidMat[3];
				}
				else
					_openOrder = 0;
			}
		}
		else
		{
			if (_openOrder == 0)
			{
				if (_leftOpenDegree >= 0.0f)
				{
					_leftOpenDegree -= _openSpeed;
					_pyramidMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_objSize, (sqrt(3) * _objSize) / 2, 0.0f));
					_pyramidMat[0] = GET_SINGLE(TransformManager).GetRotateMatrix(_leftOpenDegree, Z_AXIS) * _pyramidMat[0];
					_pyramidMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-_objSize, -(sqrt(3) * _objSize) / 2, 0.0f)) * _pyramidMat[0];
				}
				else
					_openOrder = 0;
			}

			if (_openOrder == 1)
			{
				if (_frontOpenDegree >= 0.0f)
				{
					_frontOpenDegree -= _openSpeed;
					_pyramidMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, (sqrt(3) * _objSize) / 2, -_objSize));
					_pyramidMat[1] = GET_SINGLE(TransformManager).GetRotateMatrix(_frontOpenDegree, X_AXIS) * _pyramidMat[1];
					_pyramidMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -(sqrt(3) * _objSize) / 2, _objSize)) * _pyramidMat[1];
				}
				else
					_openOrder--;
			}

			if (_openOrder == 2)
			{
				if (_rightOpenDegree <= 0.0f)
				{
					_rightOpenDegree += _openSpeed;
					_pyramidMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-_objSize, (sqrt(3) * _objSize) / 2, 0.0f));
					_pyramidMat[2] = GET_SINGLE(TransformManager).GetRotateMatrix(_rightOpenDegree, Z_AXIS) * _pyramidMat[2];
					_pyramidMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_objSize, -(sqrt(3) * _objSize) / 2, 0.0f)) * _pyramidMat[2];
				}
				else
					_openOrder--;
			}

			if (_openOrder == 3)
			{
				if (_backOpenDegree <= 0.0f)
				{
					_backOpenDegree += _openSpeed;
					_pyramidMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, (sqrt(3) * _objSize) / 2, _objSize));
					_pyramidMat[3] = GET_SINGLE(TransformManager).GetRotateMatrix(_backOpenDegree, X_AXIS) * _pyramidMat[3];
					_pyramidMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -(sqrt(3) * _objSize) / 2, -_objSize)) * _pyramidMat[3];
				}
				else
					_openOrder--;
			}

		}
	}
	
	
	if(_playReverse && !_playOpen)
	{
		if (_reverseOpen)
		{
			if (_leftOpenDegree <= 240.0f)
			{
				_leftOpenDegree += _openSpeed;
				_pyramidMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_objSize, (sqrt(3) * _objSize) / 2, 0.0f));
				_pyramidMat[0] = GET_SINGLE(TransformManager).GetRotateMatrix(_leftOpenDegree, Z_AXIS) * _pyramidMat[0];
				_pyramidMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-_objSize, -(sqrt(3) * _objSize) / 2, 0.0f)) * _pyramidMat[0];
			}

			if (_frontOpenDegree <= 240.0f)
			{
				_frontOpenDegree += _openSpeed;
				_pyramidMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, (sqrt(3) * _objSize) / 2, -_objSize));
				_pyramidMat[1] = GET_SINGLE(TransformManager).GetRotateMatrix(_frontOpenDegree, X_AXIS) * _pyramidMat[1];
				_pyramidMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -(sqrt(3) * _objSize) / 2, _objSize)) * _pyramidMat[1];
			}

			if (_rightOpenDegree >= -240.0f)
			{
				_rightOpenDegree -= _openSpeed;
				_pyramidMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-_objSize, (sqrt(3) * _objSize) / 2, 0.0f));
				_pyramidMat[2] = GET_SINGLE(TransformManager).GetRotateMatrix(_rightOpenDegree, Z_AXIS) * _pyramidMat[2];
				_pyramidMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_objSize, -(sqrt(3) * _objSize) / 2, 0.0f)) * _pyramidMat[2];
			}

			if (_backOpenDegree >= -240.0f)
			{
				_backOpenDegree -= _openSpeed;
				_pyramidMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, (sqrt(3) * _objSize) / 2, _objSize));
				_pyramidMat[3] = GET_SINGLE(TransformManager).GetRotateMatrix(_backOpenDegree, X_AXIS) * _pyramidMat[3];
				_pyramidMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -(sqrt(3) * _objSize) / 2, -_objSize)) * _pyramidMat[3];
			}

		}
		else
		{
			if (_leftOpenDegree >= 0.0f)
			{
				_leftOpenDegree -= _openSpeed;
				_pyramidMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_objSize, (sqrt(3) * _objSize) / 2, 0.0f));
				_pyramidMat[0] = GET_SINGLE(TransformManager).GetRotateMatrix(_leftOpenDegree, Z_AXIS) * _pyramidMat[0];
				_pyramidMat[0] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-_objSize, -(sqrt(3) * _objSize) / 2, 0.0f)) * _pyramidMat[0];
			}

			if (_frontOpenDegree >= 0.0f)
			{
				_frontOpenDegree -= _openSpeed;
				_pyramidMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, (sqrt(3) * _objSize) / 2, -_objSize));
				_pyramidMat[1] = GET_SINGLE(TransformManager).GetRotateMatrix(_frontOpenDegree, X_AXIS) * _pyramidMat[1];
				_pyramidMat[1] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -(sqrt(3) * _objSize) / 2, _objSize)) * _pyramidMat[1];
			}

			if (_rightOpenDegree <= 0.0f)
			{
				_rightOpenDegree += _openSpeed;
				_pyramidMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-_objSize, (sqrt(3) * _objSize) / 2, 0.0f));
				_pyramidMat[2] = GET_SINGLE(TransformManager).GetRotateMatrix(_rightOpenDegree, Z_AXIS) * _pyramidMat[2];
				_pyramidMat[2] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_objSize, -(sqrt(3) * _objSize) / 2, 0.0f)) * _pyramidMat[2];
			}

			if (_backOpenDegree <= 0.0f)
			{
				_backOpenDegree += _openSpeed;
				_pyramidMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, (sqrt(3) * _objSize) / 2, _objSize));
				_pyramidMat[3] = GET_SINGLE(TransformManager).GetRotateMatrix(_backOpenDegree, X_AXIS) * _pyramidMat[3];
				_pyramidMat[3] = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -(sqrt(3) * _objSize) / 2, -_objSize)) * _pyramidMat[3];
			}

		}
	}

}

void Ex18::Render()
{
	if (_cube == nullptr && _pyramid == nullptr)
	{
		_cube = new Objects(OBJ_CUBE, { 0,0,0 }, _objSize, NON_INDEXED);
		_pyramid = new Objects(OBJ_PYRAMID, { 0,0,0 }, _objSize, NON_INDEXED);
	}

	if (objType == true)
		RenderCube();
	else
		RenderPyramid();


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

	// 5. 밑면
	start += 6;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _cubeMat[5]);
	glDrawArrays(GL_TRIANGLES, start, 6);

}

void Ex18::RenderPyramid()
{
	glBindVertexArray(_pyramid->GetVAO().GetVAOHandle());

	int start;

	// 0. 왼쪽면
	start = 0;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _pyramidMat[0]);
	glDrawArrays(GL_TRIANGLES, start, 3);

	// 1. 앞면
	start += 3;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _pyramidMat[1]);
	glDrawArrays(GL_TRIANGLES, start, 3);

	// 2. 오른쪽면
	start += 3;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _pyramidMat[2]);
	glDrawArrays(GL_TRIANGLES, start, 3);

	// 3. 뒷면
	start += 3;
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _pyramidMat[3]);
	glDrawArrays(GL_TRIANGLES, start, 3);

	// 4. 밑면
	GET_SINGLE(TransformManager).BindTransformMatrix(_worldMat * _yrotateMat * _pyramidMat[4]);
	start += 3;
	glDrawArrays(GL_TRIANGLES, start, 3);
	start += 3;
	glDrawArrays(GL_TRIANGLES, start, 3);

}
