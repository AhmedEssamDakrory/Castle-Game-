#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <fstream>
class GUI;
class Tower;

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{

protected:
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health
	double power;   //Enemy power!!!!!!!!
	int speed;      // steps it moves every step **
	int attack_time; //attcking 
	int Reload_time;  //Reloading
	int arrival_time; // arriving to the region 
	double priority;  // Enemy Priority
	int FD; // First-shot Delay (first shot - arrival time)
	int KTS; // the time step the enemy was killed at
	int KD;//
	// TODO: Add More Data Members As Needed
	//

public:
	Enemy(color r_c, REGION r_region, int d ,int sp);
	virtual ~Enemy();
	void PrintInfoToOutputFile(ofstream &)const; //print INFO in an output file
	color GetColor() const;
	REGION GetRegion() const;
	void updateRegion(REGION r) ; 
	void DecrementDist(const int un_paved=1);    
	bool Reload_period(const int Ts);        
	void SetDistance(int d);
	int GetDistance() const;
	int getArrivalTime();
	double get_health();
	void set_health(double h);
	//void update_state(const int & Ts);  //should be called in every time step AE
	void setFD (int F);
	int getFD() const;
	void setKTS (int T);
	int getKTS() const ;
	void setKD(int);
	int getKD()const;
	double getPriority();
	 void PrintInfo(GUI* p,int x,int y) const;  //print IOFo in the statBar
	
	// Virtual Functions: ----------------

	virtual void Move(const int Ts,  Tower& t) = 0;	    //All enemies can move
	virtual void Attack( const int Ts,  Tower& t) = 0;	//All enemies can attack (attacking is paving or shooting or healing)
	virtual void update_priority(); 
	virtual Enemy* getCopy()=0; // get a new object of the same data members
	bool operator >(Enemy& e);
	bool operator <=(Enemy& e);
	//
	// TODO: Add More Member Functions As Needed
	//

};

