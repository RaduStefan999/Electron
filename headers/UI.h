#ifndef UI_H
#define UI_H

#include <fstream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

struct Board;

struct decalaj;

struct Mouse
{
    int x, y;
    bool LMBClick, RMBClick, DClick;
    bool isDraging, justDropped;
};

struct Keyboard
{
    bool R_PRESS;
    bool R_CONTINUOUS;
    bool M_CONTINUOUS;
};

struct Collor
{
    unsigned short int r, g, b;
};

struct RectangleShape
{
    int x, y;
    int width, height;
    Collor collor;
};

struct Button
{
    RectangleShape shape;
    Collor normalCollor;
    Collor highlightCollor;
    char elementRoute[100];
};

struct Buttons
{
    Button buttons[100];
    int lg;
};


//Radu
void setButtons(Buttons *ButtonsList, Board board);
//Radu
bool contains (RectangleShape shape, Mouse mouse);
//Radu
void drawRectangle (RectangleShape shape);
//Radu
void mouseUpdate(Mouse *mouse);
//Radu
void keyboardUpdate(Keyboard *keyboard);
//Iulian
void openDialogBox(Board &board, decalaj decalajTabla);
//Iulian
void salvareCircuit(Board boardn, char nume[]);
//Iulian
void incarcareCircuit(Board &board, char nume[], decalaj decalajTabla);

#endif // UI_H

