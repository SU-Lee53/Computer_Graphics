#pragma once

class Shaders
{

public:
	Shaders();
	~Shaders();

	// ���̴� ������ �Լ�
	GLuint makeShaderProgram();

	// ���� ���� �Լ�

	int GetShaderID() { return shaderID; }
	
private:
	void makeVertexShaders();
	void makeFragmentShaders();

private:
	GLuint shaderID;
	GLuint vertexShader;
	GLuint fragmentShader;

	
};

