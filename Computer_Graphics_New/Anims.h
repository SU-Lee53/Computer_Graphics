#pragma once


class Anims
{
public:
	Anims();
	Anims(Rect* r);
	~Anims();
	void AnimStraight();
	void AnimDiagnoal();
	void AnimBoth();
	static Anims* GetInstance();
	void SetSplitList(Rect* rect);
	vector<Rect*> GetSplitList() { return splitList; }
	void SetSwitchFlag(bool flag) { AnimSwitch = flag; }
	void SetEndFlag(bool flag) { AnimEnd = flag; }
	bool GetSwitchFlag() { return AnimSwitch; }
	bool GetEndFlag() { return AnimEnd; }


private:
	Rect* current;
	vector<Rect*> splitList;
	// �Ʒ� 2���� �÷��״� BOTH �ִϸ��̼ǿ����� �����
	bool AnimSwitch;
	bool AnimEnd;

	static Anims* s_instance;

};

