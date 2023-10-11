#pragma once

struct m_State
{
	int button;
	int state;
	Coord pos;
};

struct k_State
{
	unsigned char key;
	Coord pos;
};

enum INPUT_TYPE
{
	MOUSE = 0,
	MOTION,
	KEYBOARD
};

// InputManager는 실습 객체에 종속되지 않고 싱글톤으로 작동됨
class InputManager
{
public:

	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}

	// 콜백에서는 버퍼에 입력만 넣어주고 실습객체에서 버퍼를 가져와 하나씩 처리한다.
	void (*MouseFunc())(int, int, int, int) { return MouseInput; }
	void (*MotionFunc())(int, int) { return MotionInput; }
	void (*KeyboardFunc())(unsigned char, int, int) { return KeyboardInput; }

	m_State* DequeueMouseBuf();
	Coord* DequeueMotionBuf();
	k_State* DequeueKeyboardBuf();


private:
	InputManager();
	~InputManager();
	static void MouseInput(int button, int state, int x, int y);
	static void MotionInput(int x, int y);
	static void KeyboardInput(unsigned char key, int x, int y);

	queue<m_State*>& GetMouseBuf() { return mouseBuf; }
	queue<Coord*>& GetMotionBuf() { return motionBuf; }
	queue<k_State*>& GetKeyboardBuf() { return keyboardBuf; }

private:

	// 입력 버퍼
	queue<m_State*> mouseBuf;
	queue<k_State*> keyboardBuf;
	queue<Coord*> motionBuf;
	int instanceNum;
};

