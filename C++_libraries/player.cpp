#include "player.h"

Player::Player() : Player(0, 0, 'p', 'W', 'A', 'S', 'D') {}

Player::Player(int x_pos, int y_pos, char token, char up_ctr, char right_ctr, char down_ctr, char left_ctr){
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->last_door_x_pos = this->x_pos;
    this->last_door_y_pos = this->y_pos;
    this->token = token;
    this->up_ctr = up_ctr;
    this->right_ctr = right_ctr;
    this->down_ctr = down_ctr;
    this->left_ctr = left_ctr;   
    this->is_active = false;
}

//getters
int Player::getXPos() const {
    return this->x_pos;
}

int Player::getYPos() const {
    return this->y_pos;
}

char Player::getToken() const {
    return this->token;
}

char Player::getUpCtr() const {
    return this->up_ctr;
}

char Player:: getRightCtr() const{
    return this -> right_ctr;
}

char Player:: getDownCtr() const{
    return this -> down_ctr;
}

char Player:: getLeftCtr() const{
    return this -> left_ctr;
}

bool Player::isActive() const{
    return this -> is_active;
}

int Player::getLastDoorXPos() const{
    return this->last_door_x_pos;
}

int Player::getLastDoorYPos() const{
    return this->last_door_y_pos;
}

//setters
void Player::setPos(int new_x_pos, int new_y_pos){
    this -> x_pos = new_x_pos;
    this -> y_pos = new_y_pos;
};

void Player::setLastDoorPos(int new_last_door_x_pos, int new_last_door_y_pos){
    this -> last_door_x_pos = new_last_door_x_pos; //spawn x location based off of most recent passed through door x location 
    this -> last_door_y_pos = new_last_door_y_pos; //spawn y location based off of most recent pass through door y location   
}

void Player:: setToken(char new_token){
    this -> token = new_token;
};

void Player :: toggleActivate(){
    this->is_active = !this->is_active;
}

Player& Player::operator=(const Player & other){
    this -> x_pos = other.x_pos; 
    this -> y_pos = other.y_pos;
    this -> last_door_x_pos = other.last_door_x_pos;
    this -> last_door_y_pos = other.last_door_y_pos;
    this -> token = other.token;
    this -> up_ctr = other.up_ctr;
    this -> right_ctr = other.right_ctr;
    this -> down_ctr = other.down_ctr;
    this -> left_ctr = other.left_ctr;
    return *this;
};