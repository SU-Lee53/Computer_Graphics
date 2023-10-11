#pragma once

// �ǽ� Ŭ���� �������̽�
class Examples
{
public:
	virtual ~Examples();

	virtual void Update()
	{
		MouseUpdate();
		MotionUpdate();
		KeyboardUpdate();
	}


private:
	virtual void drawScene() = 0;
	virtual void Reshape(int w, int h) = 0;

	// �ǽ� ��ü�� �ʱ�ȭ�մϴ�.
	virtual void InitEx() = 0;

	virtual void MouseUpdate() = 0;
	virtual void MotionUpdate() = 0;
	virtual void KeyboardUpdate() = 0;

	// �ǽ� ��ü ������ ��ҵ��� �� �ѹ� ������Ʈ �մϴ�.
	

private:
	int exNum;

};

