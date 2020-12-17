#include "../headers/UI.h"

using namespace std;

void setButtons(Buttons *ButtonsList)
{
    int n;
    ifstream fin ("UI/buttons.txt");

    fin >> n;
    for (int i = 0; i < n; i++)
    {
        Button curentButton;

        fin >> curentButton.shape.x >> curentButton.shape.y >> curentButton.shape.width >> curentButton.shape.height;
        fin >> curentButton.normalCollor.r >> curentButton.normalCollor.g >> curentButton.normalCollor.b;
        fin >> curentButton.highlightCollor.r >> curentButton.highlightCollor.g >> curentButton.highlightCollor.b;
        fin >> curentButton.elementRoute;

        FILE *f;
        f = fopen(curentButton.elementRoute,"r");
        POINT P;
        P.x = curentButton.shape.x + curentButton.shape.width/4;
        P.y = curentButton.shape.y + curentButton.shape.height/2;
        punePiesa(f,P);

        ifstream text (curentButton.elementRoute);
        char nume[100];
        text.getline(nume, 255);
        outtextxy (curentButton.shape.x + curentButton.shape.width/2, curentButton.shape.y + curentButton.shape.height/2 - 7, nume);

        ButtonsList -> buttons[ButtonsList -> lg] = curentButton;
        ButtonsList -> lg++;
    }
}

bool contains (RectangleShape shape, Mouse mouse)
{

    if (mouse.x > shape.x && mouse.y > shape.y && mouse.x < shape.x + shape.width && mouse.y < shape.y + shape.height)
    {
        return true;
    }

    return false;
}

void drawRectangle (RectangleShape shape)
{
    setcolor(COLOR(shape.collor.r, shape.collor.g, shape.collor.b));
    setlinestyle(0,0,10);
    rectangle(shape.x, shape.y, shape.x + shape.width, shape.y + shape.height);
}

void mouseUpdate(Mouse *mouse)
{
    mouse -> x = mousex();
    mouse -> y = mousey();

    mouse -> LMBClick = mouse -> RMBClick = mouse -> justDropped = false ;

    if(ismouseclick(WM_LBUTTONDOWN))
    {
        mouse -> LMBClick = true;
        mouse -> isDraging = true;
        clearmouseclick(WM_LBUTTONDOWN);
    }

    if(ismouseclick(WM_LBUTTONUP))
    {
        mouse -> isDraging = false;
        mouse -> justDropped = true;
        clearmouseclick(WM_LBUTTONUP);
    }

    if(ismouseclick(WM_RBUTTONDOWN))
    {
        mouse -> RMBClick = true;
        clearmouseclick(WM_RBUTTONDOWN);
    }
}
