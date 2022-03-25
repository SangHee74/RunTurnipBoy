#include "Stdafx.h"
#include "MainGame.h"


HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	_title = new TitleScene();
	_title->init();

	_first = new FirstScene();
	_first->init();

	_second = new SecondScene();
	_second->init();

	_third = new ThirdScene();
	_third->init();

	_complet = new CompleteScean();
	_complet->init();


	_currentScene = _title;


	assert(_currentScene != nullptr);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_title);
	SAFE_DELETE(_first);
	SAFE_DELETE(_second);
	SAFE_DELETE(_third);
	SAFE_DELETE(_complet);

}

void MainGame::update(void)
{
	GameNode::update();

	_currentScene->update();

	if (_currentScene == _title)
	{
		if (_title->getIndex() == 0 && _title->getTitle())
		{
			if(KEYMANAGER->isOnceKeyDown('X')) 	_currentScene = _first;
		}

		if (_title->getIndex() == 1)
		{
			if(KEYMANAGER->isOnceKeyDown('X'))		PostQuitMessage(0);
		}
	};
	

	if (_currentScene == _first)
	{
		if (_first->getSceneClear())
		{

			if (KEYMANAGER->isStayKeyDown('X'))	  _currentScene = _second;
		}
	}


	if (_currentScene == _second)
	{
		if (_second->getSceneClear() )
		{
	
			if (KEYMANAGER->isStayKeyDown('X'))	  _currentScene = _third;
		}
	}

	if (_currentScene == _third)
	{
		if (_third->getSceneClear())
		{

			if (KEYMANAGER->isStayKeyDown('X'))	  _currentScene = _complet;
		}
	}

	if (_currentScene == _complet)
	{
		if (_complet->getGoTitle())
		{

			if (KEYMANAGER->isStayKeyDown('X'))	  _currentScene = _title;
		}
	}
}

void MainGame::render(void)
{

	// 검은색 빈 비트맵
	// PatBle() : 사각형 영역을 브러쉬로 채우는 함수 
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	//==========================================================

	_currentScene->render();

	this->getBackBuffer()->render(getHDC());


}

