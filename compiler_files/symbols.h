#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog.h"

typedef struct {
    char* map; // ADDITION: Added map string, will be outputted to new .cpp instead of name (since name could be a C++ key word)
    char* name;
} Symbol;

//initializing a symbol index to parse a symbol table for Map objects generated 
int map_symbol_count = 0;
//initializing am array of type symbol to act as a symbol table for Map objects
Symbol* map_symboltable[100];

//initializing a symbol index to parse a symbol table for Player objects generated
int plr_symbol_count = 0;
//initializing am array of type symbol to act as a symbol table for Player objects
Symbol* plr_symboltable[100];

//initializing a symbol index to parse a symbol table for Game objects generated
int game_symbol_count = 0;
//initializing am array of type symbol to act as a symbol Game for Map objects
Symbol* game_symboltable[100];

//initializing a symbol index to parse a symbol table for Door objects generated
int door_symbol_count = 0;
//initializing am array of type symbol to act as a symbol table for Door objects
Symbol* door_symboltable[100];

//initializing a symbol index to parse a symbol table for Enemy objects generated
int enemy_symbol_count = 0;
//initializing am array of type symbol to act as a symbol table for Enemy objects
Symbol* enemy_symboltable[100];

// this is used to see at which index in each symbol is there an open slot for new symbol to be stored in
//returns 
Symbol* getSymbol(char* s, ProgCode code) {
    if (code == AssignMap){ // case for assigning a symbol to a map 
        for (int i=0; i<map_symbol_count; i++) {
            if (strcmp(map_symboltable[i]->name, s) == 0) // hit open index 
                return map_symboltable[i];
        }
    }
    else if (code == AssignPlr){ //case for assigning a symbol to a player 
        for (int i=0; i<plr_symbol_count; i++) {
            if (strcmp(plr_symboltable[i]->name, s) == 0) // hit open index
                return plr_symboltable[i];
        }
    }
    else if (code == AssignGame){ //case for assigning a symbol to a game 
        for (int i=0; i<game_symbol_count; i++){ 
            if (strcmp(game_symboltable[i]->name, s) == 0) // hit open index
                return game_symboltable[i];
        }
    }
    else if (code == AssignDoor){ // case for assigning a symbol to a door
        for( int i = 0; i < door_symbol_count; i++){
            if (strcmp(door_symboltable[i]->name, s) == 0) // hit open index
                return door_symboltable[i];
        }
    }
    else if (code == AssignEnemy){ // case for assigning a symbol to an enemy 
        for(int i = 0; i < enemy_symbol_count; i++){
            if(strcmp(enemy_symboltable[i]->name, s) == 0) // hit open index
                return enemy_symboltable[i];
        }
    }
    return NULL;
}

//this is used to make sure no two objects are assigned the same symbol
// then places a the new symbol in the correct symbol table and increments its count
// returns the newly created symbol and is then called in assign symbol to be assigned to the correct object 
Symbol* checkSymbol(char* s, ProgCode code) {
    Symbol* symbol = getSymbol(s, code); // assigning a new symbol object to the correct symbol type for the parameters passed in
    if (symbol == NULL) {
        char buffer[256];
        char src[256];
        strcpy(src, "x");
        itoa(map_symbol_count + plr_symbol_count + game_symbol_count + door_symbol_count + enemy_symbol_count, buffer, 10);
        symbol = (Symbol*) malloc(sizeof(Symbol));
        symbol->name = (char*)strdup(s);
        symbol->map = (char*)strdup(strcat(src, buffer)); // ADDITION: This line (and the added lines above it) creates a new string saved in map
                                                          // that will be added to the cpp (name is 'x' followed by symbolcount so that every map is unique
                                                          // and compliant with C++ identifier naming rules) 
        if(code == AssignMap){ // if the passed new symbol is of type map 
            map_symboltable[map_symbol_count++] = symbol; // placing the new symbol into the next open index of the symbol table 
        }
        else if(code == AssignPlr){ // if the new symbol is of type player
            plr_symboltable[plr_symbol_count++] = symbol;
        }
        else if(code == AssignGame){ // if the new symbol is of type game 
            game_symboltable[game_symbol_count++] = symbol;
        }
        else if(code == AssignDoor) { // if the new symbol is of type door 
            door_symboltable[door_symbol_count++] = symbol;
        }
        else if(code == AssignEnemy) { // if the new symbol is of type enemy 
            enemy_symboltable[enemy_symbol_count++] = symbol;
        }
    }
    return symbol;
}

// this is used to free up all of the allocated memory used to create the symbol tables and objects 
// to be called at the very end of main 
void cleanupSymbols() {
    for (int i = 0; i < map_symbol_count; i++) { //freeing map symbols 
        free(map_symboltable[i]->name);
        free(map_symboltable[i]->map); // ADDITION: Deallocating space reserved for map
    }
    for (int i = 0; i < plr_symbol_count; i++) { // freeing player symbols 
        free(plr_symboltable[i]->name);
        free(plr_symboltable[i]->map);
    }
    for(int i = 0; i < game_symbol_count; i++) { // freeing game symbols 
        free(game_symboltable[i]->name);
        free(game_symboltable[i]->map);
    }
    for (int i = 0; i < door_symbol_count; i++) { // freeing door symbols 
        free(door_symboltable[i]->name);
        free(door_symboltable[i]->map);
    }
    for (int i = 0; i < enemy_symbol_count; i++) { // freeing enemy symbols 
        free(enemy_symboltable[i]->name);
        free(enemy_symboltable[i]->map);
    }
}

//called through each object types respective assign symbol functions
// takes in the ProgCode enum value of the object and ID type of the object 
// uses check symbol to assign a symbol of the correct index to the passed in object 
void assignSymbol(char* s, ProgCode code) {
    Symbol* symbol = checkSymbol(s, code);
    Command cmd; //creates a command that is to be added to the program command array
    cmd.code = code;
    cmd.data = symbol->map; // ADDITION: using map instead of name (since map should be what is outputted to cpp file, not name)
    addCommand(cmd); // passes the command with the assigned symbol into the array
}

//assign symbol function for maps 
void assignMapSymbol(char* s) { 
    ProgCode code = AssignMap; // indicating it will need to retrieve a map symbol 
    assignSymbol(s, code);
}

//assign symbol function for players
void assignPlrSymbol(char * s) {
    ProgCode code = AssignPlr; // indicating it will need to retrieve a player symbol 
    assignSymbol(s, code);
}

//assign symbol function for games 
void assignGameSymbol(char* s) {
    ProgCode code = AssignGame;// indicating it will need to retrieve a game symbol 
    assignSymbol(s, code);
}

//assign symbol function for doors
void assignDoorSymbol(char* s) {
    ProgCode code = AssignDoor; // indicating it will need to retrieve a door symbol 
    assignSymbol(s, code);
}

//assign symbol function for enemies
void assignEnemySymbol(char* s) {
    ProgCode code = AssignEnemy; // indicating it will need to retrieve an enemy symbol 
    assignSymbol(s, code);
}




#endif