#include "GUI.h"
#include "../Defs.h"
//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("The Castle Game");

	DrawMenu();

	ClearStatusBar();
	//ClearBattleArea();
	DrawCastle(false,false,false,false);

}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;

		PrintMessageString(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessageString( string msg ,int x , int y  ) const	//Prints a message on status bar
{
	//First clear the status bar
	pWind->SetPen(WHITE);
	pWind->SetFont(10, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(x, y, msg); // You may need to change these coordinates later 
	// to be able to write multi-line
}

void GUI :: Printinteger(int msg , int x , int y) const
{
	pWind->SetPen(WHITE);
	pWind->SetFont(10, BOLD , BY_NAME, "Arial");   
	pWind->DrawInteger(x, y, msg);
}

void GUI :: PrintDouble(double msg , int x, int y) const 
{
	pWind->SetPen(WHITE);
	pWind->SetFont(10, BOLD , BY_NAME, "Arial");   
	pWind->DrawDouble(x, y, msg);
}


//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(WHITE);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];

	MenuItemImages[LOAD] = "images\\MenuItems\\load.jpg";
	MenuItemImages[CLICK] = "images\\MenuItems\\click.jpg";
	MenuItemImages[TIME] = "images\\MenuItems\\time.jpg";
	MenuItemImages[SILENT] = "images\\MenuItems\\silent.jpg";
	MenuItemImages[MENU_EXIT] = "images\\MenuItems\\exit.jpg";

	//
	//TODO: Prepare images for each menu item (an icon for each modes) and add it to the list
	//

	// You should add an icon for each mode of operation (silent, step by step, ...etc.)

	//Draw Menu Background
	pWind->SetPen(LIGHTGRAY);
	pWind->SetBrush(LIGHTGRAY);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);

	//Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BROWN, 3);
	//pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(essam);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BROWN, 3);
	//pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea( Tower* t) const
{
	// Clearing the battle area
	pWind->SetPen(KHAKI, 3);
	pWind->SetBrush(KHAKI);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);

	// Drawing unpaved area....

	pWind->SetBrush(LIGHTBLUE);
	int x, y, refX, refY;
	refX = (WindWidth/2 - CastleWidth/2);
	x = refX - t[0].getUnpavedArea()*EnemyWidth - t[0].getUnpavedArea(); //(Distance)
	pWind->DrawRectangle(x+EnemyWidth,MenuBarHeight,WindWidth/2,YHalfBattleArea);
	x = refX - t[3].getUnpavedArea()*EnemyWidth - t[3].getUnpavedArea();
	pWind->DrawRectangle(x+EnemyWidth,YHalfBattleArea,WindWidth/2,WindHeight-StatusBarHeight);
	refX = (WindWidth/2 + CastleWidth/2);
	x = refX + (t[1].getUnpavedArea())*EnemyWidth + t[1].getUnpavedArea();
	pWind->DrawRectangle(WindWidth/2,MenuBarHeight,x-EnemyWidth,YHalfBattleArea);
	x = refX + (t[2].getUnpavedArea())*EnemyWidth + t[2].getUnpavedArea();
	pWind->DrawRectangle(WindWidth/2,YHalfBattleArea,x-EnemyWidth,WindHeight-StatusBarHeight);

}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle(bool aSilenced, bool bSilenced, bool cSilenced, bool dSilenced) const
{
	int L = CastleWidth / 2;

	// 1- Drawing the brown square of the castle
	pWind->SetPen(BROWN);
	pWind->SetBrush(BROWN);
	pWind->DrawCircle(((-CastleStartX+CastleEndX)/4+CastleStartX),((-CastleStartY+CastleEndY)/4+CastleStartY),(CastleStartX-CastleEndX)/4);
	pWind->DrawCircle(((-CastleStartX+CastleEndX)/4+CastleStartX),((-CastleStartY+CastleEndY)/4*3+CastleStartY),(CastleStartX-CastleEndX)/4);
	pWind->DrawCircle(((-CastleStartX+CastleEndX)/4*3+CastleStartX),((-CastleStartY+CastleEndY)/4+CastleStartY),(CastleStartX-CastleEndX)/4);
	pWind->DrawCircle(((-CastleStartX+CastleEndX)/4*3+CastleStartX),((-CastleStartY+CastleEndY)/4*3+CastleStartY),(CastleStartX-CastleEndX)/4);
	pWind->DrawRectangle(CastleStartX, CastleStartY+50, CastleEndX, CastleEndY-50);
	pWind->DrawRectangle(CastleStartX+50, CastleStartY, CastleEndX-50, CastleEndY);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	//pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);


	// 3- Drawing the 2 white crossed lines (inside the castle)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth/2, YHalfBattleArea - CastleWidth/2, WindWidth/2, YHalfBattleArea + CastleWidth/2);
	pWind->DrawLine(WindWidth/2 - CastleWidth/2, YHalfBattleArea, WindWidth/2 + CastleWidth/2, YHalfBattleArea);


	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(WHITE);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + 0.44*L, CastleStartY + 5*L/12, "A");
	pWind->DrawString(CastleStartX + 0.44*L, YHalfBattleArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + 0.44*L, CastleStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + 0.44*L, YHalfBattleArea + 5*L/12, "C");

	// 6- Drawing the 2 vertical brown lines at distance 60
	// that is because some rounding errors may occur if you choose another width and height for the window
	// so we draw 2 vertical lines at distance 60 to mark it
	pWind->SetPen(BROWN);
	//pWind->DrawLine(CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, MenuBarHeight,
	//CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, WindHeight-StatusBarHeight);
	//pWind->DrawLine(CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, MenuBarHeight,
	//CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, WindHeight-StatusBarHeight);

	pWind->SetPen(BLUE,3);
	
	if (aSilenced) {
		pWind->DrawCircle(((-CastleStartX + CastleEndX) / 4 + CastleStartX), ((-CastleStartY + CastleEndY) / 4 + CastleStartY), (CastleStartX - CastleEndX) / 4 , FRAME);
		pWind->DrawLine(CastleStartX+23, CastleStartY+23, (CastleStartX+CastleEndX)/2 - 23, (CastleStartY+CastleEndY)/2 - 23);
	}
	if (bSilenced) {
		pWind->DrawCircle(((-CastleStartX + CastleEndX) / 4 * 3 + CastleStartX), ((-CastleStartY + CastleEndY) / 4 + CastleStartY), (CastleStartX - CastleEndX) / 4 , FRAME);
		pWind->DrawLine((CastleStartX + CastleEndX)/2 + 23, CastleStartY + 23, CastleEndX - 23 , (CastleStartY + CastleEndY) / 2 -23);
	}
	if (cSilenced) {
		pWind->DrawCircle(((-CastleStartX + CastleEndX) / 4 * 3 + CastleStartX), ((-CastleStartY + CastleEndY) / 4 * 3 + CastleStartY), (CastleStartX - CastleEndX) / 4 , FRAME);
		pWind->DrawLine((CastleStartX + CastleEndX) / 2 + 23, (CastleStartY + CastleEndY) / 2 + 23, CastleEndX - 23, CastleEndY - 23);
	}
	if (dSilenced) {
		pWind->DrawCircle(((-CastleStartX + CastleEndX) / 4 + CastleStartX), ((-CastleStartY + CastleEndY) / 4 * 3 + CastleStartY), (CastleStartX - CastleEndX) / 4 , FRAME);
		pWind->DrawLine(CastleStartX + 23, (CastleStartY + CastleEndY) / 2 + 23, (CastleStartX + CastleEndX) / 2 - 23, CastleEndY - 23);
	}
}

void GUI ::DrawLine(int x1 , int y1 ,int x2 ,int y2) const
{
	pWind->SetPen(CADETBLUE,3);
	pWind->DrawLine(x1,y1,x2,y2);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for(int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
		// else print number of enemy in the region
		bool draw=true;
		for(int distance = MaxDistance ; distance >= MinDistance ; distance--)
		{
			CountEnemies = 0;

			for(int i = 0 ; i < size ; i++)
			{	
				if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			if(CountEnemies > 15)
			{
				draw=false;
				break;
			}
		}
		if(draw)
		{
			for( int distance = MaxDistance ; distance > 1 ; distance-- )
			{
				CountEnemies=0;

				for(int i = 0 ; i < size ; i++)
				{	
					if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessageString("Cannot Draw Enemies of region " + to_string(region+1) + 
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}
