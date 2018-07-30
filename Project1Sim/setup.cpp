#define ROBOT_COUNT 1024

#define ARENA_WIDTH 1340
#define ARENA_HEIGHT 1340

#define SIMULATION_TIME 180 //in seconds


double distanceCalculator(double x1, double x2, double y1, double y2) 
{
	double x = x1 - x2 ; 
	double y = y1 - y2 ; 
	double dist = sqrt(pow(x,2) + pow(y,2)) ; // Formula for euclidean distance 

	return dist ; 
}

//Rectangular Grid setup 

/*
void setup_positions(float robot_pos[ROBOT_COUNT][4])
{
	int columns = 32;
	int horizontal_separation = 40;
	int vertical_separation = 40;
	for (int i = 0;i < ROBOT_COUNT;i++)
	{	
		int c = i % columns + 1; 
		int r = i / columns + 1;
		robot_pos[i][0] = c * vertical_separation ; //x
		robot_pos[i][1] = r * horizontal_separation ;   //y
		robot_pos[i][2]= 2 * PI ; //theta
		
		if(i==0) 
		{
			robot_pos[i][3] = 1 ; //assign ID to the lower left bottom corner robot 
					      //Start with first gradient message
		}
		
		if(i==31)
		{ 
			robot_pos[i][3] = 31 ; //assign ID to the lower right bottom corner robot
		}
		
	}
}
*/
//Hexagonal grid setup 
void setup_positions(float robot_pos[ROBOT_COUNT][4])
{	
	int columns = 32 ; 
	int horizontal_separation = 40 ; 
	int vertical_separation = 40 ; 
	for(int i = 0 ; i < ROBOT_COUNT ; i++) 
	{ 
		int c = i % columns + 1 ; 
		int r = i / columns + 1 ; 
		if(r % 2 == 0)
		{
			robot_pos[i][0] = c * vertical_separation + 20 ; //x 
		}
		else
		{
			robot_pos[i][0] = c * vertical_separation; //x
		}
		
		robot_pos[i][1] = r * horizontal_separation ; //y 
		robot_pos[i][2] = 2 * PI ; // theta 
		
		if(i==0) 
		{
			robot_pos[i][3] = 1 ; 
		}
		if(i==31) 
		{
			robot_pos[i][3] = 31 ; 
		}
	}

}
	
	




