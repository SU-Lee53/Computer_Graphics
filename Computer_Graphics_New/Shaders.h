#pragma once

class Shaders
{

public:
	Shaders();
	~Shaders();

	void makeVertexShaders();
	void makeFragmentShaders();
	GLuint makeShaderProgram();

	GLuint GetShaderID() { return shaderProgramID; }

private:
	GLuint shaderProgramID;
	GLuint vertexShader;
	GLuint fragmentShader;

};

