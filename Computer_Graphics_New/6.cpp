#include "pch.h"
using namespace std;

// ���� ������ : �ִϸ��̼� ���ÿ� ����Ұ�
// �Ƹ��� split�� �������� ����ϰ� �ֱ� �������� ����
// �ִϸ��̼ǵ� 5���� �� ������ ���ö��� ������ ���ӤӤӹ� rand�Լ��� �����ž�������λ����ΰ� �и��ϴ�

GL_Rect* rectList[5];
GLboolean AnimSwitch;

GLvoid AnimBoth(int value)
{
	if (AnimSwitch == true)
	{
		
		// 1�ܰ� : ũ�⸦ �ٿ� ���簢������ ������
		// ���
		rectList[value]->GetSplitList().at(0)->SetCoord2({rectList[value]->GetSplitList().at(0)->GetCoord2().x - 0.02f, rectList[value]->GetSplitList().at(0)->GetCoord2().y});
		rectList[value]->GetSplitList().at(1)->SetCoord2({ rectList[value]->GetSplitList().at(1)->GetCoord2().x, rectList[value]->GetSplitList().at(1)->GetCoord2().y + 0.02f });
		rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.02f });
		rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.02f, rectList[value]->GetSplitList().at(3)->GetCoord1().y });

		glutPostRedisplay();

		if ((rectList[value]->GetSplitList().at(0)->GetCoord2().x - rectList[value]->GetSplitList().at(0)->GetCoord1().x) * 2 >= (rectList[value]->GetSplitList().at(0)->GetCoord1().y - rectList[value]->GetSplitList().at(0)->GetCoord2().y))
			glutTimerFunc(60, AnimBoth, value);
		else
		{
			// 2�ܰ� : rectList[value]->GetSplitList()�� ���簢���� �� ������ 8���� ������
			GL_Rect* s1 = rectList[value]->GetSplitList().at(0);
			GL_Rect* s2 = rectList[value]->GetSplitList().at(1);
			GL_Rect* s3 = rectList[value]->GetSplitList().at(2);
			GL_Rect* s4 = rectList[value]->GetSplitList().at(3);

			rectList[value]->ClearSplitList();	// rectList[value]->GetSplitList() ���� �ʱ�ȭ

			// �밢������ ���ư� ������ r1, r2, r3, r4
			GL_Rect* r1 = new GL_Rect(s1->GetCoord1().x, s1->GetCoord1().y, s1->GetCoord2().x, s1->GetCenter().y, s1->GetColor().Red, s1->GetColor().Green, s1->GetColor().Blue);
			GL_Rect* r2 = new GL_Rect(s2->GetCenter().x, s2->GetCoord1().y, s2->GetCoord2().x, s2->GetCoord2().y, s2->GetColor().Red, s2->GetColor().Green, s2->GetColor().Blue);
			GL_Rect* r3 = new GL_Rect(s3->GetCoord1().x, s3->GetCoord1().y, s3->GetCenter().x, s3->GetCoord2().y, s3->GetColor().Red, s3->GetColor().Green, s3->GetColor().Blue);
			GL_Rect* r4 = new GL_Rect(s4->GetCoord1().x, s4->GetCenter().y, s4->GetCoord2().x, s4->GetCoord2().y, s4->GetColor().Red, s4->GetColor().Green, s4->GetColor().Blue);

			// �������� ���ư� ����� r5, r6, r7, r8
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
		// 1. �밢 �̵�
		// �»�� �̵�
		rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x - 0.03f, rectList[value]->GetSplitList().at(0)->GetCoord1().y + 0.03f });
		rectList[value]->GetSplitList().at(0)->SetCoord2({ rectList[value]->GetSplitList().at(0)->GetCoord2().x - 0.03f, rectList[value]->GetSplitList().at(0)->GetCoord2().y + 0.03f });

		// ���� �̵�
		rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x + 0.03f, rectList[value]->GetSplitList().at(1)->GetCoord1().y + 0.03f });
		rectList[value]->GetSplitList().at(1)->SetCoord2({ rectList[value]->GetSplitList().at(1)->GetCoord2().x + 0.03f, rectList[value]->GetSplitList().at(1)->GetCoord2().y + 0.03f });

		// ���ϴ� �̵�
		rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x - 0.03f, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.03f });
		rectList[value]->GetSplitList().at(2)->SetCoord2({ rectList[value]->GetSplitList().at(2)->GetCoord2().x - 0.03f, rectList[value]->GetSplitList().at(2)->GetCoord2().y - 0.03f });

		// ���ϴ� �̵�
		rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.03f, rectList[value]->GetSplitList().at(3)->GetCoord1().y - 0.03f });
		rectList[value]->GetSplitList().at(3)->SetCoord2({ rectList[value]->GetSplitList().at(3)->GetCoord2().x + 0.03f, rectList[value]->GetSplitList().at(3)->GetCoord2().y - 0.03f });

		// ���
		rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(0)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(1)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.01f });
		rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.01f, rectList[value]->GetSplitList().at(3)->GetCoord1().y - 0.01f });

		// 2. ���� �̵�
		// �»�� �̵�
		rectList[value]->GetSplitList().at(4)->SetCoord1({ rectList[value]->GetSplitList().at(4)->GetCoord1().x - 0.03f, rectList[value]->GetSplitList().at(4)->GetCoord1().y });
		rectList[value]->GetSplitList().at(4)->SetCoord2({ rectList[value]->GetSplitList().at(4)->GetCoord2().x - 0.03f, rectList[value]->GetSplitList().at(4)->GetCoord2().y });

		// ���� �̵�
		rectList[value]->GetSplitList().at(5)->SetCoord1({ rectList[value]->GetSplitList().at(5)->GetCoord1().x, rectList[value]->GetSplitList().at(5)->GetCoord1().y + 0.03f });
		rectList[value]->GetSplitList().at(5)->SetCoord2({ rectList[value]->GetSplitList().at(5)->GetCoord2().x, rectList[value]->GetSplitList().at(5)->GetCoord2().y + 0.03f });

		// ���ϴ� �̵�
		rectList[value]->GetSplitList().at(6)->SetCoord1({ rectList[value]->GetSplitList().at(6)->GetCoord1().x, rectList[value]->GetSplitList().at(6)->GetCoord1().y - 0.03f });
		rectList[value]->GetSplitList().at(6)->SetCoord2({ rectList[value]->GetSplitList().at(6)->GetCoord2().x, rectList[value]->GetSplitList().at(6)->GetCoord2().y - 0.03f });

		// ���ϴ� �̵�
		rectList[value]->GetSplitList().at(7)->SetCoord1({ rectList[value]->GetSplitList().at(7)->GetCoord1().x + 0.03f, rectList[value]->GetSplitList().at(7)->GetCoord1().y });
		rectList[value]->GetSplitList().at(7)->SetCoord2({ rectList[value]->GetSplitList().at(7)->GetCoord2().x + 0.03f, rectList[value]->GetSplitList().at(7)->GetCoord2().y });

		// ���
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
	// �»�� �̵�
	rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x - 0.05f, rectList[value]->GetSplitList().at(0)->GetCoord1().y });
	rectList[value]->GetSplitList().at(0)->SetCoord2({ rectList[value]->GetSplitList().at(0)->GetCoord2().x - 0.05f, rectList[value]->GetSplitList().at(0)->GetCoord2().y });

	// ���� �̵�
	rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x, rectList[value]->GetSplitList().at(1)->GetCoord1().y + 0.05f });
	rectList[value]->GetSplitList().at(1)->SetCoord2({ rectList[value]->GetSplitList().at(1)->GetCoord2().x, rectList[value]->GetSplitList().at(1)->GetCoord2().y + 0.05f });

	// ���ϴ� �̵�
	rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.05f });
	rectList[value]->GetSplitList().at(2)->SetCoord2({ rectList[value]->GetSplitList().at(2)->GetCoord2().x, rectList[value]->GetSplitList().at(2)->GetCoord2().y - 0.05f });

	// ���ϴ� �̵�
	rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.05f, rectList[value]->GetSplitList().at(3)->GetCoord1().y });
	rectList[value]->GetSplitList().at(3)->SetCoord2({ rectList[value]->GetSplitList().at(3)->GetCoord2().x + 0.05f, rectList[value]->GetSplitList().at(3)->GetCoord2().y });

	// ���
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

	// �»�� �̵�
	rectList[value]->GetSplitList().at(0)->SetCoord1({ rectList[value]->GetSplitList().at(0)->GetCoord1().x - 0.05f, rectList[value]->GetSplitList().at(0)->GetCoord1().y + 0.05f });
	rectList[value]->GetSplitList().at(0)->SetCoord2({ rectList[value]->GetSplitList().at(0)->GetCoord2().x - 0.05f, rectList[value]->GetSplitList().at(0)->GetCoord2().y + 0.05f });

	// ���� �̵�
	rectList[value]->GetSplitList().at(1)->SetCoord1({ rectList[value]->GetSplitList().at(1)->GetCoord1().x + 0.05f, rectList[value]->GetSplitList().at(1)->GetCoord1().y + 0.05f });
	rectList[value]->GetSplitList().at(1)->SetCoord2({ rectList[value]->GetSplitList().at(1)->GetCoord2().x + 0.05f, rectList[value]->GetSplitList().at(1)->GetCoord2().y + 0.05f });

	// ���ϴ� �̵�
	rectList[value]->GetSplitList().at(2)->SetCoord1({ rectList[value]->GetSplitList().at(2)->GetCoord1().x - 0.05f, rectList[value]->GetSplitList().at(2)->GetCoord1().y - 0.05f });
	rectList[value]->GetSplitList().at(2)->SetCoord2({ rectList[value]->GetSplitList().at(2)->GetCoord2().x - 0.05f, rectList[value]->GetSplitList().at(2)->GetCoord2().y - 0.05f });

	// ���ϴ� �̵�
	rectList[value]->GetSplitList().at(3)->SetCoord1({ rectList[value]->GetSplitList().at(3)->GetCoord1().x + 0.05f, rectList[value]->GetSplitList().at(3)->GetCoord1().y - 0.05f });
	rectList[value]->GetSplitList().at(3)->SetCoord2({ rectList[value]->GetSplitList().at(3)->GetCoord2().x + 0.05f, rectList[value]->GetSplitList().at(3)->GetCoord2().y - 0.05f });

	// ���
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
	glutCreateWindow("�ǽ�4");

	glewExperimental = GL_TRUE;
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

	// ���� ���� Ŭ������ �簢������ �׷���
}