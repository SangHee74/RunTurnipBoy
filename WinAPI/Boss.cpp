#include "Stdafx.h"
#include "Boss.h"

HRESULT Boss::init(void)
{
	IMAGEMANAGER->addFrameImage("cat_idle", "Resources/Images/B/cat_idle.bmp ", 884, 442, 4, 2, true, MGT);
	IMAGEMANAGER->addFrameImage("cat_hurt", "Resources/Images/B/cat_hurt.bmp ", 442, 442, 2, 2, true, MGT);
	IMAGEMANAGER->addFrameImage("cat_spin", "Resources/Images/B/cat_spinFull.bmp ", 4862, 442, 22, 2, true, MGT);
	IMAGEMANAGER->addFrameImage("cat_hp", "Resources/Images/B/hp.bmp ", 1932, 85, 6, 1, true, MGT);

	// 고양이 이미지 좌표 초기화
	posX=695;	 posY=515;

	rc = RectMake(posX+35, posY +35, 170,142);

	HP = RectMake(WINSIZE_X-382, 40, 322, 85); // FULL체력 

	dmg = 1;

	count = index = 0;
	timer = 0;
	hpIndex = 5;
	isLeft = isIdle = true;
	isInvinsibility = isDead = false;
	isSkill = false;


	return S_OK;
}

void Boss::release(void)
{

}

void Boss::update(void)
{

	IMAGEMANAGER->findImage("cat_hp")->setFrameY(0);
	if (hpIndex > 5) hpIndex = 5;
	if (hpIndex < 0) hpIndex = 0;
	IMAGEMANAGER->findImage("cat_hp")->setFrameX(hpIndex);


	if (isIdle)
	{
		if (!this->isLeft)
		{
			count++;
			IMAGEMANAGER->findImage("cat_idle")->setFrameY(0);
			if (count % 7 == 0)
			{
				index++; count = 0;
				if (index > 3) index = 0;
			}
			IMAGEMANAGER->findImage("cat_idle")->setFrameX(index);
		}
		else {
			count++;
			IMAGEMANAGER->findImage("cat_idle")->setFrameY(1);
			if (count % 7 == 0)
			{
				index--; count = 0;
				if (index < 0) index = 3;
			}
			IMAGEMANAGER->findImage("cat_idle")->setFrameX(index);
		}
	}

	if (isInvinsibility)
	{
		if (!this->isLeft)
		{
			count++;
			IMAGEMANAGER->findImage("cat_hurt")->setFrameY(0);
			if (count % 7 == 0)
			{
				index++; count = 0;
				if (index > 3) index = 0;
			}
			IMAGEMANAGER->findImage("cat_hurt")->setFrameX(index);
		}
		else {
			count++;
			IMAGEMANAGER->findImage("cat_hurt")->setFrameY(1);
			if (count % 7 == 0)
			{
				index--; count = 0;
				if (index < 0) index = 3;
			}
			IMAGEMANAGER->findImage("cat_hurt")->setFrameX(index);
		}
	}



	// 충돌 후 잠시 무적
	if (this->isInvinsibility)
	{
		timer++; // 무적일 때 타이머

		if (timer > 75.0f)
		{
			this->isInvinsibility = false;
			if (this->isLeft) 		this->setRcMoveRight(5);
			else this->setRcMoveLeft(5);
			timer = 0;
			this->isIdle = true;
		}

	}

	if (isSkill)
	{
		if (!this->isLeft)
		{
			count++;
			IMAGEMANAGER->findImage("cat_spin")->setFrameY(0);
			if (count % 3 == 0)
			{
				index++; count = 0;
				if (index > 22) index = 0;
			}
			IMAGEMANAGER->findImage("cat_spin")->setFrameX(index);
		}
		else {
			count++;
			IMAGEMANAGER->findImage("cat_spin")->setFrameY(1);
			if (count % 3 == 0)
			{
				index--; count = 0;
				if (index < 0) index = 22;
			}
			IMAGEMANAGER->findImage("cat_spin")->setFrameX(index);
		}
	}




	if (this->hpIndex == 0) isDead = true;
	if(isDead) 	rc = RectMakeCenter(-400, posY, 170, 142);

}

void Boss::render(HDC hdc)
{

	//IMAGEMANAGER->frameRender("cat_hp", hdc, this->HP.left, this->HP.top);

	
	if (isIdle)
	{
		IMAGEMANAGER->frameRender("cat_idle", hdc, this->posX, this->posY);
	}


	if (isInvinsibility)
	{
		IMAGEMANAGER->frameRender("cat_hurt", hdc, this->posX, this->posY);
	}

	if (isSkill)
	{
		IMAGEMANAGER->frameRender("cat_spin", hdc, this->posX, this->posY);

	}


}
