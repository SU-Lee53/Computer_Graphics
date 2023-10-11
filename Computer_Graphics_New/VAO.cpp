#include "pch.h"
#include "VAO.h"



VAO::VAO(float* vertex, float* color, int bufSize) : _vBufSize(bufSize), _eBufSize(0)
{
	this->GetVBO(VERTEX).PushToVboBuffer(vertex, _vBufSize);
	this->GetVBO(COLOR).PushToVboBuffer(color, _vBufSize);
	InitVAO(false);
}

VAO::VAO(float* vertex, float* color, float* element, int v_bufSize, int e_bufSize) : _vBufSize(v_bufSize), _eBufSize(e_bufSize)
{
	this->GetVBO(VERTEX).PushToVboBuffer(vertex, _vBufSize);
	this->GetVBO(COLOR).PushToVboBuffer(color, _vBufSize);
	this->GetVBO(ELEMENT).PushToVboBuffer(element, _eBufSize);
	InitVAO(true);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &this->h_VAO);
}

void VAO::InitVAO(bool elementMode)	// elementMode가 true면 EBO를 사용하므로 버퍼 3개 생성함
{
	bool GenBufs = false;	// vbo를 생성할지 안할지 결정하는 플래그
	if (!h_VAO)
	{
		glGenVertexArrays(1, &h_VAO);
		GenBufs = true;
	}

	glBindVertexArray(h_VAO);

	if (GenBufs == true)
	{
		if (elementMode == true)
		{
			for (int i = 0; i < 3; i++)
				glGenBuffers(1, GetVBO(static_cast<VBO_TYPE>(i)).GetVBOHandle());
		}
		else
		{
			for (int i = 0; i < 2; i++)
				glGenBuffers(1, GetVBO(static_cast<VBO_TYPE>(i)).GetVBOHandle());
		}
	}


	glBindBuffer(GL_ARRAY_BUFFER, *GetVBO(VERTEX).GetVBOHandle());
	glBufferData(GL_ARRAY_BUFFER, _vBufSize * sizeof(float), GetVBO(VERTEX).GetBuf(), GL_DYNAMIC_DRAW);
	if (elementMode == true)	// element 버퍼 사용시에는 vbo 하나 더 사용
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *GetVBO(ELEMENT).GetVBOHandle());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _eBufSize * sizeof(GLuint), GetVBO(ELEMENT).GetBuf(), GL_DYNAMIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, *GetVBO(COLOR).GetVBOHandle());
	glBufferData(GL_ARRAY_BUFFER, _vBufSize * sizeof(float), GetVBO(COLOR).GetBuf(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

}
