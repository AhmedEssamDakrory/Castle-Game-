#pragma once
#include "Enemy.h"


class Paver : public Enemy{

public:


	Paver (int id , int T, int H,int d, int pow, int Rld ,int attacktime, REGION R, color c,int sp);
	virtual void Move(const int Ts,  Tower& t) ;
	virtual void Attack( const int Ts,  Tower& t);
	Enemy* getCopy();

};