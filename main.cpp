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

void boardUpdate(int xa, int ya, int xb, int yb)
{

    POINT cursorPosition,P;
    if(mouse.LMBClick && (xa < mouse.x && ya < mouse.y && xb > mouse.x && yb > mouse.y)){
        clearmouseclick(WM_LBUTTONDOWN);
        FILE *f;

        if ((f = fopen(elementRuta,"r")) == NULL){
            printf("Error! opening file");
            exit(1);
        }
        cursorPosition.x=mousex();
        cursorPosition.y=mousey();
        obtinePunctUtil(cursorPosition, P);
        punePiesa(f,P);
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

        draw(ButtonsList.buttons[i].shape);
    }
}

void openApp()
{
    int xmax=GetSystemMetrics(SM_CXSCREEN);
    int ymax=GetSystemMetrics(SM_CYSCREEN);

    initwindow(xmax, ymax, "");

    setPattern(450, 200, xmax - 100, ymax - 100);
    setButtons(&ButtonsList);

    while(!GetAsyncKeyState(VK_ESCAPE)){
        mouseUpdate(&mouse);
        buttonsUpdate();
        boardUpdate(450, 200, xmax - 100, ymax - 100);
    }

    closegraph();
}
int main()
{
    openApp();
}
