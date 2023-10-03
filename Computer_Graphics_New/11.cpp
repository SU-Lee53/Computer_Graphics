#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Animation(int value);
GLvoid SetAnim();
void SetAnimSolo();
GLuint shaderID;
Shaders* shader = new Shaders();

Anims11* anim[4];
Anims11* animSolo;
TF_TYPE animType = ALL;

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

	SetAnim();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(0, Animation, 0);
	glutMainLoop();
}

void SetAnim()
{
	anim[0] = new Anims11({-0.5f, 0.5f}, 0.2f, L2T, 0.002);
	anim[1] = new Anims11({0.5f, 0.5f}, 0.2f, T2R, 0.002);
	anim[3] = new Anims11({-0.5f, -0.5f}, 0.2f, R2P, 0.002);
	anim[2] = new Anims11({ 0.5f, -0.5f }, 0.2f, P2P, 0.002);
}

void SetAnimSolo()
{
	if (animSolo != nullptr)
	{
		delete animSolo;
	}

	switch (animType)
	{
	case L2T:
		animSolo = new Anims11({ 0.0f, 0.0f }, 0.5f, L2T, 0.01);
		break;

	case T2R:
		animSolo = new Anims11({ 0.0f, 0.0f }, 0.5f, T2R, 0.01);
		break;

	case R2P:
		animSolo = new Anims11({ 0.0f, 0.0f }, 0.3f, R2P, 0.005);
		break;

	case P2P:
		animSolo = new Anims11({ 0.0f, 0.0f }, 0.5f, P2P, 0.008);
		break;
	}

	glutTimerFunc(0, Animation, 0);
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);

	if(animType == ALL)
	{
		for (int i = 0; i < 4; i++)
		{
			anim[i]->Render();
		}
	}
	else
	{
		animSolo->Render();
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'l':
		animType = L2T;
		SetAnimSolo();
		break;

	case 't':
		animType = T2R;
		SetAnimSolo();
		break;

	case 'r':
		animType = R2P;
		SetAnimSolo();
		break;

	case 'p':
		animType = P2P;
		SetAnimSolo();
		break;

	case 'a':
		animType = ALL;
		for (int i = 0; i < 4; i++)
		{
			delete anim[i];
		}
		SetAnim();
		glutTimerFunc(0, Animation, 0);
		break;
	}



}

GLvoid Mouse(int button, int state, int x, int y)
{
	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y)} );

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}

}

GLvoid Animation(int value) 
{
	if(animType == ALL)
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
	else
	{
		animSolo->PlayAnim();

		glutPostRedisplay();

		if (animSolo->GetEndFlag() == false)
			glutTimerFunc(17, Animation, 0);
		else
			return;
	}
		
}