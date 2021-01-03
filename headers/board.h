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
    bool start;
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
connectionPoint *getConnectionPoint(Board &board, POINT cursorPosition);
void puneSimbol(FILE *f, POINT c);
void addBoardPiesa (POINT P, Board &board, char elementRuta[100]);
void modifyBoardPiesa (POINT P, Board &board, int indexCurrentDraggingPiesa);
void removePiesa(Board &board, int indexEliminaPiesa);
int indexOcupiesSpace(Board board, POINT P);

#endif // board_H
