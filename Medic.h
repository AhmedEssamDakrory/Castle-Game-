#pragma once
#include "Enemies\Enemy.h"
class Medic :
	public Enemy
{
public:
	Medic(int id , int T, int H,int D, int pow, int Rld,int attacktime, REGION R, color c,int sp=4);
	void Move (const int Ts,Tower& t);
	void Attack (const int Ts,Tower& t);
	Enemy*  getCopy();

};

