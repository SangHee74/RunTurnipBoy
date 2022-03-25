#include "Stdafx.h"
#include "00_TitleScean.h"

HRESULT TitleScene::init(void)
{
	IMAGEMANAGER->addImage("타이틀0",     "Resources/Images/0TitleScene/title0.bmp", 1200,800);
	IMAGEMANAGER->addFrameImage("타이틀", "Resources/Images/0TitleScene/title.bmp", 3600, 800,3,1,false,MGT);
	IMAGEMANAGER->addFrameImage("버튼",   "Resources/Images/0TitleScene/button.bmp", 310, 150, 2, 1, false,MGT);
	button = RectMake(985, 345, 155, 150);

	_bgAlpha = 0;
	_isTitle = false;
	_count = _index = 0;
	_bIndex=0;

	return S_OK;
}

void TitleScene::release(void)
{
}

void TitleScene::update(void)
{

	_bgAlpha += 1.5f;
	if (_bgAlpha >= 225) { _bgAlpha = 255; _isTitle = true; }


	if (_isTitle)
	{
		_count++;
		IMAGEMANAGER->findImage("타이틀")->setFrameY(0);
		if (_count % 8 == 0)
		{
			_index++; _count = 0;
			if (_index > 2) _index = 0;
		}
		IMAGEMANAGER->findImage("타이틀")->setFrameX(_index);


		IMAGEMANAGER->findImage("버튼")->setFrameY(0);
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_bIndex++;
			if (_bIndex >= 2)_bIndex = 0;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_bIndex--;
			if (_bIndex < 0)_bIndex = 1;
		}
		IMAGEMANAGER->findImage("버튼")->setFrameX(_bIndex);
	}
}

void TitleScene::render(void)
{

	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	if (!_isTitle) IMAGEMANAGER->alphaRender("타이틀0", getMemDC(), 0, 0, _bgAlpha);
	else
	{
	IMAGEMANAGER->frameRender("타이틀", getMemDC(),0,0);
	IMAGEMANAGER->frameRender("버튼", getMemDC(), button.left, button.top);
	}
}
