#ifndef board_H
#define board_H

#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void setPattern(int xa,int ya, int xb, int yb);
void obtinePunctUtil(POINT A, POINT &B);
void punePiesa(FILE *f, POINT c);

#endif // board_H