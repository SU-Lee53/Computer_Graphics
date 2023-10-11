#pragma once

// 실습 클래스 인터페이스
class Examples
{
public:
	virtual ~Examples();



private:
	virtual void drawScene() = 0;
	virtual void Reshape(int w, int h) = 0;

	// 실습 객체를 초기화합니다.
	virtual void InitEx() = 0;

	// 실습 객체 내부의 요소들을 싹 한번 업데이트 합니다.
	virtual void Update() = 0;

private:
	int exNum;

};

