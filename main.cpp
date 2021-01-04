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
bool buttonPressed;
Board board;
int indexCurrentDraggingPiesa = -1;
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

void boardUpdate()
{
    POINT cursorPosition,P;
    cursorPosition.x = mouse.x;
    cursorPosition.y = mouse.y;

    obtinePunctUtil(cursorPosition, P, decalajTabla); // P este transmis prin referinta, P are coord. raportate la tabla

    if(mouse.LMBClick && (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y))
    {
        indexCurrentDraggingPiesa = indexOcupiesSpace(board, cursorPosition, decalajTabla);

        if (indexCurrentDraggingPiesa == -1 && buttonPressed)
        {
            board.elements[board.elements_lg].x = P.x; //
            board.elements[board.elements_lg].y = P.y;  //

            board.elements[board.elements_lg].width = 3;
            board.elements[board.elements_lg].height = 1;

            strcpy(board.elements[board.elements_lg].source, elementRuta);
            board.elements_lg++;
            drawBoard(board, true, decalajTabla);
            buttonPressed=false;
        }
    }
    if (mouse.justDropped && (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y))
    {
        if (indexCurrentDraggingPiesa != -1 && indexOcupiesSpace(board, cursorPosition, decalajTabla) == -1)
        {
            board.elements[board.elements_lg].x = P.x;  //
            board.elements[board.elements_lg].y = P.y;  //
            drawBoard(board, true, decalajTabla);
        }
    }
    if(!buttonPressed && mouse.LMBClick && (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y)){
        indexCurrentDraggingPiesa = indexOcupiesSpace(board, cursorPosition, decalajTabla);
        if((decalajTabla.x or decalajTabla.y) and indexCurrentDraggingPiesa==-1){
            pan(mouse.x, mouse.y, decalajTabla);
            drawBoard(board, true, decalajTabla);
        }
    }
    if(GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x49) && (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y))  // ctrl + i= zoom in
        if(zoomScale<5){
            zoomIn(zoomScale, decalajTabla);
            drawBoard(board, true, decalajTabla);

        }
    if(GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x4F) && (board.xa < mouse.x && board.ya < mouse.y && board.xb > mouse.x && board.yb > mouse.y)) // ctrl + o= zoom out
    if(zoomScale>1){
        zoomOut(zoomScale, decalajTabla);
        drawBoard(board, true, decalajTabla);
    }
    if(ismouseclick(WM_LBUTTONDBLCLK)){
        clearmouseclick(WM_LBUTTONDBLCLK);
        resetPanAndZoom(decalajTabla, zoomScale);
        drawBoard(board, true, decalajTabla);
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
