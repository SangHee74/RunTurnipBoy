#pragma once
#include "GameNode.h"
#include "STATE.h"

class FirstScene : public GameNode
{
private:
	// 루프용 변수
	float _bgAlpha;
	int _bgIndex;

	bool _isStart;
	bool _talkEnd;
	bool _isClear;

	int count, index; // 프레임용 변수


public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool getSceneClear() { return _isClear; }
};



