#pragma once
#include "STATE.h"


class Turnip
{
private:

	// 순무 위치, 체력, 공격력, 상태 
	RECT rc; // 위치
	RECT HP; // 체력바

	int  hpIndex; 
	bool run, hit, invincibility; // 상태(대기, 달림, 점프, 피격, 무적 )
	bool isLeft; // 방향

	RECT swRc; // 대기 중 범위 
	RECT attSwRc; // 공격시 범위

	bool jump; // 점프? 참이면 떠잇음
	int jumpCount; // 점프 횟수
	float jumpSpeed;	//점프 속도
	float gravity;		//중력

	int count, index; // 프레임용 변수
	int  countW, indexW; // 무기 프레임 변수
	int countH, indexH; // 피격 프레임 변수

	float timer; // 피격 후 무적 타이머

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

	void setCHPUp(int x) { rc.right += x; } // 왼쪽을 기준으로 오른쪽 길이가 짧아짐
	void setCHPDown(int x) { rc.right -= x; }

	int getHpIndex() { return hpIndex; }
	void setHpIndex(int value) { hpIndex = value; }

	int getCount() { return count; }
	void setCount(int value) { count = value; }

	int getIndex() { return index; }
	void setIndex(int value) { index = value; }

	// 함수-----------------
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



