#ifndef PLAYER_H
#define PLAYER_H

//instantiation for a player object
//this will get added to a game object be controlled through keyboard input
class Player {
    private:
        int x_pos;//spawn x location
        int y_pos;//spawn y location
        int last_door_x_pos;//spawn x location when entering a new map
        int last_door_y_pos;//spawn y location when entering a new map
        char token;
        char up_ctr;
        char right_ctr;
        char down_ctr;
        char left_ctr;
        bool is_active;
    public:
        Player();
        //argumented constructor
        Player(int x_pos, int y_pos, char token, char up_ctr, char right_ctr, char down_ctr, char left_ctr);

        //getters
        int getXPos() const;
        int getYPos() const;
        char getToken() const;
        char getUpCtr() const;
        char getRightCtr() const;
        char getDownCtr() const;
        char getLeftCtr() const;
        //checking the status of an activity state flag
        bool isActive() const;
        int getLastDoorXPos() const;
        int getLastDoorYPos() const;

        //setters
        void setPos(int new_x_pos, int new_y_pos);
        void setLastDoorPos(int new_last_door_x_pos, int new_last_door_y_pos);
        void setToken(char new_token);
        //toggles the status of an activity state flag
        void toggleActivate();

        Player& operator=(const Player & other);
};
#endif