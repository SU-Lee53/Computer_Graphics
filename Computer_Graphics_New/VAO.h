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
	// 정점, 색상 버퍼만 받는 생성자
	VAO(float* vertex, float* color, int bufSize);
	// 정점, 색상, 인덱스 버퍼를 모두 받는 생성자
	VAO(float* vert, float* color, float* element, int vBufSize, int eBufSize);
	~VAO();

	// elementMode : false이면 2개 VBO, true이면 3개 VBO
	void InitVAO(bool elementMode);
	VBO& GetVBO(VBO_TYPE t) { return _vbo[static_cast<int>(t)]; }

	unsigned int GetVAOHandle() { return h_VAO; }
	int GetVertexCount() { return _vBufSize; }
	int GetElementCount() { return _eBufSize; }


private:

	unsigned int h_VAO = 0;		// VAO 핸들
	VBO _vbo[3];				// [0], [1], [2] 각각 vertex, color, element
	int _vBufSize;
	int _eBufSize;


};

