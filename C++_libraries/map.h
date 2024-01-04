#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include "door.h"
#include "enemy.h"

using namespace std;


class Map{
    private:
        //initializing a 2D vector to graphically represent a cartesian plane
        vector<vector<char>> grid;
        //allowing multiple doors to be added to a map
        vector<Door> doors;
        //allowing multiple enemies to be added to a map
        vector<Enemy> enemies;
        //inner map symbol
        char inner;
        //border mao symbol
        char border;

        //fill a 2D vector with the appropriate chars to create graphical map
        void createNewMap(int num_rows, int num_cols);

        //making sure the requested to be generated is plausible 
        void checkLegalMapDimensions(int num_rows, int num_cols) const;
        //making sure no objects are being generated outside the dimensions of the map
        void checkEntityOutOfBoundsSpawn(int x_pos, int y_pos, char token) const;

    public:
        Map();

        //argumented constructor
        Map(int num_rows, int num_cols, char inner, char border);

        //setter
        void setNumRowsCols(int row, int col);

        //used to add door objects to the vector of doors
        void addDoor(Door new_door);

        //used to add enemy objects to the vector of enemies
        void addEnemy(Enemy new_enemy);

        //getters
        int getNumRows() const;
        int getNumCols() const;
        char getBkndChar() const;
        char getBorderChar() const;
        vector<Door>& getDoors();
        vector<Enemy>& getEnemies();

        Map& operator=(const Map & other);
        vector<char>& operator[](int index);
        
        int size() const;
};
#endif