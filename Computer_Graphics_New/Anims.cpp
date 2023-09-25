#include "pch.h"
#include "Anims.h"

Anims::Anims() : current(nullptr), AnimSwitch(true), AnimEnd(false)
{
	splitList.clear();
}

Anims::Anims(Rect* r) : AnimSwitch(true), AnimEnd(false)
{
	current = r;
	SetSplitList(r);
}

Anims::~Anims()
{
}

void Anims::AnimStraight()
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

	if (splitList.at(0)->GetCoord2().x - splitList.at(0)->GetCoord1().x <= 0)
	{
		for (int i = 0; i < splitList.size(); i++)
		{
			splitList.at(i)->~Rect();
		}

		splitList.clear();
	}
}

void Anims::AnimDiagnoal()
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

	if (splitList.at(0)->GetCoord2().x - splitList.at(0)->GetCoord1().x <= 0)
	{
		for (int i = 0; i < splitList.size(); i++)
		{
			splitList.at(i)->~Rect();
		}

		splitList.clear();
	}

}

void Anims::AnimBoth()
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
			Rect* s1 = splitList.at(0);
			Rect* s2 = splitList.at(1);
			Rect* s3 = splitList.at(2);
			Rect* s4 = splitList.at(3);



			for (int i = 0; i < splitList.size(); i++)
			{
				splitList.at(i)->~Rect();
			}


			splitList.clear();		// splitList ���� �ʱ�ȭ

			// �밢������ ���ư� ������ r1, r2, r3, r4
			Rect* r1 = new Rect(s1->GetCoord1().x, s1->GetCoord1().y, s1->GetCoord2().x, s1->GetCenter().y, s1->GetColor().Red, s1->GetColor().Green, s1->GetColor().Blue);
			Rect* r2 = new Rect(s2->GetCenter().x, s2->GetCoord1().y, s2->GetCoord2().x, s2->GetCoord2().y, s2->GetColor().Red, s2->GetColor().Green, s2->GetColor().Blue);
			Rect* r3 = new Rect(s3->GetCoord1().x, s3->GetCoord1().y, s3->GetCenter().x, s3->GetCoord2().y, s3->GetColor().Red, s3->GetColor().Green, s3->GetColor().Blue);
			Rect* r4 = new Rect(s4->GetCoord1().x, s4->GetCenter().y, s4->GetCoord2().x, s4->GetCoord2().y, s4->GetColor().Red, s4->GetColor().Green, s4->GetColor().Blue);

			// �������� ���ư� ����� r5, r6, r7, r8
			Rect* r5 = new Rect(s1->GetCoord1().x, s1->GetCenter().y, s1->GetCoord2().x, s1->GetCoord2().y, s1->GetColor().Red, s1->GetColor().Green, s1->GetColor().Blue);
			Rect* r6 = new Rect(s2->GetCoord1().x, s2->GetCoord1().y, s2->GetCenter().x, s2->GetCoord2().y, s2->GetColor().Red, s2->GetColor().Green, s2->GetColor().Blue);
			Rect* r7 = new Rect(s3->GetCenter().x, s3->GetCoord1().y, s3->GetCoord2().x, s3->GetCoord2().y, s3->GetColor().Red, s3->GetColor().Green, s3->GetColor().Blue);
			Rect* r8 = new Rect(s4->GetCoord1().x, s4->GetCoord1().y, s4->GetCoord2().x, s4->GetCenter().y, s4->GetColor().Red, s4->GetColor().Green, s4->GetColor().Blue);

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

		if (splitList.at(0)->GetCoord2().x - splitList.at(0)->GetCoord1().x <= 0)
		{
			for (int i = 0; i < splitList.size(); i++)
			{
				splitList.at(i)->~Rect();
			}
			splitList.clear();

			AnimEnd = true;
		}
	}
}

void Anims::SetSplitList(Rect* rect)
{
	splitList = rect->SplitRect();
}

void Anims::SetSplitList(Rect* rect)
{
	splitList = rect->SplitRect();

}
