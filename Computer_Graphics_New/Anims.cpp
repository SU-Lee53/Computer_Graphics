#include "pch.h"
#include "Anims.h"

Anims* Anims::s_instance = nullptr;

Anims::Anims() : current(nullptr), AnimSwitch(true), AnimEnd(false)
{
	splitList.clear();
	reSplit.clear();
}

Anims::~Anims()
{
}

void Anims::AnimStraight()
{
	// 좌상단 이동
	splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x - 0.05f, splitList.at(0)->GetCoord1().y });
	splitList.at(0)->SetCoord2({ splitList.at(0)->GetCoord2().x - 0.05f, splitList.at(0)->GetCoord2().y });

	// 우상단 이동
	splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x, splitList.at(1)->GetCoord1().y + 0.05f });
	splitList.at(1)->SetCoord2({ splitList.at(1)->GetCoord2().x, splitList.at(1)->GetCoord2().y + 0.05f });

	// 좌하단 이동
	splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x, splitList.at(2)->GetCoord1().y - 0.05f });
	splitList.at(2)->SetCoord2({ splitList.at(2)->GetCoord2().x, splitList.at(2)->GetCoord2().y - 0.05f });

	// 우하단 이동
	splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.05f, splitList.at(3)->GetCoord1().y });
	splitList.at(3)->SetCoord2({ splitList.at(3)->GetCoord2().x + 0.05f, splitList.at(3)->GetCoord2().y });

	// 축소
	splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x + 0.02f, splitList.at(0)->GetCoord1().y - 0.02f });
	splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x + 0.02f, splitList.at(1)->GetCoord1().y - 0.02f });
	splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x + 0.02f, splitList.at(2)->GetCoord1().y - 0.02f });
	splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.02f, splitList.at(3)->GetCoord1().y - 0.02f });

	if (splitList.at(0)->GetCoord2().x - splitList.at(0)->GetCoord1().x <= 0)
	{
		splitList.clear();
	}
}

void Anims::AnimDiagnoal()
{
	// 좌상단 이동
	splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x - 0.05f, splitList.at(0)->GetCoord1().y + 0.05f });
	splitList.at(0)->SetCoord2({ splitList.at(0)->GetCoord2().x - 0.05f, splitList.at(0)->GetCoord2().y + 0.05f });

	// 우상단 이동
	splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x + 0.05f, splitList.at(1)->GetCoord1().y + 0.05f });
	splitList.at(1)->SetCoord2({ splitList.at(1)->GetCoord2().x + 0.05f, splitList.at(1)->GetCoord2().y + 0.05f });

	// 좌하단 이동
	splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x - 0.05f, splitList.at(2)->GetCoord1().y - 0.05f });
	splitList.at(2)->SetCoord2({ splitList.at(2)->GetCoord2().x - 0.05f, splitList.at(2)->GetCoord2().y - 0.05f });

	// 우하단 이동
	splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.05f, splitList.at(3)->GetCoord1().y - 0.05f });
	splitList.at(3)->SetCoord2({ splitList.at(3)->GetCoord2().x + 0.05f, splitList.at(3)->GetCoord2().y - 0.05f });

	// 축소
	splitList.at(0)->SetCoord1({ splitList.at(0)->GetCoord1().x + 0.02f, splitList.at(0)->GetCoord1().y - 0.02f });
	splitList.at(1)->SetCoord1({ splitList.at(1)->GetCoord1().x + 0.02f, splitList.at(1)->GetCoord1().y - 0.02f });
	splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x + 0.02f, splitList.at(2)->GetCoord1().y - 0.02f });
	splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.02f, splitList.at(3)->GetCoord1().y - 0.02f });

	if (splitList.at(0)->GetCoord2().x - splitList.at(0)->GetCoord1().x <= 0)
	{
		splitList.clear();
	}

}

void Anims::AnimBoth()
{
	if (AnimSwitch == true)
	{

		// 1단계 : 크기를 줄여 직사각형으로 만들자
		// 축소
		splitList.at(0)->SetCoord2({ splitList.at(0)->GetCoord2().x - 0.02f, splitList.at(0)->GetCoord2().y });
		splitList.at(1)->SetCoord2({ splitList.at(1)->GetCoord2().x, splitList.at(1)->GetCoord2().y + 0.02f });
		splitList.at(2)->SetCoord1({ splitList.at(2)->GetCoord1().x, splitList.at(2)->GetCoord1().y - 0.02f });
		splitList.at(3)->SetCoord1({ splitList.at(3)->GetCoord1().x + 0.02f, splitList.at(3)->GetCoord1().y });

		glutPostRedisplay();

		if ((splitList.at(0)->GetCoord2().x - splitList.at(0)->GetCoord1().x) * 2 < (splitList.at(0)->GetCoord1().y - splitList.at(0)->GetCoord2().y))

		{
			// 2단계 : splitList의 직사각형을 또 나눠서 8개로 만들자
			Rect* s1 = splitList.at(0);
			Rect* s2 = splitList.at(1);
			Rect* s3 = splitList.at(2);
			Rect* s4 = splitList.at(3);

			splitList.clear();		// splitList 벡터 초기화

			// 대각선으로 날아갈 놈들부터 r1, r2, r3, r4
			Rect* r1 = new Rect(s1->GetCoord1().x, s1->GetCoord1().y, s1->GetCoord2().x, s1->GetCenter().y, s1->GetColor().Red, s1->GetColor().Green, s1->GetColor().Blue);
			Rect* r2 = new Rect(s2->GetCenter().x, s2->GetCoord1().y, s2->GetCoord2().x, s2->GetCoord2().y, s2->GetColor().Red, s2->GetColor().Green, s2->GetColor().Blue);
			Rect* r3 = new Rect(s3->GetCoord1().x, s3->GetCoord1().y, s3->GetCenter().x, s3->GetCoord2().y, s3->GetColor().Red, s3->GetColor().Green, s3->GetColor().Blue);
			Rect* r4 = new Rect(s4->GetCoord1().x, s4->GetCenter().y, s4->GetCoord2().x, s4->GetCoord2().y, s4->GetColor().Red, s4->GetColor().Green, s4->GetColor().Blue);

			// 직선으로 날아갈 놈들은 r5, r6, r7, r8
			Rect* r5 = new Rect(s1->GetCoord1().x, s1->GetCenter().y, s1->GetCoord2().x, s1->GetCoord2().y, s1->GetColor().Red, s1->GetColor().Green, s1->GetColor().Blue);
			Rect* r6 = new Rect(s2->GetCoord1().x, s2->GetCoord1().y, s2->GetCenter().x, s2->GetCoord2().y, s2->GetColor().Red, s2->GetColor().Green, s2->GetColor().Blue);
			Rect* r7 = new Rect(s3->GetCenter().x, s3->GetCoord1().y, s3->GetCoord2().x, s3->GetCoord2().y, s3->GetColor().Red, s3->GetColor().Green, s3->GetColor().Blue);
			Rect* r8 = new Rect(s4->GetCoord1().x, s4->GetCoord1().y, s4->GetCoord2().x, s4->GetCenter().y, s4->GetColor().Red, s4->GetColor().Green, s4->GetColor().Blue);

			reSplit.push_back(r1);
			reSplit.push_back(r2);
			reSplit.push_back(r3);
			reSplit.push_back(r4);
			reSplit.push_back(r5);
			reSplit.push_back(r6);
			reSplit.push_back(r7);
			reSplit.push_back(r8);

			AnimSwitch = false;

		}
	}
	else
	{
		// 1. 대각 이동
		// 좌상단 이동
		reSplit.at(0)->SetCoord1({ reSplit.at(0)->GetCoord1().x - 0.03f, reSplit.at(0)->GetCoord1().y + 0.03f });
		reSplit.at(0)->SetCoord2({ reSplit.at(0)->GetCoord2().x - 0.03f, reSplit.at(0)->GetCoord2().y + 0.03f });

		// 우상단 이동
		reSplit.at(1)->SetCoord1({ reSplit.at(1)->GetCoord1().x + 0.03f, reSplit.at(1)->GetCoord1().y + 0.03f });
		reSplit.at(1)->SetCoord2({ reSplit.at(1)->GetCoord2().x + 0.03f, reSplit.at(1)->GetCoord2().y + 0.03f });

		// 좌하단 이동
		reSplit.at(2)->SetCoord1({ reSplit.at(2)->GetCoord1().x - 0.03f, reSplit.at(2)->GetCoord1().y - 0.03f });
		reSplit.at(2)->SetCoord2({ reSplit.at(2)->GetCoord2().x - 0.03f, reSplit.at(2)->GetCoord2().y - 0.03f });

		// 우하단 이동
		reSplit.at(3)->SetCoord1({ reSplit.at(3)->GetCoord1().x + 0.03f, reSplit.at(3)->GetCoord1().y - 0.03f });
		reSplit.at(3)->SetCoord2({ reSplit.at(3)->GetCoord2().x + 0.03f, reSplit.at(3)->GetCoord2().y - 0.03f });

		// 축소
		reSplit.at(0)->SetCoord1({ reSplit.at(0)->GetCoord1().x + 0.01f, reSplit.at(0)->GetCoord1().y - 0.01f });
		reSplit.at(1)->SetCoord1({ reSplit.at(1)->GetCoord1().x + 0.01f, reSplit.at(1)->GetCoord1().y - 0.01f });
		reSplit.at(2)->SetCoord1({ reSplit.at(2)->GetCoord1().x + 0.01f, reSplit.at(2)->GetCoord1().y - 0.01f });
		reSplit.at(3)->SetCoord1({ reSplit.at(3)->GetCoord1().x + 0.01f, reSplit.at(3)->GetCoord1().y - 0.01f });

		// 2. 직선 이동
		// 좌상단 이동
		reSplit.at(4)->SetCoord1({ reSplit.at(4)->GetCoord1().x - 0.03f, reSplit.at(4)->GetCoord1().y });
		reSplit.at(4)->SetCoord2({ reSplit.at(4)->GetCoord2().x - 0.03f, reSplit.at(4)->GetCoord2().y });

		// 우상단 이동
		reSplit.at(5)->SetCoord1({ reSplit.at(5)->GetCoord1().x, reSplit.at(5)->GetCoord1().y + 0.03f });
		reSplit.at(5)->SetCoord2({ reSplit.at(5)->GetCoord2().x, reSplit.at(5)->GetCoord2().y + 0.03f });

		// 좌하단 이동
		reSplit.at(6)->SetCoord1({ reSplit.at(6)->GetCoord1().x, reSplit.at(6)->GetCoord1().y - 0.03f });
		reSplit.at(6)->SetCoord2({ reSplit.at(6)->GetCoord2().x, reSplit.at(6)->GetCoord2().y - 0.03f });

		// 우하단 이동
		reSplit.at(7)->SetCoord1({ reSplit.at(7)->GetCoord1().x + 0.03f, reSplit.at(7)->GetCoord1().y });
		reSplit.at(7)->SetCoord2({ reSplit.at(7)->GetCoord2().x + 0.03f, reSplit.at(7)->GetCoord2().y });

		// 축소
		reSplit.at(4)->SetCoord1({ reSplit.at(4)->GetCoord1().x + 0.01f, reSplit.at(4)->GetCoord1().y - 0.01f });
		reSplit.at(5)->SetCoord1({ reSplit.at(5)->GetCoord1().x + 0.01f, reSplit.at(5)->GetCoord1().y - 0.01f });
		reSplit.at(6)->SetCoord1({ reSplit.at(6)->GetCoord1().x + 0.01f, reSplit.at(6)->GetCoord1().y - 0.01f });
		reSplit.at(7)->SetCoord1({ reSplit.at(7)->GetCoord1().x + 0.01f, reSplit.at(7)->GetCoord1().y - 0.01f });

		if (reSplit.at(0)->GetCoord2().x - reSplit.at(0)->GetCoord1().x <= 0)
		{
			splitList.clear();
			reSplit.clear();
			AnimEnd = true;
		}
	}
}

Anims* Anims::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Anims;
	}

	return s_instance;
}

void Anims::SetSplitList(Rect* rect)
{
	splitList = rect->SplitRect();

}
