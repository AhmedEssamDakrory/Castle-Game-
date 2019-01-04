                                                      
                                                               (GAME Description)  


 Back to the Middle Ages, assume you are the liege of a castle that is protected by 4 towers where every tower is required to protect a certain region . every day some enemies attack the castle and they want to destroy your towers. You need to use your programming skills and knowledge to data structures to write a simulation program of a game between your castle towers and enemies. You should simulate the war between the towers and the attacking enemies then calculate some statistics from this simulation.



                                                               Problem description
*********************************************************************************************************************************************

 Four towers are defending the castle. Each tower guards one region and can shoot only enemies in its region. Each tower has a starting health and can shoot at most N enemies at each time step.
Your system (your program) will receive the information of a list of enemies as input from an input file. This list represents the scenario to be simulated. For each enemy the system will receive the following information:

- Arrival Time stamp (Enemy Arrival Time): When the enemy arrives.
- Health: The starting health of the enemy.
- Fire Power: The shot hit power of the enemy.
- Reload Period: Time for an enemy to reload its weapon. During reload period, an enemy cannot fight but can move. After each attack time, the enemy have to wait the reload period to be able to attack again.
- Type: Three types of enemies: paver, fighter and shielded fighter
- Region: The attack region of the enemy.

*********************************************************************************************************************************************                                                     
                                                           Simulation Approach & Assumptions


You will use incremental time simulation. You will divide the time into discrete time steps of 1 time unit each and simulate the changes in the system in each time step.
Some Definitions and formulas
• Enemy State:
At any time, an enemy should be in one of three states: inactive (not arrived yet), active (described below) or killed (health = 0). Only active enemies can fight.
• Active Enemy is an enemy with Arrival Time = current time step & Health > 0.
At each time step, each tower should choose N active enemies to shoot (N is given in the input file).
• Enemy distance is the horizontal distance between the enemy and the tower of its region. All enemies start at 60 meters distance from the castle. The minimum possible distance for any enemy to approach to the tower is 2 meters. After that it may fight but not move.
• Attack Time is the time step before each reload period. The attack time of any type of enemies (including pavers) starts at the same time step of their arrival. Then, they will wait the reload time without attacking. After that they will attack in the next time step then wait the reload and so on.
? For example, Enemy e1 (arrival time = 5, reload period = 3) will attack at time step 5 then wait without attacking at time steps: 6, 7 and 8 then it will attack at time step 9 then wait and so on.
• Paver Enemy
All enemies can approach the castle one meter at every time step only if the next meter is paved. At the start of the simulation, the last 30 meters in the way to the castle (the 30 meters nearest to the tower of each region) are not paved. Only paver enemies can enter the unpaved distance (only in their attack time) to pave it so that enemies of other types can enter this paved distance later in the next time steps. Here are some notes about pavers:
? A paver does not shoot the towers. It only paves. Its “Fire Power” represents the number of meters it can pave (and move) at each allowed attack time step (not reload time).
? In the “attack time”, in addition to moving, fighters and shielded fighters shoot the tower but pavers pave.
? The enemies can approach to the castle one paved meter at every time step. This includes paver enemies during their reload period.
? During the attack time of the paver (not in the reload period), the paver can approach to the castle number of meters equal to its fire power regardless of being in a paved or not paved area.