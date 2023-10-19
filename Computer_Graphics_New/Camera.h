#pragma once
class Camera
{
public:
	Camera(glm::vec3 EYE, glm::vec3 AT, glm::vec3 UP);
	~Camera();

	void CameraMove(glm::vec3 move);

	// �ؿ� 2�� ���� ��������
	void CameraRotation(float degree, AXIS axis);
	void CameraRevoluion(float degree, AXIS axis);

	glm::mat4 GetCameraMatrix() { return _cameraMatrix; }
	void Bind();

private:
	void SetCamera();


private:
	// ���� ���������� ī�޶��� ��ġ
	glm::vec3 _EYE;
	// ���� �������� ī�޶� �ٶ󺸴� ������
	glm::vec3 _AT;
	// ī�޶��� ����� ����Ű�� ����
	glm::vec3 _UP;

	glm::mat4 _cameraMatrix;

};

