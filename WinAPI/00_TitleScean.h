#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{

private:

	float _bgAlpha;
	bool _isTitle;
	int _count, _index;
	int _bIndex;
	RECT button;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TitleScene() {}
	~TitleScene() {}

	int getIndex() { 		return _bIndex; 	}
	void setIndex(int n) { _bIndex = n; }

	bool getTitle() { return _isTitle; }

};

