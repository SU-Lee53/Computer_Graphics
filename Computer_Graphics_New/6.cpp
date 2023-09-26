#include "pch.h"
using namespace std;

struct rectSet
{
	Rect* rect;
	Anims* anim;
};

vector<rectSet> list;
bool AnimStop;

void AnimBoth(int value)
{
	if (AnimStop == false) {

		list.at(value).anim->AnimBoth();

		if (list.at(value).anim->GetEndFlag() == false)
			glutTimerFunc(17, AnimBoth, value);
	}

	glutPostRedisplay();

}

void AnimStraight(int value)
{
	if(AnimStop == false) {

		list.at(value).anim->AnimStraight();

		if (list.at(value).anim->GetSplitList().size() != 0)
			glutTimerFunc(17, AnimStraight, value);
	}

	glutPostRedisplay();
}

void AnimDiagnoal(int value)
{
	if(AnimStop == false) {

		list.at(value).anim->AnimDiagnoal();

		if (list.at(value).anim->GetSplitList().size() != 0)
			glutTimerFunc(17, AnimDiagnoal, value);
	}

	glutPostRedisplay();
}

GLvoid SetScreen()
{
	srand(time(0));
	
	for (int i = 0; i < list.size(); i++)
	{
		list.at(i).rect->~Rect();
		list.at(i).anim->~Anims();
	}

	list.clear();

	for (int i = 0; i < 5; i++)
	{
		Coord c1;
		Coord c2;
		RGB color;
		while (true)
		{
			color.Red = static_cast<float>(rand()) / RAND_MAX;
			color.Green = static_cast<float>(rand()) / RAND_MAX;
			color.Blue = static_cast<float>(rand()) / RAND_MAX;

			bool overlapped = false;
			for (int j = 0; j < i; j++)
			{
				if (list.at(j).rect->GetColor().Red == color.Red
					|| list.at(j).rect->GetColor().Green == color.Green
					|| list.at(j).rect->GetColor().Blue == color.Blue)
					overlapped = true;
			}

			if (overlapped == false)
				break;
		}

		while (true)
		{
			c1.x = -1.0f + (static_cast<float>(rand()) / (RAND_MAX / 2));
			c1.y = -1.0f + (static_cast<float>(rand()) / (RAND_MAX / 2));
			c2.x = c1.x + 0.3;
			c2.y = c1.y - 0.3;

			bool overlapped = false;
			for (int j = 0; j < i; j++)
			{
				if (list.at(j).rect->GetCoord1().x == c1.x)
					overlapped = true;
			}

			if (overlapped == false)
				if (c2.x <= 1.0f && c2.y >= -1.0f)
					break;
		}

		Rect* r = new Rect(c1.x, c1.y, c2.x, c2.y, color.Red, color.Green, color.Blue);
		Anims* a = new Anims(r);
		list.push_back({ r,a });
	}
}

GLvoid drawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 5; i++)
	{
		if (list.at(i).rect->GetValidFlag() == true)
		{
			list.at(i).rect->DrawRect();
		}
		else 
		{
			for (int j = 0; j < list.at(i).anim->GetSplitList().size(); j++)
			{
				list.at(i).anim->GetSplitList().at(j)->DrawRect();
			}
		}

	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	Coord current = AdjustMouseCoordinate({ static_cast<GLfloat>(x), static_cast<GLfloat>(y) });

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 4; i >= 0; i--)
		{
			if (list.at(i).rect->MouseClickCheck(current))
			{
				if (list.at(i).rect->GetValidFlag() == false)
					continue;

				list.at(i).rect->SetValidFlag(false);
				AnimStop = false;

				switch (list.at(i).rect->GetSplitType())
				{
				case STRAIGHT:
					glutTimerFunc(0, AnimStraight, i);
					break;

				case DIAGNOAL:
					glutTimerFunc(0, AnimDiagnoal, i);
					break;

				case BOTH:
					glutTimerFunc(0, AnimBoth, i);
				}

			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		AnimStop = true;
		SetScreen();
		glutPostRedisplay();
	}
	
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == 'r')
	{
		AnimStop = true;
		SetScreen();
		glutPostRedisplay();
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("�ǽ�4");

	glewExperimental = TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "Unable to initalize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW initalized" << endl;

	cout << "���� ������ �簢�� �ִϸ��̼�" << endl;
	cout << "ȭ���� ������ ��ġ�� 5���� �簢���� ������ �������� �׸���." << endl;
	cout << "���콺�� �簢�� ���θ� Ŭ���ϸ�, �簢���� ���еǾ� ��ġ�� �̵��Ѵ�." << endl;
	cout << "�� ��, �簢���� ũ�Ⱑ ���� �۾����� Ư�� ũ�Ⱑ �Ǹ� �������." << endl;
	cout << "��ġ �̵� �ִϸ��̼�" << endl;
	cout << "	�� �¿���� �̵�" << endl;
	cout << "	�� �밢�� �̵�" << endl;
	cout << "	�� �¿���ϴ밢�� �̵�(�̶��� ��ҵ� �簢���� 8�� ��Ÿ����)" << endl;
	
	SetScreen();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();

}