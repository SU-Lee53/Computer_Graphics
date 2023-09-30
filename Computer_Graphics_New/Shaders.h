#pragma once

class Shaders
{

public:
	Shaders();
	~Shaders();

	// ���̴� ������ �Լ�
	void makeVertexShaders();
	void makeFragmentShaders();
	GLuint makeShaderProgram();

	// ���� ���� �Լ�

	int GetShaderID() { return shaderID; }
	


private:
	GLuint shaderID;
	GLuint vertexShader;
	GLuint fragmentShader;

};

