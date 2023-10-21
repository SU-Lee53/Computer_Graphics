#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

GLuint shaderID;
Shaders* shader = new Shaders();
Objects* list[10];
const int MAX_SIZE = 10;
int objectCount = 0;
GLuint currentVao;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("½Ç½À7");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW init failed" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cerr << "GLEW INITIALIZED" << endl;

	shaderID = shader->makeShaderProgram();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderID);

	for (int i = 0; i < objectCount; i++)
	{
		list[i]->InitBuffer();
		list[i]->RenderObject();

	}

	glutSwapBuffers();

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{

	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y) });

	switch (key)
	{
	case 'p':
	{
		if (objectCount >= MAX_SIZE)
			break;
		Objects* o = new Objects(OBJ_POINT, pos, 0);
		list[objectCount] = o;
		objectCount++;
		break;
	}
	case 'l':
	{
		if (objectCount >= MAX_SIZE)
			break;
		Objects* o = new Objects(OBJ_LINE, pos, 0);
		list[objectCount] = o;
		objectCount++;
		break;
	}
	case 't':
	{
		if (objectCount >= MAX_SIZE)
			break;
		Objects* o = new Objects(OBJ_TRIANGLE, pos, 0.2);
		list[objectCount] = o;
		objectCount++;
		break;
	}
	case 'r':
	{
		if (objectCount >= MAX_SIZE)
			break;
		Objects* o = new Objects(OBJ_RECTANGLE, pos, 0.1);
		list[objectCount] = o;
		objectCount++;
		break;
	}

	case 'w':
		for (int i = 0; i < objectCount; i++)
		{
			list[i]->MoveObject(DIR_UP, 0.05f);
		}
		break;

	case 's':
		for (int i = 0; i < objectCount; i++)
		{
			list[i]->MoveObject(DIR_DOWN, 0.05f);
		}
		break;
	case 'a':
		for (int i = 0; i < objectCount; i++)
		{
			list[i]->MoveObject(DIR_LEFT, 0.05f);
		}
		break;
	case 'd':
		for (int i = 0; i < objectCount; i++)
		{
			list[i]->MoveObject(DIR_RIGHT, 0.05f);
		}
		break;

	case 'c':
		for (int i = 0; i < objectCount; i++)
			delete list[i];

		objectCount = 0;
	}

	glutPostRedisplay();

}