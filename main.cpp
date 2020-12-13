#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/UI.h"
#include "headers/board.h"

using namespace std;

Buttons ButtonsList;
Mouse mouse;


void boardUpdate()
{

    POINT cursorPosition,P;
    if(mouse.LMBClick){
        clearmouseclick(WM_LBUTTONDOWN);
        FILE *f;

        if ((f = fopen("elemente\\condensator.txt","r")) == NULL){
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
                //am apasat pe buton
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

    setPattern(xmax,ymax);
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
