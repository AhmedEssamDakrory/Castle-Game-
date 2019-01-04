#include "Enemy.h"
#include "../GUI/GUI.h"


Enemy::Enemy(color r_c, REGION r_region, int d,int sp)
{
	Clr = r_c;
	Region = r_region;
	SetDistance(d);
	speed =sp;
	priority=1;
	FD=-1;
	KTS=-1;
}

double Enemy :: get_health()
{
	return Health;
}

void Enemy :: updateRegion(REGION r)
{
	Region = r;
}

void Enemy ::set_health(double h)
{
	Health = (h > 0 ? h : 0);
}

Enemy::~Enemy()
{
}

void Enemy:: setFD(int F)
	{
	FD=F;
	}

int Enemy::getFD () const
	{
	return FD;
	}


void Enemy::setKTS (int T)
	{
	if (T>=0)
		KTS=T;
	}

int Enemy::getKTS() const 
	{
	return KTS;
	}

color Enemy::GetColor() const
{
	return Clr;
}

void Enemy :: PrintInfo(GUI* p,int x,int y) const
{

	p->Printinteger(ID , x , y);
	x = x+30;
	p->Printinteger(Distance,x,y);
	x=x+30;
	p->Printinteger(ceil(Health) , x , y);
	x=x+30;
	p->Printinteger(power , x , y);
	x=x+30;
	p->Printinteger(speed , x , y);
	x=x+30;
	p->Printinteger(attack_time,x,y);
	x=x+30;
	p->Printinteger(Reload_time , x,y);
	x=x+30;
	p->Printinteger(arrival_time , x , y);
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::DecrementDist(const int un_paved)
{

    if(Distance - un_paved <= speed)
	{
			Distance = un_paved;
	}
	else
		Distance -= speed;

}

int Enemy :: getArrivalTime()
{
	return arrival_time;
}


bool Enemy :: Reload_period(const int Ts)
{
	return(Ts != attack_time);
}

void Enemy::setKD(int kd)
{
	KD = kd;
}

int Enemy::getKD()const
{
	return KD; 
}

void Enemy::SetDistance(int d)
{
	
	Distance = d;
}

int Enemy::GetDistance() const
{
	return Distance;
}

void update_priority()
	{	}

double Enemy::getPriority()
	{
	if (Health==0)
		return KTS;
	else
		{
		update_priority();
		return priority;
		}
	}

void Enemy::update_priority()
	{}

bool Enemy::operator <=(Enemy& s)
	{
		return (getPriority()<=s.getPriority());
	}

bool Enemy::operator >(Enemy& s)
	{
	return (getPriority()>s.getPriority());
	}

void Enemy::PrintInfoToOutputFile(ofstream & out)const {
	out<<' '<< KTS <<"   "<<ID<<"  "<<FD<<"   "<<KD<<"   "<< KTS - arrival_time <<endl;
}