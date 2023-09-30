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
	glutCreateWindow("½Ç½À6");

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

	for (int i = 0; i < objectCount; i++)
	{

		glBindVertexArray(list[i]->GetVAO());
		switch (list[i]->GetShape())
		{
		case OBJ_POINT:
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, 0, 1);
			break;

		case OBJ_LINE:
			glDrawArrays(GL_LINE, 0, 2);
			break;

		case OBJ_TRIANGLE:
			glDrawArrays(GL_TRIANGLES, 0, 3);
			break;

		case OBJ_RECTANGLE:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		}

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
		Objects* o = new Objects(OBJ_POINT, pos);
		list[objectCount] = o;
		objectCount++;
		break;
	}
	case 'l':
	{
		Objects* o = new Objects(OBJ_LINE, pos);
		list[objectCount] = o;
		objectCount++;
		break;
	}
	case 't':
	{
		Objects* o = new Objects(OBJ_TRIANGLE, pos);
		list[objectCount] = o;
		objectCount++;
		break;
	}
	case 'r':
	{
		Objects* o = new Objects(OBJ_RECTANGLE, pos);
		list[objectCount] = o;
		objectCount++;
		break;
	}

	case 'w':
		for (int i = 0; i < objectCount; i++)
		{
			list[i]->MoveObject(UP);
		}
		break;

	case 's':
		for (int i = 0; i < objectCount; i++)
		{
			list[i]->MoveObject(DOWN);
		}
		break;
	case 'a':
		for (int i = 0; i < objectCount; i++)
		{
			list[i]->MoveObject(LEFT);
		}
		break;
	case 'd':
		for (int i = 0; i < objectCount; i++)
		{
			list[i]->MoveObject(RIGHT);
		}
		break;

	}

	glutPostRedisplay();

}