#include "pch.h"
#include "Ex14.h"

// 전역 실습 로드 매크로: __defines 에 정의되어있음
// ()안에 이름만 바꿔끼워넣으면 로드 완료
LOAD_EX(Ex14);

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
	Core::GetInstance().InitScreen(argc, argv, 100, 100, 800, 600, "14");
	Core::GetInstance().InitShader();

	

	while (true)
	{
		Core::GetInstance().BindDrawCallback(drawScene);
		Core::GetInstance().BindReshapeCallback(Reshape);
		Core::GetInstance().UseMouseCallback();
		glutMainLoopEvent();
	}

}

// 이상한거 : 인풋 받는게 말도안되게 느림. 인풋버퍼에 계속 쌓이고 클릭하는 이벤트가 있을때만 뒤늦게 렌더링됨
// 
// 