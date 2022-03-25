#pragma once
#include "STATE.h"


class Turnip
{
private:

	// ���� ��ġ, ü��, ���ݷ�, ���� 
	RECT rc; // ��ġ
	RECT HP; // ü�¹�

	int  hpIndex; 
	bool run, hit, invincibility; // ����(���, �޸�, ����, �ǰ�, ���� )
	bool isLeft; // ����

	RECT swRc; // ��� �� ���� 
	RECT attSwRc; // ���ݽ� ����

	bool jump; // ����? ���̸� ������
	int jumpCount; // ���� Ƚ��
	float jumpSpeed;	//���� �ӵ�
	float gravity;		//�߷�

	int count, index; // �����ӿ� ����
	int  countW, indexW; // ���� ������ ����
	int countH, indexH; // �ǰ� ������ ����

	float timer; // �ǰ� �� ���� Ÿ�̸�

public:
	Turnip() {} 
	~Turnip() {}

	stateClass* _state;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void renderSw(HDC hdc);


	RECT getRc() { return rc; }
	void setRc(int x, int y, int w, int h) { rc = { x, y, x + w, y + h }; }
	void setRcMoveLeft(int x) {  rc.left -= x; rc.right -= x; }
	void setRcMoveRight(int x) { rc.left += x; rc.right += x; }
	void setRcMoveUp(int y) { rc.top -= y; rc.bottom -= y; }
	void setRcMoveDown(int y) { rc.top += y; rc.bottom += y; }

	RECT getSwRc() { return swRc; }
	void setSwRc(int x, int y, int w, int h) { swRc = {x,y,w,h}; }
	void setSwRcMoveLeft(int x) { swRc.left -= x; swRc.right -= x; }
	void setSwRcMoveRight(int x) { swRc.left += x; swRc.right += x; } 


	RECT getAttSwRc() { return attSwRc; }
	void setAttSwRc(int x, int y, int w, int h) { attSwRc = { x, y, x + w, y + h }; }


	RECT getHP() { return HP; }
	void setHP(int x, int y, int w, int h) { HP = { x, y, x + w, y + h }; }

	void setCHPUp(int x) { rc.right += x; } // ������ �������� ������ ���̰� ª����
	void setCHPDown(int x) { rc.right -= x; }

	int getHpIndex() { return hpIndex; }
	void setHpIndex(int value) { hpIndex = value; }

	int getCount() { return count; }
	void setCount(int value) { count = value; }

	int getIndex() { return index; }
	void setIndex(int value) { index = value; }

	// �Լ�-----------------
	void resetHP(void);
	void jumping(void);
	void attack(void);
	

	int getJumpCount() { return jumpCount; }
	void setJumpCount(int num) { jumpCount = num; }

	float getJumpSpeed() { return jumpSpeed; }
	void setJumpSpeed(int num) { jumpSpeed = num; }

	float getGravity() { return gravity; }
	void setGravity(int num) { gravity = num; }

	bool getIsLeft() { return isLeft; }
	void setIsLeft(bool state) { isLeft = state; }

	bool getRun() { return run; }
	void setRun(bool state) { run = state; }

	bool getJump() { return jump; }
	void setJump(bool state) { jump = state; }

	bool getHit() { return hit; }
	void setHit(bool state) { hit = state; }

	bool getInvinsibility() { return invincibility; }
	void setInvinsibility(bool state) { invincibility = state; }

};



