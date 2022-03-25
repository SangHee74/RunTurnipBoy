#include "Stdafx.h"
#include "03_ThirdScene.h"

HRESULT ThirdScene::init(void)
{
	IMAGEMANAGER->addImage("bg_3rd", "Resources/Images/3rdScene/map_3.bmp", WINSIZE_X, WINSIZE_Y,false,MGT);
	IMAGEMANAGER->addImage("buttonInfo_3rd", "Resources/Images/3rdScene/buttonInfo_3rd.bmp ",400, 100, true, MGT);
	IMAGEMANAGER->addImage("okButtonInfo_3rd", "Resources/Images/3rdScene/okButtonInfo_3rd.bmp ", 200, 100, true, MGT);
	IMAGEMANAGER->addImage("clear_3rd", "Resources/Images/3rdScene/end_3rd.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("intro_3rd_1", "Resources/Images/3rdScene/intro_3rd_1.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("intro_3rd_2", "Resources/Images/3rdScene/intro_3rd_2.bmp ", WINSIZE_X, WINSIZE_Y);

	IMAGEMANAGER->addFrameImage("lostCat", "Resources/Images/3rdScene/lostCat.bmp ", 288, 60,4,1, true, MGT);
	IMAGEMANAGER->addFrameImage("dropE1", "Resources/Images/dropEffect.bmp ", 96, 16, 6, 1, true, MGT);
	IMAGEMANAGER->addFrameImage("dropE2", "Resources/Images/dropEffect.bmp ", 96, 16, 6, 1, true, MGT);
	IMAGEMANAGER->addFrameImage("dropE3", "Resources/Images/dropEffect.bmp ", 96, 16, 6, 1, true, MGT);

	IMAGEMANAGER->addFrameImage("worm", "Resources/Images/2ndScene/worm.bmp ", 1635, 650, 324, 50, 3, 1, true, MGT);

	_ground = RectMake(0, 700, WINSIZE_X, WINSIZE_Y - 700);

	_turnip = new Turnip();
	_turnip->init();
	_tCount = 0;
	_tIndex = 0;
	_tHpIndex = 6;

	_appleCat = new Boss();
	_appleCat->init();
	_bCount = 0;
	_bIndex = 0;
	_bHpIndex = 5;
	//onBarn = false;

	worm[0].rc = RectMake( -580, 650, 108, 50); 	worm[1].rc = RectMake(-890, 650, 108, 50);
	worm[0].die = false; worm[0].die2 = true; 
	worm[1].die = false; worm[1].die2 = true;

	_lostCat = RectMake( -200, 615,72,60); //lost cat 
	for (int i = 0; i < 3; i++) { 	_dropEffect[i].count = 0; _dropEffect[i].index = i * 2; 	}
	

	// 씬 전환 
	_isStart = false;
	_isDead = false; 
	_isReady = false;
	_isClear = false;
	_SceneClearCount = 0;

	_intro = true;
	_introCount = 0; 
	_alpha3rd = 0;

	_turnip->_state->isState = RUN;
	

	return S_OK;
}

void ThirdScene::release(void)
{
	SAFE_DELETE(_turnip);
	SAFE_DELETE(_appleCat);
}

void ThirdScene::update(void)
{
	_turnip->resetHP();
	_appleCat->update();

	if (_intro)
	{
		_alpha3rd+=4;
		if (_alpha3rd >= 255)
		{
			_alpha3rd = 255;

			_introCount++;
			if (_introCount % 120 == 0) _intro = false;
		}
	}

	if (!_intro && !_isStart && (_turnip->getRc().right <= 340))
	{		
		_turnip->setRcMoveRight(4);
		_turnip->setSwRcMoveRight(4);
		if (_turnip->_state->isState == RUN)
		{
			_tCount++;
			IMAGEMANAGER->findImage("turnip_run")->setFrameY(0);
			if (_tCount % 5 == 0)
			{
				_tIndex++; _tCount = 0;
				if (_tIndex > 3) _tIndex = 0;
			}
			IMAGEMANAGER->findImage("turnip_run")->setFrameX(_tIndex);
		}
	}
	else if(!_intro &&(_turnip->getRc().right >= 340)) { _isStart = true; _turnip->_state->isState = IDLE; }


	if (!_isDead && _isStart )
	{

#pragma region 순무 업데이트
		
		if (_turnip->getRc().left > 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				_turnip->setIsLeft(true);
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_turnip->setIsLeft(true);
				_turnip->_state->isState = RUN;
				_turnip->setRcMoveLeft(4);
				_turnip->setSwRcMoveLeft(4);
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
			{
				_turnip->_state->isState = IDLE;
			}
		}

		if (_turnip->getRc().right < WINSIZE_X)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				_turnip->setIsLeft(false);
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_turnip->setIsLeft(false);
				_turnip->_state->isState = RUN;
				_turnip->setRcMoveRight(4);
				_turnip->setSwRcMoveRight(4);
			}
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				_turnip->_state->isState = IDLE;
			}
		}

		if (KEYMANAGER->isStayKeyDown('Z'))
		{
			_turnip->attack();
			_turnip->_state->isState = ATTACK;
		}

		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			_turnip->setAttSwRc(_turnip->getRc().right - 1500, _turnip->getRc().top + 54, 87, 53);
			_turnip->_state->isState = IDLE;
		}

		_turnip->update();


		// 달리기로 변경 + 점프 초기화 + 바닥 맞추기 
		if (_turnip->getRc().bottom >= _ground.top)
		{
			_turnip->setJumpCount(1);

			_turnip->setRcMoveUp(10);

			_turnip->setJump(false);
			if (!_turnip->_state->isState == INVINCIBILITY)_turnip->_state->isState = IDLE;
			if (_turnip->_state->isState == JUMP)_turnip->_state->isState = IDLE;
		}

		if ((_turnip->getRc().bottom < _ground.top) && _turnip->_state->isState != JUMP)
		{
			_turnip->setRcMoveDown(10);
		}

#pragma endregion 

		if (_appleCat->getIsDead() && !_isReady)
		{
			_lostCat = RectMake(800, 640, 72, 60);
		}

		if(_appleCat-> getIsSkill())
		{ 
			if(worm[0].die = false )
		worm[0].rc = RectMake(580, 650, 108, 50); 	worm[1].rc = RectMake(890, 650, 108, 50);

		}

#pragma region 충돌검사


		if (!_turnip->getInvinsibility()) checkCollision(_turnip->getRc(), _appleCat->getRc());

		if (!_appleCat->getInvinsibility() && (_appleCat->getHpIndex() >0) )
		{
			checkAttack(_turnip->getAttSwRc(), _appleCat->getRc());
		}

		if(_appleCat->getIsSkill())
		{
		checkAttack(_turnip->getAttSwRc(), worm[0].rc);
		checkAttack(_turnip->getAttSwRc(), worm[1].rc);
		}

		if ((_appleCat->getIsDead()))
		{
			if (IntersectRect(&temp, &_turnip->getRc(), &_lostCat))
			{
				_isReady = true;
				_lostCat = RectMake(-200, 610, 72, 60);
			}
		}

#pragma endregion

		if (_isReady)
		{
			_SceneClearCount++;

			if (_SceneClearCount >= 150)
			{
				_SceneClearCount = 150; _isClear = true;
			}
		}

	}// !_isDead && _isStart end

#pragma region 사과냥 프레임

	_bCount++;
	IMAGEMANAGER->findImage("lostCat")->setFrameY(0);
	if (_bCount %7 == 0)
	{
		_bIndex++; _bCount = 0;
		if (_bIndex > 3) _bIndex = 0;
	}
	IMAGEMANAGER->findImage("lostCat")->setFrameX(_bIndex);

	_dropEffect[0].count++;
	IMAGEMANAGER->findImage("dropE1")->setFrameY(0);
	if (_dropEffect[0].count % 4 == 0)
	{
		_dropEffect[0].index++; _dropEffect[1].index++; _dropEffect[2].index++;
		_dropEffect[0].count = 0;
		if (_dropEffect[0].index > 6) _dropEffect[0].index = 0;
		if (_dropEffect[1].index > 6) _dropEffect[1].index = 0;
		if (_dropEffect[2].index > 6) _dropEffect[2].index = 0;
	}
	IMAGEMANAGER->findImage("dropE1")->setFrameX(_dropEffect[0].index);
	IMAGEMANAGER->findImage("dropE2")->setFrameX(_dropEffect[1].index);
	IMAGEMANAGER->findImage("dropE3")->setFrameX(_dropEffect[2].index);

#pragma endregion

	if (_turnip->getHpIndex() == 0) _isDead = true;
	if (_isDead)
	{
		_tHpIndex = 0; _turnip->_state->isState = DEAD;

		// 죽었을 때 재시작
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			if (!_isStart) _isStart = true;
			if (_isStart&&_isDead) this->init();
		}
	}
}

void ThirdScene::render(void)
{
	char str[128];

	if (_intro)
	{
		IMAGEMANAGER->alphaRender("intro_3rd_1", getMemDC(), 0, 0, _alpha3rd);
	
		if (_introCount > 50) IMAGEMANAGER->render("intro_3rd_2", getMemDC(), 0, 0);
	}

	if (!_intro & !_isStart)
	{
		IMAGEMANAGER->render("bg_3rd", getMemDC(), 0, 0);
		_turnip->renderSw(getMemDC());
		_turnip->render(getMemDC());
		_appleCat->render(getMemDC());
	}

	if (!_intro & _isStart)
	{
		IMAGEMANAGER->render("bg_3rd", getMemDC(), 0, 0);
		IMAGEMANAGER->render("buttonInfo_3rd", getMemDC(), WINSIZE_X - 400, WINSIZE_Y - 100);
	
		if (!_appleCat->getIsDead())
		{
			IMAGEMANAGER->frameRender("cat_hp", getMemDC(), WINSIZE_X - 382, 40);
			_appleCat->render(getMemDC());
		}
		_turnip->renderSw(getMemDC());
		_turnip->render(getMemDC());
	}

	IMAGEMANAGER->frameRender("lostCat", getMemDC(), _lostCat.left, _lostCat.top);
	IMAGEMANAGER->frameRender("dropE1", getMemDC(), _lostCat.left - 10, _lostCat.top + 5);
	IMAGEMANAGER->frameRender("dropE2", getMemDC(), _lostCat.left + 70, _lostCat.top + 15);
	IMAGEMANAGER->frameRender("dropE3", getMemDC(), _lostCat.left + 2, _lostCat.top + 45);


	if (_isReady)
	{
		IMAGEMANAGER->render("clear_3rd", getMemDC(), 0, 0);
	}

	if (_isClear)
	{
		IMAGEMANAGER->render("clear_3rd", getMemDC(), 0, 0);
		IMAGEMANAGER->render("okButtonInfo_3rd", getMemDC(), 30, 650);
	}



	if (KEYMANAGER->isToggleKey(VK_F2))
	{
#pragma region 화면 표시 가이드 

		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

		rcMake(getMemDC(), _ground); 
		//rcMake(getMemDC(), worm[0].rc); 
		//rcMake(getMemDC(), worm[1].rc);

		std::sprintf(str, "STATE : %d ", _turnip->_state->isState);
		TextOut(getMemDC(), _turnip->getRc().left + 10, _turnip->getRc().top + 20, str, strlen(str));

		rcMake(getMemDC(), _turnip->getRc());
		rcMake(getMemDC(), _turnip->getAttSwRc());

		rcMake(getMemDC(), _appleCat->getRc());

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
#pragma endregion 
	}

}


void ThirdScene::checkCollision(RECT &player, RECT &BossPos)
{
	if (IntersectRect(&temp, &player, &BossPos))
	{
		_tHpIndex--;
		_turnip->setHpIndex(_tHpIndex);
		_turnip->setInvinsibility(true); _turnip->_state->isState = INVINCIBILITY;
		
		if(_turnip->getIsLeft()) 		_turnip->setRcMoveLeft(5);
		else _turnip->setRcMoveRight(5);
		_turnip->setRcMoveUp(8);
	}
}


void ThirdScene::checkAttack(RECT &playerWeapon, RECT &BossPos)
{

	if (IntersectRect(&temp, &playerWeapon, &BossPos) )
	{
		_bHpIndex--;
		_appleCat->setHpIndex(_bHpIndex);
		_appleCat->setInvinsibility(true); _appleCat->setIsIdle(false);
		if  (_appleCat->getIsLeft()) 		_appleCat->setRcMoveLeft(5);
		else _appleCat->setRcMoveRight(5);
	}
}

