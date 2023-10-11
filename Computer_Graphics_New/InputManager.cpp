#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
	instanceNum = rand();
}

InputManager::~InputManager()
{
}

void InputManager::MouseInput(int button, int state, int x, int y)
{
	Coord pos = { x, y };
	pos = AdjustMouseCoordinate(pos);
	m_State* s = new m_State { button, state, pos };
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
	k_State s = { key, pos };
	InputManager::GetInstance().GetKeyboardBuf().push(&s);
}

m_State* InputManager::DequeueMouseBuf()
{
	if (mouseBuf.empty())
	{
		return nullptr;
	}
	m_State* temp = mouseBuf.front();
	m_State* ret = new m_State{temp->button, temp->state, temp->pos };
	mouseBuf.pop();
	return ret;
}

Coord* InputManager::DequeueMotionBuf()
{
	if (keyboardBuf.empty())
	{
		return nullptr;
	}

	Coord* s = motionBuf.front();
	motionBuf.pop();
	return s;
}

k_State* InputManager::DequeueKeyboardBuf()
{
	if (keyboardBuf.empty())
	{
		return nullptr;
	}

	k_State* s = keyboardBuf.front();
	keyboardBuf.pop();
	return s;
}
