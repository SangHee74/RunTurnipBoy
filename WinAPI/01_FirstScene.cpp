#include "Stdafx.h"
#include "01_FirstScene.h"

HRESULT FirstScene::init(void)
{

	IMAGEMANAGER->addImage("0_bg", "Resources/Images/1stScene/0_talk_bg.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("0_bg2", "Resources/Images/1stScene/0_talk_bg2.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("0_1", "Resources/Images/1stScene/0_talk_1.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("0_2", "Resources/Images/1stScene/0_talk_2.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("0_3", "Resources/Images/1stScene/0_talk_3.bmp ", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("turnip_idle", "Resources/Images/T/t_idle.bmp ", 432, 300, 4, 2, true, MGT);

	// 루프랜더
	_bgAlpha = 0;
	_bgIndex = 0;

	_isStart = false;
	_isClear = false;
	_talkEnd = false;

	count = index = 0;


	return S_OK;
}

void FirstScene::release(void)
{
}

void FirstScene::update(void)
{
	_bgAlpha++;
	if (_bgAlpha >= 255 )
	{
		_bgAlpha = 255;
		_isStart = true;
	}


	if (!_talkEnd)
	{
		if (KEYMANAGER->isOnceKeyUp('X')) _bgIndex++;
	}


	if (_bgIndex > 3)
	{
		_bgIndex = 0;	_talkEnd = false; _isClear = true;
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

void FirstScene::render(void)
{
	IMAGEMANAGER->alphaRender("0_bg", getMemDC(), 0, 0, _bgAlpha);

	if(_isStart  )
	{
		IMAGEMANAGER->render("0_bg", getMemDC(), 0, 0);

	if (_bgIndex == 1) IMAGEMANAGER->render("0_1", getMemDC(), 0, 0);
	if (_bgIndex == 2) IMAGEMANAGER->render("0_2", getMemDC(), 0, 0);
	if (_bgIndex == 3) IMAGEMANAGER->render("0_3", getMemDC(), 0, 0);
	}
	
	if (_isClear)
	{
		IMAGEMANAGER->render("0_bg2", getMemDC(), 0, 0);
		IMAGEMANAGER->frameRender("turnip_idle", getMemDC(), 340, 540);
	}


}
