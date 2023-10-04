#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void SetScreen();
GLuint shaderID;
Shaders* shader = new Shaders();

Objects* objList[5];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("½Ç½À11");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW init failed" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cerr << "GLEW INITIALIZED" << endl;

	shaderID = shader->makeShaderProgram();

	SetScreen();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

void SetScreen()
{
	srand(time(0));
	objList[0] = new Objects(OBJ_POINT, GetRandomCoord(), 0.2);
	objList[1] = new Objects(OBJ_LINE, GetRandomCoord(), 0.2);
	objList[2] = new Objects(OBJ_TRIANGLE, GetRandomCoord(), 0.2);
	objList[3] = new Objects(OBJ_RECTANGLE, GetRandomCoord(), 0.2);
	objList[4] = new Objects(OBJ_PENTAGON, GetRandomCoord(), 0.2);
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);

	for (int i = 0; i < 5; i++)
	{
		objList[i]->RenderObject();
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y) });

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutPostRedisplay();
	}


}