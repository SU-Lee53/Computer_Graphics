#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Animation(int value);
GLvoid SetAnim();
GLuint shaderID;
Shaders* shader = new Shaders();

Anims11* anim[4];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("½Ç½À10");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW init failed" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cerr << "GLEW INITIALIZED" << endl;

	shaderID = shader->makeShaderProgram();

	SetAnim();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(0, Animation, 0);
	glutMainLoop();
}

GLvoid SetAnim()
{
	anim[0] = new Anims11({-0.5f, 0.5f}, 0.2f, L2T);
	anim[1] = new Anims11({0.5f, 0.5f}, 0.2f, T2R);
	anim[2] = new Anims11({-0.5f, -0.5f}, 0.2f, R2P);
	anim[3] = new Anims11({ 0.5f, -0.5f }, 0.2f, P2P);
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);

	for (int i = 0; i < 4; i++)
	{
		anim[i]->Render();
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y)} );

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 4; i++)
		{
			anim[i]->SetAnim();
		}
		glutTimerFunc(0, Animation, 0);
	}

}

GLvoid Animation(int value) 
{
	for (int i = 0; i < 4; i++)
	{
		anim[i]->PlayAnim();
	}

	glutPostRedisplay();
	
	bool stop = true;
	for (int i = 0; i < 4; i++)
	{
		if (anim[i]->GetEndFlag() == false)
		{
			stop = false;
			break;
		}
	}

	if (stop == false)
		glutTimerFunc(17, Animation, 0);
	else
	{
		cout << "end" << endl;
		return;
	}
		
}