#ifndef _EVALEXPR_H_
#define _EVALEXPR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog.h"
#include "symbols.h"

//taking in a code type and then adding it to the program command array
void push(ProgCode code, char* num) {
    Command cmd;
    cmd.code = code;
    cmd.data = num;
    addCommand(cmd);
}

//creates a command that pushes an ID value to a char* called map of the symbol passed in
//the pushes the new command to the program command array
void pushid(char* id, Symbol* symbol, ProgCode push_id) {
    Command cmd;
    cmd.code = push_id;
    cmd.data = symbol->map; //ADDITION: No longer adding name to cmd.data, instead adding map (since we want map to end up in the new cpp)
    addCommand(cmd);
}

//used to generate a Map object based off inputted parameters from top level language
void genMap(char* row, char* column, char* inner_char, char* border_char) {
    push(Map, NULL);
    push(Map_Inner, inner_char);
    push(Map_Border, border_char);
    push(Map_Column, column); 
    push(Map_Row, row);
}

//used to generate a Player object based off inputted parameters from top level language
void genPlr(char* x_pos, char* y_pos, char* token, char* ctr_up, char* ctr_right, char* ctr_down, char* ctr_left) {
    push(Player, NULL);
    push(Plr_X_Pos, x_pos);
    push(Plr_Y_Pos, y_pos);
    push(Plr_Token, token);
    push(Plr_Up_Ctr, ctr_up);
    push(Plr_Right_Ctr, ctr_right);
    push(Plr_Down_Ctr, ctr_down);
    push(Plr_Left_Ctr, ctr_left);
}

//used to generate a Door object based off inputted parameters from top level language
void genDoor(char* x_pos, char* y_pos, char* token) {
    push(Door, NULL);
    push(Door_X_Pos, x_pos);
    push(Door_Y_Pos, y_pos);
    push(Door_Token, token);
}

//used to generate a Enemy object based off inputted parameters from top level language
void genEnemy(char* x_pos, char* y_pos, char* token, char* speed) {
    push(Enemy, NULL);
    push(Enemy_X_Pos, x_pos);
    push(Enemy_Y_Pos, y_pos);
    push(Enemy_Token, token);
    push(Enemy_Speed, speed);
}

//used to generate a Game object based off inputted parameters from top level language
void genGame(char* speed){
    push(Game, speed);
}

//generates a symbol pointer of struct type symbol
// this is then used when calling push ID to assign the symbol to a Map object that is being initialized
void genIdentifierMap(char* id){
    Symbol* symbol = getSymbol(id, AssignMap);
    pushid(id, symbol, PushMapId);
}

//generates a symbol pointer of struct type symbol
// this is then used when calling push ID to assign the symbol to a Player object that is being initialized
void genIdentifierPlr(char* id){
    Symbol* symbol = getSymbol(id, AssignPlr);
    pushid(id, symbol, PushPlrId);
}

//generates a symbol pointer of struct type symbol
// this is then used when calling push ID to assign the symbol to a Game object that is being initialized 
void genIdentifierGame(char*id){
    Symbol* symbol = getSymbol(id, AssignGame);
    pushid(id, symbol, PushGameId);
}

//generates a symbol pointer of struct type symbol
// this is then used when calling push ID to assign the symbol to a Door object that is being initialized
void genIdentifierDoor(char* id){
    Symbol* symbol = getSymbol(id, AssignDoor);
    pushid(id, symbol, PushDoorId);
}

//generates a symbol pointer of struct type symbol
// this is then used when calling push ID to assign the symbol to an Enemy object that is being initialized 
void genIdentifierEnemy(char* id){
    Symbol* symbol = getSymbol(id, AssignEnemy);
    pushid(id, symbol, PushEnemyId);
}

//used to add an AddMap (ADDM) command to the program array
void addMap(){
    Command cmdOp;
    cmdOp.code = AddMap;
    addCommand(cmdOp);
}

//used to add an AddPlr (ADDP) command to the program array
void addPlr(){
    Command cmdOp;
    cmdOp.code = AddPlr;
    addCommand(cmdOp);
}

//used to add an AddEnemy (ADDE) command to the program array
void addEnemy(){
    Command cmdOp;
    cmdOp.code = AddEnemy;
    addCommand(cmdOp);
}

//used to add an AddDoor (ADDD) command to the program array
void addDoor(){
    Command cmdOp;
    cmdOp.code = AddDoor;
    addCommand(cmdOp);
}

//used to add a Run command (RUN) command to the program array
void runGame() {
    Command cmdOp;
    cmdOp.code = Run;
    addCommand(cmdOp);
}

#endif