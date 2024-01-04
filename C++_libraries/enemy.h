#ifndef ENEMY_H
#define ENEMY_H

//these used to create objects on the map that can affect the game win state
//they will chase the closest player object and try to remove them from the game
class Enemy{
    private:
        // spawn point (x,y) coords
        int x_pos;
        int y_pos;
        //displayed token
        char token;
        //movement speed in ms
        int speed;
        //counter to stall movement 
        int time_until_move;
    
    public:
        Enemy();
        //arguemented constructor 
        Enemy(int x_pos, int y_pos, char token, int speed);

        //getters 
        int getXPos() const;
        int getYPos() const;
        char getToken() const;
        int getTimeUntilMove() const;

        //stall function to make movement non-instantaneous 
        void tickTime();
        //update position 
        void setPos(int new_x, int new_y);
        Enemy& operator=(const Enemy & other);

};
#endif