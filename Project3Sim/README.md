---
### File Information
kilobot.cpp and setup.cpp were written from scratch to create a flock of 10 to 100 robots which show heading agreement.
Starter code for the simulation was offered by professor, I altered main.cpp as well for the purpose of the simulation

### Goal and achievements
The aim of the simulation is to create a flock of 10 to 100 robots which show good heading agreement. Starting from random positions and orientations. The communication range and rate of the robots is fixed from the start.
A central light source is used as a migrating point for the robots to flock around. The final aimis to have the flock migrating around the central point keeping good heading agreement between each other. 

### Approach
* Robots are randomly seeded within the 2-dimensional grid 
* Each robot is subject to 4 forces: migration, cohesion, alignment and separation within their communication range.  
* Alignment: mean velocity of all robots within communication range. This vector is normalized and given a weight of 0.9
* Cohesion: vector pointing towards the center of mass of all robots within communication range and assigned a weight of 0.001.
* Separation: at each timestep every individual robot measures the distance to the closest robot within its communication range. A repulsion vector is generated, inverseley proportional to the measured distance to each robot and in the opposite direction. The resulting vectors are summed, and then normalized and assigned a weight of 4.5. 
* Migration: force vector pointing to the central migration point, scaled by .03. 
* Random walk: at each timestep the robots randomly generate a bearing, a force vector is applied in that direction, this force vector is given a weight of .8.
* General motion: the motion of each robot is a result of the weighted sum of each force vector in terms of bearing and magnitude
* PERFORMANCE: criteria for performance is established as a functions of the relative distance of each robot to each other as well as the relative bearing difference of all robots within the flock. 
* SIMULATION: multiple simulations were run to establish optimal communication parameters along with determining the optimal weight parameters for each force vector

### Further research 
* The basis of flocking was used to re-create results from the paper "Inspiring and Modeling Multi-Robot Search with Particle Swarm Optimization".

