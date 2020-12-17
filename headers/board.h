#ifndef board_H
#define board_H

#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

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

void setPattern(int xa,int ya, int xb, int yb);
void obtinePunctUtil(POINT A, POINT &B);
void punePiesa(FILE *f, POINT c);

#endif // board_H
