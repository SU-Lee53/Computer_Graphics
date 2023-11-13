#include "pch.h"
#include "Ex22.h"
#include "Ex23.h"

#include "Ex19.h"	
#include "Ex15.h"

// LOAD_EX(Ex21);
LOAD_EX(Ex23);



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
	Core::GetInstance().UseMouseCallback();
	Core::GetInstance().UseMotionCallback();
	Core::GetInstance().UseSpecialKeyCallback();
	GET_SINGLE(TimeManager).Init();


	while (true)
	{
		GET_SINGLE(TimeManager).Update();
		glutMainLoopEvent();
	}

}
