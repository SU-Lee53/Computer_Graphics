#pragma once

class Shaders
{

public:
	Shaders();
	~Shaders();

	// ���̴� ������ �Լ�
	GLuint makeShaderProgram1();
	GLuint makeShaderProgram2();

	// ���� ���� �Լ�

	int GetShaderID() { return shaderID; }
	int GetuShaderID() { return uShaderID; }

private:
	void makeVertexShaders();
	void makeFragmentShaders();
	void makeUniformFragmentShader();

private:
	GLuint shaderID;
	GLuint uShaderID;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint uniformShader;
	
};

