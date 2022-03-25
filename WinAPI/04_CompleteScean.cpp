#include "Stdafx.h"
#include "04_CompleteScean.h"


HRESULT CompleteScean::init(void)
{
	IMAGEMANAGER->addImage("c1_bg", "Resources/Images/4CompleteScene/c1_talk_bg.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("c1_1", "Resources/Images/4CompleteScene/c1_talk_1.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("c1_2", "Resources/Images/4CompleteScene/c1_talk_2.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("c1_3", "Resources/Images/4CompleteScene/c1_talk_3.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("c1_4", "Resources/Images/4CompleteScene/c1_talk_4.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("c1_5", "Resources/Images/4CompleteScene/c1_talk_5.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("turnip_idle", "Resources/Images/T/t_idle.bmp ", 432, 300, 4, 2, true, MGT);

	_bgAlpha = 0;
	_bgIndex = 1;

	_isStart = false;
	_talkEnd = false;
	_goTitle = false;

	return S_OK;
}

void CompleteScean::release(void)
{
}

void CompleteScean::update(void)
{
	_bgAlpha++;
	if (_bgAlpha >= 255)
	{
		_bgAlpha = 255;
		_isStart = true;
	}

	if (!_talkEnd)
	{
		if (KEYMANAGER->isOnceKeyDown('X')) _bgIndex++;
	}

	if (_bgIndex > 5)
	{
		_bgIndex = 0;	_talkEnd = false; _goTitle = true;

	}

	count++;
	IMAGEMANAGER->findImage("turnip_idle")->setFrameY(0);
	if (count % 6 == 0)
	{
		index++; count = 0;
		if (index > 3) index = 0;
	}
	IMAGEMANAGER->findImage("turnip_idle")->setFrameX(index);

}

void CompleteScean::render(void)
{

	IMAGEMANAGER->alphaRender("c1_bg", getMemDC(), 0, 0, _bgAlpha);

	if (_isStart)
	{
		IMAGEMANAGER->frameRender("turnip_idle", getMemDC(), 340, 540);
		IMAGEMANAGER->render("c1_bg", getMemDC(), 0, 0);

		if (_bgIndex == 1) IMAGEMANAGER->render("c1_1", getMemDC(), 0, 0);
		if (_bgIndex == 2) IMAGEMANAGER->render("c1_2", getMemDC(), 0, 0);
		if (_bgIndex == 3) IMAGEMANAGER->render("c1_3", getMemDC(), 0, 0);
		if (_bgIndex == 4) IMAGEMANAGER->render("c1_4", getMemDC(), 0, 0);
		if (_bgIndex == 5) IMAGEMANAGER->render("c1_5", getMemDC(), 0, 0);
	}

}
