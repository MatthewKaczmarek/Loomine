#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <utility>
#include "..\C++_libraries\consInteraction.h"
#include "..\C++_libraries\map.h"
#include "..\C++_libraries\player.h"
#include "..\C++_libraries\enemy.h"

//instantiation of a game object
class Game {
    private:
        int speed; //refresh rate of the displayed grid in ms
        int cur_map;
        bool game_over;
        vector<Player> game_players; //used to store multiple players within the game
        vector<Map> game_maps; //used to store multiple maps within the game

        //takes in a player index and a direction to move a player across the 2D grid
        void movePlayer(int plr_ind, char dir);
        
        //sets the move direction and calls move player 
        void movePlayerUp(int plr_ind);
        void movePlayerRight(int plr_ind);
        void movePlayerDown(int plr_ind);
        void movePlayerLeft(int plr_ind);

        //updates the tokens and positions of the enemy objects on the printed 2D grid
        void moveEnemies();
        
        //sets the direction for an enemies movement to chase the closest player 
        char getEnemyMoveDirection(Enemy e);
        //calculates the distances of every player from an enemy
        int getDistance(int new_enemy_x, int new_enemy_y, Player p);
        //determines the closest player to the enemy 
        char minDistanceDirection(vector<pair<int,char>> directions);
        //makes sure the enemy is moving into a position on the grid
        bool validEnemyPos(Enemy e, char dir);

        //checks if a player is in contact with an enemy
        void handleEnemyPlayerContact();
        //pops the a player from the player stack when in contact with an enemy 
        void removePlayer(int plr_index);

        //displays the grid and all of its object to the terminal 
        void printGrid();
        //loops to see if there is a user input to update a player token on the grid
        void detectInput();
        //initialization error checks 
        void checkPlayerOutOfBoundsSpawn() const;

        void checkValidDoorLocations();

        void checkValidEnemySpawn();

        void checkMapAndPlayerExistence();

        void checkGameCreationErrors();
    public:
        //constructors
        Game();
        Game(int speed);
        
        //adds a map object to the vector of map objects
        void addMap(Map new_map);
        //adds a player object to the vector of player objects
        void addPlayer(Player new_player);

        //refreshes what the print grid function will display
        void updateMap();
        void spawnPlayers();
        bool checkAnyActive() const;
        void checkDoors();
        void gameLoop();

        Game& operator=(Game & other);
};

#endif