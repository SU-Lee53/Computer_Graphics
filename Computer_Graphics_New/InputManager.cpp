#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::MouseInput(int button, int state, int x, int y)
{
	Coord pos = { x, y };
	pos = AdjustMouseCoordinate(pos);
	MouseState* s = new MouseState { button, state, pos };
	InputManager::GetInstance().GetMouseBuf().push(s);
}

void InputManager::MotionInput(int x, int y)
{
	Coord pos = { x, y };
	pos = AdjustMouseCoordinate(pos);
	InputManager::GetInstance().GetMotionBuf().push(&pos);
}

void InputManager::KeyboardInput(unsigned char key, int x, int y)
{
	Coord pos = { x, y };
	pos = AdjustMouseCoordinate(pos);
	KeyboardState s = { key, pos };
	InputManager::GetInstance().GetKeyboardBuf().push(&s);
}

MouseState* InputManager::DequeueMouseBuf()
{
	if (mouseBuf.empty())
	{
		return nullptr;
	}
	MouseState* temp = mouseBuf.front();

	// 반환을 위해 새로 할당. 실습객체에서 사용후 반드시 delete 할것
	MouseState* ret = new MouseState{temp->button, temp->state, temp->pos };
	mouseBuf.pop();
	return ret;
}

Coord* InputManager::DequeueMotionBuf()
{
	if (keyboardBuf.empty())
	{
		return nullptr;
	}

	Coord* temp = motionBuf.front();

	// 반환을 위해 새로 할당. 실습객체에서 사용후 반드시 delete 할것
	Coord* ret = new Coord{ temp->x, temp->y, temp->z };
	motionBuf.pop();
	return ret;
}

KeyboardState* InputManager::DequeueKeyboardBuf()
{
	if (keyboardBuf.empty())
	{
		return nullptr;
	}

	KeyboardState* temp = keyboardBuf.front();
	KeyboardState* ret = new KeyboardState{ temp->key, temp->pos };
	keyboardBuf.pop();
	return ret;
}
