#include "pch.h"
#include "Shaders.h"
using namespace std;

Shaders::Shaders()
{
}

Shaders::~Shaders()
{
}

void Shaders::makeVertexShaders()
{
	GLchar* vertexSource;

	// ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	// filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
	// �� ���Ͽ����� Utills�� �Լ����� �� ���ǰ� �������

	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: Failed to compile vertex shader\n" << errorLog << endl;
		return;
	}
}

void Shaders::makeFragmentShaders()
{
	GLchar* fragmentSource;

	// �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentSource = filetobuf("fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: Failed to complie fragment shader\n" << errorLog << endl;
		return;
	}
}

GLuint Shaders::makeShaderProgram()
{
	GLuint shaderID;
	shaderID = glCreateProgram();

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		cerr << "ERROR: Failed to link shader program\n" << errorLog << endl;
		return false;
	}

	glUseProgram(shaderID);

	return shaderID;

}