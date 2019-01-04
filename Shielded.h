# pragma once
#include "Enemies\Enemy.h"
class Shielded : public Enemy
{
	double C1,C2,C3;
public:
	
	Shielded(int id , int T, int H,int d, int pow, int Rld , int attackTime , REGION R, color c,double c1,double c2, double c3,int sp);
	virtual void Move(const int Ts,  Tower& t) ;
	virtual void Attack( const int Ts,  Tower& t);
	virtual void update_priority();
	Enemy* getCopy();
	};

