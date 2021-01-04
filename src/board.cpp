#include "../headers/board.h"

using namespace std;


void drawBoard (Board board, bool redraw, decalaj decalajTabla)
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
    setPattern(board, decalajTabla);

    for (int i = 0; i < board.elements_lg; i++)
    {
        FILE *f;
        POINT P, P1;

        if ((f = fopen(board.elements[i].source,"r")) == NULL){
            printf("Error! opening file");
            exit(1);
        }

        P.x = board.elements[i].x;
        P.y = board.elements[i].y;

        int xEcran, yEcran;
        obtineCoordEcran(P.x, P.y, xEcran, yEcran, decalajTabla, zoomScale);
        P1.x=xEcran; P1.y=yEcran;
        if(xEcran>board.xa and xEcran<board.xb and yEcran>board.ya and yEcran<board.yb) //
        puneSimbol(f, P);


        for (int j = 0; j < board.elements[i].connectionPoints_nr; j++)
        {
            setlinestyle(0,0,1);
            setcolor(RED);
            circle(board.elements[i].connectionPoints[j].x, board.elements[i].connectionPoints[j].y, board.elements[i].connectionPoints[j].r);

            if (board.elements[i].connectionPoints[j].legatura != NULL)
            {
                setlinestyle(1,0,3);

                if (board.elements[i].connectionPoints[j].legatura -> start)
                {
                    line(board.elements[i].connectionPoints[j].x, board.elements[i].connectionPoints[j].y, board.elements[i].connectionPoints[j].legatura -> x, board.elements[i].connectionPoints[j].y);
                    line(board.elements[i].connectionPoints[j].legatura -> x, board.elements[i].connectionPoints[j].y, board.elements[i].connectionPoints[j].legatura -> x, board.elements[i].connectionPoints[j].legatura -> y);
                }
            }
        }
    }
}

void setPattern(Board board, decalaj decalajTabla)
{
    int i,j;
    setcolor(COLOR(200,200,200));

    int xEcran, yEcran, xEcran1, yEcran1;
    for(i=board.ya; i<=board.yb; i=i+laturaPatrat) // liniile orizontale
    {
        obtineCoordEcran(board.xa, i, xEcran, yEcran, decalajTabla, zoomScale);
        obtineCoordEcran(board.xb, i, xEcran1, yEcran1, decalajTabla, zoomScale);
        if(yEcran>board.ya && yEcran1<board.yb)
            line( max(xEcran, board.xa), yEcran, min(xEcran1, board.xb), yEcran1 );
    }
    for(j=board.xa; j<=board.xb; j=j+laturaPatrat){ // liniile verticale
        obtineCoordEcran(j,board.ya, xEcran, yEcran, decalajTabla, zoomScale);
        obtineCoordEcran(j, board.yb, xEcran1, yEcran1, decalajTabla, zoomScale);
        if(xEcran>board.xa && xEcran1<board.xb)
            line( xEcran, max(yEcran, board.ya), xEcran1, min(yEcran1, board.yb) );
    }
    setcolor(BLACK);
}

int indexOcupiesSpace(Board board, POINT P, decalaj decalajTabla)
{
    int indexPiesa = -1;

    int x1, y1;
    POINT P1; // punctul de pe tabla corspunzator lui P
    obtineCoordTabla(P.x, P.y, x1, y1, decalajTabla, zoomScale);
    P1.x=x1; P1.y=y1;

    for (int i = 0; i < board.elements_lg; i++)
    {
        if ((abs(board.elements[i].x - P1.x) < board.elements[i].width * laturaPatrat) && (abs(board.elements[i].y - P1.y) < board.elements[i].height * laturaPatrat))
        {
            indexPiesa = i;
            break;

        }
    }
    return indexPiesa;
}

connectionPoint *getConnectionPoint(Board &board, POINT cursorPosition)
{
    connectionPoint *punctGasit = NULL;

    for (int i = 0; i < board.elements_lg; i++)
    {
        for (int j = 0; j < board.elements[i].connectionPoints_nr; j++)
        {
            int x = board.elements[i].connectionPoints[j].x - cursorPosition.x;
            int y = board.elements[i].connectionPoints[j].y - cursorPosition.y;

            if (x*x + y*y <= (board.elements[i].connectionPoints[j].r)*(board.elements[i].connectionPoints[j].r))
            {
                punctGasit = &(board.elements[i].connectionPoints[j]);
            }
        }
    }

    return punctGasit;
}

void addBoardPiesa (POINT P, Board &board, char elementRuta[100])
{
    board.elements[board.elements_lg].x = P.x;
    board.elements[board.elements_lg].y = P.y;

    board.elements[board.elements_lg].width = 2;
    board.elements[board.elements_lg].height = 1;

    board.elements[board.elements_lg].connectionPoints_nr = 2;

    board.elements[board.elements_lg].connectionPoints[0].x = P.x + 45;
    board.elements[board.elements_lg].connectionPoints[0].y = P.y;
    board.elements[board.elements_lg].connectionPoints[0].r = 5;

    board.elements[board.elements_lg].connectionPoints[1].x = P.x - 45;
    board.elements[board.elements_lg].connectionPoints[1].y = P.y;
    board.elements[board.elements_lg].connectionPoints[1].r = 5;

    strcpy(board.elements[board.elements_lg].source, elementRuta);
    board.elements_lg++;
}

void modifyBoardPiesa (POINT P, Board &board, int indexCurrentDraggingPiesa)
{
    board.elements[indexCurrentDraggingPiesa].x = P.x;
    board.elements[indexCurrentDraggingPiesa].y = P.y;

    board.elements[indexCurrentDraggingPiesa].connectionPoints[0].x = P.x + 45;
    board.elements[indexCurrentDraggingPiesa].connectionPoints[0].y = P.y;
    board.elements[indexCurrentDraggingPiesa].connectionPoints[0].r = 5;

    board.elements[indexCurrentDraggingPiesa].connectionPoints[1].x = P.x - 45;
    board.elements[indexCurrentDraggingPiesa].connectionPoints[1].y = P.y;
    board.elements[indexCurrentDraggingPiesa].connectionPoints[1].r = 5;
}

void removePiesa(Board &board, int indexEliminaPiesa)
{
    for (int j = 0; j < board.elements[indexEliminaPiesa].connectionPoints_nr; j++)
    {
        if (board.elements[indexEliminaPiesa].connectionPoints[j].legatura != NULL)
        {
            board.elements[indexEliminaPiesa].connectionPoints[j].legatura -> legatura -> start = false;
            board.elements[indexEliminaPiesa].connectionPoints[j].legatura -> legatura = NULL;

            board.elements[indexEliminaPiesa].connectionPoints[j].start = false;
            board.elements[indexEliminaPiesa].connectionPoints[j].legatura = NULL;
        }
    }

    for (int i = indexEliminaPiesa; i < board.elements_lg; i++)
    {
        board.elements[i] = board.elements[i + 1];
    }

    board.elements_lg--;
}

void obtinePunctUtil(POINT A, POINT &B, decalaj decalajTabla)
{
    int xTabla, yTabla;
    int xTabla1, yTabla1;
    obtineCoordTabla(A.x, A.y, xTabla, yTabla, decalajTabla, zoomScale);
    int rx,ry;
    rx = xTabla%laturaPatrat;
    ry = yTabla%laturaPatrat;
    if(rx<laturaPatrat/2)
        xTabla1 = xTabla-rx;
    else xTabla1 = xTabla+(laturaPatrat-rx);
    if(ry<laturaPatrat/2)
        yTabla1 = yTabla-ry;
    else yTabla1 = yTabla+(laturaPatrat-ry);
    B.x=xTabla1;
    B.y=yTabla1;
}

void puneSimbol(FILE *f, POINT c)
{
    setlinestyle(0,0,3);
    /*
    linesettingstype linfo;
    getlinesettings(&linfo);
    //cout<<linfo.thickness; */

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
            line(c.x+laturaPatrat*zoomScale*cf[0] , c.y+laturaPatrat*zoomScale*cf[1] , c.x+laturaPatrat*zoomScale*cf[2] , c.y+laturaPatrat*zoomScale*cf[3] );
        }
        else if(lit=='a'){
            for(j=0;j<5;++j)
                fscanf(f,"%f", &cf[j]);
            arc(c.x+laturaPatrat*zoomScale*cf[0], c.y+laturaPatrat*zoomScale*cf[1],cf[2],cf[3],laturaPatrat*zoomScale*cf[4]);
        }
        else if(lit=='c'){
            for(j=0;j<5;++j)
                fscanf(f,"%f", &cf[j]);
            circle(c.x+laturaPatrat*zoomScale*cf[0], c.y+laturaPatrat*zoomScale*cf[1],laturaPatrat*zoomScale*cf[2]);
        }
        else if(lit=='e'){
            for(j=0;j<6;++j)
                fscanf(f,"%f", &cf[j]);
            ellipse(c.x+laturaPatrat*zoomScale*cf[0], c.y+laturaPatrat*zoomScale*cf[1],cf[2],cf[3],laturaPatrat*zoomScale*cf[4],laturaPatrat*zoomScale*cf[5]);
        }
    }
}
