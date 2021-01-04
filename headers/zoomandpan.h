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


void obtineCoordEcran(int x1, int y1, int &x2, int &y2, decalaj decalajTabla, double zoomScale);
void obtineCoordTabla(int x1, int y1, int &x2, int &y2, decalaj decalajTabla, double zoomScale);

void pan(int x, int y, decalaj &decalajTabla);

void setZoomScale(double &zoomScale);
void zoomIn(double &zoomScale, decalaj &decalajTabla);
void zoomOut(double &zoomScale, decalaj &decalajTabla);

void resetPanAndZoom(decalaj &decalajTabla, double &zoomScale);

#endif // ZOOMANDPAN_H_INCLUDED
