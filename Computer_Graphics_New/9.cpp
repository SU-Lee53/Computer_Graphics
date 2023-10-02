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
bool anim1 = false;
bool anim2 = false;
bool anim3 = false;
bool anim4 = false;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("½Ç½À9");

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
	glutTimerFunc(0, Animation, 0);
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

		list[objCount] = { anim, obj };
		objCount++;
	}

}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (anim1 == false)
		{
			anim1 = true;
			anim2 = false;
			anim3 = false;
			anim4 = false;
		}
		else
		{
			anim1 = false;
		}
		break;

	case '2':
		if (anim2 == false)
		{
			anim1 = false;
			anim2 = true;
			anim3 = false;
			anim4 = false;
		}
		else
		{
			anim2 = false;
		}
		break;

	case '3':
		if (anim3 == false)
		{
			anim1 = false;
			anim2 = false;
			anim3 = true;
			anim4 = false;
			
			for (int i = 0; i < objCount; i++)
			{
				list[i].anim->SetRSpiral();
			}
		}
		else
		{
			anim3 = false;
		}
		break;

	case '4':
		if (anim4 == false)
		{
			anim1 = false;
			anim2 = false;
			anim3 = false;
			anim4 = true;

			for (int i = 0; i < objCount; i++)
			{
				list[i].anim->SetCSpiral();
			}
		}
		else
		{
			anim4 = false;
		}
		break;
	}
}

void Animation(int value)
{
	for (int i = 0; i < objCount; i++)
	{
		if (anim1 == true)
		{
			list[i].anim->Bounce();
		}
		else if (anim2 == true)
		{
			list[i].anim->Zigzag();
		}
		else if (anim3 == true)
		{
			list[i].anim->RSpiral();
		}
		else if (anim4 == true)
		{
			list[i].anim->CSpiral();
		}
	}

	glutPostRedisplay();
	glutTimerFunc(17, Animation, 0);
}