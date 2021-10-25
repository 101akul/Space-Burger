#include <iostream>
#include <string>
#include "CMUgraphicsLib\auxil.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include <time.h>
#include <random>
#include <vector>


const int WIN_WIDTH = 720;
const int WIN_HEIGHT = 1010;
const int leftKey = 97;
const int rightKey = 100;
const int moveAmount = 10; 

const color BACKGROUND = BLACK;

void clearScreen();
void titlescreen();


vector<int> bXCoord(100);
vector<int> bYCoord(100);
vector<color> bColor(100);

vector<int> fXCoord(5);
vector<int> fYCoord(5);
vector<color> fColor(5);
vector<int> fSpeed(5);


int items = 1;
int level = 4;

window testWindow(WIN_WIDTH, WIN_HEIGHT,0,0);

int main()
{
	
	srand(time(NULL));
	bool end = false;
	char key;
	testWindow.SetBuffering(true);

	testWindow.SetWaitClose(false);

	//falling object coordinates
	fXCoord[0] = rand()%621;
	fYCoord[0] = 0;
	fColor[0] = RED;
	fSpeed[0] = (rand()%5)+4;

	fXCoord[1] = rand()%621;
	fYCoord[1] = 0;
	fColor[1] = GREEN;
	fSpeed[1] = (rand()%5)+4; 

	fXCoord[2] = rand()%621;
	fYCoord[2] = 0;
	fColor[2] = BROWN;
	fSpeed[2] = (rand()%5)+4; 

	fXCoord[3] = rand()%621;
	fYCoord[3] = 0;
	fColor[3] = YELLOW;
	fSpeed[3] = (rand()%5)+4;

	// stacked objects coordinates
	bXCoord[0] = 310;
	bYCoord[0] = 975;
	bColor[0] = BROWN;

	
 

 while(!end)
 {

	  clearScreen();

	  //draw burger stuff
	  for(int i = 0; i < items; i++)

	  {
		  if(i == 0)
			testWindow.DrawImage("Picture1.jpg",bXCoord[0],bYCoord[0],100,25);
		  else
		  {
			  testWindow.SetPen(bColor[i]);
			  testWindow.SetBrush(bColor[i]);
			  testWindow.DrawRectangle(bXCoord[i],bYCoord[i],bXCoord[i]+100,bYCoord[i]+25);
		  }
	  }
	  	
	  //draw falling stuff
	  for(int i = 0; i < level; i++)
	  {

			testWindow.SetPen(fColor[i]);







			testWindow.SetBrush(fColor[i]);
			testWindow.DrawRectangle(fXCoord[i],fYCoord[i],fXCoord[i]+100,fYCoord[i]+25);

			

		  
	  }
	  
	  testWindow.UpdateBuffer();
  
	  testWindow.GetKeyPress(key);

	  //controls for stack
	  for(int i = 0; i < items; i++)
	  {

		  if(int(key)==leftKey)
		  {
			bXCoord[i] = bXCoord[i]-moveAmount;
		  }
		  else if(int(key) == rightKey)
		  {
		   bXCoord[i] = bXCoord[i]+moveAmount;
		  }

		  if(bXCoord[i]>720)
		  {
		   bXCoord[i] = -30;
		  }

		  if(bXCoord[i]+100<0)
		  {
		   bXCoord[i] = 720;
		  }
	  }

	  
	  for(int i = 0; i < level; i++)
	  {
		fYCoord[i] = fYCoord[i] + fSpeed[i];

		if(fYCoord[i] > 985)
		{
			fYCoord[i] = 0;
			fSpeed[i] = (rand()%5)+4; 
			fXCoord[i] = rand()%621;
		}
	  
		  //collision
		 if(fXCoord[i]+50>=bXCoord[items-1]+35 && fXCoord[i]+50<=bXCoord[items-1]+65 && fYCoord[i]+25 >= bYCoord[items-1] && fYCoord[i] <= bYCoord[items-1])
		 {
			  bXCoord[items] = bXCoord[items-1]; 
			  bYCoord[items] = bYCoord[items-1] - 25;
			  bColor[items] = fColor[i];
			  items++;
			  fYCoord[i] = 0;
			  fXCoord[i] = rand()%621;
			  fSpeed[i] = (rand()%5)+4; 

		 }

	  }
	  
	  Pause(1);
     
 }
  

 return 0;
}

void clearScreen()
{
	 testWindow.SetPen(BACKGROUND);
	 testWindow.SetBrush(BACKGROUND);
	 testWindow.DrawRectangle(0,0,WIN_WIDTH,WIN_HEIGHT);
}



