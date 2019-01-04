#include "Paver.h"
#include "../Castle/Tower.h"

Paver :: Paver (int id , int T, int H,int d, int pow, int Rld , int attackTime,REGION R, color c,int sp):Enemy(c,R,d,sp)
{
	ID = id;
	arrival_time = T;
	Health = H;
	power = pow;
	Reload_time = Rld;
	attack_time = attackTime;
}



void Paver :: Move(const int Ts,Tower& t)
{

	if(!Reload_period(Ts))
	{
		if(Distance - MinDistance <= power)
		{
			Distance = MinDistance;
		}

		else
		{
			Distance = Distance - power;
			attack_time = attack_time + Reload_time + 1;
		}


	}

	else
		DecrementDist(t.getUnpavedArea());

}

void Paver :: Attack(const int Ts , Tower& t)
{
	int ability = Distance - t.getUnpavedArea();
	if(!Reload_period(Ts))
	{
		if(power > ability && t.getUnpavedArea() != MinDistance)
			t.setUnpavedArea( (t.getUnpavedArea() - (power - ability) >= MinDistance ? (t.getUnpavedArea() - (power - ability)) : MinDistance ) );
	}

	Move(Ts,t);

}

Enemy* Paver :: getCopy()
{

	Enemy* e = new Paver(ID,arrival_time,Health,Distance,power,Reload_time,attack_time,Region,Clr,speed);
	e->setKTS(getKTS());
	e->setFD(getFD());
	e->setKD(getKD());
	return e;
}




