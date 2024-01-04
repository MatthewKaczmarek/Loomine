#include "door.h"

Door::Door() : Door(0, 0, '#') {}

//setting the spawn point and token to the passed in parameters from the top level language
Door::Door(int x_pos, int y_pos, char token){
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->token = token;
}

//getters
int Door::getXPos() const{
    return this->x_pos;
}

int Door::getYPos() const{
    return this->y_pos;
}

char Door::getToken() const{
    return this->token;
}