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
	RECT _ground;  // 지형

	// 플레이어 - 순무 
	Turnip* _turnip;
	int _tCount, _tIndex; 
	int _tHpIndex;


	// 보스 - 사과냥이
	Boss* _appleCat;
	int _bCount, _bIndex;  
	int _bHpIndex; 

	//bool onBarn;
	RECT _lostCat;

	Effect _dropEffect[3];
	int _alpha3rd;

	// 게임시작-엔딩 관련 
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

	// 충돌 확인용 렉트
	RECT temp;

	// 충돌함수 
	void checkCollision(RECT &player, RECT &BossPos);

	void checkAttack(RECT &playerWeapon, RECT &BossPos);

	bool getSceneClear() { return _isClear; }



};

