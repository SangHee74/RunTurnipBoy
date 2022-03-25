#pragma once
#include <sdkddkver.h>

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN 

// ����ȯ ������ �ս� 
//#pragma warning(disable:4244)

//! Windows ��� ����
#include <Windows.h>

// ������ �ܼ�â
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

//! C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

//! C++ ��Ÿ�� ��� ����
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

//===================================
// # ���� ���� ��������� �̰��� �߰� #
//===================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"

//========================
// # �̱����� �̰��� �߰� #
//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()


//============================
// # ��ũ�� # (������â �ʱ�ȭ)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

#define MGT RGB(255,0,255)

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X	 1920 // ����Ϳ� ���� �ٸ� 
#define WINSTART_Y	 0
// GetSystemMetrics ���ڷ� ���޵Ǵ� �ý��� ���� ���� ��Ȳ
// ��SM_CXSCREEN / SM_CYSCREEN :  ���� ȭ�� �ػ� X, Y�� ��ȯ 
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
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # �������� #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;