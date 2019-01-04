#include "Shielded.h"
#include "Castle\Tower.h"


Shielded::Shielded(int id , int T, int H,int d, int pow, int Rld ,int attackTime, REGION R, color c,double c1,double c2, double c3,int sp):Enemy(c,R,d,sp)
	{
		ID = id;
		arrival_time = T;
		Health = H;
		power = pow;
		Reload_time = Rld;
		attack_time = attackTime;
		C1=c1;
		C2=c2;
		C3=c3;
		update_priority();
	}


void Shielded :: Move(const int Ts,Tower& t)
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

void Shielded :: Attack(const int Ts , Tower& t)
{
	if (Ts==attack_time)
	{
		double damage = (2*1.0/Distance)*power;
		t.SetHealth(t.GetHealth()-damage);
		attack_time=attack_time+Reload_time+1; //set the new attack_time
	}

	Move(Ts,t);
	update_priority();
}

void Shielded::update_priority()
{
	priority=(power*C1)/Distance+C2/Reload_time+Health*C3;
}

Enemy* Shielded :: getCopy()
{
	Enemy* e = new Shielded(ID,arrival_time,Health,Distance,power,Reload_time,attack_time,Region,Clr,C1,C2,C3,speed);
	e->setKTS(getKTS());
	e->setKD(getKD());
	e->setFD(getFD());
	return e;
}
