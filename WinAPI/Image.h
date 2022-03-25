#pragma once

class Image
{

public:

	// ���� ����ϴ� API �ڷ���
	// DWORD : Unsigened long
	// WORD : Unsigened short
	// BYTE : Unsigend char : �������� 256 (char = 128 -> *2)
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, // ���ҽ� ���Ϳ��� ��������
		LOAD_FILE, // ���丮�� �����б�
		LOAD_EMPTY, // �� ��Ʈ��
		LOAD_END // �ƹ��͵�
	};

	typedef struct tagImage
	{
		DWORD resID; // ���ҽ� ID
		HDC hMemDC; // �޸� DC : �� ������ �޸�
		HBITMAP hBit; // ��Ʈ�� ������
		HBITMAP hOBit; // �õ� ��Ʈ�� : ������ �������� ������
		int x;
		int y;
		int width; // �̹��� ���� 
		int height; // �̹��� ���� 
		int maxFrameX;
		int maxFrameY;
		int currentFrameX;
		int currentFrameY;
		int frameWidth;
		int frameHeight;
		BYTE loadType; // �̹��� �ε� Ÿ�� ������

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit=NULL;
			hOBit = NULL;
			x =0;
			y =0;
			width = 0;
			height = 0;
			maxFrameX=0;
			maxFrameY=0;
			currentFrameX=0;
			currentFrameY=0;
			frameWidth=0;
			frameHeight=0;
			loadType = LOAD_RESOURCE;
		}

	}	IMAGE_INFO, *LPIMAGE_INFO; 
	// ����ü�� �̸��� �ΰ��� �߿� �����, �����͸� �����(������� if�� ��� ��.)

private:
	LPIMAGE_INFO _imageInfo; //�̹��� ���� , ����ü�� �ּҰ� 
	CHAR* _fileName; // ���ϸ�
	BOOL _isTrans; // ������ ���ٰ��� ����
	COLORREF _transColor; // ������ ����  RGB�� (���� 1����Ʈ 0~255 �󵵷� ǥ�� ����)
						  // �� �ɰ����� ����Ʈ ���
	BLENDFUNCTION _blendFunc;
	LPIMAGE_INFO _blendImage;

public:
    // ==> �������� LOAD_KIND�� ����
	// �� ��Ʈ������ �ʱ�ȭ
	HRESULT init(int width, int height);

	// �̹��� ���ҽ��� �ʱ�ȭ
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	// �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	// ������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y,int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));


	// ���ĺ����� �ʱ�ȭ(�߻�ȭ)
	HRESULT initForAlphaBlend(void);

	// ���� �÷�Ű ����(���� ��������, ���)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	// ����
	void release(void);

	//=======================================

	// ���� / ���, �÷��̾� 
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// Ŭ���� ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// ���ķ��� / ���, �÷��̾�
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX,int destY, BYTE alpha);
	// Ŭ���� ���ķ���
	void alphaRender(HDC hdc, int destX, int destY,int sourX,int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// ������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// ���� ���� 
	void loopRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY, BYTE alpha);



	//=========================
	// �ζ��� �Լ�
	//=========================

	// DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// �̹��� X��ǥ
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x=x; }

	// �̹��� Y��ǥ
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y=y; }

	// �̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// �̹��� ���μ���
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// �ٿ���ڽ�(�浹�뷺Ʈ)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
		(int)_imageInfo->x,
		(int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->width,
		(int)_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	// �ٿ���ڽ�(�浹�뷺Ʈ)
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
		(int)_imageInfo->x,
		(int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->frameWidth,
		(int)_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	// ������X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	
	}

	// ������Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// �̹��� 1 ������ ����, ���� ũ�� 
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// �ִ� ������ x,y ����
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	Image();
	~Image() {};
};
