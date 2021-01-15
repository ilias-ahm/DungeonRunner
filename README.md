# DungeonRunner
Welcome to DungeonRunner, this is a game where the player does his best in avoiding obstacles and making sure they stay ahead so they can escape from the dungeon.

Configuration:
  WASD Keys to move, changeable in Configuration.h
    W - Speed up (hold)
    S - Slow down (hold)
    A - Move left
    D - Move right
    SPACEBAR - Interact with obstacles (doors will open)
  Player name is "Player" by default, if you like you could change this in Configuration.h
  The screensize is 1000 pixels x 1000 pixels, this is changeable in Configuration.h
  FPS is also changeable but its is recommended to keep it at 60FPS since this may cause some slight anomalies.

Gameplay:\n
  There are obstacles you need to avoid
    - Swords: High velocity, -20points penalty
    - Doors: Static, will take away up to half of your velocity when hit head-on. Opening doors has a 100% chance of opening (interact) and will result in a -50points penalty
  AI:
    - Maxspeed : 10% faster than player
    - Acceleration is also faster
   Scoring system:
    - Hitting other runners will not be penalized 
    - Running into a sword : -20p
    - Opening a door : -50p
    - Finishing 1st place : +100p
    - Finishing 2nd place : +75p
    - Finishing 3rd place : +50
    - Finishing last place : +0p
    Running will bring points over time, you get more points if you're running in first place than if you were running in second place etc,...
 
 Happy running!
