# Segregation based on Brazil nut effect
### Based on paper: “Segregation in Swarms of e-puck Robots Based On the Brazil Nut Effect"
---
### File Information
kilobot.cpp and setup.cpp were written from scratch to sort robots in concentric shells and measure a segregation error-based on section 2.4 of the paper- the measure metric is in main.cpp.
Starter code for the simulation was offered by professor, I altered main.cpp as well for the purpose of the simulation

### Goal and achievements
The aim of the simulation is to sort robots in concentric shells around a central "light source" to mimick the distribution of different sized particles in a bag. In such situations larger particles are distributed on the outside (or top of a bag) and smaller particles will be distributed towards the center (or bottom of a bag). 
Each robot is governed by 3 forces, attraction to the central light source, repulsion from other robots and a random walk. Additionally robots have virtual radiis assigned to them. 
Segregation error is calculated based on the princicple that larger robots should be on the outside of the 2-dimensional grid. If a robot with a larger radius is closer to the center than a robot with a smaller radius, it will contribute to the segregation error and vice versa. 

### Approach
*Robots are randomly seeded in the grid with a given radii. 
*Under the constraint of the 3 forces acting upon them, attractiion, repulsion and random walk. They progressively arrange in the wanted configuration, where smaller robots are on the inside and larger robots are on the outside. 
*Repulsion: each robot assumes that neighbours have the same radius as its own. At each timesteop the robot assesses the angle to each of its neighbours. By taking the weighted sum of all perceived neighbors, it assigns a force vector in the opposite direction of the robots within it vicinity.
*Attraction to the light source: each robot estimates its angle to the light source. At every cycle a force vector, inversely proportional to the robots distance form the center, is applied in the direction of the light source. 
*Random walk: at each timestep the robots randomly generate a bearing, a force vector is applied in that direction
*General motion: the motion of each robot is a result of the weighted sum of each force vector in terms of bearing and magnitude
*Bearing calculations were established by calculating the difference from the observed bearing of a neighbour and their own. 

### Results 
Results are the 3 pictures: 
1. [100 Robots for 1 shell]
2. [100 Robots for 2 shells (50/50)]
3. [210 Robotos for 3 shells (70/70/70)]
