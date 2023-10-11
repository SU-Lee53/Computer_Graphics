#pragma once

enum VBO_TYPE
{
	VERTEX = 0,
	COLOR,
	ELEMENT
};

class VAO
{
public:
	// ����, ���� ���۸� �޴� ������
	VAO(float* vertex, float* color, int bufSize);
	// ����, ����, �ε��� ���۸� ��� �޴� ������
	VAO(float* vert, float* color, float* element, int vBufSize, int eBufSize);
	~VAO();

	// elementMode : false�̸� 2�� VBO, true�̸� 3�� VBO
	void InitVAO(bool elementMode);
	VBO& GetVBO(VBO_TYPE t) { return _vbo[static_cast<int>(t)]; }

	unsigned int GetVAOHandle() { return h_VAO; }
	int GetVertexCount() { return _vBufSize; }
	int GetElementCount() { return _eBufSize; }


private:

	unsigned int h_VAO = 0;		// VAO �ڵ�
	VBO _vbo[3];				// [0], [1], [2] ���� vertex, color, element
	int _vBufSize;
	int _eBufSize;


};

