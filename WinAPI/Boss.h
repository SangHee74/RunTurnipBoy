#pragma once
#include "STATE.h"

class Boss 
{

private:

	RECT rc; // 피격범위
	int posX, posY;
	RECT HP; // 체력바
	int  dmg;
	int hpIndex;
	int  count, index; // 프레임용 변수
	float timer; // 피격 후 무적 타이머
	bool isLeft,isIdle,isDead,isInvinsibility;
	bool isSkill;

public:

	Boss() {}
	virtual ~Boss() {}

	//stateClass* _state;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	RECT getRc() { return rc; }
	void setRc(int x, int y, int w, int h) { rc = { x, y, x + w, y + h }; }
	void setRcMoveLeft(int x) { rc.left -= x; rc.right -= x; }
	void setRcMoveRight(int x) { rc.left += x; rc.right += x; }
	void setRcMoveUp(int y) { rc.top -= y; rc.bottom -= y; }

	//RECT getHP() { return HP; }
	//void setHP(int x, int y, int w, int h) { HP = { x, y, x + w, y + h }; }

	float getPosX() { return posX; }
	void setPosX(int value) { posX = value; }

	float getPosY() { return posY; }
	void setPosY(int value) { posY = value; }

	int getHpIndex() { return hpIndex; }
	void setHpIndex(int value) { hpIndex = value; }

	int getCount() { return count; }
	void setCount(int value) { count = value; }

	int getIndex() { return index; }
	void setIndex(int value) { index = value; }
	
	bool getInvinsibility() { return isInvinsibility; }
	void setInvinsibility(bool state) { isInvinsibility = state; }

	bool getIsLeft() { return isLeft; }
	void setIsLeft(bool state) { isLeft = state; }

	bool getIsIdle() { return isIdle; }
	void setIsIdle(bool state) { isIdle = state; }

	bool getIsDead() { return isDead; }
	void setIsDead(bool state) { isDead = state; }

	bool getIsSkill() { return isSkill; }
	void setIsSkill(bool state) { isSkill = state; }

};

