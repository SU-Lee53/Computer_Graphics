#pragma once

// �ǽ� Ŭ���� �������̽�
class Examples
{
public:
	virtual ~Examples();



private:
	virtual void drawScene() = 0;
	virtual void Reshape(int w, int h) = 0;

	// �ǽ� ��ü�� �ʱ�ȭ�մϴ�.
	virtual void InitEx() = 0;

	// �ǽ� ��ü ������ ��ҵ��� �� �ѹ� ������Ʈ �մϴ�.
	virtual void Update() = 0;

private:
	int exNum;

};

