#include "pch.h"
#include "Ex14.h"
#include "Ex15.h"
#include "Ex16.h"

// 전역 실습 로드 매크로: __defines 에 정의되어있음
// ()안에 이름만 바꿔끼워넣으면 로드 완료

LOAD_EX(Ex16);

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
