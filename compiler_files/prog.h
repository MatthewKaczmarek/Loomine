#ifndef _PROG_H_
#define _PROG_H_

#include <stdio.h>
// creating an Enum that will be used to correctly assign command operations 
// this includes assigning tokens, movement controls, maps, games, doors, variable assignment,
// mad addition, door addition, enemy addition, player addition, and enemy movement speed
typedef enum {
    Map_Row, Map_Column, Map_Inner, Map_Border, Map, Plr_X_Pos, Plr_Y_Pos, 
    Plr_Token, Plr_Up_Ctr, Plr_Right_Ctr, Plr_Down_Ctr, Plr_Left_Ctr, Player, 
    Door_X_Pos, Door_Y_Pos, Door_Token, Door, 
    AssignMap, AssignPlr, PushPlrId, PushMapId, PushGameId, Game, AssignGame,
    AssignDoor, PushDoorId, Enemy_Speed, AssignEnemy, PushEnemyId,
    AddMap, AddPlr, AddDoor, AddEnemy, Run, Enemy, Enemy_X_Pos, Enemy_Y_Pos, Enemy_Token,
} ProgCode; 

// generating a struct that will contain a name and hold a char of data
// this be used to track which command we are calling from the stack
typedef struct {
    ProgCode code;
    char* data;
} Command;

int cmds = 0;
//max commands in the program will be 1000
Command program[1000];

//adds a command to the program array and checks to see if the command limit is reached 
void addCommand(Command cmd) {
    if (cmds == 1000){
        printf("stack overflow\n");
    }
    else
    program[cmds++] = cmd;
}

#endif