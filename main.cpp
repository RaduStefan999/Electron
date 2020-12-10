#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define laturaPatrat 20
using namespace std;

void setPattern(int x,int y)
{
    int i,j;
    setbkcolor(WHITE);
    cleardevice();
    for(i=laturaPatrat; i<y; i=i+laturaPatrat)
    {
        setcolor(COLOR(200,200,200));
        line(0,i,x,i);
        line(i,0,i,y);
    }
    for(j=i; j<x; j=j+laturaPatrat)
        line(j,0,j,y);


}
void obtinePunctUtil(POINT A, POINT &B)
{
    int rx,ry;
    rx=A.x%laturaPatrat;
    ry=A.y%laturaPatrat;
    if(rx<laturaPatrat/2)
        B.x=A.x-rx;
    else B.x=A.x+(laturaPatrat-rx);
    if(ry<laturaPatrat/2)
        B.y=B.x-ry;
    else B.y=A.y+(laturaPatrat-ry);
}

void punePiesa(FILE *f, POINT c)
{
    fscanf(f, "%*[^\n]\n");
    int nrNoduri,i=0;
    fscanf(f, "%d", &nrNoduri);
    while(i<=nrNoduri){
        POINT nod;
        fscanf(f, "%f", &nod.x);
        fscanf(f, "%f", &nod.y);

    }


}

void boardUpdate()
{
    FILE *f=fopen("D:\\Proiect IP\\Electron\\elemente\\rezistor.txt","r");
    POINT cursorPosition,P;
    GetCursorPos(&cursorPosition);

    if(GetAsyncKeyState(VK_LBUTTON)){
        obtinePunctUtil(cursorPosition, P);
        punePiesa(f,P);
    }

}

void openApp()
{
    DWORD xmax=GetSystemMetrics(SM_CXSCREEN);
    DWORD ymax=GetSystemMetrics(SM_CYSCREEN);
    initwindow(xmax, ymax, "");
    setPattern(xmax,ymax);
    while(!GetAsyncKeyState(VK_ESCAPE)){
        boardUpdate();
    }
    closegraph();
}
int main()
{
    openApp();
}
