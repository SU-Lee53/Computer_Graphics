#include "pch.h"
#include "Camera.h"

Camera::Camera(glm::vec3 EYE, glm::vec3 AT, glm::vec3 UP) : _EYE(EYE), _AT(AT), _UP(UP)
{
	SetCamera();
}

Camera::~Camera()
{
}

void Camera::CameraMove(glm::vec3 move)
{
	_cameraMatrix = GET_SINGLE(TransformManager).GetTranslateMatrix(move) * _cameraMatrix;
}

void Camera::CameraRotation(float degree, AXIS axis)
{
	_cameraMatrix = GET_SINGLE(TransformManager).GetRotateMatrix(degree, axis) * _cameraMatrix;
}

void Camera::CameraRevoluion(float degree, AXIS axis)
{
	_cameraMatrix = _cameraMatrix * GET_SINGLE(TransformManager).GetRotateMatrix(degree, axis);
}


void Camera::SetCamera()
{
	_cameraMatrix = glm::lookAt(_EYE, _AT, _UP);

	// lookAt의 결과로 나오는 뷰 변환 행렬
	// 
	//	|	_u(x)	_u(y)	_u(z)	-_EYE·_u	|
	//	|										|
	//	|	_v(x)	_v(y)	_v(z)	-_EYE·_v	|
	//	|										|
	//	|	_n(x)	_n(y)	_n(z)	-_EYE·_n	|
	//	|										|
	//	|	  0	      0	      0			1		|
}

void Camera::Bind(unsigned int shaderID)
{
	unsigned int viewLocation = glGetUniformLocation(shaderID, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &_cameraMatrix[0][0]);
}