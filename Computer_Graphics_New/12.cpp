#include "pch.h"
using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Motion(int x, int y);
void SetScreen();

GLuint shaderID;
Shaders* shader = new Shaders();

vector<Objects*> list;
int objCount = 0;
Objects* selected;
Coord beforePos = { 0, 0 };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
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
	glutMainLoop();
}

void SetScreen()
{
	srand(time(0));
	list.push_back(new Objects(OBJ_POINT, { -0.5f, 0.5f }, 1));
	list.push_back(new Objects(OBJ_LINE, { 0.5f, 0.5f }, 0.2));
	list.push_back(new Objects(OBJ_TRIANGLE, { -0.5f, -0.5f }, 0.2));
	list.push_back(new Objects(OBJ_RECTANGLE, { 0.5f, -0.5f }, 0.2));
	list.push_back(new Objects(OBJ_PENTAGON, { 0.0f, 0.0f }, 0.2));
	objCount = 5;
	
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);

	for (int i = 0; i < list.size(); i++)
	{
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
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->CheckClicked(pos) == true)
			{
				selected = list[i];
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

	bool isCollision = false;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == selected)
			continue;

		if (selected->GetCollision(list[i]))
		{
			cout << "Collition!!!: " << i << endl;
			isCollision = true;
			break;
		}
		
	}

	if (isCollision == false)
	{
		cout << "No Collition" << endl;
	}

	glutPostRedisplay();

	beforePos = pos;

}