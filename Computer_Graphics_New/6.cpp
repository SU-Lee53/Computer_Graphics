#include "pch.h"
using namespace std;

GL_Rect* rectList[5];
GLboolean AnimStop;

GLvoid AnimBoth(int value)
{
	if(AnimStop == false) {
		
		rectList[value]->AnimBoth();

		if ((rectList[value]->GetSplitList().at(0)->GetCoord2().x - rectList[value]->GetSplitList().at(0)->GetCoord1().x) >= 0)
			glutTimerFunc(60, AnimBoth, value);
		else
			rectList[value]->ClearSplitList();
	}
}

GLvoid AnimStraight(int value)
{
	if(AnimStop == false) {
		
		rectList[value]->AnimStraight();

		if ((rectList[value]->GetSplitList().at(0)->GetCoord2().x - rectList[value]->GetSplitList().at(0)->GetCoord1().x) > 0)
			glutTimerFunc(60, AnimStraight, value);
		else
			rectList[value]->ClearSplitList();
	}

}

GLvoid AnimDiagnoal(int value)
{

	if(AnimStop == false) {
		
		rectList[value]->AnimDiagnoal();

		if ((rectList[value]->GetSplitList().at(0)->GetCoord2().x - rectList[value]->GetSplitList().at(0)->GetCoord1().x) > 0)
			glutTimerFunc(60, AnimDiagnoal, value);
		else
			rectList[value]->ClearSplitList();

	}
}

GLvoid SetScreen()
{
	srand(time(0));
	
	for (int i = 0; i < 5; i++)
	{
		GL_Coord c1;
		GL_Coord c2;
		RGB color;
		while (true)
		{
			color.Red = static_cast<float>(rand()) / RAND_MAX;
			color.Green = static_cast<float>(rand()) / RAND_MAX;
			color.Blue = static_cast<float>(rand()) / RAND_MAX;

			bool overlapped = false;
			for (int j = 0; j < i; j++)
			{
				if (rectList[j]->GetColor().Red == color.Red
					|| rectList[j]->GetColor().Green == color.Green
					|| rectList[j]->GetColor().Blue == color.Blue)
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
				if (rectList[j]->GetCoord1().x == c1.x)
					overlapped = true;
			}

			if(overlapped == false)
				if (c2.x <= 1.0f && c2.y >= -1.0f)
					break;
		}

		GL_Rect* r = new GL_Rect(c1.x, c1.y, c2.x, c2.y, color.Red, color.Green, color.Blue);
		rectList[i] = r;
	}
}

GLvoid drawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 5; i++)
	{
		if (rectList[i]->GetValidFlag() == true)
		{
			rectList[i]->DrawRect();
		}

		for (int j = 0; j < rectList[i]->GetSplitList().size(); j++)
		{
			rectList[i]->GetSplitList().at(j)->DrawRect();
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
	GL_Coord current = AdjustMouseCoordinate({ static_cast<GLfloat>(x), static_cast<GLfloat>(y) });

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 4; i >= 0; i--)
		{
			if (rectList[i]->MouseClickCheck(current))
			{
				if (rectList[i]->GetValidFlag() == false)
					continue;

				rectList[i]->SplitRect();
				rectList[i]->SetValidFlag(false);
				AnimStop = false;

				switch (rectList[i]->GetSplitType())
				{
				case STRAIGHT:
					glutTimerFunc(0, AnimStraight, i);
					break;

				case DIAGNOAL:
					glutTimerFunc(0, AnimDiagnoal, i);
					break;

				case BOTH:
					rectList[i]->SetAnimSwitch(true);
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
	glutCreateWindow("실습4");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "Unable to initalize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW initalized" << endl;

	cout << "퍼져 나가는 사각형 애니메이션" << endl;
	cout << "화면의 랜덤한 위치에 5개의 사각형을 랜덤한 색상으로 그린다." << endl;
	cout << "마우스로 사각형 내부를 클릭하면, 사각형은 사등분되어 위치를 이동한다." << endl;
	cout << "이 때, 사각형은 크기가 점점 작아지며 특정 크기가 되면 사라진다." << endl;
	cout << "위치 이동 애니메이션" << endl;
	cout << "	① 좌우상하 이동" << endl;
	cout << "	② 대각선 이동" << endl;
	cout << "	③ 좌우상하대각선 이동(이때는 축소된 사각형이 8개 나타난다)" << endl;
	
	SetScreen();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();

}