#pragma once
#include "GameNode.h"
#include "TempSoundTest.h"
#include "Turnip.h"

#define HURDLE_MAX 14
#define SNAILINFO 615, 100, 80
#define WORMINFO 650,108,50
#define OUTRCINFO 645,280,155
#define INRCINFO 680,105,70
#define HFINFO 625,55, 60

enum E_HURDLE
{   SNAIL1, SNAIL2, SNAIL3, SNAIL4, SNAIL5, SNAIL6,
	WORM1, WORM2, WORM3, WORM4, 
	OUTSIDE1, INSIDE1 , OUTSIDE2, INSIDE2  };

// ��ֹ�
struct HURDLE
{
	RECT rc;
};

struct POTION
{
	RECT rc;
};

// _t : ����, _h : ��ֹ�(���)
class SecondScene : public GameNode
{
private:
	

	RECT _button;
	RECT _ground;  // ����

	// �÷��̾� - ���� 
	Turnip* _turnip;  
	int _tCount , _tIndex;
	int _tHpIndex; 
	
	// ȸ����
	POTION _heartFruit[2];
	int _hfCount, _hfIndex; 


	// ��ֹ� 
	HURDLE _hurdle[HURDLE_MAX];
	int _hCcount[HURDLE_MAX];
	int _hIndex[HURDLE_MAX]; 

	// ������ ����
	int _offsetX, _offsetY;
	int _bgSpeed, _gameSpeed;
	int _alpha2nd;

	// ���ӽ���-���� ���� 
	bool _isDead;		
	bool _isStart;
	bool _isClear;
	bool _isReady;
	int _SceneClearCount;

public:
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	// �浹 Ȯ�ο� ��Ʈ
	RECT temp; 

	// �浹�Լ� 
	void checkCollision(RECT &player, RECT &hurdle);
	void checkHeartFruit(RECT &player, RECT &heartFruit);

	bool getSceneClear() { return _isClear; }
};

