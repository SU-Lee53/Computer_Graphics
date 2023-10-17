#include "pch.h"
#include "Ex14.h"
#include "Ex15.h"
#include "Ex16.h"

// ���� �ǽ� �ε� ��ũ��: __defines �� ���ǵǾ�����
// ()�ȿ� �̸��� �ٲ㳢�������� �ε� �Ϸ�

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
