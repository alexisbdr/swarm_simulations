#pragma once
#include "kilolib.h"
#include <math.h>

class mykilobot : public kilobot
{
	//random walk should be equal distribution of all angles?
	//kiloticks is limiting angle
	//print out error metric to consule--graph per timestep 
	//gonna need trig to calculate bearing
	int init_loop = 0 ; 
	double rad = 40  ; 

	unsigned char distance;
	float theta;
	
	double heading = 0 ; 
	double repulsion = 0 ;
	int num = 0 ;
	
	long int motion_timer = 0 ; 
	int motion = 0 ;
	
	int count = 0 ;  
	double repulsion_sum = 0 ;
	double x_combination = 0 ; 
	double y_combination = 0 ; 
	double magnitude = 0 ; 
	
	//main loop
	void loop()
	{	
		//This loop will only run once at the start of the code. it will initialize the robots in the arena according to their ID
		//Color and radius will be set here 
		if(init_loop == 0)
		{
			if(id==0)
			{
				set_color(RGB(0,0,3)) ; //Blue robot 
	
			}
			else if(id == 1)
			{
				set_color(RGB(0,3,0)) ; //Green robot
				rad = rad * 3.2 ; 
			}
			else if(id == 2) 
			{
				set_color(RGB(3,0,0)) ; //Red robot 
				rad = rad *3.5 ; 
			}
			
			init_loop = 1 ; 
			
		}
		
		
		if(motion==0)
		{
			motion_timer = kilo_ticks ;
			motion = 1 ; 
		}
		if(motion == 1) 
		{
			//Robot sensing 
			//We will calculate here each of the vectors for gravity, repulsion and random walk
			//The magnitude and orientation will be separate
			//Repulsion is calculated first 
			double dist = (double)distance ; //The calculated distance is an unsigned char, casted it to double to perform calcs on it
		
			//Here we will calculate repulsion using the formula given by the formula in the paper
			double k = 0.2 ; 
			repulsion = k*(2*rad - dist) ; 
			if(repulsion < 0)//Handling negative repulsion
			{
				repulsion = 0 ; 
			}  
			else if(repulsion > 6.4) 
			{
				repulsion = 6.4 ;
			}
			repulsion_sum = repulsion_sum + repulsion ; 
			count++ ; 
		
			
			if(kilo_ticks > motion_timer + 30) 
			{
				//Generate a random heading, radian value between 0 and 2pi 
				double random_orientation = rand() * 2 * PI / RAND_MAX ; //Couldn't get rand_hard() to work
				//Had to rely on rand() to do random walk, it is pseudo-random though...  
	
				//We will now calculate the heading of the robot based on the angle to the light, the opposite of the relative angle and a random facto
				double x_rand = cos(random_orientation) ; 
				double y_rand = sin(random_orientation) ; 
		
				double x_follow = cos(angle_to_light) ; 
				double y_follow = sin(angle_to_light) ; 
				
				double v_repulsion = repulsion_sum / count ; //Average out all the repulsion vector magnitudes 
				double x_theta = -v_repulsion*cos(theta) ; //opposite values to obtain the reflected angle
				double y_theta = -v_repulsion*sin(theta) ; 

				x_combination = (.6*x_rand + x_follow + x_theta)/2.6 ; 
				y_combination = (.6 * y_rand +  y_follow + y_theta)/2.6 ; 
				double angle = atan2(y_combination,x_combination) ; 
				magnitude = .6 + 1 + repulsion ; 
				motion = 2 ; 
			}	
		}
		
	
		if(motion==2)
		{
			
			if(y_combination > 0.1) 
			{
				spinup_motors() ; 
				set_motors(0,kilo_turn_right) ; 
			}
			else if(y_combination < -0.1) 
			{
				spinup_motors() ;
				set_motors(kilo_turn_left,0) ; 
			}
			else
			{
				spinup_motors() ; 
				set_motors(kilo_straight_left,kilo_straight_right) ; 
			}
		
			
			if(kilo_ticks > motion_timer +40) 
			{
				motion = 3 ; 
			} 
		
		}
		if(motion == 3)
		{
			spinup_motors() ; 
			set_motors(kilo_straight_left,kilo_straight_right) ; 
			
			if(kilo_ticks > (motion_timer + 40 + magnitude*4)) 
			{
				set_motors(0,0) ; 
				motion = 0 ; 
				repulsion_sum = 0 ;
				count = 0 ;
			}   
		}
		
		

		
		
		
	}

	//executed once at start
	void setup()
	{
	
		
	}

	//executed on successfull message send
	void message_tx_success()
	{
		
	}

	//sends message at fixed rate
	message_t *message_tx()
	{
	
	}

	//receives message
	void message_rx(message_t *message, distance_measurement_t *distance_measurement,float t)
	{
		
		distance = estimate_distance(distance_measurement);
		theta=t ; //Relative angle to other robot.
		
		
		
	}
};

