#include "Tower.h"
#include "../Battle.h"


Tower :: Tower()
{
	Unpaved_area = 30;
	Ckilled = 0;
	silenced = false;
}

void Tower ::setUnpavedArea(int unpaved)
{
	Unpaved_area = unpaved;
}

int Tower ::getUnpavedArea()
{
	return Unpaved_area;
}

priorityList<Enemy*>* Tower :: getKilled()
{
	return &killed;
}

void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Tower::GetHealth() const
{
	return Health;
}

void Tower::SetTargetsPerShot(int n)
{
	TargetsPerShot = n > 0 ? n : 1;
}

int Tower::getTargetsPerShot()
{
	return TargetsPerShot;
}

void Tower::SetFirePower(int TP)
{
	FirePower = TP >= 0 ? TP : 0;
}

int Tower::getFirePower()
{
	return FirePower;
}

LinkedList<Enemy*>* Tower ::getlist3()
{
	return list3;
}

void Tower ::add_Active_enemies(Enemy* e)
{

	if(dynamic_cast<Shielded*>(e))
		list2->add(e);
	else if(dynamic_cast<Medic*>(e))
		list3->append(e);
	else if(dynamic_cast<Wizard*>(e))
	    list3->append(e);
	else
		list1->append(e);

}

void Tower :: Exit()
{
	list1->clear();
	list2->clear();
	list3->clear();
	delete list1;
	delete list2;
	delete list3;
}

void Tower ::CreateTonewLoad()
{
	list1 = new LinkedList<Enemy*>;
	list2 = new priorityList<Enemy*>;
	list3 = new LinkedList<Enemy*>;
	Unpaved_area = 30;
	Ckilled = 0;
}


bool Tower :: damaged()
{
	return (Health <= 0);
}


void Tower ::getAttacked(const int Ts)
{
	Enemy** arr1 = list1->ToArr(list1->size());
	Enemy** arr2 = list2->ToArr(list2->size());
	Enemy** arr3 = list3->ToArr(list3->size());
	for(int i = 0;i<list1->size();i++)
		arr1[i]->Attack(Ts , *this);
	for(int i = 0;i<list2->size();i++)
		arr2[i]->Attack(Ts , *this);
	for(int i = 0;i<list3->size();i++)
		arr3[i]->Attack(Ts , *this);

}

void Tower::revive(Enemy*& toRevive)
{
	Enemy* temp=toRevive->getCopy();
	killed.remove(toRevive);
	Ckilled--;
	toRevive=temp;
	if (dynamic_cast<Shielded*> (toRevive))
	{
		list2->add(toRevive);
	}
	if (dynamic_cast<Fighter*> (toRevive) || dynamic_cast<Paver*> (toRevive))
	{
		list1->append(toRevive);
	}
}

void Tower :: Attack(Battle* B,int Ts)
{
	//handle the 3rd list .... kloko 3lya - _ -  ....
	

	int m = TargetsPerShot - list3->size();
	int size = 0;

	Enemy** arr3 = list3->ToArr(TargetsPerShot);
	if (!silenced) {
		if (m <= 0)
		{

			for (int i = 0; i < TargetsPerShot; i++)
			{
				double h = arr3[i]->get_health() - (1.0 / (arr3[i]->GetDistance()))*FirePower*0.8; //l % 3l4an lw y2der ydrab akter mn l size 
				arr3[i]->set_health(h);

				if (arr3[i]->getFD() == -1)
					arr3[i]->setFD(Ts - arr3[i]->getArrivalTime()); //set the FD

				if (arr3[i]->get_health() == 0)
				{
					arr3[i]->setKTS(Ts);    //set the KTS
					arr3[i]->setKD(arr3[i]->getKTS() - arr3[i]->getArrivalTime() - arr3[i]->getFD()); //set the KD
					Enemy* temp = arr3[i]->getCopy();           //get a copy cuz list.remove deletes the object
					bool f = list3->remove(arr3[i]);
					killed.add(temp);                                      //add the copy to killed list
					Ckilled++;
				}
			}


		}
		else
		{
			size = list3->size();

			for (int i = 0; i < size; i++)
			{
				double h = arr3[i]->get_health() - (1.0 / (arr3[i]->GetDistance()))*FirePower*0.8; //l % 3l4an lw y2der ydrab akter mn l size 
				arr3[i]->set_health(h);

				if (arr3[i]->getFD() == -1)
					arr3[i]->setFD(Ts - arr3[i]->getArrivalTime()); //set the FD

				if (arr3[i]->get_health() == 0)
				{
					arr3[i]->setKTS(Ts);    //set the KTS
					arr3[i]->setKD(arr3[i]->getKTS() - arr3[i]->getArrivalTime() - arr3[i]->getFD()); //set the KD
					Enemy* temp = arr3[i]->getCopy();           //get a copy cuz list.remove deletes the object
					bool f = list3->remove(arr3[i]);
					killed.add(temp);                                      //add the copy to killed list
					Ckilled++;
				}
			}


			int n = m - list2->size();
			n = (n > 0 ? n : 0); //is that right ya 3saam XD .. yes m3l4.....
			Enemy** arr2 = list2->ToArr(m);
			Enemy** arr1 = list1->ToArr(n);

			if (n <= 0)  //all enemies to be attacked are depend on priority like shielded
			{
				for (int i = 0; i < m; i++)
				{
					double h = arr2[i]->get_health() - (1.0 / (arr2[i]->GetDistance()))*FirePower*0.5; //l % 3l4an lw y2der ydrab akter mn l size 
					arr2[i]->set_health(h);

					if (arr2[i]->getFD() == -1)
						arr2[i]->setFD(Ts - arr2[i]->getArrivalTime()); //set the FD

					//arr2[i%list2.size()]->update_state(-1);// if enemy's health =0 then the state will be Killed
					if (arr2[i]->get_health() == 0)
					{
						arr2[i]->setKTS(Ts);    //set the KTS
						arr2[i]->setKD(arr2[i]->getKTS() - arr2[i]->getArrivalTime() - arr2[i]->getFD()); //set the KD
						Enemy* temp = arr2[i]->getCopy();           //get a copy cuz list.remove deletes the object
						bool f = list2->remove(arr2[i]);
						killed.add(temp);                                      //add the copy to killed list
						Ckilled++;
					}
				}
			}

			// all kinds 
			else
			{

				size = list2->size();
				for (int i = 0; i < size; i++)
				{
					double h = arr2[i]->get_health() - (1.0 / (arr2[i]->GetDistance()))*FirePower*0.5;
					arr2[i]->set_health(h);


					//priority updated inside the operator .........

					if (arr2[i]->getFD() == -1)
						arr2[i]->setFD(Ts - arr2[i]->getArrivalTime()); //set the FD


					//arr2[i%list2.size()]->update_state(-1); // if enemy's health =0 then the state will be Killed
					if (arr2[i]->get_health() == 0)
					{
						arr2[i]->setKTS(Ts);                      //set the KTS
						arr2[i]->setKD(arr2[i]->getKTS() - arr2[i]->getArrivalTime() - arr2[i]->getFD()); //set the KD
						Enemy* temp = arr2[i]->getCopy();           //get a copy cuz list.remove deletes the object
						bool f = list2->remove(arr2[i]);
						killed.add(temp);                                      //add the copy to killed list
						Ckilled++;
					}

					//the priority may change after every shielded is killed so we will remove it and add it in its proportional position..... 

					else
					{
						Enemy* temp = arr2[i]->getCopy();
						bool f = list2->remove(arr2[i]);
						list2->add(temp);
					}
				}

				if (n > list1->size())
					n = list1->size();

				for (int i = 0; i < n; i++)
				{
					double h = arr1[i]->get_health() - (1.0 / (arr1[i]->GetDistance()))*FirePower;
					arr1[i]->set_health(h);

					if (arr1[i]->getFD() == -1)
						arr1[i]->setFD(Ts - arr1[i]->getArrivalTime()); //set the FD

					//arr1[i]->update_state(-1);// if enemy's health =0 then the state will be Killed
					if (arr1[i]->get_health() == 0)
					{
						arr1[i]->setKTS(Ts);                      //set the KTS
						arr1[i]->setKD(arr1[i]->getKTS() - arr1[i]->getArrivalTime() - arr1[i]->getFD());
						Enemy* temp = arr1[i]->getCopy();           //get a copy cuz list.remove deletes the object
						bool f = list1->remove(arr1[i]);
						killed.add(temp);                                      //add the copy to killed list
						Ckilled++;
					}
				}

			}




		}
	}
	else {
		silence_duration--;
		if (silence_duration == 0)
			silenced = false;
	}

	

	//concerning to the revived and killed enemies

	sureKilled(B,Ts);

	
}

int Tower :: getCkilled()
{
	return Ckilled;
}


void Tower :: sureKilled(Battle* b , int Ts)
{
	int m=killed.size();
	Enemy** karr=killed.ToArr(m);
	for (int i=0;i<m;i++)
	{

		if( ( Ts-karr[i]->getKTS()) >= 5 )
		{
			//add to killed of the battle and remove it from the killed list
			Enemy* temp=karr[i]->getCopy();
			killed.remove(karr[i]);
			b->AddtoKilled(temp);
		}
	}
}

void Tower :: MoveEnemies(LinkedList<Enemy*>* l1,priorityList<Enemy*>* l2,LinkedList<Enemy*>* l3)
{
	int size1 = l1->size();
	int size2 = l2->size();
	int size3 = l3->size();

	for(int i=0;i<size1;i++)
	{
		Enemy* e = l1->getEntry(0)->getCopy();
		if (e->GetDistance() <= Unpaved_area)
			e->SetDistance(Unpaved_area);
		e->updateRegion(Region);
		list1->append(e);
		bool f = l1->remove(l1->getEntry(0));

	}

	for(int i=0;i<size2;i++)
	{
		Enemy* e = l2->getEntry(0)->getCopy();
		if (e->GetDistance() <= Unpaved_area)
			e->SetDistance(Unpaved_area);
		e->updateRegion(Region);
		list2->add(e);
		bool f = l2->remove(l2->getEntry(0));

	}

	for(int i=0;i<size3;i++)
	{
		Enemy* e = l3->getEntry(0)->getCopy();
		if (e->GetDistance() <= Unpaved_area)
			e->SetDistance(Unpaved_area);
		e->updateRegion(Region);
		list3->append(e);
		bool f = l3->remove(l3->getEntry(0));

	}




}

bool Tower::isSilenced()
{
	return silenced;
}

void Tower::silence(int duration)
{
	if (duration > 0) {
		silenced = true;
		silence_duration = duration;
	}
}

REGION Tower::getRegion()
{
	return Region;
}

void Tower::setRegion(REGION R)
{
	Region=R;
}



LinkedList<Enemy*>* Tower:: getlist1()
{
	return list1;
}


priorityList<Enemy*>* Tower :: getlist2()
{
	return list2;
}

Enemy* Tower::GetNearestEnemy (int D,int max) //find the Nearest Enemy In the Range [D-max,D+max]
{
	int n=killed.size();
	Enemy** arr=killed.ToArr(n);
	int min = max ;
	Enemy* toheal = NULL;

		for (int j=0;j<n;j++)
		{
			if (arr[j]->GetDistance() <= D+max &&  arr[j]->GetDistance() >= D-max )
			{
				if(abs(arr[j]->GetDistance()-D) <= min)
				{
					min =abs(arr[j]->GetDistance()-D);
					toheal = arr[j];
				}
			}
		}

		if(toheal)
			return toheal;


	n=list2->size();
	arr=list2->ToArr(n);

	for (int j=0;j<n;j++)
	{
		if (arr[j]->GetDistance() <= D+max &&  arr[j]->GetDistance() >= D-max )
		{
			if(abs(arr[j]->GetDistance()-D) < min)
			{
				min =abs(arr[j]->GetDistance()-D);
				toheal = arr[j];
			}
		}
	}

	if(toheal)
		return toheal;

	
	n=list1->size();
	arr=list1->ToArr(n);

	for (int j=0;j<n;j++)
	{
		if (arr[j]->GetDistance() <= D+max &&  arr[j]->GetDistance() >= D-max )
		{
			if(abs(arr[j]->GetDistance()-D) < min)
			{
				min =abs(arr[j]->GetDistance()-D);
				toheal = arr[j];
			}
		}
	}

	return toheal;
	
}
void Tower::PrintTotalDamage(ofstream& out)const {
	out << "   " << originalHealth - Health << "       ";
}
void Tower::setOriginalHealth(int H) {
	originalHealth = H;
}
void Tower::printUnpavedDis(ofstream& out)const {
	out << "   " << Unpaved_area << "       ";
}