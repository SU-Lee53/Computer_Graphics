#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Motion(int x, int y);
GLvoid Animation(int value);
void SetScreen();

GLuint shaderID;
Shaders* shader = new Shaders();

struct ANIM
{
	Objects* obj;
	Anims* anim;
};

vector<Objects*> list;
vector<ANIM> animList;
int objCount = 0;
Objects* selected;
int sIdx;
Coord beforePos = { 0, 0 };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("½Ç½À12");

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
	glutMotionFunc(Motion);
	glutTimerFunc(0, Animation, 1);
	glutMainLoop();
}

Coord GetRandomPos()
{
	float x = (static_cast<float>(rand()) / (RAND_MAX / 2)) - 1;
	float y = (static_cast<float>(rand()) / (RAND_MAX / 2)) - 1;

	return { x, y };
}

void SetScreen()
{
	srand(time(0));

	for (int i = 0; i < 3; i++)
	{
		list.push_back(new Objects(OBJ_POINT, GetRandomPos(), 1));
	}
	for (int i = 0; i < 3; i++)
	{
		list.push_back(new Objects(OBJ_LINE, GetRandomPos(), 0.5));
	}
	for (int i = 0; i < 3; i++)
	{
		list.push_back(new Objects(OBJ_TRIANGLE, GetRandomPos(), 0.08));
	}
	for (int i = 0; i < 3; i++)
	{
		list.push_back(new Objects(OBJ_RECTANGLE, GetRandomPos(), 0.08));
	}
	for (int i = 0; i < 3; i++)
	{
		list.push_back(new Objects(OBJ_PENTAGON, GetRandomPos(), 0.08));
	}
	
	for (int i = 0; i < list.size(); i++)
	{
		RGB rgb = { static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX , static_cast<float>(rand()) / RAND_MAX };
		list[i]->SetRGB(rgb);
	}
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);

	for (int i = 0; i < list.size(); i++)
	{
		if(list[i]->GetValid() == true)
			list[i]->RenderObject();
	}

	for (int i = 0; i < animList.size(); i++)
	{
		animList[i].obj->RenderObject();
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
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->GetValid() == false)
				continue;

			if (list[i]->CheckClicked(pos) == true)
			{
				selected = list[i];
				sIdx = i;
				cout << i << " selected" << endl;
				break;
			}
		}
	}
	else
	{
		selected = nullptr;
		cout << "unselected" << endl;
	}


	beforePos = pos;

}

GLvoid Motion(int x, int y)
{
	if (selected == nullptr)
		return;

	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y) });

	float dx = pos.x - beforePos.x;
	float dy = pos.y - beforePos.y;

	selected->MoveVertex(dx, dy);
	cout << "Moved: " << dx << ", " << dy << endl;

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == selected || list[i]->GetValid() == false)
			continue;

		if (selected->GetCollision(list[i]))
		{
			int v1 = selected->GetVertexCount() / 3;
			int v2 = list[i]->GetVertexCount() / 3;

			int finalV = v1 + v2;

			if (finalV >= 6)
			{
				finalV = 1;
			}

			ANIM a;
			switch (finalV)
			{
			case 1:
			{
				a.obj = new Objects(OBJ_POINT, pos, 1);
				RGB rgb = { static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX , static_cast<float>(rand()) / RAND_MAX };
				a.obj->SetRGB(rgb);
				a.anim = new Anims(a.obj);
				break;
			}
			case 2:
			{
				a.obj = new Objects(OBJ_LINE, pos, 0.5);
				RGB rgb = { static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX , static_cast<float>(rand()) / RAND_MAX };
				a.obj->SetRGB(rgb);
				a.anim = new Anims(a.obj);
				break;
			}
			case 3:
			{
				a.obj = new Objects(OBJ_TRIANGLE, pos, 0.08);
				RGB rgb = { static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX , static_cast<float>(rand()) / RAND_MAX };
				a.obj->SetRGB(rgb);
				a.anim = new Anims(a.obj);
				break;
			}
			case 4:
			{
				a.obj = new Objects(OBJ_RECTANGLE, pos, 0.08);
				RGB rgb = { static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX , static_cast<float>(rand()) / RAND_MAX };
				a.obj->SetRGB(rgb);
				a.anim = new Anims(a.obj);
				break;
			}
			case 5:
			{
				a.obj = new Objects(OBJ_PENTAGON, pos, 0.08);
				RGB rgb = { static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX , static_cast<float>(rand()) / RAND_MAX };
				a.obj->SetRGB(rgb);
				a.anim = new Anims(a.obj);
				break;
			}

			}

			selected->SetValid(false);
			list[i]->SetValid(false);

			animList.push_back(a);

			selected = nullptr;
			cout << "unselected" << endl;
			break;
		}
		
	}

	glutPostRedisplay();

	beforePos = pos;

}

GLvoid Animation(int value)
{
	for (int i = 0; i < animList.size(); i++)
	{
		animList.at(i).anim->Bounce();
	}

	glutPostRedisplay();

	glutTimerFunc(17, Animation, 0);

}