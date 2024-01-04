#ifndef CONSINTERACTION_H
#define CONSINTERACTION_H

//set console print color to color with code text_color
extern void setTextColor(int text_color);

//clear the contents of the console
extern void clearScreen();

//set the cursor position to position marked by (x,y)
extern void setCursorPos(int x, int y);

#endif