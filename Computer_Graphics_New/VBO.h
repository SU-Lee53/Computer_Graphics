#pragma once

class VBO
{
public:
	VBO();
	~VBO();

	// VBO��ü ���� ���ۿ� ������ ������ ���۸� ����ֽ��ϴ�.
	void PushToVboBuffer(float* buf, int bufSize);
	unsigned int* GetVBOHandle() { return &h_VBO; }
	float* GetBuf() { return Buf; }

private:
	unsigned int h_VBO = 0;
	float Buf[256];
};

