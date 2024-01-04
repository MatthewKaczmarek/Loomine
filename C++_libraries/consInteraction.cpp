#include <iostream>
#include "windows.h"
#include "consInteraction.h"

// NOTE: This code is from Ryan Trader and Andrew Tucker's Database final project

/*
The different color codes are

0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/
//sets the text color of the console output based on text_color, which is one of the above color codes
//SOURCE: FROM https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
void setTextColor(int text_color){
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, text_color); //set the text color
}

//clears the contents of the console and resets the cursor to the top left position
//SOURCE: FROM https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
void clearScreen(){
    //Get the Win32 handle representing standard output
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi; //used to store data regarding the console window
    COORD topLeft = {0,0}; //sets the top left position of the cursor (just stores it, does not move the cursor)

    std::cout.flush(); //called to get rid of stale buffered text
    //attempt to find the width and height of the current console window and store it within csbi
    if(!GetConsoleScreenBufferInfo(hOut, &csbi)){
        abort(); //handle error in finding width and height of console width
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y; //number of spaces to be outputted to the console

    DWORD written;

    //fills the entirety of the console with spaces thereby clearing the screen (starts at 
    //position topleft and fills length number of spaces)
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    //Resets attributes of every character to defaults (used to reset background color formatting)
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    //Move cursor to the top left of the screen
    SetConsoleCursorPosition(hOut, topLeft);
}

//set the cursor to a custom position
//inputs: int x - the x position that the cursor will be set to
//        int y - the y position that the cursor will be set to 
//SOURCE: FROM https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
void setCursorPos(int x, int y){
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush(); // force all characters in the buffer to be written before moving the cursor
    COORD coord = {(SHORT)x, (SHORT)y}; //store the new cursor position
    SetConsoleCursorPosition(hOut, coord); //move the cursor based on contents of coord
}