#pragma once
#include "kilolib.h"

class mykilobot : public kilobot
{
	unsigned char distance;
	message_t out_message;
	int rxed=0;
	int msrx=0;
	int count1 = 1 ;  
	int count2 = 0 ; 
	int smooth_count = 1 ; 
	
	double gradient1 = 100 ; //Initialization of bottom left corner hop count
	double gradient2 = 100 ; //Initialization of bottom right corner hop count
	double xc = 0 ; 
	double yc = 0 ; 
	double smooth_gradient1 = 0 ;  
	double smooth_gradient2 = 0 ;
	double sxc = 0 ; 
	double syc = 0 ; 
	
	int coordinate_system_delay = 500 ; //Establishes when the coordinate systm should be established
					    // Corresponds to the number of time steps
	int smoothing_delay = 800 ; // Number of times you take in local hop count for smoothing
	
	double comm_rad = 4 ;  // Comm radius is about 4 robots 
	
	
	struct mydata {
		unsigned int data1;
		unsigned int data2;
	};
	
	//main loop
	void loop()
	{	
		 
		if(id==1) 
		{
			gradient1 = 0 ; 
		}
		if(id==31) 
		{
			gradient2 = 0 ; 
		}
		
		
	 	
	}

	//executed once at start
	void setup()
	{
		id=id&0xff;
		out_message.type = NORMAL;
		out_message.data[0] = gradient1 ;
		out_message.data[1] = gradient2 ; 
		//out_message.data[2] =   ; 
		
		set_color(RGB(2,0,2)); //In the setup, all robots are initially set to a purple colour
		
		out_message.crc = message_crc(&out_message);
	}

	//executed on successfull message send
	void message_tx_success()
	{
		msrx=1;
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
	void message_rx(message_t *message, distance_measurement_t *distance_measurement)
	{
		distance = estimate_distance(distance_measurement);
		if(count1 < coordinate_system_delay)
		{
			if(message->data[0] < gradient1) 
			{	
				gradient1 = message->data[0] ; 
				out_message.data[0] = gradient1 + 1 ; 
				count1 = 0 ; 
			}
			else 
			{	 
				out_message.data[0] = gradient1 + 1 ; 
				count1++ ; 
			}
		
			if(message->data[1] < gradient2) 
			{ 
				gradient2 = message->data[1] ; 
				out_message.data[1] = gradient2 + 1 ;  
			}
			else 
			{
				out_message.data[1] = gradient2 + 1 ; 
			}
			smooth_gradient1 = gradient1 ; 
			smooth_gradient2 = gradient2 ;
		}
		
		/*
		if(count1 < coordinate_system_delay)
		{ 
			//Obtain Coordinates using distance from each points. 
			//Using euclidean distance between given point and seed in coordinate system
			//This will calculate the x an y coordinates every single time, once the gradient hop count has been established for each robot
			//This coordinate system won't be very accurate. 
			double g1 = gradient1 ; //For simplificity in formula 
			double g2 = gradient2 ; 
			double seed2_xhop = 32/comm_rad ; // correspnds to the x_coordinate of the lower right seed in terms of the hop count values. 
			double var = 2*(seed2_xhop) ; //for simplicity in the following formula
			
			xc =  (g1*g1)/(var) - (g2*g2)/(var) + pow(seed2_xhop,2)/(var) ;  //Calculate x coordinate based on circle intersection
			yc = abs(sqrt((g1*g1)-(xc*xc))) ; //Calculate y coordinate based on circle intersection
		
			//Color testing to check x-y coordinate system, disregard// this is just a test
			/*
			if(yc>6) 
			{set_color(RGB(2,2,2)) ; } 
			else if(yc > 5)
			{set_color(RGB(2,0,0)) ; } 
			else if(yc > 4)
			{set_color(RGB(2,2,0)) ; }  
			else if(yc > 3)
			{set_color(RGB(0,3,0)) ; }
			else if(yc > 2)12
			{set_color(RGB(0,3,3)) ; }
			else if(yc > 1)
			{set_color(RGB(1,1,3)) ; } 
			*/
			
			//Drawing the N for non-smoothed coordinates
			//As we can see the N is really inaccurate around center areas of the coordinate system, where the comm radii intersect. 
			/*
			if(yc < (-2)*xc+7.7 && yc > (-2)*xc+3 && xc>2) 
			{set_color(RGB(3,3,3)) ; }
			if(xc > 1.8 && xc < 2.2 && yc < 1.1) 
			{set_color(RGB(3,3,3)) ; } 
			if(yc > 3 && yc < (-2.5)*xc+18 && yc > (-1.8)*xc+12 && xc < 5)
			{set_color(RGB(3,3,3)) ; } 
			if( yc > 3 && xc < 5.5 && xc > 4) 
			{set_color(RGB(3,3,3)) ; } 
			*/
			
			
		
			
			//Start smoothing the gradient messages 	

		else if(smooth_count < 600)
		{
			smooth_gradient1 = smooth_gradient1 + message->data[0] ; 
			smooth_gradient2 = smooth_gradient2 + message->data[1] ;
			smooth_count++ ;
		}
		
		if(smooth_count == 600) 
		{
			smooth_gradient1 = (smooth_gradient1/600) -.5 ; 
			smooth_gradient2 = (smooth_gradient2/600) -.5 ; 
			//Running short test to make sure that the new gradient are more accurate 
			/*
			if(smooth_gradient1 > 2) 
			{ set_color(RGB(2,2,2)) ;} 
			if(smooth_gradient2 > 2 && smooth_gradient2<2.3)
			{ set_color(RGB(2,1,0)) ; } 
			*/
		
			//Calculating the coordinates from the smoothed gradient system 
			double sg1 = smooth_gradient1 ; 
			double sg2 = smooth_gradient2 ; 
			double seed2_xhop = 32/comm_rad ; // correspnds to the x_coordinate of the lower right seed in terms of the hop count values. 
			double var = 2*(seed2_xhop) ; //for simplicity in the following formula
		
			sxc =  (sg1*sg1)/(var) - (sg2*sg2)/(var) + pow(seed2_xhop,2)/(var) ;  //Calculate x coordinate based on circle intersection
			syc = abs(sqrt((sg1*sg1)-(sxc*sxc))) ; //Calculate y coordinate based on circle intersection
			
			if( syc < -2*sxc + 10 && syc > -1.7*sxc + 5 && sxc > 2.4 && syc<5)  
			{ 
				set_color(RGB(0,0,0)) ; 
			}
			if(syc < -2 * sxc + 18 && syc > -2 * sxc + 14 && sxc <5.7 && syc > 3)
			{
				set_color(RGB(0,0,0)) ;
			}
			smooth_count++;
			
		
		
			//Drawing N for smoothed coodinate system 
			//Should give more accurate results than previous N for non-smoothed coordinate system
		
		}
	}	
};
