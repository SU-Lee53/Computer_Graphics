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

// InputManager�� �ǽ� ��ü�� ���ӵ��� �ʰ� �̱������� �۵���
class InputManager
{
public:

	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}

	// �ݹ鿡���� ���ۿ� �Է¸� �־��ְ� �ǽ���ü���� ���۸� ������ �ϳ��� ó���Ѵ�.
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

	// �Է� ����
	queue<m_State*> mouseBuf;
	queue<k_State*> keyboardBuf;
	queue<Coord*> motionBuf;
	int instanceNum;
};

