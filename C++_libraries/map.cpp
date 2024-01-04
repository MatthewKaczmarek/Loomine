#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include "map.h"

#include "consInteraction.h"
#include "windows.h"


void Map::createNewMap(int num_rows, int num_cols){
    //create our char grid to print
    grid.clear();
    grid.assign(num_rows, vector<char>());
    for(int i = 0; i < num_rows; i++){
        grid[i].assign(num_cols, this->inner);
    }
}

//error check 
void Map::checkLegalMapDimensions(int num_rows, int num_cols) const{
    if (num_rows <= 0 || num_cols <= 0){
        setTextColor(4);
        throw invalid_argument("Error: Attempted to initialize map with 0 or less rows or 0 or less columns!");
    }
}

//error check 
void Map::checkEntityOutOfBoundsSpawn(int x_pos, int y_pos, char token) const{
    if (x_pos < 0 || x_pos >= this->grid[0].size() || 
    y_pos < 0 || y_pos >= this->grid.size()){
        setTextColor(4);
        throw invalid_argument("Error: Attempted to add entity (Door or Enemy) with token '" + string(1, token) + "' outside the bounds of map!");
    }
}

Map::Map() : Map(10, 10, 'x', '*') {}
Map::Map(int num_rows, int num_cols, char inner, char border){
    this->checkLegalMapDimensions(num_rows, num_cols);
    this->inner = inner;
    this->border = border;
    createNewMap(num_rows, num_cols);
}

void Map::setNumRowsCols(int row, int col){
    // set number of rows in the grid
    grid.resize(row);
    // for each row in grid, set column size
    for(int i = 0; i < row; i++){
        grid[i].resize(col);
    }
}

//getters
int Map::getNumRows() const {
    return grid.size();
}

int Map::getNumCols() const {
    return grid[0].size();
}

// adds
void Map::addDoor(Door new_door){
    this->checkEntityOutOfBoundsSpawn(new_door.getXPos(), new_door.getYPos(), new_door.getToken()); //error check
    this->doors.push_back(new_door);
    this->grid[new_door.getYPos()][new_door.getXPos()] = new_door.getToken();//places the door token within the 2D vector grid
}

void Map::addEnemy(Enemy new_enemy){
    this->checkEntityOutOfBoundsSpawn(new_enemy.getXPos(), new_enemy.getYPos(), new_enemy.getToken()); //error check
    this->enemies.push_back(new_enemy);
    this->grid[new_enemy.getYPos()][new_enemy.getXPos()] = new_enemy.getToken();//places an enemy token within the 2D grid
}

//more getters
char Map::getBkndChar() const{
    return this->inner;
}

char Map::getBorderChar() const {
    return this->border;
}

vector<Door>& Map::getDoors() {
    return this->doors;
}

vector<Enemy>& Map::getEnemies(){
    return this-> enemies;
}

Map& Map::operator=(const Map & other){
    this->grid = other.grid;
    this->inner = other.inner;
    this->border = other.border;
    this->doors = other.doors;
    this->enemies = other.enemies;
    return *this;
}

vector<char>& Map::operator[](int index) {
    return this->grid[index];
}

int Map::size() const {
    return this->grid.size();
}