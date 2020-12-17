#include "../headers/board.h"

#define laturaPatrat 20

using namespace std;

void drawBoard (Board board, bool redraw)
{
    if (!redraw)
    {
        setbkcolor(WHITE);
        cleardevice();
    }

    setcolor(COLOR(100, 0, 0));
    setlinestyle(0,0,1);
    rectangle(board.xa - 1, board.ya - 1, board.xb + 1, board.yb + 1);
    floodfill(board.xa, board.ya, COLOR(100, 0, 0));

    setPattern(board);

    for (int i = 0; i < board.elements_lg; i++)
    {
        FILE *f;
        POINT P;

        if ((f = fopen(board.elements[i].source,"r")) == NULL){
            printf("Error! opening file");
            exit(1);
        }

        P.x = board.elements[i].x;
        P.y = board.elements[i].y;

        punePiesa(f, P);

    }
}

void setPattern(Board board)
{
    int i,j;
    setcolor(COLOR(200,200,200));
    for(i=board.ya; i<board.yb; i=i+laturaPatrat)
    {
        line(board.xa,i,board.xb,i);
    }
    for(j=board.xa; j<board.xb; j=j+laturaPatrat)
        line(j,board.ya,j,board.yb);
    setcolor(BLACK);
}

int indexOcupiesSpace(Board board, POINT P)
{
    int indexPiesa = -1;

    for (int i = 0; i < board.elements_lg; i++)
    {
        if ((abs(board.elements[i].x - P.x) < board.elements[i].width * laturaPatrat) && (abs(board.elements[i].y - P.y) < board.elements[i].height * laturaPatrat))
        {
            indexPiesa = i;

        }
    }
    return indexPiesa;
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
    //cout<<linfo.thickness;

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
