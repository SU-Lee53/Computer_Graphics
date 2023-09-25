#pragma once


class Anims
{
public:
	Anims();
	~Anims();

	void AnimStraight();
	void AnimDiagnoal();
	void AnimBoth();
	static Anims* GetInstance();
	void SetSplitList(Rect* rect);
	vector<Rect*> GetSplitList() { return splitList; }
	vector<Rect*> GetReSplitList() { return reSplit; }
	void SetSwitchFlag(bool flag) { AnimSwitch = flag; }
	void SetEndFlag(bool flag) { AnimEnd = flag; }
	bool GetSwitchFlag() { return AnimSwitch; }
	bool GetEndFlag() { return AnimEnd; }


private:
	Rect* current;
	vector<Rect*> splitList;
	vector<Rect*> reSplit;

	// 아래 2개의 플래그는 BOTH 애니메이션에서만 사용함
	bool AnimSwitch;
	bool AnimEnd;

	static Anims* s_instance;
};

