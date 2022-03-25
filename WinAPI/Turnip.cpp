#include "Stdafx.h"
#include "Turnip.h"

HRESULT Turnip::init(void)
{
	_state = new stateClass();

	// 순무 이미지
	IMAGEMANAGER->addFrameImage("turnip_idle", "Resources/Images/T/t_idle.bmp ", 432 ,300, 4, 2, true, MGT);
	IMAGEMANAGER->addFrameImage("turnip_run", "Resources/Images/T/t_run.bmp ", 324, 300, 3, 2, true, MGT);
	IMAGEMANAGER->addFrameImage("turnip_hit", "Resources/Images/T/t_hit.bmp ", 216, 300, 2, 2, true, MGT);
	IMAGEMANAGER->addFrameImage("turnip_jump", "Resources/Images/T/t_jump.bmp ", 216, 300, 2, 2, true, MGT);
	IMAGEMANAGER->addFrameImage("turnip_die", "Resources/Images/T/t_die.bmp ", 216, 300, 2, 2, true, MGT);

	IMAGEMANAGER->addFrameImage("sw_idle", "Resources/Images/T/sw_idle.bmp ",140,300, 1, 2, true, MGT);
	IMAGEMANAGER->addFrameImage("sw_att", "Resources/Images/T/sw_att.bmp ", 174, 106, 2, 2, true, MGT);

	IMAGEMANAGER->addImage("die_bg", "Resources/Images/die_bg.bmp ", 1200, 800);
	IMAGEMANAGER->addImage("die_text", "Resources/Images/die_text.bmp ", 1200, 800, true, MGT);


	// 순무 하트 체력바 
	IMAGEMANAGER->addFrameImage("hp", "Resources/Images/T/HpHeart.bmp ", 2065, 90, 7, 1, true, MGT); // 하트 체력바

	// 순무 초기화
	rc = RectMakeCenter(-120, 625, 108, 150); // 위치
	HP = RectMake(35, 40,  295, 90); // FULL체력 
	swRc = RectMakeCenter(-134, 635, 140, 150);
	attSwRc = RectMakeCenter(-200, 679, 87, 53);
	
	hpIndex = 6; 
	timer = 0.0f;
	
	run = true;
	hit = false; invincibility = false;  isLeft = false;

	// 점프 관련
	jump = false;
	jumpCount = 1;  
	jumpSpeed = 0.0f; 	
	gravity = 0.0f; 

	// 프레임용
	count = index = 0;
	countW = indexW = 0;
	countH = indexH = 0;


	return S_OK;
}

void Turnip::release(void)
{
	SAFE_DELETE(_state);
}

void Turnip::update(void)
{
	
	// == 순무 기능 update ==============================================

		if (!isLeft) setSwRc(rc.left - 27, rc.top + 14, 140, 150);
		else setSwRc(rc.left -10, rc.top + 14, 140, 150);


		

	// 점프 순무 
	if (KEYMANAGER->isOnceKeyDown('X') && this->jumpCount < 2)
	{
		jumpSpeed = 18.0f;
		gravity = 0.01f;

		jump = true;
		this->_state->isState = JUMP;
	}
	jumping();


	if (_state->isState == IDLE || _state->isState == ATTACK)
	{
		if (!this->isLeft)
		{
			count++;
			IMAGEMANAGER->findImage("turnip_idle")->setFrameY(0);
			if (count % 6 == 0)
			{
				index++; count = 0;
				if (index > 3) index = 0;
			}
			IMAGEMANAGER->findImage("turnip_idle")->setFrameX(index);
		}
		else {
			count++;
			IMAGEMANAGER->findImage("turnip_idle")->setFrameY(1);
			if (count % 6 == 0)
			{
				index--; count = 0;
				if (index < 0) index = 3;
			}
			IMAGEMANAGER->findImage("turnip_idle")->setFrameX(index);
		}


	}

	if (_state->isState == RUN)
	{
		if (! this->isLeft )
		{
			count++;
			IMAGEMANAGER->findImage("turnip_run")->setFrameY(0);
			if (count % 4 == 0)
			{
				index++; count = 0;
				if (index > 3) index = 0;
			}
			IMAGEMANAGER->findImage("turnip_run")->setFrameX(index);
		}
		else {
			count++;
			IMAGEMANAGER->findImage("turnip_run")->setFrameY(1);
			if (count % 4 == 0)
			{
				index--; count = 0;
				if (index < 0) index = 3;
			}
			IMAGEMANAGER->findImage("turnip_run")->setFrameX(index);
		}
	}
	

	if (_state->isState == JUMP)
	{
		if (!this->isLeft)
		{
			count++;
			IMAGEMANAGER->findImage("turnip_jump")->setFrameY(0);
			if (count % 5 == 0)
			{
				index++; count = 0;
				if (index > 3) index = 0;
			}
			IMAGEMANAGER->findImage("turnip_jump")->setFrameX(index);
		}
		else 
		{
			count++;
			IMAGEMANAGER->findImage("turnip_jump")->setFrameY(1);
			if (count % 5 == 0)
			{
				index--; count = 0;
				if (index < 0) index = 3;
			}
			IMAGEMANAGER->findImage("turnip_jump")->setFrameX(index);
		}
	}

	if (_state->isState == INVINCIBILITY)
	{
		if (!this->isLeft)
		{
			countH++;
			IMAGEMANAGER->findImage("turnip_hit")->setFrameY(0);
			if (countH % 6 == 0)
			{
				indexH++; countH = 0;
				if (indexH > 2) indexH = 0;
			}
			IMAGEMANAGER->findImage("turnip_hit")->setFrameX(indexH);
		}
		else {
			countH++;
			IMAGEMANAGER->findImage("turnip_hit")->setFrameY(0);
			if (countH % 6 == 0)
			{
				indexH--; countH = 0;
				if (indexH < 0) indexH = 2;
			}
			IMAGEMANAGER->findImage("turnip_hit")->setFrameX(indexH);
		}

		
	}

	if (_state->isState == DEAD)
	{
		if (!this->isLeft)
		{
			count++;
			IMAGEMANAGER->findImage("turnip_die")->setFrameY(0);
			if (count % 3 == 0)
			{
				index++; count = 0;
				if (index > 2) index = 0;
			}
			IMAGEMANAGER->findImage("turnip_die")->setFrameX(index);
		}
		else
		{
			count++;
			IMAGEMANAGER->findImage("turnip_die")->setFrameY(0);
			if (count % 3 == 0)
			{
				index--; count = 0;
				if (index < 0) index = 2;
			}
			IMAGEMANAGER->findImage("turnip_die")->setFrameX(index);
		}
	}

#pragma region 무기 업데이트 

	if (!this->isLeft) IMAGEMANAGER->findImage("sw_idle")->setFrameY(0);

	else IMAGEMANAGER->findImage("sw_idle")->setFrameY(1);


	if (!this->isLeft)
	{
		countW++;
		IMAGEMANAGER->findImage("sw_att")->setFrameY(0);
		if (count % 10 == 0)
		{
			indexW++; countW = 0;
			if (indexW > 2) indexW = 0; 
		}
		IMAGEMANAGER->findImage("sw_att")->setFrameX(indexW);
	}
	else
	{
		countW++;
		IMAGEMANAGER->findImage("sw_att")->setFrameY(1);
		if (countW % 10 == 0)
		{
			indexW--; countW = 0;
			if (indexW < 0) indexW = 2;
		}
		IMAGEMANAGER->findImage("sw_att")->setFrameX(indexW);
	}

#pragma endregion 


	// 충돌 후 잠시 무적
	if (this->invincibility)
	{
		this->_state->isState = INVINCIBILITY;
		timer++; // 무적일 때 타이머

		if (timer > 75.0f)
		{
			this->invincibility = false;
			timer = 0;
			this->_state->isState = IDLE;
		}

	}

}

void Turnip::render(HDC hdc)
{
		IMAGEMANAGER->frameRender("hp", hdc, this->HP.left, this->HP.top);


	if (this->_state->isState == IDLE)
	{
		IMAGEMANAGER->frameRender("turnip_idle", hdc, this->rc.left, this->rc.top);
	}

	if (this->_state->isState == RUN)
	{
		IMAGEMANAGER->frameRender("turnip_run", hdc, this->rc.left, this->rc.top);
	}

	if (this->_state->isState == JUMP)
	{
		IMAGEMANAGER->frameRender("turnip_jump", hdc, this->rc.left, this->rc.top);
	}

	if (this->_state->isState == INVINCIBILITY)
	{
		IMAGEMANAGER->frameRender("turnip_hit", hdc, this->rc.left, this->rc.top);
	}

	if (this->_state->isState == DEAD)
	{
		IMAGEMANAGER->frameRender("turnip_die", hdc, this->rc.left, this->rc.top);
		IMAGEMANAGER->alphaRender("die_bg", hdc, 180);
		IMAGEMANAGER->render("die_text", hdc);
	}

	if (this->_state->isState == ATTACK)
	{
		IMAGEMANAGER->frameRender("turnip_idle", hdc, this->rc.left, this->rc.top);
	}


}
void Turnip::renderSw(HDC hdc)
{
	if (this->_state->isState == ATTACK)
	{
		IMAGEMANAGER->frameRender("sw_att", hdc, this->attSwRc.left, this->attSwRc.top);
	}
	else
	{
		IMAGEMANAGER->frameRender("sw_idle", hdc, this->swRc.left, this->swRc.top);
	}
}


void Turnip::resetHP(void)
{
	IMAGEMANAGER->findImage("hp")->setFrameY(0);
	if (hpIndex > 6) hpIndex = 6;
	if (hpIndex < 0) hpIndex = 0;
	IMAGEMANAGER->findImage("hp")->setFrameX(hpIndex);
}

void Turnip::jumping(void)
{
	if (this->jump)
	{
		this->run = false;

		this->rc.bottom -= this->jumpSpeed + this->gravity;
		this->rc.top -= this->jumpSpeed + this->gravity;

		this->gravity -= 0.6f;

		this->jumpCount++;
	}
}

void Turnip::attack(void)
{
	setSwRc(-500, 652, 140, 150);

	if (!isLeft) setAttSwRc(rc.right + 2, rc.top + 54, 87, 53);
	else setAttSwRc(rc.left - 82, rc.top + 54, 87, 53);
}
