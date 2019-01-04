#include "Battle.h"
#include <Windows.h>
#include "Shielded.h"
#include"Fighter.h"
#include <fstream>
#include "Enemies\Paver.h"
#include "Wizard.h"
#include <cmath>
Battle::Battle()
{
	EnemyCount = 0;
	inactiveCount = 0;
	warNumber = 1;
	KilledEnemy = 0;
	TotalNumberOfEnemys = 0;
	time_step= 1 ;
	totalFD = 0;
	totalKD = 0;
}

int Battle :: get_time_step()
{
	return time_step;
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount) 
		BEnemiesForDraw[EnemyCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle ::CreateToNewLoad()
{
	inactive = new queue<Enemy*>;

	EnemyCount = 0;
	inactiveCount = 0;
	warNumber = 1;
	KilledEnemy = 0;
	TotalNumberOfEnemys = 0;
	time_step= 1 ;
	totalFD = 0;
	totalKD = 0;
	BCastle.CreateTonewLoad();
}


bool Battle::load(GUI* pGUI) {


	
	CreateToNewLoad();
	string filename;
	ifstream input;
	while (1) {
		filename = GetFileName("Choose the input text file");
		if (filename.size() == 0)
			return false;
		else {
			if ((filename.substr(filename.size() - 4, 4) == ".txt"))
				break;
		}
	}
	input.open(filename);
	double x;
	double C1,C2,C3;
	input >> x;
	BCastle.SetTowersHealth(x);
	input >> x;
	BCastle.SetTowersTargetsPerShot(x);
	input >> x;
	BCastle.SetTowersFirePower(x);
	input >> C1 >> C2 >> C3;
	int S,T,H,POW,RLD,sp;
	char R;
	input >> x;
	while (x != -1) {
		S = (int)x;
		input >> x >> T >> H >> POW >> RLD >> R>>sp;
		switch ((int)x)
		{
		case 0: {
			Enemy* newEnemy = new Paver(S, T, H,60+sp, POW, RLD,T,(REGION)(R-65),DARKBLUE,sp);
			inactive->enqueue(newEnemy);
			break;
				}
		case 1: {
			Enemy* newEnemy = new Fighter(S, T, H,60+sp, POW, RLD,T,(REGION)(R-65),DARKOLIVEGREEN,sp);
			inactive->enqueue(newEnemy);
			break;
				}
		case 2: {
			Enemy* newEnemy = new Shielded(S, T, H,60+sp, POW, RLD,T,(REGION)(R-65),ORANGERED,C1,C2,C3,sp);
			inactive->enqueue(newEnemy);
			break;
				}
		case 3: {
			Enemy* newEnemy = new Wizard(S, T, H, 60+sp, POW, RLD,T, (REGION)(R - 65), VIOLETRED, sp);
			inactive->enqueue(newEnemy);
			break;
				}
		case 4: {

			Enemy* newEnemy = new Medic(S, T, H, 60+sp, POW, RLD,-1, (REGION)(R - 65), WHITE, sp);
			inactive->enqueue(newEnemy);
			break;

			break;
				}
		default:
			break;
		}
		TotalNumberOfEnemys++;
		inactiveCount++;
		input >> x;
	}

	pGUI->ClearBattleArea(BCastle.get_towers());
	pGUI->DrawCastle(false,false,false,false);
	total = inactiveCount;
	return true;
}

string Battle::GetFileName(const string & prompt) {
	const int BUFSIZE = 512;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = prompt.c_str();
	GetOpenFileName(&ofns);
	return buffer;
}

void Battle :: Exit()
{
	BCastle.Exit();

	bool f = true;

	while(f)
	{

		f = inactive->dequeue();  

	}

	delete inactive;
	
	//initializing every thing to its default value......

	EnemyCount = 0;
	inactiveCount = 0;
	warNumber = 1;
	KilledEnemy = 0;
	TotalNumberOfEnemys = 0;
	time_step=1;
	totalFD = 0;
	totalKD = 0;


}


void Battle :: mode(GUI* pGUI, MenuItem& actiontype)
{


	if(actiontype == CLICK)
	{
		Point p;
		pGUI->GetPointClicked(p);
		actiontype = pGUI->getActionType(p);
	}

	else if(actiontype == TIME)
	{
		Sleep(1000);
	}

	else if(actiontype == MENU_EXIT)
	{
		Exit();
	}

	else if(actiontype == LOAD)
	{
		Exit();
		bool f = load(pGUI);
		actiontype = CLICK;
	}


	



}

void Battle ::Drawing(GUI* pGUI )
{
	pGUI->ClearBattleArea(BCastle.get_towers());
	pGUI->DrawEnemies(BEnemiesForDraw,drawCount);
	
	bool a = ((BCastle.get_towers())[0]).isSilenced();
	bool b = ((BCastle.get_towers())[1]).isSilenced();
	bool c = ((BCastle.get_towers())[2]).isSilenced();
	bool d = ((BCastle.get_towers())[3]).isSilenced();
	pGUI->DrawCastle(a,b,c,d);
	

}

void Battle :: FromInactiveTothegame()
{

	Enemy* e;

	if(inactiveCount != 0)
		e = inactive->queuefront()->getCopy();
	else
		return;

	while(e ->getArrivalTime() == time_step && inactiveCount != 0)
	{
			bool f = inactive->dequeue();
			inactiveCount--;
			BCastle.distribute_ActiveEnemies_On_Towers(e);
			EnemyCount++;
			//	e->update_state(time_step);  //updata the state form inactive to active 
			if(inactiveCount != 0)
				e = inactive->queuefront()->getCopy();
	}


}

void Battle :: Printing_sorted_KilledEnemies()
{
		int m=killed.size();
		Enemy** karr=killed.ToArr(m);
		for (int i=0;i<m;i++)
		{
			karr[i]->PrintInfoToOutputFile(out);
			totalFD=totalFD+karr[i]->getFD();
			totalKD = totalKD + karr[i]->getKD();
			killed.remove(karr[i]);
			KilledEnemy++;
		}
}

void Battle :: fillling_enemiesforDraw(GUI* pGUI )
{

 	    drawCount = 0;
	    LinkedList<Enemy*>* l1 ;
		LinkedList<Enemy*>* l3 ;
		priorityList<Enemy*>* l2 ;
		for(int i=0;i<NoOfRegions ;i++)
		{
			l1 = BCastle.getTower(i).getlist1();
			l2 = BCastle.getTower(i).getlist2();
			l3 = BCastle.getTower(i).getlist3();
			total += l1->size()+l2->size()+l3->size(); //number of enemies 
			Enemy** arr1 = l1->ToArr(l1->size());
			Enemy** arr2 = l2->ToArr(l2->size());
			Enemy** arr3 = l3->ToArr(l3->size());
			pGUI->Printinteger(l1->size()+l2->size(),150+i*400,1000-50);
			pGUI->Printinteger(BCastle.getTower(i).getCkilled(),150+i*400,1000-100);
			pGUI->PrintMessageString("# killed",50+i*400,1000-100);
			pGUI->PrintMessageString("# active",50+i*400,1000-50);
			if(i!=3)
				pGUI->DrawLine(60+(i+1)*380,550, 60+(i+1)*380,1000-50);

			int count=0;
			if(i==0)
			{
				pGUI->PrintMessageString("REGION A" ,50+i*400,520 );
				pGUI->PrintMessageString("H" , 100+i*400,550);
				pGUI->PrintMessageString("Pow" , 100+i*400+30,550);
				pGUI->PrintMessageString("n" , 100+i*400+60,550);
				pGUI->PrintMessageString("unpaved" , 100+i*400+90,550);
				pGUI->PrintMessageString("Tower A :",50+i*400,570 );
				pGUI->PrintMessageString("ID" , 100+i*400,600);
				pGUI->PrintMessageString("Di" , 100+i*400+30,600);
				pGUI->PrintMessageString("H" , 100+i*400+60,600);
				pGUI->PrintMessageString("pow" , 100+i*400+90,600);
				pGUI->PrintMessageString("sp" , 100+i*400+120,600);
				pGUI->PrintMessageString("A_t" , 100+i*400+150,600);
				pGUI->PrintMessageString("RL" , 100+i*400+180,600);
				pGUI->PrintMessageString("Arr_T" , 100+i*400+210,600);

			}
			else if(i==1)
			{
				pGUI->PrintMessageString("REGION B" ,100+i*400,520 );
				pGUI->PrintMessageString("H" , 100+i*400,550);
				pGUI->PrintMessageString("Pow" , 100+i*400+30,550);
				pGUI->PrintMessageString("n" , 100+i*400+60,550);
				pGUI->PrintMessageString("unpaved" , 100+i*400+90,550);
				pGUI->PrintMessageString("Tower B:",50+i*400,570 );
				pGUI->PrintMessageString("ID" , 100+i*400,600);
				pGUI->PrintMessageString("Di" , 100+i*400+30,600);
				pGUI->PrintMessageString("H" , 100+i*400+60,600);
				pGUI->PrintMessageString("pow" , 100+i*400+90,600);
				pGUI->PrintMessageString("sp" , 100+i*400+120,600);
				pGUI->PrintMessageString("A_t" , 100+i*400+150,600);
				pGUI->PrintMessageString("RL" , 100+i*400+180,600);
				pGUI->PrintMessageString("Arr_T" , 100+i*400+210,600);

			}
			else if(i==2)
			{
				pGUI->PrintMessageString("REGION C" ,100+i*400,520 );
				pGUI->PrintMessageString("H" , 100+i*400,550);
				pGUI->PrintMessageString("Pow" , 100+i*400+30,550);
				pGUI->PrintMessageString("n" , 100+i*400+60,550);
				pGUI->PrintMessageString("unpaved" , 100+i*400+90,550);
				pGUI->PrintMessageString("Tower C :",50+i*400,570 );
				pGUI->PrintMessageString("ID" , 100+i*400,600);
				pGUI->PrintMessageString("Di" , 100+i*400+30,600);
				pGUI->PrintMessageString("H" , 100+i*400+60,600);
				pGUI->PrintMessageString("pow" , 100+i*400+90,600);
				pGUI->PrintMessageString("sp" , 100+i*400+120,600);
				pGUI->PrintMessageString("A_t" , 100+i*400+150,600);
				pGUI->PrintMessageString("RL" , 100+i*400+180,600);
				pGUI->PrintMessageString("Arr_T" , 100+i*400+210,600);
			}

			else
			{
				pGUI->PrintMessageString("REGION D" ,80+i*400,520 );
				pGUI->PrintMessageString("H" , 100+i*400,550);
				pGUI->PrintMessageString("Pow" , 100+i*400+30,550);
				pGUI->PrintMessageString("n" , 100+i*400+60,550);
				pGUI->PrintMessageString("unpaved" , 100+i*400+90,550);
				pGUI->PrintMessageString("Tower D :",10+i*400,570 );
				pGUI->PrintMessageString("ID" , 50+i*400,600);
				pGUI->PrintMessageString("Di" , 50+i*400+30,600);
				pGUI->PrintMessageString("H" , 50+i*400+60,600);
				pGUI->PrintMessageString("pow" , 50+i*400+90,600);
				pGUI->PrintMessageString("sp" , 50+i*400+120,600);
				pGUI->PrintMessageString("A_t" , 50+i*400+150,600);
				pGUI->PrintMessageString("RL" , 50+i*400+180,600);
				pGUI->PrintMessageString("Arr_T" , 50+i*400+210,600);

			}

			
			
			pGUI->Printinteger(ceil(BCastle.getTower(i).GetHealth()),100+i*400,570);
			pGUI->Printinteger(BCastle.getTower(i).getFirePower(),130+i*400,570);
			pGUI->Printinteger(BCastle.getTower(i).getTargetsPerShot(),160+i*400,570);
			pGUI->Printinteger(BCastle.getTower(i).getUnpavedArea(),200+i*400,570);

			for(int j=0;j<l1->size();j++)
			{
				BEnemiesForDraw[drawCount++]=arr1[j];
				
				if(dynamic_cast<Paver*>(arr1[j]))
					pGUI->PrintMessageString("Paver :",50+i*400,600+(count+1)*25 );
				else if(dynamic_cast<Fighter*>(arr1[j]))
					pGUI->PrintMessageString("Fighter :",50+i*400,600 +(count+1)*25 );

				arr1[j]->PrintInfo(pGUI , 50+i*400,(600) +(count+1)*25);
				count++;//convert from j to count



			}

			for(int j=0;j<l2->size();j++)
			{
				BEnemiesForDraw[drawCount++]=arr2[j];

				pGUI->PrintMessageString("Shielded :",50+i*400,600 +(count+1)*25 );
				arr2[j]->PrintInfo(pGUI , 50+i*400,(600) +(count+1)*25);
				count++;
			}


			for(int j=0;j<l3->size();j++)
			{
				BEnemiesForDraw[drawCount++]=arr3[j];

				if(dynamic_cast<Medic*>(arr3[j]))
					pGUI->PrintMessageString("Medic :",50+i*400,600 +(count+1)*25 );
				else if(dynamic_cast<Wizard*>(arr3[j]))
					pGUI->PrintMessageString("Wizrad :",50+i*400,600 +(count+1)*25 );

				arr3[j]->PrintInfo(pGUI , 50+i*400,(600) +(count+1)*25);
				count++;
			}
		}

}

void Battle :: start()
{
	sndPlaySound("project sound.wav", SND_FILENAME | SND_ASYNC);//If you don't want to wait until the playback is over

	createFileOutput();

	GUI* pGUI = new GUI;
	bool f = load(pGUI);  //loading.......

	MenuItem actiontype = CLICK ;  // click mode by default..

	
	 
	while(!BCastle.damaged() && total != 0 ) // start........................
	{

		   
		

        mode(pGUI,actiontype); 		   // changing mode....&& drawing......

		if(actiontype == MENU_EXIT)
			break;

		FromInactiveTothegame();  //moving enemies from inactive to active....

		total = inactiveCount;

		BCastle.getAttacked(this,time_step);  //active enemies will attack......

		if(!BCastle.damaged())
			BCastle.Attack(this,time_step);  //castle will attack if itsn't damaged....

		//printing the killed enemies in this time step then removing them.......
		
		Printing_sorted_KilledEnemies();


		pGUI->ClearStatusBar();

		// fillling enemiesforDraw array and writing info in status bar 

		fillling_enemiesforDraw(pGUI );

		//drawing enemies..............

		if(actiontype != SILENT && actiontype != MENU_EXIT)
			Drawing(pGUI);

		time_step++;
	}

	printWarResult();
}

void Battle::AddtoKilled(Enemy* e)
{
	killed.add(e);
}


void Battle::createFileOutput() {
	string fileName = "The Result Of Number " + warNumber ;
	fileName = fileName + ".txt";
	out.open(fileName);
	out.clear();
	out << "KTS  S  FD  KD  LT" << endl;
	warNumber++;
}


void Battle::printWarResult() {
	BCastle.printTotalTowersDamage(out);
	BCastle.printTotalTowersUnpavedDist(out);
	if (BCastle.damaged())
	{
		out << "Game is LOSS" << endl;
		out << "Number Of Killed Enemy: " << KilledEnemy << endl;
		out << "NUmber Of Alive Enemy: " << TotalNumberOfEnemys - KilledEnemy << endl;
		out << "Average First-Shot Delay: " << totalFD / KilledEnemy << endl;
		out << "Average Kill Delay: " << totalKD / KilledEnemy << endl;
	}
	else
	{
		out << "Game is WIN " << endl;
		out << "Total Enemies: " << TotalNumberOfEnemys << endl;
		out << "Average First-Shot Delay: " << totalFD / TotalNumberOfEnemys << endl;
		out << "Average Kill Delay: " << totalKD / TotalNumberOfEnemys << endl;

	}
	out.close();
}