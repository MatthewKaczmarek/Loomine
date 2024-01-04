#ifndef DOOR_H
#define DOOR_H

//instantiation for a door object
//these are used points on a map to progress to new map
class Door {
    private:
        //spawn point (x,y) coords
        int x_pos;
        int y_pos;
        //displayed token
        char token;
    public:
        Door();
        //argumented constructor 
        Door(int x_pos, int y_pos, char token);

        //getters 
        int getXPos() const;
        int getYPos() const;
        char getToken() const;
};

#endif