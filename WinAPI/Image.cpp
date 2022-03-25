#include "Stdafx.h"
#include "Image.h" 

#pragma comment (lib,"msimg32.lib")

Image::Image() : _imageInfo(NULL)
				,_fileName(NULL)
				,_isTrans(FALSE)
				,_transColor(RGB(0,0,0))
				,_blendImage(NULL)
				
{
}


HRESULT Image::init(int width, int height)
{

	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID; 
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance,MAKEINTRESOURCE(_imageInfo)); 
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
 
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; 
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,IMAGE_BITMAP,
		width,height,LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 공백입력 방지
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


HRESULT Image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{

	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;


	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
	
}

HRESULT Image::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; 
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX-1;
	_imageInfo->maxFrameY = maxFrameY-1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; 
	_imageInfo->resID = 0; 
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;



	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; 
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;


	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}


	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

// 알파블렌드 초기화
HRESULT Image::initForAlphaBlend(void)
{

	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0; // 혼합비율 사용안함
	_blendFunc.AlphaFormat = 0; 
	_blendFunc.BlendOp = AC_SRC_OVER; 
	

	// 이미지 정보 새로 생성 후 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;  
	_blendImage->resID = 0; 
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap	(hdc,_imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


void Image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}


void Image::release(void) 
{
	if (_imageInfo) 
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}


	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);
	}
}

// 0.0 렌더
void Image::render(HDC hdc)
{
	if (_isTrans)
	{

		GdiTransparentBlt 
		(
			hdc,					
			0, 0,					
			_imageInfo->width,		
			_imageInfo->height,
		//--------------------------
			_imageInfo->hMemDC,		
			0,0,					
			_imageInfo->width,		
			_imageInfo->height,
		//--------------------------
			_transColor				
		);
	}
	else 
	{
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
		_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

// x.y 렌더
void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) 
	{
		GdiTransparentBlt 
		(
			hdc,					
			destX, destY,			
			_imageInfo->width,		
			_imageInfo->height,
		//--------------------------
			_imageInfo->hMemDC,		
			0, 0,					
			_imageInfo->width,		
			_imageInfo->height,
		//--------------------------
			_transColor				
		);
	}
	else 
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//클리핑 렌더
void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) 
	{
		GdiTransparentBlt 
		(
			hdc,					
			destX, destY,			
			sourWidth,				
			sourHeight,
			//----------------------
			_imageInfo->hMemDC,		
			sourX, sourY,			
			sourWidth,				
			sourHeight,
			//----------------------
			_transColor				
		);
	}
	else 
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}


}

// 알파렌더(배경)
void Image::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();
	
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{ 
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_transColor
		);

		AlphaBlend
		(
		hdc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
	else 
	{
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
}

// 알파렌더(플레이어)
void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 
			destX, destY, SRCCOPY
		);

		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_transColor
		);

		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
	else{
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc);
	}
	
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,						
			destX, destY,				
			_imageInfo->frameWidth,		
			_imageInfo->frameHeight,
			//--------------------------
			_imageInfo->hMemDC,			
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 복사 시작 지점 : X, Y
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		
			_imageInfo->frameHeight,
			//--------------------------
			_transColor					
		);
	}

	else 
	{
		BitBlt(hdc, destX, destY, 
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					
			destX, destY,			
			_imageInfo->frameWidth,	
			_imageInfo->frameHeight,
			//----------------------
			_imageInfo->hMemDC,		
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 복사 시작 지점 : X, Y
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,								
			_imageInfo->frameHeight,
			//----------------------
			_transColor				
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY)
{
	// 음수 보정
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	// 그려야 할 전체 영역
	int dramAreaX = dramArea->left;
	int dramAreaY = dramArea->top;
	int dramAreaW = dramArea->right - dramArea->left;
	int dramAreaH = dramArea->bottom - dramArea->top;

	// 세로 루프
	for (int y = 0; y < dramAreaH; y += sourHeight)
	{
		// 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > dramAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - dramAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// 그려지는 영역
		rcDest.top = y + dramAreaY;
		rcDest.bottom = rcDest.top + sourHeight;


		// 가로 루프
		for (int x = 0; x < dramAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > dramAreaW)
			{
				rcSour.right -= (x + sourWidth) - dramAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + dramAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				sourWidth, sourHeight);

		}//end of second
		
	}//end of for

}

void Image::loopAlphaRender(HDC hdc, const LPRECT dramaArea, int offsetX, int offsetY, BYTE alpha)
{



}

