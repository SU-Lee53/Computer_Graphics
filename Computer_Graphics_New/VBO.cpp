#include "pch.h"
#include "VBO.h"

VBO::VBO()
{
	memset(this->Buf, 0.0f, sizeof(float) * 256);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &this->h_VBO);
}

void VBO::PushToVboBuffer(float* buf, int bufSize)
{
	memcpy(this->Buf, buf, sizeof(float) * bufSize);
}
