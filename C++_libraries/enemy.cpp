#include "enemy.h"

Enemy::Enemy() : Enemy(0, 0, 'M', 10) {}
//setting the spawn point token and speed 
Enemy::Enemy(int x_pos, int y_pos, char token, int speed) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->token = token;
    this->speed = speed;
    this->time_until_move = speed;   
}

//getters
int Enemy::getXPos() const{
    return this->x_pos;
}

int Enemy::getYPos() const{
    return this->y_pos;
}

char Enemy::getToken() const{
    return this->token;
}

int Enemy::getTimeUntilMove() const {
    return this->time_until_move;
}

//checks to see if it is time to move based off a decrementing variable 
//every time time_until move decrements to 0 the enemy will move 
void Enemy::tickTime() {
    if(this->time_until_move <= 0) {
        this->time_until_move = this->speed; //resetting the count
    }
    else{
        this->time_until_move--;
    }
}

//updating the objects position on the screen
void Enemy::setPos(int new_x, int new_y){
    this -> x_pos = new_x;
    this -> y_pos = new_y;
}

Enemy& Enemy:: operator=(const Enemy & other){
    this-> x_pos = other.x_pos;
    this -> y_pos = other.y_pos;
    this -> token = other.token;
    this -> speed = other.speed;
    this -> time_until_move = other.time_until_move;    
    return *this;
}