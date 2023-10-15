#pragma once

// inputManager와 VAO, VBO에서 메모리가 세고있는것으로 추정됨

struct MouseState
{
	int button;
	int state;
	Coord pos;
};

struct KeyboardState
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
// 현재 문제점: 싱글톤 객체 내부 정적함수 -> 좋지않다
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

	MouseState* DequeueMouseBuf();
	Coord* DequeueMotionBuf();
	KeyboardState* DequeueKeyboardBuf();


private:
	InputManager();
	~InputManager();
	static void MouseInput(int button, int state, int x, int y);
	static void MotionInput(int x, int y);
	static void KeyboardInput(unsigned char key, int x, int y);

	queue<MouseState*>& GetMouseBuf() { return mouseBuf; }
	queue<Coord*>& GetMotionBuf() { return motionBuf; }
	queue<KeyboardState*>& GetKeyboardBuf() { return keyboardBuf; }

private:

	// 입력 버퍼
	queue<MouseState*> mouseBuf;
	queue<KeyboardState*> keyboardBuf;
	queue<Coord*> motionBuf;

};

