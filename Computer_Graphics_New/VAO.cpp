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

void VAO::InitVAO(bool elementMode)	// elementMode�� true�� EBO�� ����ϹǷ� ���� 3�� ������
{
	bool GenBufs = false;	// vbo�� �������� ������ �����ϴ� �÷���
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
	if (elementMode == true)	// element ���� ���ÿ��� vbo �ϳ� �� ���
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
