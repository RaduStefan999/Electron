#ifndef ZOOMANDPAN_H_INCLUDED
#define ZOOMANDPAN_H_INCLUDED

#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "UI.h"


struct decalaj
{
    int x;
    int y;
};
extern double zoomScale;

//Iulian
void obtineCoordEcran(int x1, int y1, int &x2, int &y2, decalaj decalajTabla, double zoomScale);
//Iulian
void obtineCoordTabla(int x1, int y1, int &x2, int &y2, decalaj decalajTabla, double zoomScale);
//Iulian
void pan(int x, int y, decalaj &decalajTabla);
//Iulian
void setZoomScale(double &zoomScale);
//Iulian
void zoomIn(double &zoomScale, decalaj &decalajTabla);
//Iulian
void zoomOut(double &zoomScale, decalaj &decalajTabla);
//Iulian
void resetPanAndZoom(decalaj &decalajTabla, double &zoomScale);

#endif // ZOOMANDPAN_H_INCLUDED
