#pragma once
#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

//===================================
// # 내가 만든 헤더파일을 이곳에 추가 #
//===================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"

//========================
// # 싱글톤을 이곳에 추가 #
//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()


//============================
// # 매크로 # (윈도우창 초기화)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

#define MGT RGB(255,0,255)

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X	 1920 
#define WINSTART_Y	 0
#define WINSIZE_X	 GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	 WS_POPUPWINDOW | WS_MAXWIZE

#else
#define WINSTART_X	 200
#define WINSTART_Y	 0
#define WINSIZE_X	 1200
#define WINSIZE_Y	 800
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU
#endif 

//===============================================
// # 매크로 함수 # 
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # 전역변수 #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;