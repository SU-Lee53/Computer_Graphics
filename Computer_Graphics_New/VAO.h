#pragma once

enum VAO_TYPE
{
	NON_INDEXED = 0,
	INDEXED
};

class VAO
{
public:
	// ����, ���� ���۸� �޴� ������
	VAO(float* vertex, float* color, int bufSize);
	// ����, ����, �ε��� ���۸� ��� �޴� ������
	VAO(float* vert, float* color, unsigned int* element, int vBufSize, int eBufSize);
	~VAO();

	// VAO_TYPE: NON_INDEXED or INDEXED
	void InitVAO(VAO_TYPE type);

	unsigned int GetVAOHandle() { return h_VAO; }
	int GetVertexCount() { return _vBufSize; }
	int GetElementCount() { return _eBufSize; }


private:

	unsigned int h_VAO = 0;		// VAO �ڵ�
	VBO _vbo;				
	int _vBufSize;	// == cBufSize
	int _eBufSize;


};

