#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "Tower.h"

class Castle
{
	Tower Towers[NoOfRegions];

	//
	// TODO: Add More Data Members As Needed
	//
	
public:

	Castle();
	void SetTowersHealth(double h);
	void SetTowersTargetsPerShot(int n);
	void SetTowersFirePower(int TP);
	void distribute_ActiveEnemies_On_Towers(Enemy* e);
	bool damaged();
	void Attack(Battle* B,int Ts);
	void getAttacked(Battle* b,const int Ts);
	Tower getTower(int ind);
	Tower* get_towers();
	bool MoveEnemiesToNextRegion(int region);
	void printTotalTowersDamage(ofstream &)const;
	void printTotalTowersUnpavedDist(ofstream &)const;
	void Exit();
	void CreateTonewLoad();

	//
	// TODO: Add More Member Functions As Needed
	//
};
