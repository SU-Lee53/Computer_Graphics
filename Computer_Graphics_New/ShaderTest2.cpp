#include "pch.h"

GLvoid drawScene();
GLvoid Reshape(int w, int h);
void InitBuffer();
void MakeShaderProgram();
void MakeVertexShader();
void MakeFragmentShader();
void RGBrandomize(int value);

const GLfloat triShape[3][3] = {
	{-0.5, -0.5, 0.0},
	{0.5, -0.5, 0.0},
	{0.0, 0.5, 0.0}
};

GLfloat colors[3][3] = {
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0}
};

GLuint vao, vbo[2];
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "����" << std::endl;
		exit(EXIT_FAILURE);
	}

	MakeShaderProgram();
	InitBuffer();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(17, RGBrandomize, 0);
	glutMainLoop();

}

GLvoid drawScene()
{
	InitBuffer();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ������ ���������ο��� ���̴� �ҷ�����
	glUseProgram(shaderID);

	// ����� VAO �ҷ�����
	glBindVertexArray(vao);
	
	// �ﰢ�� �׸���
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao);		// VAO�� �����ϰ� �Ҵ��ϱ�

	glBindVertexArray(vao);			// VAO�� ���ε��ϱ�

	glGenBuffers(2, vbo);			// 2���� VBO�� �����ϰ� �Ҵ��ϱ�


	// 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ� ���ؽ� �Ӽ�(��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// ���� triShape���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�
	// triShape �迭�� ������ : 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);

	//  ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3 * float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// attrbute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);


	// 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε��ϰ�, ���ؽ� ������ ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	// ���� colors���� ���ؽ� ������ �����Ѵ�
	// colors �迭�� ������ : 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	// ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ��� 3 * float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// attribute �ε��� 1���� ��� �����ϰ���
	glEnableVertexAttribArray(1);

}

void MakeShaderProgram()
{
	MakeVertexShader();
	MakeFragmentShader();

	shaderID = glCreateProgram();

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	glUseProgram(shaderID);
}

void MakeVertexShader()
{
	GLchar* vertexSource = filetobuf("vertex.glsl");

	// ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);

	// ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);

	// �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����" << errorLog << std::endl;
		return;
	}
}

void MakeFragmentShader()
{
	GLchar* fragmentSource = filetobuf("fragment.glsl");

	// �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);

	// �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);

	// �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����" << errorLog << std::endl;
		return;
	}

}

void RGBrandomize(int value)
{


	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			colors[i][j] += 0.01f;

			if (colors[i][j] > 1.0f)
			{
				colors[i][j] = 0.0f;
			}
		}
	}

	glutTimerFunc(17, RGBrandomize, 0);
}