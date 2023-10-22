#include "pch.h"
#include "Ex18.h"
#include "Ex19.h"
#include "Ex20.h"
// 전역 실습 로드 매크로: __defines 에 정의되어있음
// ()안에 이름만 바꿔끼워넣으면 로드 완료

LOAD_EX(Ex18);
// LOAD_EX(Ex19);
// LOAD_EX(Ex20);



void drawScene()
{
	ex->drawScene();
}

void Reshape(int w, int h)
{
	ex->Reshape(w, h);
}

int main(int argc, char** argv)
{
	Core::GetInstance().InitScreen(argc, argv, 100, 100, 800, 800, "Examples");
	Core::GetInstance().InitShader();

	Core::GetInstance().BindDrawCallback(drawScene);
	Core::GetInstance().BindReshapeCallback(Reshape);
	Core::GetInstance().UseKeyboardCallback();
	Core::GetInstance().UseSpecialKeyCallback();
	

	while (true)
	{
		glutMainLoopEvent();
	}

}
