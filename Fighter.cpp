#include "Fighter.h"
#include "Castle\Tower.h"

Fighter::Fighter(int id , int T, int H,int d, int pow, int Rld ,int attacktime, REGION R, color c,int sp):Enemy(c,R,d,sp)
{
	ID = id;
	arrival_time = T;
	Health = H;
	power = pow;
	Reload_time = Rld;
	attack_time = attacktime;
}

Enemy* Fighter :: getCopy()
{
	Enemy* e = new Fighter(ID,arrival_time,Health,Distance,power,Reload_time,attack_time,Region,Clr,speed);
	e->setKTS(getKTS());
	e->setFD(getFD());
	e->setKD(getKD());
	return e;
}


void Fighter :: Move(const int Ts,Tower& t)
{

	if((Distance)==t.getUnpavedArea()||Distance==MinDistance)
		return;
	if((Distance-speed)<=t.getUnpavedArea())
	{
		Distance=t.getUnpavedArea();
		return;
	}
	Distance = Distance-speed;
}

void Fighter :: Attack(const int Ts , Tower& t)
{
	if (Ts==attack_time)
	{
		double damage = (1.0/Distance)*power;
		t.SetHealth(t.GetHealth()-damage);
		attack_time=attack_time+Reload_time+1; //set the new attack_time
	}

	Move(Ts,t);

}
