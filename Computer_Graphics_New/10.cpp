#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Animation(int value);
void SpiralAnimation(int value);
void SetAnim(int count, Coord pos);
void SetBackground();
Coord GetRandomPos();

GLuint shaderID;
Shaders* shader = new Shaders();

Anims* anim[5];
int animCount = 0;
bool drawType = false;
RGB Background = { 0.0f, 0.0f, 0.0f };

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

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(Background.Red, Background.Green, Background.Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);
	

	if(animCount > 0)
	{
		for(int i = 0; i < animCount; i++)
		{
			glBindVertexArray(anim[i]->GetSpiralVAO());
			int vCount = anim[i]->GetSpiralVertexCount() - 1;
			for (int j = 0; j < vCount - 1; j++)
			{
				if (drawType == false)
				{
					glPointSize(3.0);
					glDrawArrays(GL_POINTS, j, 1);
				}
				else
				{
					glLineWidth(3.0);
					glDrawArrays(GL_LINES, j, 2);
				}
			}
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
	case '1':
		SetAnim(1, pos);
		SetBackground();
		glutTimerFunc(0, SpiralAnimation, 0);
		break;
	case '2':
		SetAnim(2, pos);
		SetBackground();
		glutTimerFunc(0, SpiralAnimation, 0);
		break;
	case '3':
		SetAnim(3, pos);
		SetBackground();
		glutTimerFunc(0, SpiralAnimation, 0);
		break;
	case '4':
		SetAnim(4, pos);
		SetBackground();
		glutTimerFunc(0, SpiralAnimation, 0);
		break;
	case '5':
		SetAnim(5, pos);
		SetBackground();
		glutTimerFunc(0, SpiralAnimation, 0);
		break;
	case 'p':
		drawType = false;
		glutPostRedisplay();
		break;

	case 'l':
		drawType = true;
		glutPostRedisplay();
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y) });

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}

}

void SpiralAnimation(int value)
{
	bool stop = true;
	bool isMixed = false;
	for (int i = 0; i < animCount; i++)
	{
		anim[i]->SymSpiral();
		glutPostRedisplay();
	}

	for (int i = 0; i < animCount; i++)
	{
		if (anim[i]->GetSpiralEndFlag() == false)
			stop = false;
	}

	if (!stop)
		glutTimerFunc(17, SpiralAnimation, 0);
}

void SetAnim(int count, Coord pos)
{
	animCount = count;

	anim[0] = new Anims(pos);

	
	for (int i = 1; i < count; i++)
	{
		Coord randPos = GetRandomPos();
		anim[i] = new Anims(randPos);
	}
}

void SetBackground()
{
	srand(time(0));
	Background.Red = static_cast<float>(rand()) / RAND_MAX;
	Background.Green = static_cast<float>(rand()) / RAND_MAX;
	Background.Blue = static_cast<float>(rand()) / RAND_MAX;
}

Coord GetRandomPos()
{
	Coord randPos;
	randPos.x = (static_cast<float>(rand()) / RAND_MAX * 2) - 1.0f;
	randPos.y = (static_cast<float>(rand()) / RAND_MAX * 2) - 1.0f;

	return randPos;
}