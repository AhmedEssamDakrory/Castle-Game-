#include "Wizard.h"
#include "Castle\Tower.h"


Wizard::Wizard(int id, int T, int H, int d, int pow, int Rld,int attcktime, REGION R, color c, int sp) :Enemy(c, R, d, sp)
{
	ID = id;
	arrival_time = T;
	Health = H;
	power = pow;
	Reload_time = Rld;
	attack_time = attcktime;
}

void Wizard::Move(const int Ts, Tower& t)
{

	if ((Distance) == t.getUnpavedArea() || Distance == MinDistance)
		return;
	if ((Distance - speed) <= t.getUnpavedArea())
	{
		Distance = t.getUnpavedArea();
		return;
	}

	Distance = Distance - speed;
}

void Wizard::Attack(const int Ts, Tower & t)
{
	if (Ts == attack_time)
	{
		int ability = power + ((60 - Distance) / 60)*power;
		t.silence(ability);
		attack_time = attack_time + Reload_time + 1; //set the new attack_time
	}

	Move(Ts, t);
}


Enemy* Wizard::getCopy()
{
	Enemy* e = new Wizard(ID, arrival_time, Health, Distance, power, Reload_time,attack_time, Region, Clr, speed);
	e->setKTS(getKTS());
	e->setFD(getFD());
	e->setKD(getKD());
	return e;
}

Wizard::~Wizard()
{
}
