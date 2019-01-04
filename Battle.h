#pragma once

#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include "queue.h"
#include <string>
// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int TotalNumberOfEnemys; //the total number of enemy in the game
	double totalFD;
	double totalKD;
	int warNumber;
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	int time_step;                          // time
	//
	// TODO: Add More Data Members As Needed
	//
	queue<Enemy*>* inactive;
	priorityList<Enemy*> killed;
	// TO DO: add a List for the killed enemies who reached the limit of being revived
	ofstream out;
	int inactiveCount;
	int KilledEnemy;
	int total; //total number of enemies.....
	int drawCount;  //number of enemies to be drawn.... 
public:
	
	Battle();
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	void AddtoKilled(Enemy*);
	Castle * GetCastle();
	int get_time_step();                    //return time step !!!!!!!!!!!!! 
	//
	// TODO: Add More Member Functions As Needed
	//
	void set_killed(Enemy*);//filling up Killed queue
	bool load(GUI* pGUI);
	void start();
	void mode(GUI* pGUI ,MenuItem& actiontype) ;
	void createFileOutput();
	void printWarResult();
	void Drawing(GUI* pGUI);
	void FromInactiveTothegame();
	void Printing_sorted_KilledEnemies();
	void fillling_enemiesforDraw(GUI* pGUI);
	void Exit();
	void CreateToNewLoad();
private:
	string GetFileName(const string & prompt);
};

