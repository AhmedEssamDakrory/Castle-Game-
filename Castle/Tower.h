#pragma once
#include "../LinkedList.h"
#include "../priorityList.h"
#include "../Shielded.h"
#include "../Medic.h"
#include "../fighter.h"
#include "../Enemies/Paver.h"
#include "../Wizard.h"
class Battle;

class Tower
{
	double originalHealth;
    double Health;
	int Unpaved_area; //unpaved area from the tower !!!!!!!!!!!!!!!!!!!!
    int TargetsPerShot;
	int FirePower;
	int Ckilled; //number of killed enemies 
	int silence_duration;
	bool silenced;
	//
	// TODO: Add More Data Members As Needed
	//

	LinkedList<Enemy*>* list1; //list for fighters and pavers
	priorityList<Enemy*>* list2; // list for shielded
	LinkedList<Enemy*>* list3; // list for sanad and medic
	priorityList<Enemy*> killed; // killed enemies

	REGION Region;  //Region of this Tower AE



public:
	Tower ();                       //initializing the unpaved area to 30!!!!!!!!!!!
	void SetHealth(double h);
	double GetHealth() const;
	void SetTargetsPerShot(int n);
	int getTargetsPerShot();
	void SetFirePower(int TP);
	void setOriginalHealth(int H);
	int getFirePower();
	void Attack(Battle*,int);                  // logic of towers when attack !!!!!!!!!!!!!!!!!
	void getAttacked(const int Ts);            //  logic of enemies when attack ...here so that i will need to access unpavedarea when enemies move 
	void revive (Enemy*& toRevive);    //a fn moves the revived enemy from killed list to their original list
	//
	// TODO: Add More Member Functions As Needed
	//
	void setRegion(REGION R);
	REGION getRegion();
	void add_Active_enemies(Enemy* e);
	bool damaged();
	int getUnpavedArea();
	void setUnpavedArea(int unpaved);
	LinkedList<Enemy*>*  getlist1();
	priorityList<Enemy*>*  getlist2();
	LinkedList<Enemy*>* getlist3();
	priorityList<Enemy*>* getKilled();
	int getCkilled();
	Enemy* GetNearestEnemy (int D,int max);
	void MoveEnemies(LinkedList<Enemy*>* l1 , priorityList<Enemy*>* l2,LinkedList<Enemy*>* l3);
	void PrintTotalDamage(ofstream &)const; //print INFO in an output file
	void printUnpavedDis(ofstream &)const;//print INFO in output file
	void sureKilled(Battle* b ,int Ts ) ;
	void Exit();
	void CreateTonewLoad();
	bool isSilenced();
	void silence(int duration);
};

