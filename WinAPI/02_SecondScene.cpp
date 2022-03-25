#include "Stdafx.h"
#include "02_SecondScene.h"

HRESULT SecondScene::init(void)
{

#pragma region 배경, 시스템 
	IMAGEMANAGER->addImage("bg", "Resources/Images/2ndScene/bg.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("loop_bg", "Resources/Images/2ndScene/map_1B.bmp ", 7150, 800);
	IMAGEMANAGER->addImage("fence", "Resources/Images/2ndScene/fenceFull.bmp ", 7150, 200, true, MGT);
	IMAGEMANAGER->addImage("buttonInfo_2nd", "Resources/Images/2ndScene/buttonInfo_2nd.bmp ", WINSIZE_X - 200, WINSIZE_Y - 100, 200, 100, true, MGT);
	IMAGEMANAGER->addImage("okButtonInfo_2nd", "Resources/Images/2ndScene/okButtonInfo_2nd.bmp ",200, 100, true, MGT);
	IMAGEMANAGER->addImage("clear_2nd", "Resources/Images/2ndScene/end_2nd.bmp ", 1200, 800);

	_button = RectMake(WINSIZE_X - 200, WINSIZE_Y - 100, 200, 100);

	_ground = RectMake(0, 700, WINSIZE_X, WINSIZE_Y - 700);

	// 루프랜더
	_offsetX = _offsetY = 0;
	_bgSpeed = _gameSpeed = 0;
	_alpha2nd = 0;

	// 씬 전환 
	_isStart = false;
	_isDead = false; 
	_isReady = false;
	_isClear = false;
	_SceneClearCount = 0;

#pragma endregion 

#pragma region 순무 


	_turnip = new Turnip();
	_turnip->init();


	_tCount = 0;
	_tIndex = 0;
	_tHpIndex = 6; 


	_turnip->_state->isState = RUN;


	IMAGEMANAGER->addFrameImage("hf", "Resources/Images/HeartFruit.bmp ", 228, 62, 4, 1, true, MGT);

	_heartFruit[0].rc = RectMake(3420, HFINFO);	 
	_heartFruit[1].rc = RectMake(4910, HFINFO);  
	_hfCount = 0;   _hfIndex = 0;



#pragma endregion 

#pragma region 장애물

	IMAGEMANAGER->addImage("snail", "Resources/Images/2ndScene/snail.bmp ", 2000,592,123,86, true, MGT);
	IMAGEMANAGER->addFrameImage("worm", "Resources/Images/2ndScene/worm.bmp ",1635,650, 324, 50, 3, 1, true, MGT);
	IMAGEMANAGER->addFrameImage("swamp1", "Resources/Images/2ndScene/swamp.bmp ", 2385, 682, 3948, 155, 14, 1, true, MGT);
	IMAGEMANAGER->addFrameImage("swamp2", "Resources/Images/2ndScene/swamp.bmp ", 2385, 682, 3948, 155, 14, 1, true, MGT);

	// 장애물 배치	 
	 _hurdle[SNAIL1].rc = RectMake(9000, SNAILINFO);
	 _hurdle[SNAIL2].rc = RectMake(1800, SNAILINFO);
	 _hurdle[SNAIL3].rc = RectMake(4545,SNAILINFO);
	 _hurdle[SNAIL4].rc = RectMake(5250,SNAILINFO);
	 _hurdle[SNAIL5].rc = RectMake(6105,SNAILINFO);
	 _hurdle[SNAIL6].rc = RectMake(7930, SNAILINFO);
	 _hurdle[WORM1].rc=RectMake(1635,WORMINFO);
	 _hurdle[WORM2].rc=RectMake(2930,WORMINFO);
	 _hurdle[WORM3].rc=RectMake(4640, WORMINFO); 
	 _hurdle[WORM4].rc=RectMake(6480,WORMINFO);
	 _hurdle[OUTSIDE1].rc = RectMake(2385,OUTRCINFO);
	 _hurdle[OUTSIDE2].rc = RectMake(4550, OUTRCINFO);
	 _hurdle[INSIDE1].rc = RectMake(2465, INRCINFO);
	 _hurdle[INSIDE2].rc = RectMake(4634, INRCINFO);

	for (int i = 0; i < HURDLE_MAX; i++)
	{
		_hCcount[i] = 0; _hIndex[i] = 0;
	}

#pragma endregion

	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_turnip);
}

void SecondScene::update(void)
{
	_turnip->resetHP();

	_alpha2nd++;
	if (_alpha2nd >= 255) _alpha2nd = 255;


	if ((_alpha2nd >= 255) && (_turnip->getRc().right <=304) && !_isStart)
	{
		_turnip->setRcMoveRight(4);

		_bgSpeed += 0;    _gameSpeed = 0;

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
	else if (_turnip->getRc().right >= 304) { _isStart = true; }


	// 달리기 시작
	if (!_isDead && _isStart)
	{
		if (_alpha2nd >= 255)
		{
			_bgSpeed += 4;    _gameSpeed = 6;
		}

#pragma region 순무 업데이트	

		_turnip->update();
 
		if (_turnip->getRc().bottom >= _ground.top)
		{
			_turnip->setJumpCount(1);

			_turnip->setRcMoveUp(10);

			_turnip->setJump(false);
			_turnip->setRun(true);
			if( ! _turnip->_state->isState == INVINCIBILITY )_turnip->_state->isState = RUN;
			if (_turnip->_state->isState == JUMP)_turnip->_state->isState = RUN;
		}


		if ((_turnip->getRc().bottom < _ground.top) && _turnip->_state->isState != JUMP )
		{
			_turnip->setRcMoveDown(10);
		}		


		_heartFruit[0].rc.left -= 4; 		_heartFruit[0].rc.right -= 4;
		_heartFruit[1].rc.left -= 4; 		_heartFruit[1].rc.right -= 4;
	
		_hfCount++; 
		IMAGEMANAGER->findImage("hf")->setFrameY(0);
		if (_hfCount % 10 == 0)
		{
			_hfIndex++; _hfCount = 0;
			if (_hfIndex > 4) _hfIndex = 0;
		}
		IMAGEMANAGER->findImage("hf")->setFrameX(_hfIndex);


#pragma endregion  

#pragma region 장애물 이동, 프레임 update

		if (_alpha2nd >= 255) 
		{
			//장애물 이동 
			for (int i = 1; i < 6; i++)
			{
				_hurdle[i].rc.left -= _gameSpeed;
				_hurdle[i].rc.right -= _gameSpeed;
			}

			for (int i = 6; i < 10; i++)
			{
				_hurdle[i].rc.left -= _gameSpeed + 1;
				_hurdle[i].rc.right -= _gameSpeed + 1;
			}

			for (int i = 10; i < 14; i++)
			{
				_hurdle[i].rc.left -= 4;
				_hurdle[i].rc.right -= 4;

			}
		}
		// 몬스터 프레임 (worm_A)
		_hCcount[WORM1]++;
		IMAGEMANAGER->findImage("worm")->setFrameY(0);
		if (_hCcount[WORM1] % 4 == 0)
		{
			_hIndex[WORM1]++; _hIndex[WORM3]++; 
			if (_hIndex[WORM1] > 3) _hIndex[WORM1] = 0; _hIndex[WORM3] = 0;
		}
		IMAGEMANAGER->findImage("worm")->setFrameX(_hIndex[WORM1]);

		// 몬스터2 프레임 (worm_B)
		_hCcount[WORM2]++;
		IMAGEMANAGER->findImage("worm")->setFrameY(0);
		if (_hCcount[WORM2] % 5 == 0)
		{
			_hIndex[WORM2]++;
			if (_hIndex[WORM2] > 3) _hIndex[WORM2] = 0;
		}
		IMAGEMANAGER->findImage("worm")->setFrameX(_hIndex[WORM2]);

		// 함정 프레임 (swamp)
		_hCcount[OUTSIDE1]++;
		IMAGEMANAGER->findImage("swamp1")->setFrameY(0);
		IMAGEMANAGER->findImage("swamp1")->setFrameY(0);
		if (_hCcount[OUTSIDE1] % 15 == 0)
		{
			_hIndex[OUTSIDE1]++;
			if (_hIndex[OUTSIDE1] > 14) _hIndex[OUTSIDE1] = 0;
		}
		IMAGEMANAGER->findImage("swamp1")->setFrameX(_hIndex[OUTSIDE1]);
		IMAGEMANAGER->findImage("swamp2")->setFrameX(_hIndex[OUTSIDE1]);

#pragma endregion 

#pragma region 충돌검사 

		for (int i =0; i < 2; i++)
		{
			checkHeartFruit(_turnip->getRc(), _heartFruit[i].rc);
		}


		if (!_turnip->getInvinsibility())
		{
			for (int i = 1; i < 10; i++)
			{
				checkCollision(_turnip->getRc(), _hurdle[i].rc);
			}

			if (IntersectRect(&temp, &_turnip->getRc(), &_hurdle[INSIDE1].rc))
			{
				if (_tHpIndex > 2)
				{
					_tHpIndex -= 2;
					_turnip->setHpIndex(_tHpIndex);
					_turnip->setInvinsibility(true);
					_turnip->_state->isState = INVINCIBILITY;
				}
			}
			if (IntersectRect(&temp, &_turnip->getRc(), &_hurdle[INSIDE2].rc))
			{
				if (_tHpIndex > 2) 
				{
					_tHpIndex -= 2;
					_turnip->setHpIndex(_tHpIndex);
					_turnip->setInvinsibility(true);
					_turnip->_state->isState = INVINCIBILITY;
				}
			}
		}

	
#pragma endregion 

	if (_turnip->getRc().top - _turnip->getRc().bottom > 150
		 && _turnip->_state->isState == RUN)
	 {
		 _turnip->setRc(_turnip->getRc().left, _ground.top + 150, 108, 150);
	 }
		

		if (_bgSpeed >= 5950)
		{
			_isReady = true; 	_bgSpeed = 5950;  _gameSpeed = 0;
		}

		// 클리어 시 맵 밖으로 나가기
		if (_isReady)
		{
			_turnip->setRcMoveRight(4);

			if (_turnip->getRc().left > WINSIZE_X + 20)
			{				
				_SceneClearCount++;

				if (_SceneClearCount >= 150)
				{
					_SceneClearCount = 150; _isClear = true;
				}	
			}
		}



	} // !_isDead && _isStart end


	if (_turnip->_state->isState != INVINCIBILITY && _turnip->_state->isState != JUMP)
	{
		_turnip->_state->isState = RUN;
	}


	if (_turnip->getHpIndex() == 0) _isDead = true;
	if (_isDead) 
	{
		_tHpIndex = 0; _turnip->_state->isState = DEAD;  _bgSpeed = 0;    _gameSpeed = 0;

		if (KEYMANAGER->isOnceKeyDown('X')) // 재시작
		{
			if (!_isStart) _isStart = true;
			if (_isStart&&_isDead) this->init();
		}
	}
}



void SecondScene::render(void)
{

	char str[128];

	if (_alpha2nd < 255)
	{
		PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		IMAGEMANAGER->alphaRender("bg", getMemDC(), 0,0, _alpha2nd);
	}
	else if (_alpha2nd >= 255)
	{
		IMAGEMANAGER->loopRender("loop_bg", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);
		IMAGEMANAGER->frameRender("swamp1", getMemDC(), _hurdle[OUTSIDE1].rc.left, _hurdle[OUTSIDE1].rc.top);
		IMAGEMANAGER->frameRender("swamp2", getMemDC(), _hurdle[OUTSIDE2].rc.left, _hurdle[OUTSIDE2].rc.top);
		IMAGEMANAGER->loopRender("fence", getMemDC(), &RectMake(0, 600, WINSIZE_X, 200), _bgSpeed, 0);
		IMAGEMANAGER->render("buttonInfo_2nd", getMemDC(), _button.left, _button.top);

		//장애물 렌더
		for (int i = 1; i < 6; i++)
		{
			IMAGEMANAGER->render("snail", getMemDC(), _hurdle[i].rc.left - 15, _hurdle[i].rc.top - 10);
		}

		for (int i = 6; i < 10; i++)
		{
			IMAGEMANAGER->frameRender("worm", getMemDC(), _hurdle[i].rc.left, _hurdle[i].rc.top);
		}

		for (int i = 0; i < 2; i++)
		{
			IMAGEMANAGER->frameRender("hf", getMemDC(), _heartFruit[i].rc.left, _heartFruit[i].rc.top);
		}

		//플레이어 렌더
		_turnip->render(getMemDC());

	}

	
	if (_isReady) IMAGEMANAGER->frameRender("turnip_run", getMemDC(), _turnip->getRc().left, _turnip->getRc().top);

	if (_isReady && (_turnip->getRc().left > WINSIZE_X +100)) IMAGEMANAGER->render("clear_2nd", getMemDC(), 0, 0);

	if (_isClear)
	{
			IMAGEMANAGER->render("clear_2nd", getMemDC(), 0, 0);
			IMAGEMANAGER->render("okButtonInfo_2nd", getMemDC(), 30, 650);
	}
	

	if(KEYMANAGER->isToggleKey(VK_F2))
	{
#pragma region 화면 표시 가이드 

		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

		rcMake(getMemDC(), _ground);

		std::sprintf(str, "STATE : %d ", _turnip->_state->isState);
		TextOut(getMemDC(), _turnip->getRc().left + 10, _turnip->getRc().top + 20, str, strlen(str));
		rcMake(getMemDC(), _turnip->getRc());

		rcMake(getMemDC(), _heartFruit[0].rc);
		rcMake(getMemDC(), _heartFruit[1].rc);

		// 장애물 
		for (int i = 0; i < HURDLE_MAX; i++)
		{
			rcMake(getMemDC(), _hurdle[i].rc);
			std::sprintf(str, "%d hurdle ", i);
			TextOut(getMemDC(),_hurdle[i].rc.left + 10, _hurdle[i].rc.top + 30, str, strlen(str));
		}

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
#pragma endregion 
	}





}


void SecondScene::checkCollision(RECT &player, RECT &hurdle)
{
	if (IntersectRect(&temp, &player, &hurdle))
	{
		_tHpIndex--;  
		_turnip->setHpIndex(_tHpIndex);
		_turnip->setInvinsibility(true); _turnip->_state->isState = INVINCIBILITY;
		_turnip->setRcMoveLeft(5);  _turnip->setRcMoveUp(8);
	}
}

void SecondScene::checkHeartFruit(RECT &player, RECT &heartFruit)
{
	if (IntersectRect(&temp, &player, &heartFruit))
	{
		if (_turnip->getHpIndex() < 6)
		{ 
			_tHpIndex++;
			_turnip->setHpIndex(_tHpIndex);
			heartFruit.left = -200;
			heartFruit.top = 200;
			heartFruit.right = heartFruit.left + 55;
			heartFruit.bottom = heartFruit.top + 60;

		}
		
	}
}
