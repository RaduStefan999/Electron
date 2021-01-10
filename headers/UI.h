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
    bool LMBClick, RMBClick;
    bool isDraging, justDropped;
};

struct Keyboard
{
    bool R_PRESS;
    bool R_CONTINUOUS;
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



void setButtons(Buttons *ButtonsList, Board board);
bool contains (RectangleShape shape, Mouse mouse);
void drawRectangle (RectangleShape shape);
void mouseUpdate(Mouse *mouse);
void keyboardUpdate(Keyboard *keyboard);

void openDialogBox(Board &board, decalaj decalajTabla);
void salvareCircuit(Board boardn, char nume[]);
void incarcareCircuit(Board &board, char nume[], decalaj decalajTabla);

#endif // UI_H

