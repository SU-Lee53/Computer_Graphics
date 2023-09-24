#include "pch.h"
#include "GL_Rect.h"

GL_Rect::GL_Rect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLclampf Red, GLclampf Green, GLclampf Blue)
{
	this->coord1.x = x1;
	this->coord1.y = y1;
	this->coord2.x = x2;
	this->coord2.y = y2;

	this->color.Red = Red;
	this->color.Green = Green;
	this->color.Blue = Blue;
	this->isValid = true;

	SetSplitType(static_cast<SPLIT_TYPE>(rand() % 3));
	SetCenter();
	SetPoint();
}

GL_Rect::GL_Rect(GLfloat x, GLfloat y, GLfloat size, GLclampf Red, GLclampf Green, GLclampf Blue)
{
	this->coord1.x = x - (size / 2);
	this->coord1.y = y + (size / 2);
	this->coord2.x = x + (size / 2);
	this->coord2.y = y - (size / 2);

	this->color.Red = Red;
	this->color.Green = Green;
	this->color.Blue = Blue;
	this->isValid = true;

	SetSplitType(static_cast<SPLIT_TYPE>(rand() % 3));
	SetCenter();
	SetPoint();
}

GL_Rect::GL_Rect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	this->coord1.x = x1;
	this->coord1.y = y1;
	this->coord2.x = x2;
	this->coord2.y = y2;

	this->ColorRandomize();
	this->isValid = true;

	SetSplitType(static_cast<SPLIT_TYPE>(rand() % 3));
	SetCenter();
	SetPoint();
}

GL_Rect::GL_Rect(GLfloat x, GLfloat y, GLfloat size)
{
	this->coord1.x = x - (size / 2);
	this->coord1.y = y + (size / 2);
	this->coord2.x = x + (size / 2);
	this->coord2.y = y - (size / 2);

	this->ColorRandomize();
	this->isValid = true;

	SetSplitType(static_cast<SPLIT_TYPE>(rand() % 3));
	SetCenter();
	SetPoint();
}

GL_Rect::~GL_Rect()
{
}

GLvoid GL_Rect::SizeChange(GLfloat dx, GLfloat dy)
{
	coord1.x -= dx;
	coord1.y += dy;
	coord2.x += dx;
	coord2.y -= dy;

	point[0] = coord1;
	point[1] = { coord2.x, coord1.y };
	point[2] = { coord1.x, coord2.y };
	point[3] = coord2;

}

GLvoid GL_Rect::SizeRandomize()
{
	GL_Coord before1 = { coord1.x, coord1.y };
	GL_Coord before2 = { coord2.x, coord2.y };

	GLfloat change = (((static_cast<GLfloat>(rand()) / RAND_MAX) - 0.5) * 0.1f);
	coord1.x -= change;
	change = (((static_cast<GLfloat>(rand()) / RAND_MAX) - 0.5) * 0.1f);
	coord1.y += change;
	change = (((static_cast<GLfloat>(rand()) / RAND_MAX) - 0.5) * 0.1f);
	coord2.x += change;
	change = (((static_cast<GLfloat>(rand()) / RAND_MAX) - 0.5) * 0.1f);
	coord2.y -= change;

	// ����� ���� or 0�� �Ǹ� ���󺹱�
	if (coord1.x >= coord2.x || coord1.y <= coord2.y)
	{
		coord1.x = before1.x;
		coord1.y = before1.y;
		coord2.x = before2.x;
		coord2.y = before2.y;
	}

	SetPoint();
}

GLvoid GL_Rect::SetSplitType(SPLIT_TYPE st)
{
	splitType = st;
}

GLvoid GL_Rect::SplitRect()
{
	splitList.clear();

	GL_Rect* r1 = new GL_Rect(coord1.x, coord1.y, (coord1.x + coord2.x) / 2, (coord1.y + coord2.y) / 2, color.Red, color.Green, color.Blue);
	GL_Rect* r2 = new GL_Rect((coord1.x + coord2.x) / 2, coord1.y, coord2.x, (coord1.y + coord2.y) / 2, color.Red, color.Green, color.Blue);
	GL_Rect* r3 = new GL_Rect(coord1.x, (coord1.y + coord2.y) / 2, (coord1.x + coord2.x) / 2, coord2.y, color.Red, color.Green, color.Blue);
	GL_Rect* r4 = new GL_Rect((coord1.x + coord2.x) / 2, (coord1.y + coord2.y) / 2, coord2.x, coord2.y, color.Red, color.Green, color.Blue);
	
	splitList.push_back(r1);
	splitList.push_back(r2);
	splitList.push_back(r3);
	splitList.push_back(r4);

}

GLvoid GL_Rect::DrawRect()
{
	glColor3f(color.Red, color.Green, color.Blue);
	glRectf(coord1.x, coord1.y, coord2.x, coord2.y);
}

GLfloat GL_Rect::GetSize()
{
	GLfloat x = coord2.x - coord1.x;
	GLfloat y = coord1.y - coord2.y;

	return x * y;
}

GLboolean GL_Rect::CollitionCheck(GL_Rect* r1, GL_Rect* r2)
{
	// �浹üũ
	GLboolean Collition = false;

	if (r1->GetSize() >= r2->GetSize())
	{
		// r1�� �� ũ�Ƿ� r2�� ����Ʈ�� r1�ȿ� ����ִٸ� �浹��
		GL_Coord* pointList = r2->GetPoint();
		if ((pointList[0].x >= r1->coord1.x && pointList[0].x <= r1->coord2.x && pointList[0].y <= r1->coord1.y && pointList[0].y >= r1->coord2.y)
			|| (pointList[1].x >= r1->coord1.x && pointList[1].x <= r1->coord2.x && pointList[1].y <= r1->coord1.y && pointList[1].y >= r1->coord2.y)
			|| (pointList[2].x >= r1->coord1.x && pointList[2].x <= r1->coord2.x && pointList[2].y <= r1->coord1.y && pointList[2].y >= r1->coord2.y)
			|| (pointList[3].x >= r1->coord1.x && pointList[3].x <= r1->coord2.x && pointList[3].y <= r1->coord1.y && pointList[3].y >= r1->coord2.y))
		{
			Collition = true;
		}
	}
	else
	{
		// r1�� �� ũ�Ƿ� r2�� ����Ʈ�� r1�ȿ� ����ִٸ� �浹��
		GL_Coord* pointList = r1->GetPoint();
		if ((pointList[0].x >= r2->coord1.x && pointList[0].x <= r2->coord2.x && pointList[0].y <= r2->coord1.y && pointList[0].y >= r2->coord2.y)
			|| (pointList[1].x >= r2->coord1.x && pointList[1].x <= r2->coord2.x && pointList[1].y <= r2->coord1.y && pointList[1].y >= r2->coord2.y)
			|| (pointList[2].x >= r2->coord1.x && pointList[2].x <= r2->coord2.x && pointList[2].y <= r2->coord1.y && pointList[2].y >= r2->coord2.y)
			|| (pointList[3].x >= r2->coord1.x && pointList[3].x <= r2->coord2.x && pointList[3].y <= r2->coord1.y && pointList[3].y >= r2->coord2.y))
		{
			Collition = true;
		}
	}

	return Collition;
}

GLboolean GL_Rect::MouseClickCheck(GL_Coord Clicked)
{
	GLboolean isClicked = false;
	
	if ((Clicked.x >= coord1.x && Clicked.x <= coord2.x)
		&& (Clicked.y <= coord1.y && Clicked.y >= coord2.y))
	{
		isClicked = true;
	}

	return isClicked;

}

GLvoid GL_Rect::AnimStraight()
{
	// �»�� �̵�
	splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x - 0.05f, splitList.at(0)->GetCoord1().y });
	splitList.at(0)->SetCoord2({ splitList.at(0)->GetCoord2().x - 0.05f, splitList.at(0)->GetCoord2().y });

	// ���� �̵�
	splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x, splitList.at(1)->GetCoord1().y + 0.05f });
	splitList.at(1)->SetCoord2({ splitList.at(1)->GetCoord2().x, splitList.at(1)->GetCoord2().y + 0.05f });

	// ���ϴ� �̵�
	splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x, splitList.at(2)->GetCoord1().y - 0.05f });
	splitList.at(2)->SetCoord2({ splitList.at(2)->GetCoord2().x, splitList.at(2)->GetCoord2().y - 0.05f });

	// ���ϴ� �̵�
	splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.05f, splitList.at(3)->GetCoord1().y });
	splitList.at(3)->SetCoord2({ splitList.at(3)->GetCoord2().x + 0.05f, splitList.at(3)->GetCoord2().y });

	// ���
	splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x + 0.02f, splitList.at(0)->GetCoord1().y - 0.02f });
	splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x + 0.02f, splitList.at(1)->GetCoord1().y - 0.02f });
	splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x + 0.02f, splitList.at(2)->GetCoord1().y - 0.02f });
	splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.02f, splitList.at(3)->GetCoord1().y - 0.02f });

	glutPostRedisplay();

}

GLvoid GL_Rect::AnimDiagnoal()
{
	// �»�� �̵�
	splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x - 0.05f, splitList.at(0)->GetCoord1().y + 0.05f });
	splitList.at(0)->SetCoord2({ splitList.at(0)->GetCoord2().x - 0.05f, splitList.at(0)->GetCoord2().y + 0.05f });

	// ���� �̵�
	splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x + 0.05f, splitList.at(1)->GetCoord1().y + 0.05f });
	splitList.at(1)->SetCoord2({ splitList.at(1)->GetCoord2().x + 0.05f, splitList.at(1)->GetCoord2().y + 0.05f });

	// ���ϴ� �̵�
	splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x - 0.05f, splitList.at(2)->GetCoord1().y - 0.05f });
	splitList.at(2)->SetCoord2({ splitList.at(2)->GetCoord2().x - 0.05f, splitList.at(2)->GetCoord2().y - 0.05f });

	// ���ϴ� �̵�
	splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.05f, splitList.at(3)->GetCoord1().y - 0.05f });
	splitList.at(3)->SetCoord2({ splitList.at(3)->GetCoord2().x + 0.05f, splitList.at(3)->GetCoord2().y - 0.05f });

	// ���
	splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x + 0.02f, splitList.at(0)->GetCoord1().y - 0.02f });
	splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x + 0.02f, splitList.at(1)->GetCoord1().y - 0.02f });
	splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x + 0.02f, splitList.at(2)->GetCoord1().y - 0.02f });
	splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.02f, splitList.at(3)->GetCoord1().y - 0.02f });

	glutPostRedisplay();
}

GLvoid GL_Rect::AnimBoth()
{
	if (AnimSwitch == true)
	{

		// 1�ܰ� : ũ�⸦ �ٿ� ���簢������ ������
		// ���
		splitList.at(0)->SetCoord2({ splitList.at(0)->GetCoord2().x - 0.02f, splitList.at(0)->GetCoord2().y });
		splitList.at(1)->SetCoord2({ splitList.at(1)->GetCoord2().x, splitList.at(1)->GetCoord2().y + 0.02f });
		splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x, splitList.at(2)->GetCoord1().y - 0.02f });
		splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.02f, splitList.at(3)->GetCoord1().y });

		glutPostRedisplay();

		if ((splitList.at(0)->GetCoord2().x - splitList.at(0)->GetCoord1().x) * 2 < (splitList.at(0)->GetCoord1().y - splitList.at(0)->GetCoord2().y))

		{
			// 2�ܰ� : splitList�� ���簢���� �� ������ 8���� ������
			GL_Rect* s1 = splitList.at(0);
			GL_Rect* s2 = splitList.at(1);
			GL_Rect* s3 = splitList.at(2);
			GL_Rect* s4 = splitList.at(3);

			splitList.clear();		// splitList ���� �ʱ�ȭ

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

			splitList.push_back(r1);
			splitList.push_back(r2);
			splitList.push_back(r3);
			splitList.push_back(r4);
			splitList.push_back(r5);
			splitList.push_back(r6);
			splitList.push_back(r7);
			splitList.push_back(r8);

			AnimSwitch = false;

		}
	}
	else
	{
		// 1. �밢 �̵�
		// �»�� �̵�
		splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x - 0.03f, splitList.at(0)->GetCoord1().y + 0.03f });
		splitList.at(0)->SetCoord2({ splitList.at(0)->GetCoord2().x - 0.03f, splitList.at(0)->GetCoord2().y + 0.03f });

		// ���� �̵�
		splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x + 0.03f, splitList.at(1)->GetCoord1().y + 0.03f });
		splitList.at(1)->SetCoord2({ splitList.at(1)->GetCoord2().x + 0.03f, splitList.at(1)->GetCoord2().y + 0.03f });

		// ���ϴ� �̵�
		splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x - 0.03f, splitList.at(2)->GetCoord1().y - 0.03f });
		splitList.at(2)->SetCoord2({ splitList.at(2)->GetCoord2().x - 0.03f, splitList.at(2)->GetCoord2().y - 0.03f });

		// ���ϴ� �̵�
		splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.03f, splitList.at(3)->GetCoord1().y - 0.03f });
		splitList.at(3)->SetCoord2({ splitList.at(3)->GetCoord2().x + 0.03f, splitList.at(3)->GetCoord2().y - 0.03f });

		// ���
		splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x + 0.01f, splitList.at(0)->GetCoord1().y - 0.01f });
		splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x + 0.01f, splitList.at(1)->GetCoord1().y - 0.01f });
		splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x + 0.01f, splitList.at(2)->GetCoord1().y - 0.01f });
		splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.01f, splitList.at(3)->GetCoord1().y - 0.01f });

		// 2. ���� �̵�
		// �»�� �̵�
		splitList.at(4)->SetCoord1({ splitList.at(4)->GetCoord1().x - 0.03f, splitList.at(4)->GetCoord1().y });
		splitList.at(4)->SetCoord2({ splitList.at(4)->GetCoord2().x - 0.03f, splitList.at(4)->GetCoord2().y });

		// ���� �̵�
		splitList.at(5)->SetCoord1({ splitList.at(5)->GetCoord1().x, splitList.at(5)->GetCoord1().y + 0.03f });
		splitList.at(5)->SetCoord2({ splitList.at(5)->GetCoord2().x, splitList.at(5)->GetCoord2().y + 0.03f });

		// ���ϴ� �̵�
		splitList.at(6)->SetCoord1({ splitList.at(6)->GetCoord1().x, splitList.at(6)->GetCoord1().y - 0.03f });
		splitList.at(6)->SetCoord2({ splitList.at(6)->GetCoord2().x, splitList.at(6)->GetCoord2().y - 0.03f });

		// ���ϴ� �̵�
		splitList.at(7)->SetCoord1({ splitList.at(7)->GetCoord1().x + 0.03f, splitList.at(7)->GetCoord1().y });
		splitList.at(7)->SetCoord2({ splitList.at(7)->GetCoord2().x + 0.03f, splitList.at(7)->GetCoord2().y });

		// ���
		splitList.at(4)->SetCoord1({ splitList.at(4)->GetCoord1().x + 0.01f, splitList.at(4)->GetCoord1().y - 0.01f });
		splitList.at(5)->SetCoord1({ splitList.at(5)->GetCoord1().x + 0.01f, splitList.at(5)->GetCoord1().y - 0.01f });
		splitList.at(6)->SetCoord1({ splitList.at(6)->GetCoord1().x + 0.01f, splitList.at(6)->GetCoord1().y - 0.01f });
		splitList.at(7)->SetCoord1({ splitList.at(7)->GetCoord1().x + 0.01f, splitList.at(7)->GetCoord1().y - 0.01f });

		glutPostRedisplay();

	}
}

GLvoid GL_Rect::SetPoint()
{
	point[0] = coord1;
	point[1] = { coord2.x, coord1.y };
	point[2] = { coord1.x, coord2.y };
	point[3] = coord2;
}

GLvoid GL_Rect::SetCenter()
{
	center.x = (coord1.x + coord2.x) / 2;
	center.y = (coord1.y + coord2.y) / 2;
}
