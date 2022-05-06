﻿//WinMain
#include "Stdafx.h"
#include "MainGame.h"


//==============
//# 전역 변수 #
//==============
HINSTANCE _hInstance;
HWND      _hWnd;
POINT	  _ptMouse;


//! 콜백 함수
//===================
//# 함수 전방 선언 #
//===================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int wideh, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_mg = new MainGame();

	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;									 
	wndClass.cbWndExtra = 0;							    	 
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	  
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);		 
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		
	wndClass.hInstance = hInstance;							
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						       
	wndClass.lpszClassName = WINNAME;					     		
	wndClass.lpszMenuName = NULL;									 
	wndClass.style = CS_HREDRAW | CS_VREDRAW;				  

	RegisterClass(&wndClass);

#ifdef FULLSCREEN

	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));
	dm.dmBitsPerPel = 32; 
	dm.dmPelsWidth=1980; 
	dm.dmPelsHeight = 1020;
	dm.dmDisplayFrequency = 80;	

	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

#else
	_hWnd = CreateWindow 
	(
		WINNAME,					 
		WINNAME,					 
		WINSTYLE,					 
		WINSTART_X,					 
		WINSTART_Y,					 
		WINSIZE_X,					 
		WINSIZE_Y,					 
		NULL,	 
		(HMENU)NULL,				 
		hInstance,					 
		NULL						 
									 
	);


	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#endif

	ShowWindow(_hWnd, nCmdShow); 


	if (FAILED(_mg->init()))
	{
		return 0;
	}

	MSG message;


	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	_mg->release();
	delete _mg;
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}


void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };


	AdjustWindowRect(&rc, WINSTYLE, false);


	SetWindowPos
	(
		_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE
	);

}