# Coordinate system based on hopcount
### Based on paper: “Organizing a global coordinate system from local information on an ad hoc sensor network.”
---
### File Information
kilobot.cpp and setup.cpp were written from scratch to display Notheswestern N in square of 32x32 robots. 
Starter code for the simulation was offered by professor, I altered main.cpp as well for the purpose of the simulation

### Goal and achievements
The aim of the simulation is to use distributed hopcount to achieve a global coordinate system within on a two dimensional plane or robots. Each robot sensor communicates with other sensors within their communication range r, where r is smaller than the dimensions of the plane. Once the coordinate system is established, the robots communicate with each other to change their colours and create a shape, the Northwestern N. 

### Approach
* Two seed robots are placed in bottom corners of the grid with special ID's 
* ID's are propagated to robots within communication range
* Each robot within communication range knows the approximate distance to the seed robot it receives a message from. 
* Sensors within both communication ranges can describe their position (x,y) as a function of their distance to both seed robots. 
* On following passes each sensor uses a multilateration procedure to combine the distance from all the seeds to produce its own position
* Two approaches were used for the multilateration algorithm, using smoothed and standard coordinates. 

### Results 
Results are the 4 pictures: 
1.Rectangular lattice
2.Rectangular lattice smoothed
3.Hexagonal lattice
4.Hexagonal lattice smoothed

