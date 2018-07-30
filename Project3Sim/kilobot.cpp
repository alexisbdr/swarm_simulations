#pragma once
#include "kilolib.h"
#include <math.h>

class mykilobot : public kilobot
{
	//Communication variables and other 
	unsigned char distance;
	float theta;
	message_t out_message ;
	int msrx = 0 ; 
	struct mydata {
		unsigned int data1 ; 
		unsigned int data2 ;
	}; 

	//Time variables initialized here
	int delayed_onset1 = 5 ; //Defines how long the robot senses its neighbourhood 
	int delayed_onset2 = 10 ; //Defines for how long the robot rotates
	int delayed_onset3 = 15 ; //Defines for how long the robot moves 
	long int motion_timer = 0 ; 
	
	//Loop variable initialiations
	double repulsion = 0 ;
	int motion = 0 ;
	int count = 0 ;  
	double repulsion_sum = 0 ;
	double theta_sum = 0 ; 
	double x_combination = 0 ; 
	double y_combination = 0 ; 
	double magnitude = 0 ; 
	double heading = 0 ; 
	int init_loop = 0 ; 
	int id = 0 ; 
	double x_repulsion = 0 ; 
	double y_repulsion = 0 ;
	double x_cohesion = 0 ;
	double y_cohesion = 0 ;
	double x_heading = 0 ; 
	double y_heading = 0 ; 
	double neighbour = 0 ;
	
	//Weight initializations 
	double r_weight = .8 ;//The weight assigned to the random walk component
	double m_weight = .03  ; //weight assigned to the migration component 
	double rep_weight = 4.5 ;//weight assigned to the repulsion force component 
	double head_weight = .9 ; //weight assigned to the global heading force component 
	double c_weight = 0.001;  //weight assigned to the cohesion component 
	double tot_weights = r_weight + m_weight + rep_weight + head_weight + c_weight ; //Used to normalize the weight calculations, corresponds to sum of all weights being used. 
	
	//main loop
	void loop()
	{	
		//Assigning random id's 
		if(init_loop==0){
			id = rand() ; 
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
		
			//Here we will calculate repulsion by adding up at each time step the sensed angles and distances
			//Start by calculating the repulsion vector
			double x = cos(theta - PI)/dist ; 
			double y = sin(theta - PI)/dist ;
			//Sum up the reulsion vector
			x_repulsion += x ; 
			y_repulsion += y ; 
			
			//Calculate the cohesion vector
			x = cos(PI-theta) ; 
			y = sin(PI-theta) ; 
			//Sum up the cohesion vector
			x_cohesion += x ;
			y_cohesion += y ;  
			
			//Heading calculations for neighbourhood
			//Calculate the general heading vector
			x = cos(PI+neighbour-theta) ; 
			y = sin(PI+neighbour-theta) ; 
			//Sum up for neighborhod 
			x_heading += x ; 
			y_heading += y ; 
		
			
			if(kilo_ticks > motion_timer + delayed_onset1) 
			{
				//Generate a random heading, radian value between 0 and 2pi 
				double random_orientation = rand() * 2 * PI / RAND_MAX ; //Couldn't get rand_hard() to work
				//Had to rely on rand() to do random walk, it is pseudo-random though...  
				unsigned char r = rand_hard() ; 
				std::cout << random_orientation << std::endl ; 
				
				//We will now calculate the heading of the robot based on the angle to the light, the opposite of the relative angle and a random facto
				double x_rand = cos(random_orientation) ; 
				double y_rand = sin(random_orientation) ; 
				
				//angle_to_light is the migration force, break down the relative angle into two components, x and y 
				double x_follow = cos(angle_to_light) ; 
				double y_follow = sin(angle_to_light) ;  
								
				//Normalizing cohesion vector 
				x_cohesion = x_cohesion/(sqrt(pow(x_cohesion,2)+pow(y_cohesion,2))) ; 
				y_cohesion = y_cohesion/(sqrt(pow(x_cohesion,2)+pow(y_cohesion,2))) ; 
				
				//Normalizing repulsion vector 
				x_repulsion = x_repulsion/(sqrt(pow(x_repulsion,2)+pow(y_repulsion,2))) ; 
				y_repulsion = y_repulsion/(sqrt(pow(x_repulsion,2)+pow(y_repulsion,2))) ; 
				
				//Normalizing the heading vector 
				x_heading = x_heading/(sqrt(pow(x_heading,2)+pow(y_heading,2))) ; 
				y_heading = y_heading/(sqrt(pow(x_heading,2)+pow(y_heading,2))) ;

				x_combination = (r_weight*x_rand + m_weight*x_follow + rep_weight*x_repulsion + head_weight*x_heading + c_weight*x_cohesion)/tot_weights ; 
				y_combination = (r_weight*y_rand + m_weight*y_follow + rep_weight*y_repulsion + head_weight*y_heading + c_weight*y_cohesion)/tot_weights ; 
				//Linear combination commments : 
				//Rand weight --> seems to give better separation between stuck partners above 2 
				//Migration weight --> will need to try to lower it 
				//Repulsion weight  
				motion = 2 ; 
				count = 0 ; 
			}	
		}
		
	
		if(motion==2)
		{
			
			if(y_combination > 0.001) 
			{
				spinup_motors() ; 
				set_motors(0,kilo_turn_right) ; 
			}
			else if(y_combination < -0.001) 
			{
				spinup_motors() ;
				set_motors(kilo_turn_left,0) ; 
			}
			
			else
			{
				spinup_motors() ; 
				set_motors(kilo_straight_left,kilo_straight_right) ; 
			}
			
			
			if(kilo_ticks > motion_timer + delayed_onset2) 
			{
				motion = 3 ; 
			} 
		
		}
		if(motion == 3)
		{
			spinup_motors() ; 
			set_motors(kilo_straight_left,kilo_straight_right) ; 
			
			if(kilo_ticks > (motion_timer + delayed_onset3)) 
			{
				set_motors(0,0) ; 
				motion = 0 ; 
				count = 0 ;
				x_repulsion = 0 ; 
				y_repulsion = 0 ;
				x_cohesion = 0 ;
				y_cohesion = 0 ;
				x_heading = 0 ; 
				y_heading = 0 ; 
			}   
		}
		
		

	//Communication step for global heading agreement
	
	int deg = (theta*360)/(2*PI) ; //first step, convert sensed relative angle to degrees
	out_message.data[0] = deg ;
	out_message.data[1] = id ;  
	out_message.crc = message_crc(&out_message) ; 
		
		
	}

	//executed once at start
	//Will use setup function to initialize robot color
	//Robot colors will be random, for entertainment purposes
	void setup()
	{
		
		int r = rand() % 3 ; //My rand_hard function does not seem to be working anymore, I have tried everything I knot, must rely on rand()
		int g = rand() % 3 ; 
		int b = rand() % 3 ; 
		set_color(RGB(r,g,b)) ; 
	}

	//executed on successfull message send
	void message_tx_success()
	{
		msrx = 1 ; 
	}

	//sends message at fixed rate
	message_t *message_tx()
	{
		static int count = rand();
		count--;
		if (!(count % 10))
		{
			return &out_message;
		}
		return NULL;

	}
	
	//receives message
	void message_rx(message_t *message, distance_measurement_t *distance_measurement,float t)
	{
		
		distance = estimate_distance(distance_measurement);
		theta=t ; //Relative angle to other robot.
		out_message.data[0] = message->data[0]; 
		out_message.data[1] = message->data[1]; 
		double neighbour = ((double)out_message.data[0]*360)/255 ; //mapping out from 8 bit back to degrees
		neighbour = (neighbour*2*PI)/360 ; 
		unsigned char r = rand_hard()  ; 
		std::cout << (int)r << std::endl ; 
	}
};

