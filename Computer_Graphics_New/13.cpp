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

Objects* obj;
Objects* axis[2];
int selectedVtx = -1;
bool selected = false;
Coord beforePos = { 0,0 };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("½Ç½À13");

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
	obj = new Objects(OBJ_RECT13, { 0,0 }, 0.5);
	axis[0] = new Objects(OBJ_LINE, { 0,0 }, 0);

	axis[0]->SetAxis(true);
	axis[0]->SetRGB({ 0.0f, 0.0f, 0.0f });

	axis[1] = new Objects(OBJ_LINE, { 0,0 }, 0);
	axis[1]->SetAxis(false);
	axis[1]->SetRGB({ 0.0f, 0.0f, 0.0f });
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);
	glPolygonMode(GL_FRONT, GL_LINE);
	
	
	for (int i = 0; i < 2; i++)
	{
		glLineWidth(1.0);
		axis[i]->RenderObject();
	}

	glLineWidth(3.0);

	obj->RenderObject();

	glutSwapBuffers();

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y) });
	beforePos = pos;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		selectedVtx = obj->CheckSpecificVertexClicked(pos);
		selected = obj->CheckClicked(pos);
		if (selectedVtx != -1)
		{
			cout << selectedVtx << " Vertex selected" << endl;
			selected = false;
			return;
		}
		else if (selected == true)
		{
			cout << "Object selected" << endl;
			selectedVtx = -1;
			return;
		}
		else
		{
			selectedVtx = -1;
			selected = false;
		}


	}
	else
	{
		cout << "Released" << endl;
	}

	

}

GLvoid Motion(int x, int y)
{
	if (selected == false && selectedVtx == -1)
		return;

	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y) });

	float dx = pos.x - beforePos.x;
	float dy = pos.y - beforePos.y;

	if (selectedVtx != -1)
	{
		obj->ModifySpecificVertex(selectedVtx, dx, dy);
	}
	else if (selected == true)
	{
		obj->MoveVertex(dx, dy);
	}


	glutPostRedisplay();
	beforePos = pos;
}