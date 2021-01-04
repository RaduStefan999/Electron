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
char elementRuta[100];
Board board;
int indexCurrentDraggingPiesa = -1;

connectionPoint *firstPoint = NULL;

decalaj decalajTabla;
double zoomScale = 1;
int laturaPatrat = 20;



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
            }
        }
        else
        {
            ButtonsList.buttons[i].shape.collor = ButtonsList.buttons[i].normalCollor;
        }

        drawRectangle(ButtonsList.buttons[i].shape);
    }
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
                drawBoard(board, true, decalajTabla);
            }

            if(GetAsyncKeyState(0x49) && zoomScale<5)  // ctrl + i= zoom in
            {
                zoomIn(zoomScale, decalajTabla);
                drawBoard(board, true, decalajTabla);
            }

            if(GetAsyncKeyState(0x4F) && zoomScale>1) // ctrl + o= zoom out
            {
                zoomOut(zoomScale, decalajTabla);
                drawBoard(board, true, decalajTabla);
            }
            if(GetAsyncKeyState(0x52)) // ctrl + r= reset zoom
            {
                resetPanAndZoom(decalajTabla, zoomScale);
                drawBoard(board, true, decalajTabla);
            }
        }
        else
        {
            if(mouse.LMBClick)
            {
                indexCurrentDraggingPiesa = indexOcupiesSpace(board, cursorPosition, decalajTabla);
                firstPoint = getConnectionPoint(board, cursorPosition, decalajTabla);

                if (indexCurrentDraggingPiesa == -1 && firstPoint == NULL && strlen(elementRuta) != 0)
                {
                    addBoardPiesa(P, board, elementRuta);
                    drawBoard(board, true, decalajTabla);
                }
            }
            if (mouse.justDropped)
            {
                if (indexCurrentDraggingPiesa != -1 && indexOcupiesSpace(board, cursorPosition, decalajTabla) == -1)
                {
                    modifyBoardPiesa(P, board, indexCurrentDraggingPiesa);
                    drawBoard(board, true, decalajTabla);
                }
                else
                {
                    connectionPoint *lastPoint = getConnectionPoint(board, cursorPosition, decalajTabla);
                    if (firstPoint != NULL && lastPoint != NULL && firstPoint != lastPoint)
                    {
                        firstPoint -> legatura = lastPoint;
                        firstPoint -> start = 1;
                        lastPoint -> legatura = firstPoint;

                        drawBoard(board, true, decalajTabla);
                    }
                }
            }

            if(mouse.RMBClick)
            {
                int indexEliminaPiesa = indexOcupiesSpace(board, cursorPosition, decalajTabla);
                if (indexEliminaPiesa != -1)
                {
                    removePiesa(board, indexEliminaPiesa);
                    drawBoard(board, true, decalajTabla);
                }
            }
        }

    }
}

void openApp()
{
    int xmax=GetSystemMetrics(SM_CXSCREEN);
    int ymax=GetSystemMetrics(SM_CYSCREEN);

    board.xa = 400; board.ya = 40; board.xb = board.xa + 1000; board.yb = board.ya+ 800;

    initwindow(xmax, ymax, "");
    drawBoard(board, false, decalajTabla);
    setButtons(&ButtonsList);

    while(!GetAsyncKeyState(VK_ESCAPE)){
        mouseUpdate(&mouse);
        buttonsUpdate();
        boardUpdate();
    }

    closegraph();
}
int main()
{
    openApp();
}
