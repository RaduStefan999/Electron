#ifndef UI_H
#define UI_H

#include <fstream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

struct Mouse
{
    int x, y;
    bool LMBClick, RMBClick;
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

void setButtons(Buttons *ButtonsList);
bool contains (RectangleShape shape, Mouse mouse);
void draw (RectangleShape shape);
void mouseUpdate(Mouse *mouse);

#endif // UI_H

