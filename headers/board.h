#ifndef board_H
#define board_H

#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#include "UI.h"

struct connectionPoint
{
    int x, y, r;
    connectionPoint *legatura;
};

struct boardElement
{
    char source[100];
    int x, y, width, height;
    int connectionPoints_nr;
    connectionPoint connectionPoints[100];
};

struct Board
{
    int xa, ya, xb, yb;
    int elements_lg;
    boardElement elements[100];
};

void drawBoard (Board board, bool redraw);
void setPattern(Board board);
void obtinePunctUtil(POINT A, POINT &B);
void punePiesa(FILE *f, POINT c);
int indexOcupiesSpace(Board board, POINT P);

#endif // board_H
