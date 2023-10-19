#pragma once

class Projection
{
public:
	Projection(float fovy, float aspect, float Near, float Far, float move);
	Projection(float left, float right, float bottom, float top, float Near, float Far);
	~Projection();
	void SetPerspectiveProjection();
	void SetOrthoProjection();

	void Bind();

	glm::mat4 GetProjectionMatrix() { return _projMatrix; }


private:
	// 원근 투영시 사용
	float _fovy;
	float _aspect;
	float _move;

	// 직교 투영시 사용
	float _left; 
	float _right;
	float _bottom; 
	float _top;

	float _near;
	float _far;

	glm::mat4 _projMatrix = glm::mat4(1.0);
};

