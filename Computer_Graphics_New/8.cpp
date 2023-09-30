#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

void SetScreen();

GLuint shaderID;
Shaders* shader = new Shaders();
Objects* list[4];

bool RenderFill = true;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("실습8");

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
	glutKeyboardFunc(Keyboard);

	glutMainLoop();
}

void SetScreen()
{
	srand(time(0));

	// 1사분면
	list[0] = new Objects(OBJ_TRIANGLE, {-0.5f, 0.5f}, 0.2);
	// 2사분면
	list[1] = new Objects(OBJ_TRIANGLE, {0.5f, 0.5f}, 0.2);
	// 3사분면
	list[2]  = new Objects(OBJ_TRIANGLE, {-0.5f, -0.5f}, 0.2);
	// 4사분면
	list[3]  = new Objects(OBJ_TRIANGLE, {0.5f, -0.5f}, 0.2);

	for (int i = 0; i < 4; i++)
	{
		RGB rgb = { static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX , static_cast<float>(rand()) / RAND_MAX };
		list[i]->SetRGB(rgb);
	}

}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderID);

	if (RenderFill)
	{
		glPolygonMode(GL_FRONT, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_LINE);
	}

	for (int i = 0; i < 4; i++)
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

GLvoid Mouse(int button, int state, int x, int y)
{
	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y) });

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float size = static_cast<float>(rand()) / (RAND_MAX * 4);
		size += 0.03f;


		if (pos.x < 0 && pos.y > 0)
		{
			list[0]->SetVertexPos(pos, size);
		}
		else if (pos.x > 0 && pos.y > 0)
		{
			list[1]->SetVertexPos(pos, size);
		}
		else if (pos.x < 0 && pos.y < 0)
		{
			list[2]->SetVertexPos(pos, size);
		}
		else if (pos.x > 0 && pos.y < 0)
		{
			list[3]->SetVertexPos(pos, size);
		}
	}

}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		RenderFill = true;
		glutPostRedisplay();
		break;

	case 'b':
		RenderFill = false;
		glutPostRedisplay();
		break;
	}


}