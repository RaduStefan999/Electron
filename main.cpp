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

void boardUpdate()
{
    POINT cursorPosition,P;

    cursorPosition.x = mouse.x;
    cursorPosition.y = mouse.y;
    obtinePunctUtil(cursorPosition, P);


    if(mouse.LMBClick && (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y))
    {
        indexCurrentDraggingPiesa = indexOcupiesSpace(board, cursorPosition);

        if (indexCurrentDraggingPiesa == -1)
        {
            board.elements[board.elements_lg].x = P.x;
            board.elements[board.elements_lg].y = P.y;

            board.elements[board.elements_lg].width = 3;
            board.elements[board.elements_lg].height = 1;

            strcpy(board.elements[board.elements_lg].source, elementRuta);
            board.elements_lg++;

            drawBoard(board, true);
        }
    }
    if (mouse.justDropped && (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y))
    {
        if (indexCurrentDraggingPiesa != -1 && indexOcupiesSpace(board, cursorPosition) == -1)
        {
            board.elements[indexCurrentDraggingPiesa].x = P.x;
            board.elements[indexCurrentDraggingPiesa].y = P.y;

            drawBoard(board, true);
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
