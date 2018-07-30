#define ROBOT_COUNT 210
#define ROBOT_SPACING 40

#define ARENA_WIDTH 32*32 + 33*ROBOT_SPACING
#define ARENA_HEIGHT 32*32 + 33*ROBOT_SPACING

#define LIGHT_CENTER_X 1172
#define LIGHT_CENTER_Y 1172

#define SIMULATION_TIME 180 //in seconds

#include "kilolib.h"
 

double distanceCalculator(double x1, double x2, double y1, double y2) 
{
	double x = x1 - x2 ; 
	double y = y1 - y2 ; 
	double dist = sqrt(pow(x,2) + pow(y,2)) ; // Formula for euclidean distance 

	return dist ; 
}

void setup_positions(float robot_pos[ROBOT_COUNT][4])
{
	
		/*robot_pos[0][0] = 100;
		robot_pos[0][1] = 100;
		robot_pos[0][2] = 0; //theta
		robot_pos[0][3] = 0; 



		robot_pos[1][0] = 150;
		robot_pos[1][1] = 150;
		robot_pos[1][2] = 0; //theta
		robot_pos[1][3] = 1; 
		*/


	//assign each robot a random position, centered around light source
	/*
	int robot_num;
	int x=100;
	int y=100;
	
	for(robot_num=0;robot_num<=ROBOT_COUNT;robot_num++) //for 100 robots
	{


		robot_pos[robot_num][0]=x;
		robot_pos[robot_num][1]=y;
		robot_pos[robot_num][3]=1;
		x+=200;
		if ( x>2430)
		{		
			x=100;
			y+=200;
		}

		if(robot_num>=50)
		robot_pos[robot_num][3]=1;


	}
	*/
	
	//Here is the commented out code for random distribution of the robots in the arena

	for (int i = 0;i < ROBOT_COUNT;i++)
	{
		//int z = rand() % 50;
		//int c = (rand() % i)/10 % columns + 1;
		//int r = i / columns + 1;
		robot_pos[i][0] = rand() % 2322 + 17 ; //x
		robot_pos[i][1] = rand() % 2322 + 17;   //y
		//For 1 shell of 100 robots 
		robot_pos[i][3] = 0 ;
		 
		//For 2 shells of 100 robots 
		
		if(i>=70){ 
		robot_pos[i][3] = 1 ; }
		
		if(i>=140){
		robot_pos[i][3] = 2 ; }
		
		// Overlap calculation loop
		for (int l = 0 ; l<i ; l++)
		{
			//start by calculating the distance qand storing it in var dist
			double dist = 0 ;
			while(dist<70) // buffer of 50
			{
				//generate new rand positions if loop is active
				robot_pos[i][0] = rand() % 2322 + 17  ; //x
				robot_pos[i][1] = rand() % 2322 + 17 ;   //y
				
				//calculate the distance again to make sure the newly generated position doesn't overlap
				dist = distanceCalculator(robot_pos[i][0],robot_pos[l][0],robot_pos[i][1],robot_pos[l][1]) ;
			}

		}
		
		robot_pos[i][2]= rand() * 2 * PI / RAND_MAX; //theta
	
	}
	
}


