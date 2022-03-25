#pragma once

enum STATE 
{
	IDLE, RUN, JUMP, HURT, INVINCIBILITY, DEAD, ATTACK
};


enum STAGE
{
	BARN
};


class stateClass
{
public :

	STATE isState;

	STAGE isStage;
};
