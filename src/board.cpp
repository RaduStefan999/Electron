#include "../headers/board.h"

#define laturaPatrat 20

using namespace std;

void setPattern(int xa,int ya, int xb, int yb)
{
    int i,j;
    setbkcolor(WHITE);
    cleardevice();
    setcolor(COLOR(200,200,200));
    for(i=ya; i<yb; i=i+laturaPatrat)
    {
        line(xa,i,xb,i);
    }
    for(j=xa; j<xb; j=j+laturaPatrat)
        line(j,ya,j,yb);
    setcolor(BLACK);
    setlinestyle(0,0,3);


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
        B.y=A.y-ry;
    else B.y=A.y+(laturaPatrat-ry);
}

void punePiesa(FILE *f, POINT c)
{
    setlinestyle(0,0,3);
    linesettingstype linfo;
    getlinesettings(&linfo);
    cout<<linfo.thickness;

    char text[20];
    fgets(text,20,f);
    text[0]=NULL; //nu avem nevoie de text, doar sarim peste el
    int nrNoduri,i=1;
    fscanf(f, "%d", &nrNoduri);
    while(i<=nrNoduri){
        POINT nod;
        fscanf(f, "%f", &nod.x);
        fscanf(f, "%f", &nod.y);
        //asociazaNod(nod);
        i++;
    }
    fseek(f,2,SEEK_CUR);
    fgets(text,20,f);
    text[0]=NULL;
    while(!feof(f)){
        setcolor(BLACK);
        char lit; int j;
        float cf[6];
        fscanf(f,"%c", &lit);
        if(lit=='l'){
            for(j=0;j<4;++j)
                fscanf(f,"%f", &cf[j]);
            line(c.x+laturaPatrat*cf[0] , c.y+laturaPatrat*cf[1] , c.x+laturaPatrat*cf[2] , c.y+laturaPatrat*cf[3] );
        }
        else if(lit=='a'){
            for(j=0;j<5;++j)
                fscanf(f,"%f", &cf[j]);
            arc(c.x+laturaPatrat*cf[0], c.y+laturaPatrat*cf[1],cf[2],cf[3],laturaPatrat*cf[4]);
        }
        else if(lit=='c'){
            for(j=0;j<5;++j)
                fscanf(f,"%f", &cf[j]);
            circle(c.x+laturaPatrat*cf[0], c.y+laturaPatrat*cf[1],laturaPatrat*cf[2]);
        }
        else if(lit=='e'){
            for(j=0;j<6;++j)
                fscanf(f,"%f", &cf[j]);
            ellipse(c.x+laturaPatrat*cf[0], c.y+laturaPatrat*cf[1],cf[2],cf[3],laturaPatrat*cf[4],laturaPatrat*cf[5]);
        }
    }



}
