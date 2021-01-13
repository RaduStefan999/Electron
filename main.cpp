#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "headers/UI.h"
#include "headers/board.h"
#include "headers/zoomandpan.h"

using namespace std;

Buttons ButtonsList;
Mouse mouse;
Keyboard keyboard;

char elementRuta[100];
Board board;
int indexCurrentDraggingPiesa = -1;

connectionPoint *firstPoint = NULL;

bool buttonPressed=false;
decalaj decalajTabla;
double zoomScale = 1;
int laturaPatrat = 20;

//Amandoi
void openApp();
//Amandoi
void boardUpdate();
//Radu
void buttonsUpdate();


int main()
{
    openApp();
}

void openApp()
{

    int xmax=GetSystemMetrics(SM_CXSCREEN);
    int ymax=GetSystemMetrics(SM_CYSCREEN);

    initwindow(xmax, ymax, "");

    if ((float)xmax/ymax > 1.4)
    {
        readimagefile ("UI/ElectronMeniu16x9.jpg", 0,0,xmax,ymax);
        board.xa = 400; board.ya = 40; board.xb = board.xa + 1150; board.yb = board.ya+ 920;
    }
    else
    {
        readimagefile ("UI/ElectronMeniu4x3.jpg", 0,0,xmax,ymax);
        board.xa = 400; board.ya = 40; board.xb = board.xa + 1000; board.yb = board.ya+ 800;
    }

    while (ismouseclick(WM_LBUTTONDOWN) == false) {}
    clearmouseclick(WM_LBUTTONDOWN);

    drawBoard(board, false, decalajTabla, -1);
    setButtons(&ButtonsList, board);

    while(!GetAsyncKeyState(VK_ESCAPE)){
        mouseUpdate(&mouse);
        keyboardUpdate(&keyboard);

        buttonsUpdate();
        boardUpdate();
    }

    closegraph();
}

void boardUpdate()
{
    POINT cursorPosition,P;
    cursorPosition.x = mouse.x;
    cursorPosition.y = mouse.y;

    obtinePunctUtil(cursorPosition, P, decalajTabla); // P este transmis prin referinta, P are coord. raportate la tabla

    if (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y)
    {
        if(GetAsyncKeyState(VK_CONTROL))
        {
            if (mouse.LMBClick)
            {
                pan(mouse.x, mouse.y, decalajTabla);
                drawBoard(board, true, decalajTabla, -1);
            }

            if(GetAsyncKeyState(0x49) && zoomScale<5)  // ctrl + i= zoom in
            {
                zoomIn(zoomScale, decalajTabla);
                drawBoard(board, true, decalajTabla, -1 );
            }

            if(GetAsyncKeyState(0x4F) && zoomScale>1) // ctrl + o= zoom out
            {
                zoomOut(zoomScale, decalajTabla);
                drawBoard(board, true, decalajTabla, -1);
            }
            if(keyboard.R_PRESS) // ctrl + r= reset zoom
            {
                resetPanAndZoom(decalajTabla, zoomScale);
                drawBoard(board, true, decalajTabla, -1);
            }

        }

        else
        {
            if(mouse.LMBClick)
            {
                indexCurrentDraggingPiesa = indexOcupiesSpace(board, cursorPosition, decalajTabla);

                firstPoint = getConnectionPoint(board, cursorPosition, decalajTabla);

                if (indexCurrentDraggingPiesa == -1 && firstPoint == NULL && strlen(elementRuta) != 0 && buttonPressed)
                {
                    addBoardPiesa(P, board, elementRuta);
                    drawBoard(board, true, decalajTabla, -1);
                    buttonPressed=false;
                }
            }
            if (mouse.justDropped)
            {
                if (indexCurrentDraggingPiesa != -1 && ( indexOcupiesSpace(board, cursorPosition, decalajTabla) == -1 || indexOcupiesSpace(board, cursorPosition, decalajTabla)==indexCurrentDraggingPiesa))
                {
                    modifyBoardPiesa(P, board, indexCurrentDraggingPiesa);
                    drawBoard(board, true, decalajTabla, -1 );
                }
                else
                {
                    connectionPoint *lastPoint = getConnectionPoint(board, cursorPosition, decalajTabla);
                    if (firstPoint != NULL && lastPoint != NULL && firstPoint != lastPoint)
                    {
                        firstPoint -> legatura = lastPoint;
                        firstPoint -> start = 1;
                        lastPoint -> legatura = firstPoint;

                        drawBoard(board, true, decalajTabla, -1);
                    }
                }
            }

            if(mouse.RMBClick)
            {
                int indexEliminaPiesa = indexOcupiesSpace(board, cursorPosition, decalajTabla);
                if (indexEliminaPiesa != -1)
                {
                    removePiesa(board, indexEliminaPiesa);
                    drawBoard(board, true, decalajTabla, -1);
                }
            }

            if(keyboard.R_PRESS) // r= rotate part
            {
                int indexRotatePiesa = indexOcupiesSpace(board, cursorPosition, decalajTabla);

                if (indexRotatePiesa != -1)
                {
                    board.elements[indexRotatePiesa].rotation = (board.elements[indexRotatePiesa].rotation + 1) % 4;
                    drawBoard(board, true, decalajTabla, -1);
                }
            }
            if(mouse.DClick){
                int indexPiesaSelectata = indexOcupiesSpace(board, cursorPosition, decalajTabla);
                if(indexPiesaSelectata !=-1){
                        board.elements[indexPiesaSelectata].display_continut=true;
                        drawBoard(board, true, decalajTabla, indexPiesaSelectata);

                }
            }

        }

    }
    if(mouse.LMBClick and mouse.x>board.xb){
                board.dialogBox.afis=true;
                board.dialogBox.mod=1; //mod 1= salvare
                drawBoard(board,true,decalajTabla,-1);
            }
    if(mouse.RMBClick and mouse.x>board.xb){
                board.dialogBox.afis=true;
                board.dialogBox.mod=2; //mod 1= salvare
                drawBoard(board,true,decalajTabla,-1);
            }
}

void buttonsUpdate()
{
    for (int i = 0; i < ButtonsList.lg; i++)
    {
        if (contains(ButtonsList.buttons[i].shape, mouse))
        {
            ButtonsList.buttons[i].shape.collor = ButtonsList.buttons[i].highlightCollor;
            if (mouse.LMBClick)
            {
                strcpy(elementRuta, ButtonsList.buttons[i].elementRoute);
                buttonPressed=true;
            }
        }
        else
        {
            ButtonsList.buttons[i].shape.collor = ButtonsList.buttons[i].normalCollor;
        }

        drawRectangle(ButtonsList.buttons[i].shape);
    }
}
