# AI Game Development

In this Unreal Engine 5 project, I am diving deep into the world of AI programming for enemies. As I craft and fine-tune their behaviors, this project is to push the boundaries of my knowledge and skills in game development. 
With each new enemy AI that I create and add to my collection, I am not only showcasing my expertise in AI programming but also expanding my capabilities in creating immersive and challenging gameplay experiences.

# MassAI:
A simple AI that follows the player and attacks him when it is in range to the player.

  ### Follow Player 
  A simple movement to the player with a smooting function.
  ### Avoidance
  Is integrated in the FollowPlayer where each entity pushes itself away if they get too close to each other. 
  ### Jump/Attack 
  When an entity is within jump range, it jumps towards the player and lands behind him.
  ### Visualization
  A custom processor that handles the visualization of the entities and the vertex animation.
  <p align="center">
   <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/MassAI_01.gif" width="45%"/>
   &nbsp; &nbsp;
   <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/MassAI_03.gif" width="45%"/>
  </p>


# Attack Objects
Attack Objects is a easy method for creating and executing attacks or actions.
An object is created that exists in the background and contains information for the desired attack/action and is deleted after execution. This makes it easy to create attacks or actions which are then be executed by the enemy and each attack/action is separated from one another, making the addition of new attacks/actions more organized.

 ### Creation
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/CreateAttackObj.gif" width="50%" height="50%"/>

 Example of information and scripts in an attack object:
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/AttackObj_01.PNG" width="85%" height="85%"/>
 
 ### Assign
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/AssignAttackObj.gif" width="50%" height="50%"/>
 
 ### Attack Execute
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/ExecuteAttackObj.gif" width="50%" height="50%"/>

 
# Currupted Raccoon

## Boss Entrance
A start sequence that is activated when entering the boss arena that starts the boss fight

<img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/BossAI_Entrance.gif" width="85%" height="85%"/>

## Attacks

 ### Simple Attacks
 Simple bite and claw attacks that are combined and executed rapidly by the boss
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/BossAI_Attack_Simple_01.gif" width="85%" height="85%"/>
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/BossAI_Attack_Simple_02.gif" width="85%" height="85%"/>
 
 ### Delayed Attack
 An attack that is delayed by the boss to disorient the player
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/BossAI_Attack_Delay.gif" width="85%" height="85%"/>
 
 ### Stumper Attack
 An environmental attack that deals damage to everything within a radius of the boss
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/BossAI_Attack_Stumper.gif" width="85%" height="85%"/>
 
 ### Roll Attack
 An attack that is added in the second phase (below 50 % boss life) in which the boss first jumps upwards and disappears from sight, only to deal major damage to the player after a short time with a roll attack. During this attack, the player is warned which side the attack is coming from (indicated by a red pulse effect in the HUD).
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/BossAI_RollAttack.gif" width="85%" height="85%"/>
 
## Player Action Reading and Player Punishment
The boss can read certain actions of the player and then execute counter attacks to punish the player. In this case, the boss only reads whether the player is healing, which means that badly timed heals are punished (the boss has a 50% chance of performing a counterattack).

<img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/BossAI_PunishAttack.gif" width="85%" height="85%"/>

## Boss Stunn
The Guard mechanic already implemented in SpearFighter was also used here, where the boss's guard breaks and he cannot move for a short time.

<img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/BossAI_Stunn.gif" width="85%" height="85%"/>

# SpearFighter

## Patrolling
Patrolling is pretty simple, the enemy moves to each PatrolPoint, waits there for a while and then moves on to the next one. In order to create a **PatrolPath**, you have to drag the blueprint **BP_EnemyPatrolPath** into the level and then you can add an array of vectors in the details panel, where for each new element a **Gizmo** is added, allowing you to set the respective **PatrolPoint Location**.

 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/LanceFighterGIF-Pathfollowing.gif" width="85%" height="85%"/>
 
## Defense
 ### Guard Buildup
 The **Guard** is the enemy's **Defense Stamina**, which is built up when the enemy blocks attacks from the player. This bar is shown as a yellow outline around the enemy's life bar and is also reduced again if the player does not attack the enemy for a longer   period of time.
 ### Guard Break
 If the Guard bar is fully built up, the enemy's defense breaks, resulting in the opponent being stunned for a short time and losing life.
 
 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/LanceFighterGIF-GuardBuildUpAndBreake.gif" width="85%" height="85%"/>
 
## Attacks

### 1. Spear Thrust
The Spear Thrust Attack, where the enemy rushes towards the player and damages the player when it hits him, is used to prevent the player from running away from the enemy so easily.
This attack is only executed by the enemy when he is far away from the player.

 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/LanceFighterGIF-Thrust.gif" width="85%" height="85%"/>

### 2. Windblade Projectile Attack
The WindBlade Projectile Attack, in which the enemy shoots a projectile towards the player, is executed when the enemy is not too close to the player or after the enemy blocks an attack from the player and then dashes backwards to get distance to the player. The player can then dodge or block this attack.  

 <img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/LanceFighterGIF-Windblade.gif" width="85%" height="85%"/>

### 3. Close Combat Attacks
The close combat attacks consist of 3 different fast attacks, where each attack has its own percentage probability of being executed. These probabilities are set in the corresponding enemy blueprint (e.g. BP_LanceFighter).  

### Attack 1
<img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/LanceFighterGIF-CombatAttack1.gif" width="85%" height="85%"/>
### Attack 2
<img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/LanceFighterGIF-CombatAttack2.gif" width="85%" height="85%"/>
### Attack 3
<img src="https://github.com/Almin-B/Boss_AI/blob/main/AI_Gifs/LanceFighterGIF-CombatAttack3.gif" width="85%" height="85%"/>
