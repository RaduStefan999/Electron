#include "../headers/zoomandpan.h"
using namespace std;

void obtineCoordEcran(int x1, int y1, int &x2, int &y2, decalaj decalajTabla, double zoomScale)
{
    x2=(x1-decalajTabla.x)*zoomScale;
    y2=(y1-decalajTabla.y)*zoomScale;
}

void obtineCoordTabla(int x1, int y1, int &x2, int &y2, decalaj decalajTabla, double zoomScale)
{
    x2=x1/zoomScale+decalajTabla.x;
    y2=y1/zoomScale+decalajTabla.y;
}

void pan(int x, int y, decalaj &decalajTabla)
{
    int startPanX=x;
    int startPanY=y;
    while(!ismouseclick(WM_LBUTTONUP)){
        decalajTabla.x -= (mousex()-startPanX)/zoomScale;
        decalajTabla.y -= (mousey()-startPanY)/zoomScale;
        startPanX=mousex();
        startPanY=mousey();
    }
    clearmouseclick(WM_LBUTTONUP);
    //cout<<decalajTabla.x<<' '<<decalajTabla.y<<'\n';
}


void zoomIn(double &zoomScale, decalaj &decalajTabla)
{
    int mouseTablaX, mouseTablaY;
    obtineCoordTabla(mousex(), mousey(), mouseTablaX, mouseTablaY, decalajTabla, zoomScale);

    zoomScale *= 1.1;

    int mouseTablaX1, mouseTablaY1;
    obtineCoordTabla(mousex(), mousey(), mouseTablaX1, mouseTablaY1, decalajTabla, zoomScale);

    decalajTabla.x += mouseTablaX-mouseTablaX1;
    decalajTabla.y += mouseTablaY-mouseTablaY1;
}
void zoomOut(double &zoomScale, decalaj &decalajTabla)
{
    int mouseTablaX, mouseTablaY;
    obtineCoordTabla(mousex(), mousey(), mouseTablaX, mouseTablaY, decalajTabla, zoomScale);

    zoomScale /= 1.1;
    int mouseTablaX1, mouseTablaY1;
    obtineCoordTabla(mousex(), mousey(), mouseTablaX1, mouseTablaY1, decalajTabla, zoomScale);

    decalajTabla.x += mouseTablaX-mouseTablaX1;
    decalajTabla.y += mouseTablaY-mouseTablaY1;
}


void resetPanAndZoom(decalaj &decalajTabla, double &zoomScale)
{
    decalajTabla.x=0;
    decalajTabla.y=0;
    zoomScale=1;
}
