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
		std::cerr << "실패" << std::endl;
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

	// 렌더링 파이프라인에서 셰이더 불러오기
	glUseProgram(shaderID);

	// 사용할 VAO 불러오기
	glBindVertexArray(vao);
	
	// 삼각형 그리기
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
	glGenVertexArrays(1, &vao);		// VAO를 지정하고 할당하기

	glBindVertexArray(vao);			// VAO를 바인드하기

	glGenBuffers(2, vbo);			// 2개의 VBO를 지정하고 할당하기


	// 1번째 VBO를 활성화하여 바인드하고 버텍스 속성(좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// 변수 triShape에서 버텍스 데이터 값을 버퍼에 복사한다
	// triShape 배열의 사이즈 : 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);

	//  좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3 * float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// attrbute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);


	// 2번째 VBO를 활성화 하여 바인드하고, 버텍스 속정을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	// 변수 colors에서 버텍스 색상을 복사한다
	// colors 배열의 사이즈 : 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	// 색상값을 attribute 인덱스 1번에 명시한다: 버텍스당 3 * float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// attribute 인덱스 1번을 사용 가능하게함
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

	// 버텍스 셰이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 셰이더 코드를 셰이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);

	// 버텍스 셰이더 컴파일하기
	glCompileShader(vertexShader);

	// 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패" << errorLog << std::endl;
		return;
	}
}

void MakeFragmentShader()
{
	GLchar* fragmentSource = filetobuf("fragment.glsl");

	// 프래그먼트 셰이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 셰이더 코드를 셰이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);

	// 프래그먼트 셰이더 컴파일
	glCompileShader(fragmentShader);

	// 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패" << errorLog << std::endl;
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