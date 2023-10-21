#include "pch.h"
#include "Ex18.h"
#include "Ex19.h"

// ���� �ǽ� �ε� ��ũ��: __defines �� ���ǵǾ�����
// ()�ȿ� �̸��� �ٲ㳢�������� �ε� �Ϸ�

LOAD_EX(Ex19);

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
