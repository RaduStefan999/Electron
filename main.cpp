#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "headers/UI.h"
#include "headers/board.h"

using namespace std;

Buttons ButtonsList;
Mouse mouse;
char elementRuta[100];

Board board;
int indexCurrentDraggingPiesa = -1;
connectionPoint *firstPoint = NULL;

void boardUpdate()
{
    POINT cursorPosition,P;

    cursorPosition.x = mouse.x;
    cursorPosition.y = mouse.y;
    obtinePunctUtil(cursorPosition, P);

    if (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y)
    {
        if(mouse.LMBClick)
        {
            indexCurrentDraggingPiesa = indexOcupiesSpace(board, cursorPosition);
            firstPoint = getConnectionPoint(board, cursorPosition);

            if (indexCurrentDraggingPiesa == -1 && firstPoint == NULL && strlen(elementRuta) != 0)
            {
                addBoardPiesa(P, board, elementRuta);
                drawBoard(board, true);
            }
        }
        if (mouse.justDropped)
        {
            if (indexCurrentDraggingPiesa != -1 && indexOcupiesSpace(board, cursorPosition) == -1)
            {
                modifyBoardPiesa(P, board, indexCurrentDraggingPiesa);
                drawBoard(board, true);
            }
            else
            {
                connectionPoint *lastPoint = getConnectionPoint(board, cursorPosition);
                if (firstPoint != NULL && lastPoint != NULL && firstPoint != lastPoint)
                {
                    firstPoint -> legatura = lastPoint;
                    firstPoint -> start = 1;
                    lastPoint -> legatura = firstPoint;

                    drawBoard(board, true);
                }
            }
        }

        if(mouse.RMBClick)
        {
            int indexEliminaPiesa = indexOcupiesSpace(board, cursorPosition);
            if (indexEliminaPiesa != -1)
            {
                removePiesa(board, indexEliminaPiesa);
                drawBoard(board, true);
            }
        }
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
            }
        }
        else
        {
            ButtonsList.buttons[i].shape.collor = ButtonsList.buttons[i].normalCollor;
        }

        drawRectangle(ButtonsList.buttons[i].shape);
    }
}

void openApp()
{
    int xmax=GetSystemMetrics(SM_CXSCREEN);
    int ymax=GetSystemMetrics(SM_CYSCREEN);

    board.xa = 450; board.ya = 200; board.xb = xmax - 50; board.yb = ymax - 50;

    initwindow(xmax, ymax, "");
    drawBoard(board, false);
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
