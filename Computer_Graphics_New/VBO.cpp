#include "pch.h"
#include "VBO.h"

VBO::VBO()
{
	memset(this->vBuf, 0.0f, sizeof(float) * 256);
	memset(this->cBuf, 0.0f, sizeof(float) * 256);
	memset(this->eBuf, 0, sizeof(unsigned int) * 256);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &this->vBufHandle);
	glDeleteBuffers(1, &this->cBufHandle);
	glDeleteBuffers(1, &this->eBufHandle);
}

void VBO::PushToVertexBuffer(float* buf, int bufSize)
{
	memcpy(this->vBuf, buf, sizeof(float) * bufSize);
}

void VBO::PushToColorBuffer(float* buf, int bufSize)
{
	memcpy(this->cBuf, buf, sizeof(float) * bufSize);
}

void VBO::PushToElementBuffer(unsigned int* eBuf, int ebufSize)
{
	memcpy(this->eBuf, eBuf, sizeof(unsigned int) * ebufSize);
}
