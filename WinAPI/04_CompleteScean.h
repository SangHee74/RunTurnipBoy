#pragma once
#include "GameNode.h"
#include "STATE.h"


class CompleteScean : public GameNode
{
private:

	int _bgAlpha;
	int _bgIndex;

	bool _isStart;
	bool _talkEnd;
	bool _goTitle;

	int count, index; // �����ӿ� ����

public:

	STAGE* stage;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool getGoTitle() { return _goTitle; }

};

