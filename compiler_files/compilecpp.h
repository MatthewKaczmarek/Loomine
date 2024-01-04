#include <stdio.h>
#include <stdlib.h>
#include "symbols.h"
#include "prog.h"

char *outfile = "a.cpp";

void addHeader(FILE** cpp) { //printing appropiate headers to the final generated main file 
    fprintf(*cpp, "#include <stack>\n");
    fprintf(*cpp, "#include \"..\\C++_libraries\\consInteraction.cpp\"\n#include \"..\\C++_libraries\\map.cpp\"\n");
    fprintf(*cpp, "#include \"..\\C++_libraries\\player.cpp\"\n#include \"..\\C++_libraries\\game.cpp\"\n");
    fprintf(*cpp, "#include \"..\\C++_libraries\\door.cpp\"\n#include \"..\\C++_libraries\\enemy.cpp\"\nusing namespace std;\n\n");
    fprintf(*cpp, "int main() {\n");
    fprintf(*cpp, "stack<Map> expr_map;\n");
    fprintf(*cpp, "stack<Player> expr_plr;\n");
    fprintf(*cpp, "stack<Game> expr_game;\n");
    fprintf(*cpp, "stack<Door> expr_door;\n");
    fprintf(*cpp, "stack<Enemy> expr_enemy;\n");

    for (int i=0; i<map_symbol_count; i++) { //printing the correct number of map objects
        fprintf(*cpp, "Map %s;\n", map_symboltable[i]->map);
    }
    for (int i=0; i<plr_symbol_count; i++){ //printing the correct number of player objects
        fprintf(*cpp, "Player %s;\n", plr_symboltable[i]->map);
    }
    for (int i=0; i<game_symbol_count; i++) { //printing the correct number of game objects
        fprintf(*cpp, "Game %s;\n", game_symboltable[i]->map);
    }
    for (int i = 0; i<door_symbol_count; i++){ //printing the correct number of door objects 
        fprintf(*cpp, "Door %s;\n", door_symboltable[i]->map);
    }
    for (int i = 0; i<enemy_symbol_count; i++){ //printing the correct number of enemy objects
        fprintf(*cpp, "Enemy %s;\n", enemy_symboltable[i]->map);
    }
    fprintf(*cpp, "\n");
}

//this is used to create a map object based off of the desired parameters
//it takes in a pointer to the current index of the program's command array 
void handleMap(FILE** cpp, int* cur_cmd_ptr){
    *cur_cmd_ptr = ((*cur_cmd_ptr) + 1); // increments the value of that dereferenced pointer by 1
    int index = (*cur_cmd_ptr); // used to hold the de referenced pointer value 
    //variables need to construct a map object
    int num_parameters = 4;
    int num_columns;
    int num_rows;
    char inner_char;
    char border_char;
    for (int i = index; i < index + num_parameters; i++){ //making sure all of of the parameters get assigned to a usable value from char
        switch(program[i].code){
            case Map_Column: num_columns = atoi(program[i].data); break; // converting the char num value of columns to an int
            case Map_Row: num_rows = atoi(program[i].data); break;  // converting the char num value of rows to an int
            case Map_Inner: inner_char = (program[i].data[1]); break;
            case Map_Border: border_char = (program[i].data[1]); break;
        }
    } // passing in the now usable parameters to the map constructor and printing it in the final main in a.cpp
    fprintf(*cpp, "{Map m = Map(%i, %i, '%c', '%c');\n", num_rows, num_columns, inner_char, border_char);
    fprintf(*cpp, "expr_map.push(m);}\n"); //pushing the object onto a stack of maps 
    *cur_cmd_ptr = ((*cur_cmd_ptr) + num_parameters); //incrementing the index of the program array to account for commands called in the function
}

//this is used to create a player object based off of the desired parameters
//it takes in a pointer to the current index of the program's command array 
void handlePlayer(FILE** cpp, int* cur_cmd_ptr){ 
    *cur_cmd_ptr = ((*cur_cmd_ptr) + 1); // increments the value of that dereferenced pointer by 1
    int index = (*cur_cmd_ptr);// used to hold the de referenced pointer value 
    //variables need to construct a player object 
    int num_parameters = 7;
    int x_pos;
    int y_pos;
    char token_char;
    char up_ctr_char;
    char right_ctr_char;
    char down_ctr_char;
    char left_ctr_char;
    for (int i = index; i < index + num_parameters; i++){ //making sure all of the variables get assigned to a usable value from char
        switch(program[i].code){
            case Plr_X_Pos: x_pos = atoi(program[i].data); break; //converting the char value of xpos to an int
            case Plr_Y_Pos: y_pos = atoi(program[i].data); break; //converting the char value of ypos to an int
            case Plr_Token: token_char = (program[i].data[1]); break;
            case Plr_Up_Ctr: up_ctr_char = (program[i].data[1]); break;
            case Plr_Right_Ctr: right_ctr_char = (program[i].data[1]); break;
            case Plr_Down_Ctr: down_ctr_char = (program[i].data[1]); break;
            case Plr_Left_Ctr: left_ctr_char = (program[i].data[1]); break;
        }
    }
    // passing in the now usable parameters to the player constructor and printing it in the final main in a.cpp
    fprintf(*cpp, "{Player p = Player(%i, %i, '%c', '%c', '%c', '%c', '%c');\n", x_pos, y_pos, token_char, up_ctr_char, right_ctr_char, down_ctr_char, left_ctr_char);
    fprintf(*cpp, "expr_plr.push(p);}\n"); //pushing the object on the stack of players 
    *cur_cmd_ptr = ((*cur_cmd_ptr) + num_parameters);
}

//this is used to create a door object based off of the desired parameters
//it takes in a pointer to the current index of the program's command array 
void handleDoor(FILE ** cpp, int* cur_cmd_ptr){
    *cur_cmd_ptr = ((*cur_cmd_ptr) + 1); // increments the value of that dereferenced pointer by 1
    int index = (*cur_cmd_ptr);
    // variables required to create a door object 
    int num_parameters = 3;
    int x_pos;
    int y_pos;
    char token_char;
    for (int i = index; i < index + num_parameters; i++){ //making sure all of the variables get assigned to a usable value from char
        switch(program[i].code){
            case Door_X_Pos: x_pos = atoi(program[i].data); break; // converting the door xpos from a char to an int
            case Door_Y_Pos: y_pos = atoi(program[i].data); break; // converting the door ypos from a char to an int
            case Door_Token: token_char = (program[i].data[1]); break;
        }
    }

    // passing in the now usable parameters to the door constructor and printing it in the final main in a.cpp
    fprintf(*cpp, "{Door d = Door(%i, %i, '%c');\n", x_pos, y_pos, token_char);
    fprintf(*cpp, "expr_door.push(d);}\n"); // pushing the object onto a stack of doors
    *cur_cmd_ptr = ((*cur_cmd_ptr) + num_parameters);
}

//this is used to create an enemy object based off of the desired parameters
//it takes in a pointer to the current index of the program's command array 
void handleEnemy(FILE ** cpp, int* cur_cmd_ptr){
    *cur_cmd_ptr = ((*cur_cmd_ptr) + 1); // increments the value of that dereferenced pointer by 1
    int index = (*cur_cmd_ptr);
    //variables need to make an enemy object
    int num_parameters = 4;
    int x_pos;
    int y_pos;
    char token_char;
    int speed;
    for (int i = index; i < index + num_parameters; i++){//making sure all of the variables get assigned to a usable value from char
        switch(program[i].code){
            case Enemy_X_Pos: x_pos = atoi(program[i].data); break; //converting the enemy xpos from a char to an int
            case Enemy_Y_Pos: y_pos = atoi(program[i].data); break; //converting the enemy ypos from a char to an int
            case Enemy_Token: token_char = (program[i].data[1]); break;
            case Enemy_Speed: speed = atoi(program[i].data); break; //converting the enemy speed from a char to an int
        }
    }
    // passing in the now usable parameters to the enemy constructor and printing it in the final main in a.cpp
    fprintf(*cpp, "{Enemy e = Enemy(%i, %i, '%c', %i);\n", x_pos, y_pos, token_char, speed);
    fprintf(*cpp, "expr_enemy.push(e);}\n");
    *cur_cmd_ptr = ((*cur_cmd_ptr) + num_parameters);
}

//adding a map object to a game object via pulling and popping from the game and map stacks 
void handleAddMap(FILE** cpp) {
    fprintf(*cpp, "{/*Get Game*/\n Game left = expr_game.top(); expr_game.pop();\n");
    fprintf(*cpp, "/*Get Map*/\n Map right = expr_map.top(); expr_map.pop();\n");
    fprintf(*cpp, "/*Add Map to Game*/\n left.addMap(right);\n");
    fprintf(*cpp, "/*Push Map onto stack*/\n expr_game.push(left);\n}");
}

//adding a player object to a game object via pulling and popping from the game and player stacks 
void handleAddPlr(FILE** cpp) {
    fprintf(*cpp, "{/*Get Game*/\n Game left = expr_game.top(); expr_game.pop();\n");
    fprintf(*cpp, "/*Get Player*/\n Player right = expr_plr.top(); expr_plr.pop();\n");
    fprintf(*cpp, "/*Add Player to Game*/\n left.addPlayer(right);\n");
    fprintf(*cpp, "/*Push Player onto stack*/\n expr_game.push(left);\n}");
}

//adding a door object to a map object via pulling and popping from the map and door stacks 
void handleAddDoor(FILE** cpp) {
    fprintf(*cpp, "{/*Get Map*/\n Map left = expr_map.top(); expr_map.pop();\n");
    fprintf(*cpp, "/*Get Door*/\n Door right = expr_door.top(); expr_door.pop();\n");
    fprintf(*cpp, "/*Add Door to Map*/\n left.addDoor(right);\n");
    fprintf(*cpp, "/*Push Door onto stack*/\n expr_map.push(left);\n}");
}

//adding an enemy object to a map object via pulling and popping from the map and enemy stacks 
void handleAddEnemy(FILE** cpp){
    fprintf(*cpp, "{/*Get Map*/\n Map left = expr_map.top(); expr_map.pop();\n");
    fprintf(*cpp, "/*Get Enemy*/\n Enemy right = expr_enemy.top(); expr_enemy.pop();\n");
    fprintf(*cpp, "/*Add Enemy to Map*/\n left.addEnemy(right);\n");
    fprintf(*cpp, "/*Push Enemy onto stack*/\n expr_map.push(left);\n}");
}
//calls the run game function to start a game session
void handleRunGame(FILE** cpp) {
    fprintf(*cpp, "{/*Get Game*/\n Game left = expr_game.top(); expr_game.pop();\n");
    fprintf(*cpp, "/*Run Game*/\n left.gameLoop();\n}");
}

//this is used to process the clause for every command pushed onto the program command array
void addProgram(FILE** cpp) {
    int cur_cmd = 0; //index for parsing the command array
    int* cur_cmd_ptr = &cur_cmd; // pointer to that index
    while(cur_cmd < cmds) { // while there are still commands left to be handled 
        switch(program[cur_cmd].code) {
            //initializes every variable that needs to be created from the symbol tables then increments the current command index by 1
            case PushGameId: fprintf(*cpp, "/*Push game id*/\nexpr_game.push(%s);\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            case PushMapId: fprintf(*cpp,"/*Push map id*/\nexpr_map.push(%s);\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            case PushPlrId: fprintf(*cpp, "/*Push player id*/\nexpr_plr.push(%s);\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            case PushDoorId: fprintf(*cpp, "/*Push door id*/\nexpr_door.push(%s);\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            case PushEnemyId: fprintf(*cpp, "/*Push enemy id*/\nexpr_enemy.push(%s);\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            //initializes every object that needs to be created and assigns them to a generated variable 
            case AssignMap: fprintf(*cpp, "/*Assign Map*/\n%s = expr_map.top(); expr_map.pop();\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            case AssignPlr: fprintf(*cpp, "/*Assign Player*/\n%s = expr_plr.top(); expr_plr.pop();\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            case AssignGame: fprintf(*cpp, "/*Assign Game*/\n%s = expr_game.top(); expr_game.pop();\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            case AssignDoor: fprintf(*cpp, "/*Assign Door*/\n%s = expr_door.top(); expr_door.pop();\n", program[cur_cmd].data); cur_cmd = cur_cmd + 1; break;
            case AssignEnemy: fprintf(*cpp, "/*Assign Enemy*/\n%s = expr_enemy.top(); expr_enemy.pop();\n", program[cur_cmd].data); cur_cmd= cur_cmd + 1; break;
            //calls the appropriate handle function to generate objects from the top level language 
            case Map: handleMap(cpp, cur_cmd_ptr); break;
            case Player: handlePlayer(cpp, cur_cmd_ptr); break;
            case Door: handleDoor(cpp, cur_cmd_ptr); break;
            case Enemy: handleEnemy(cpp, cur_cmd_ptr); break;
            case Game: int speed = atoi(program[cur_cmd].data); fprintf(*cpp, "{Game g = Game(%i);\n", speed); fprintf(*cpp, "expr_game.push(g);}\n"); cur_cmd = cur_cmd + 1; break;
            //calls the appropriate handleAdd function to add generated objects to their respective objects i.e players get added to games and doors get added to maps 
            case AddMap: handleAddMap(cpp); cur_cmd = cur_cmd + 1; break;
            case AddPlr: handleAddPlr(cpp); cur_cmd = cur_cmd + 1; break;
            case AddDoor: handleAddDoor(cpp); cur_cmd = cur_cmd + 1; break;
            case AddEnemy: handleAddEnemy(cpp); cur_cmd = cur_cmd +1; break;
            case Run: handleRunGame(cpp); cur_cmd = cur_cmd + 1; break;
            default: printf("Unknown command: %d\n", program[cur_cmd].code); break;
        }
    }
}

void addFooter(FILE** cpp) {
    fprintf(*cpp, "}\n");
}

//builds the a.cpp file to run 
void compileCPP() {
    FILE* cpp = fopen(outfile, "w");
    addHeader(&cpp);
    addProgram(&cpp);
    addFooter(&cpp);
    fclose(cpp);
}