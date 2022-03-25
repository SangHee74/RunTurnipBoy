#pragma once
#include "GameNode.h"
#include "00_TitleScean.h"
#include "01_FirstScene.h"
#include "02_SecondScene.h"
#include "03_ThirdScene.h"
#include "04_CompleteScean.h"

/*
�ַ�� �÷��� : x64

���� �� ������Ʈ ��ġ Ȯ�� : F2 

*/

class MainGame : public GameNode
{
private:
	
	TitleScene* _title;
	FirstScene* _first;
	SecondScene* _second;
	ThirdScene* _third;
	CompleteScean* _complet;

	GameNode* _currentScene;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame():_currentScene(nullptr)  {}
	~MainGame() {}

	

};
