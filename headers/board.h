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
#include "zoomandpan.h"

extern int laturaPatrat;

struct decalaj;
struct dialog;

struct connectionPoint
{
    int x, y, r; //
    bool start; //
    connectionPoint *legatura;
};

struct boardElement
{
    char source[100], nume[100]; // //continut_piesa[200];
    int rotation; //
    short nr_marimi_fizice; //
    char marimeFizica[10];//
    char unitateMasura[10];//
    int valoare[10]; //
    short indexMF; //
    bool display_continut,  modifica_continut; //
    int x, y, width, height;  //
    int connectionPoints_nr;  //
    connectionPoint connectionPoints[5];
};

struct dialog
{
    bool afis;
    int mod;
};

struct Board
{
    int xa, ya, xb, yb;
    int elements_lg;  //
    dialog dialogBox;
    boardElement elements[100];
};


//Iulian
void puneSimbol(FILE *f, POINT c, Board &board, int indexSimbol);
//Radu
void addBoardPiesa (POINT P, Board &board, char elementRuta[100]);
//Radu
void modifyBoardPiesa (POINT P, Board &board, int indexCurrentDraggingPiesa);
//Radu
void removePiesa(Board &board, int indexEliminaPiesa);
//Radu
void rotatePoints(float points[], int rotation);
void rotateAngles(float angles[], int rotation);
//Radu
void updateConnectionPointRotation(boardElement &element);
//Amandoi
void drawBoard (Board &board, bool redraw, decalaj decalajTabla, int indexText);
//Iulian
void setPattern(Board board, decalaj decalajTabla);
//Iulian
void obtinePunctUtil(POINT A, POINT &B, decalaj decalajTabla);
//Radu
int indexOcupiesSpace(Board board, POINT P, decalaj decalajTabla);
//Radu
connectionPoint *getConnectionPoint(Board &board, POINT cursorPosition, decalaj decalajTabla);
//Iulian
void displayContinutPiesa(Board &board, int indexPiesaSelectata, decalaj decalajTabla);
//Iulian
void modificaContinutPiesa(Board &board,int indexPiesaSelectata, decalaj decalajTabla);
//Iulian
void setMF_UM(Board &board, int indexPiesaSelectata);

#endif // board_H
