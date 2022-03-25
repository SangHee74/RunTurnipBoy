#pragma once
#include "GameNode.h"
#include "TempSoundTest.h"
#include "Turnip.h"
#include "Boss.h"

struct Effect
{
	int count, index;
};

struct WORM
{
	RECT rc;
	bool die;
	bool die2;
};

class ThirdScene : public GameNode
{
private:
	Image _img;
	RECT _ground;  // ����

	// �÷��̾� - ���� 
	Turnip* _turnip;
	int _tCount, _tIndex; 
	int _tHpIndex;


	// ���� - �������
	Boss* _appleCat;
	int _bCount, _bIndex;  
	int _bHpIndex; 

	//bool onBarn;
	RECT _lostCat;

	Effect _dropEffect[3];
	int _alpha3rd;

	// ���ӽ���-���� ���� 
	bool _isDead;
	bool _isStart;
	bool _isReady;
	bool _isClear;

	int _introCount;
	bool _intro;
	int _SceneClearCount;

public:

	WORM worm[2];

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// �浹 Ȯ�ο� ��Ʈ
	RECT temp;

	// �浹�Լ� 
	void checkCollision(RECT &player, RECT &BossPos);

	void checkAttack(RECT &playerWeapon, RECT &BossPos);

	bool getSceneClear() { return _isClear; }



};

