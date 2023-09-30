#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Animation(int value);
void SetScreen();

GLuint shaderID;
Shaders* shader = new Shaders();

struct Set
{
	Anims* anim;
	Objects* obj;
};

Set list[4];
int objCount = 0;
const int MAX_COUNT = 4;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("½Ç½À8");

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
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);

	for (int i = 0; i < objCount; i++)
	{
		list[i].obj->InitBuffer();
		list[i].obj->RenderObject();
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
		if (objCount >= MAX_COUNT)
			return;
		
		Objects* obj = new Objects(OBJ_TRIANGLE, pos, 0.1);
		RGB rgb = { static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX , static_cast<float>(rand()) / RAND_MAX };
		obj->SetRGB(rgb);

		Anims* anim = new Anims(obj);
		anim->SetBounceDir();

		list[objCount] = { anim, obj };
		objCount++;
	}

}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		glutTimerFunc(0, Animation, 0);
		break;
	}
}

void Animation(int value)
{
	for (int i = 0; i < objCount; i++)
	{
		list[i].anim->Bounce();
	}

	glutPostRedisplay();
	glutTimerFunc(17, Animation, 0);
}