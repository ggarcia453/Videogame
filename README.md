# Introduction
This is the Github repository for the maze videogame developed by me as a side project. As the name implies, 
it is a videogame where you, the player, must traverse through various levels of a maze and escape. 
Currently, this project is still under development. 

# Overview of Files
This section gives a brief runthrough of the files content. More sophiscated documentation will be available in each file. 
## Constants.hpp
Constants and Enums used across different files. 

## Items.hpp/Items.cpp
Code related to Items class. Items will be displayed on screen and the player should collect them to move on to
the next level. 

## Player.hpp/Player.cpp
Code related to Player class. This handles all things related to the playable character including initialization, player movement and other player related functions. 

## Settings.hpp/Settings.cpp 
Code related to Settings class. THe Settings hadnles all settings for the game and can be customized by the user via the questions/settings screen. 

## main.cpp
The main driver code for the program. 

## Test Folder
Code related to background tests I developed. These help ensure all of the parts are working properly. 

# Future Plans
1. Items to grab on maze to advance levels. 
2. Future levels
3. Background changes + more sophiscated sprites. 

# Steps to reproduce
To reproduce this work wou will need the following:
1. C++ Compiler (This project uses GCC)
2. [SFML Dev libraries installed ](https://www.sfml-dev.org/index.php)
3. Gtest (To run the tests in the test directory )
Then you can folllow the steps as below using unix Make Files
```bash
git clone https://github.com/ggarcia453/Videogame
cd Videogame/
mkdir build
cd build
cmake ../
make
```