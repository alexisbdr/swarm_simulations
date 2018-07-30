#define ROBOT_COUNT 40
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
	//Here is the commented out code for random distribution of the robots in the arena
	//Robotrs get assigned a random starting position and random orientation.
	
	for (int i = 0;i < ROBOT_COUNT;i++)
	{
		robot_pos[i][0] = rand() % 2320 + 20 ; //assigning x position within arena 
		robot_pos[i][1] = rand() % 2320 + 20;   //assigning y position within arena
		
		// Overlap calculation loop
		for (int l = 0 ; l<i ; l++)
		{
			//start by calculating the distance qand storing it in var dist
			double dist = 0 ;
			while(dist<100) // buffer of 50
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


