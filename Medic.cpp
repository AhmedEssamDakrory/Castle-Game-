#include "Medic.h"
#include "Castle\Tower.h"

Medic::Medic(int id , int T, int H,int D, int pow, int Rld ,int attacktime, REGION R, color c,int sp):Enemy(c,R,D,sp)
{
	ID = id;
	arrival_time = T;
	Health = H;
	power = pow;
	Reload_time = Rld;
	attack_time = attacktime;
}


void Medic :: Move(const int Ts,Tower& t)
{
	Enemy* toHeal=t.GetNearestEnemy(Distance,speed);
	if(!toHeal)
	{
		if((Distance)==t.getUnpavedArea()||Distance==MinDistance)
			return;
		if((Distance-speed)<=t.getUnpavedArea())
		{
			Distance=t.getUnpavedArea();
			return;
		}
		Distance = Distance-speed;

		return;
	}
	this->SetDistance(toHeal->GetDistance());
}

void Medic :: Attack(const int Ts , Tower& t)
{ // To Do: Get The Nearest Enemy and Heal him with the attack power of the medic.
	Enemy* toHeal=t.GetNearestEnemy(Distance,speed);
	if(toHeal)
		Distance = toHeal->GetDistance();

	if(Ts==attack_time || attack_time == -1)
	{
		if (toHeal  && toHeal->GetDistance()==this->GetDistance() )
		{
			double healage=power;

			if(toHeal->get_health()==0) {

				toHeal->set_health(toHeal->get_health()+healage);
				t.revive(toHeal);
			}
			else
				toHeal->set_health(toHeal->get_health()+healage);

			if(attack_time == -1)
				attack_time = Ts+Reload_time+1;
			else
				attack_time=attack_time+Reload_time+1; //set the new attack_time
		}
		else
		{
			if(attack_time != -1)
				attack_time++ ;
		}

	}

	Move(Ts,t); 
}

Enemy*  Medic :: getCopy()
{
	Enemy* e = new Medic(ID,arrival_time,Health,Distance,power,Reload_time,attack_time,Region,Clr,speed);
	e->setKTS(getKTS());
	e->setFD(getFD());
	e->setKD(getKD());
	return e;
}

