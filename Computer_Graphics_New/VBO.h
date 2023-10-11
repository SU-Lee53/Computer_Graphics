#pragma once

class VBO
{
public:
	VBO();
	~VBO();

	// VBO객체 내부 버퍼에 생성된 도형의 버퍼를 집어넣습니다.
	void PushToVboBuffer(float* buf, int bufSize);
	unsigned int* GetVBOHandle() { return &h_VBO; }
	float* GetBuf() { return Buf; }

private:
	unsigned int h_VBO = 0;
	float Buf[256];
};

