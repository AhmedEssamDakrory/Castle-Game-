#include "Castle.h"
#include "../Battle.h"
#include "../Enemies/Paver.h"
#include "..\GUI\GUI.h"

Castle::Castle()
{
	Towers[0].setRegion(A_REG);
	Towers[1].setRegion(B_REG);
	Towers[2].setRegion(C_REG);
	Towers[3].setRegion(D_REG);
}

void Castle::SetTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
		Towers[i].setOriginalHealth(h);
	}
}

void Castle::SetTowersTargetsPerShot(int n)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetTargetsPerShot(n);
	}
}

void Castle::SetTowersFirePower(int TP)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetFirePower(TP);
	}
}

void Castle :: distribute_ActiveEnemies_On_Towers(Enemy* e)
{
	int region;
	if(e->GetRegion()==A_REG)
		region = 0;
	else if(e->GetRegion()==B_REG)
		region = 1;
	else if(e->GetRegion()==C_REG)
		region = 2;
	else if(e->GetRegion()==D_REG)
		region = 3;


	while(Towers[region].damaged())
	{
		if(region == 3)
			region = 0;
		else
			region++;
	}

	e->updateRegion(Towers[region].getRegion());
	Towers[region].add_Active_enemies(e);
}


void Castle ::Exit()
{
	for(int i=0;i<4;i++)
		Towers[i].Exit();
}

void Castle::CreateTonewLoad()
{
	for(int i=0;i<4;i++)
		Towers[i].CreateTonewLoad();

	Towers[0].setRegion(A_REG);
	Towers[1].setRegion(B_REG);
	Towers[2].setRegion(C_REG);
	Towers[3].setRegion(D_REG);
}


bool Castle :: MoveEnemiesToNextRegion(int region)
{ 
	int last = region;
	if(damaged())
		return false;
 
	if(region == 3)
			region = 0;
	else
		region++;

	while(Towers[region].damaged())
	{
		if(region == 3)
			region = 0;
		else
			region++;
	}


	LinkedList<Enemy*>* l1;
	priorityList<Enemy*>* l2;
	LinkedList<Enemy*>* l3;
	l1 = Towers[last].getlist1();
	l2 = Towers[last].getlist2();
	l3 = Towers[last].getlist3();
	Towers[region].MoveEnemies(l1,l2,l3);
	return true;

}


bool Castle :: damaged()
{
	if(Towers[0].damaged() && Towers[1].damaged() && Towers[2].damaged() && Towers[3].damaged() )
		return true;
	return false;
}


void Castle ::getAttacked(Battle* b,const int Ts)
{

	for(int i = 0 ;i<NoOfRegions ;i++)
	{
		if(!Towers[i].damaged())
		{
			Towers[i].getAttacked(Ts);

			if(Towers[i].damaged())
			{
				bool f = MoveEnemiesToNextRegion(i);

				//killed enemies in the list who were have hope to be revived ...will die so the should be moved to the battle...

				priorityList<Enemy*>* l = Towers[i].getKilled();

				int size = l->size();
				for(int i=0;i<size;i++)
				{
					Enemy* e = l->getEntry(0)->getCopy();
					l->remove(l->getEntry(0));
					b->AddtoKilled(e);
				}
			}
		}
	}

}

void Castle :: Attack(Battle* B,int Ts)
{
	for(int i=0 ; i< NoOfRegions ; i++)
	{
		if(!Towers[i].damaged())
			Towers[i].Attack(B,Ts);
	}
}

Tower Castle :: getTower(int ind)
{
	return Towers[ind];
}

Tower* Castle :: get_towers()
{
	return Towers;
}

void Castle::printTotalTowersDamage(ofstream & out)const {
	out << "T1_Total_Damage    T2_Total_Damage    T3_Total_Damage    T4_Total_Damage " << endl;
	for (int i = 0; i < 4; i++)
		Towers[i].PrintTotalDamage(out);
	out << endl;
}

void Castle::printTotalTowersUnpavedDist(ofstream & out)const {
	out << "R1_Unpaved_Dist     R2_Unpaved_Dist    R3_Unpaved_Dist     R4_Unpaved_Dist " << endl;
	for (int i = 0; i < 4; i++)
		Towers[i].printUnpavedDis(out);
	out << endl;
}