#include "pch.h"
#include "Ex14.h"

Ex14* ex;

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

	ex = new Ex14();

	Core::GetInstance().BindDrawCallback(drawScene);
	Core::GetInstance().BindReshapeCallback(Reshape);
	Core::GetInstance().UseMouseCallback();

	while (true)
	{
		glutMainLoopEvent();
	}

}

// �̻��Ѱ� : ��ǲ �޴°� �����ȵǰ� ����. ��ǲ���ۿ� ��� ���̰� Ŭ���ϴ� �̺�Ʈ�� �������� �ڴʰ� ��������
// 
// 