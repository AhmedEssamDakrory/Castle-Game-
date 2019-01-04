#pragma once
#include "Enemies\Enemy.h"
class Wizard :
	public Enemy
{
public:
	Wizard(int id, int T, int H, int d, int pow, int Rld,int attcktime, REGION R, color c, int sp);
	virtual void Move(const int Ts, Tower& t);
	virtual void Attack(const int Ts, Tower& t);
	Enemy* getCopy();
	~Wizard();
};

