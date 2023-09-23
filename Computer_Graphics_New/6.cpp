#include "pch.h"
using namespace std;

// 현재 문제점 : 애니매이션 동시에 재생불가
// 아마도 split을 전역으로 사용하고 있기 때문으로 보임
// 애니매이션도 5개가 다 같은게 나올때가 많은데 씨ㅣㅣㅣ발 rand함수는 좆병신씨발장애인새끼인게 분명하다

GL_Rect* rectList[5];
GLboolean AnimSwitch;

GLvoid AnimBoth(int value)
{
	if (AnimSwitch == true)
	{
		
		// 1단계 : 크기를 줄여 직사각형으로 만들자
		// 축소
		rectList[value]->GetSplitList().at(0)->SetCoord2({rectList[value]->GetSplitList().at(0)->GetCoord2().x - 0.02f, rectList[value]->GetSplitList().at(0)->GetCoord2().y});
		rectList[value]->GetSplitList().at(1)->SetCoord2({ rectList[value]->GetSplitList().at(1)->GetCoord2().x, rectList[value]->GetSplitList().at(1)->GetCoord2().y + 0.02f });
		rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.02f });
		rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(3)->GetCoord1().y });

		glutPostRedisplay();

		if ((rectList[value]->GetSplitList().at(0)->GetCoord2().x - rectList[value]->GetSplitList().at(0)->GetCoord1().x) * 2 >= (rectList[value]->GetSplitList().at(0)->GetCoord1().y - rectList[value]->GetSplitList().at(0)->GetCoord2().y))
			glutTimerFunc(60, AnimBoth, value);
		else
		{
			// 2단계 : rectList[value]->GetSplitList()의 직사각형을 또 나눠서 8개로 만들자
			GL_Rect* s1 = rectList[value]->GetSplitList().at(0);
			GL_Rect* s2 = rectList[value]->GetSplitList().at(1);
			GL_Rect* s3 = rectList[value]->GetSplitList().at(2);
			GL_Rect* s4 = rectList[value]->GetSplitList().at(3);

			rectList[value]->ClearSplitList();	// rectList[value]->GetSplitList() 벡터 초기화

			// 대각선으로 날아갈 놈들부터 r1, r2, r3, r4
			GL_Rect* r1 = new GL_Rect(s1->GetCoord1().x, s1->GetCoord1().y, s1->GetCoord2().x, s1->GetCenter().y, s1->GetColor().Red, s1->GetColor().Green, s1->GetColor().Blue);
			GL_Rect* r2 = new GL_Rect(s2->GetCenter().x, s2->GetCoord1().y, s2->GetCoord2().x, s2->GetCoord2().y, s2->GetColor().Red, s2->GetColor().Green, s2->GetColor().Blue);
			GL_Rect* r3 = new GL_Rect(s3->GetCoord1().x, s3->GetCoord1().y, s3->GetCenter().x, s3->GetCoord2().y, s3->GetColor().Red, s3->GetColor().Green, s3->GetColor().Blue);
			GL_Rect* r4 = new GL_Rect(s4->GetCoord1().x, s4->GetCenter().y, s4->GetCoord2().x, s4->GetCoord2().y, s4->GetColor().Red, s4->GetColor().Green, s4->GetColor().Blue);

			// 직선으로 날아갈 놈들은 r5, r6, r7, r8
			GL_Rect* r5 = new GL_Rect(s1->GetCoord1().x, s1->GetCenter().y, s1->GetCoord2().x, s1->GetCoord2().y, s1->GetColor().Red, s1->GetColor().Green, s1->GetColor().Blue);
			GL_Rect* r6 = new GL_Rect(s2->GetCoord1().x, s2->GetCoord1().y, s2->GetCenter().x, s2->GetCoord2().y, s2->GetColor().Red, s2->GetColor().Green, s2->GetColor().Blue);
			GL_Rect* r7 = new GL_Rect(s3->GetCenter().x, s3->GetCoord1().y, s3->GetCoord2().x, s3->GetCoord2().y, s3->GetColor().Red, s3->GetColor().Green, s3->GetColor().Blue);
			GL_Rect* r8 = new GL_Rect(s4->GetCoord1().x, s4->GetCoord1().y, s4->GetCoord2().x, s4->GetCenter().y, s4->GetColor().Red, s4->GetColor().Green, s4->GetColor().Blue);

			rectList[value]->PushSplitList(r1);
			rectList[value]->PushSplitList(r2);
			rectList[value]->PushSplitList(r3);
			rectList[value]->PushSplitList(r4);
			rectList[value]->PushSplitList(r5);
			rectList[value]->PushSplitList(r6);
			rectList[value]->PushSplitList(r7);
			rectList[value]->PushSplitList(r8);



			AnimSwitch = false;
			glutTimerFunc(60, AnimBoth, value);
		}
	}
	else
	{
		// 1. 대각 이동
		// 좌상단 이동
		rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x - 0.03f, rectList[value]->GetSplitList().at(0)->GetCoord1().y + 0.03f });
		rectList[value]->GetSplitList().at(0)->SetCoord2({ rectList[value]->GetSplitList().at(0)->GetCoord2().x - 0.03f, rectList[value]->GetSplitList().at(0)->GetCoord2().y + 0.03f });

		// 우상단 이동
		rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x + 0.03f, rectList[value]->GetSplitList().at(1)->GetCoord1().y + 0.03f });
		rectList[value]->GetSplitList().at(1)->SetCoord2({ rectList[value]->GetSplitList().at(1)->GetCoord2().x + 0.03f, rectList[value]->GetSplitList().at(1)->GetCoord2().y + 0.03f });

		// 좌하단 이동
		rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x - 0.03f, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.03f });
		rectList[value]->GetSplitList().at(2)->SetCoord2({ rectList[value]->GetSplitList().at(2)->GetCoord2().x - 0.03f, rectList[value]->GetSplitList().at(2)->GetCoord2().y - 0.03f });

		// 우하단 이동
		rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.03f, rectList[value]->GetSplitList().at(3)->GetCoord1().y - 0.03f });
		rectList[value]->GetSplitList().at(3)->SetCoord2({ rectList[value]->GetSplitList().at(3)->GetCoord2().x + 0.03f, rectList[value]->GetSplitList().at(3)->GetCoord2().y - 0.03f });

		// 축소
		rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(0)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(1)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(3)->GetCoord1().y - 0.01f });

		// 2. 직선 이동
		// 좌상단 이동
		rectList[value]->GetSplitList().at(4)->SetCoord1({ rectList[value]->GetSplitList().at(4)->GetCoord1().x - 0.03f, rectList[value]->GetSplitList().at(4)->GetCoord1().y });
		rectList[value]->GetSplitList().at(4)->SetCoord2({ rectList[value]->GetSplitList().at(4)->GetCoord2().x - 0.03f, rectList[value]->GetSplitList().at(4)->GetCoord2().y });

		// 우상단 이동
		rectList[value]->GetSplitList().at(5)->SetCoord1({ rectList[value]->GetSplitList().at(5)->GetCoord1().x, rectList[value]->GetSplitList().at(5)->GetCoord1().y + 0.03f });
		rectList[value]->GetSplitList().at(5)->SetCoord2({ rectList[value]->GetSplitList().at(5)->GetCoord2().x, rectList[value]->GetSplitList().at(5)->GetCoord2().y + 0.03f });

		// 좌하단 이동
		rectList[value]->GetSplitList().at(6)->SetCoord1({ rectList[value]->GetSplitList().at(6)->GetCoord1().x, rectList[value]->GetSplitList().at(6)->GetCoord1().y - 0.03f });
		rectList[value]->GetSplitList().at(6)->SetCoord2({ rectList[value]->GetSplitList().at(6)->GetCoord2().x, rectList[value]->GetSplitList().at(6)->GetCoord2().y - 0.03f });

		// 우하단 이동
		rectList[value]->GetSplitList().at(7)->SetCoord1({ rectList[value]->GetSplitList().at(7)->GetCoord1().x + 0.03f, rectList[value]->GetSplitList().at(7)->GetCoord1().y });
		rectList[value]->GetSplitList().at(7)->SetCoord2({ rectList[value]->GetSplitList().at(7)->GetCoord2().x + 0.03f, rectList[value]->GetSplitList().at(7)->GetCoord2().y });

		// 축소
		rectList[value]->GetSplitList().at(4)->SetCoord1({ rectList[value]->GetSplitList().at(4)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(4)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(5)->SetCoord1({ rectList[value]->GetSplitList().at(5)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(5)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(6)->SetCoord1({ rectList[value]->GetSplitList().at(6)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(6)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(7)->SetCoord1({ rectList[value]->GetSplitList().at(7)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(7)->GetCoord1().y - 0.01f });

		glutPostRedisplay();


		if ((rectList[value]->GetSplitList().at(0)->GetCoord2().x - rectList[value]->GetSplitList().at(0)->GetCoord1().x) >= 0)
			glutTimerFunc(60, AnimBoth, value);
		else
			rectList[value]->ClearSplitList();

	}
}

GLvoid AnimStraight(int value)
{
	// 좌상단 이동
	rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x - 0.05f, rectList[value]->GetSplitList().at(0)->GetCoord1().y });
	rectList[value]->GetSplitList().at(0)->SetCoord2({ rectList[value]->GetSplitList().at(0)->GetCoord2().x - 0.05f, rectList[value]->GetSplitList().at(0)->GetCoord2().y });

	// 우상단 이동
	rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x, rectList[value]->GetSplitList().at(1)->GetCoord1().y + 0.05f });
	rectList[value]->GetSplitList().at(1)->SetCoord2({ rectList[value]->GetSplitList().at(1)->GetCoord2().x, rectList[value]->GetSplitList().at(1)->GetCoord2().y + 0.05f });

	// 좌하단 이동
	rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.05f });
	rectList[value]->GetSplitList().at(2)->SetCoord2({ rectList[value]->GetSplitList().at(2)->GetCoord2().x, rectList[value]->GetSplitList().at(2)->GetCoord2().y - 0.05f });

	// 우하단 이동
	rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.05f, rectList[value]->GetSplitList().at(3)->GetCoord1().y });
	rectList[value]->GetSplitList().at(3)->SetCoord2({ rectList[value]->GetSplitList().at(3)->GetCoord2().x + 0.05f, rectList[value]->GetSplitList().at(3)->GetCoord2().y });

	// 축소
	rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(0)->GetCoord1().y - 0.02f });
	rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(1)->GetCoord1().y - 0.02f });
	rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.02f });
	rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(3)->GetCoord1().y - 0.02f });

	glutPostRedisplay();

	if ((rectList[value]->GetSplitList().at(0)->GetCoord2().x - rectList[value]->GetSplitList().at(0)->GetCoord1().x) > 0)
		glutTimerFunc(60, AnimStraight, value);
	else
		rectList[value]->ClearSplitList();

}

GLvoid AnimDiagnoal(int value)
{

	// 좌상단 이동
	rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x - 0.05f, rectList[value]->GetSplitList().at(0)->GetCoord1().y + 0.05f });
	rectList[value]->GetSplitList().at(0)->SetCoord2({ rectList[value]->GetSplitList().at(0)->GetCoord2().x - 0.05f, rectList[value]->GetSplitList().at(0)->GetCoord2().y + 0.05f });

	// 우상단 이동
	rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x + 0.05f, rectList[value]->GetSplitList().at(1)->GetCoord1().y + 0.05f });
	rectList[value]->GetSplitList().at(1)->SetCoord2({ rectList[value]->GetSplitList().at(1)->GetCoord2().x + 0.05f, rectList[value]->GetSplitList().at(1)->GetCoord2().y + 0.05f });

	// 좌하단 이동
	rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x - 0.05f, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.05f });
	rectList[value]->GetSplitList().at(2)->SetCoord2({ rectList[value]->GetSplitList().at(2)->GetCoord2().x - 0.05f, rectList[value]->GetSplitList().at(2)->GetCoord2().y - 0.05f });

	// 우하단 이동
	rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.05f, rectList[value]->GetSplitList().at(3)->GetCoord1().y - 0.05f });
	rectList[value]->GetSplitList().at(3)->SetCoord2({ rectList[value]->GetSplitList().at(3)->GetCoord2().x + 0.05f, rectList[value]->GetSplitList().at(3)->GetCoord2().y - 0.05f });

	// 축소
	rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(0)->GetCoord1().y - 0.02f });
	rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(1)->GetCoord1().y - 0.02f });
	rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.02f });
	rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(3)->GetCoord1().y - 0.02f });

	glutPostRedisplay();

	if ((rectList[value]->GetSplitList().at(0)->GetCoord2().x - rectList[value]->GetSplitList().at(0)->GetCoord1().x) > 0)
		glutTimerFunc(60, AnimDiagnoal, value);
	else
		rectList[value]->ClearSplitList();
	
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
		if(rectList[i]->GetValidFlag() == true)
			rectList[i]->DrawRect();

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
		for (int i = 0; i < 5; i++)
		{
			if (rectList[i]->MouseClickCheck(current))
			{
				if (rectList[i]->GetValidFlag() == false)
					break;
				
				rectList[i]->SplitRect();
				rectList[i]->SetValidFlag(false);

				switch (rectList[i]->GetSplitType())
				{
				case STRAIGHT:
					glutTimerFunc(0, AnimStraight, i);
					break;

				case DIAGNOAL:
					glutTimerFunc(0, AnimDiagnoal, i);
					break;

				case BOTH:
					AnimSwitch = true;
					glutTimerFunc(0, AnimBoth, i);
				}
			}
		}
	}
	
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == 'r')
	{
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

	// 현재 대충 클래스로 사각형까지 그려짐
}