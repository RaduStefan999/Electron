#include "../headers/board.h"

using namespace std;


void drawBoard (Board &board, bool redraw, decalaj decalajTabla, int indexPiesaSelectata)
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
        updateConnectionPointRotation(board.elements[i]);
    }

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

        if((xEcran - board.elements[i].width*laturaPatrat*zoomScale > board.xa) and (xEcran + board.elements[i].width*laturaPatrat*zoomScale < board.xb) and (yEcran - board.elements[i].height*laturaPatrat*zoomScale > board.ya) and (yEcran + board.elements[i].height*laturaPatrat*zoomScale < board.yb))
        {
            puneSimbol(f, P1, board, i);
            //cout<<board.elements[i].indexMF<<' ';
        }

        for (int j = 0; j < board.elements[i].connectionPoints_nr; j++)
        {
            setlinestyle(0,0,1);
            setcolor(RED);

            int xCerc, yCerc;

            obtineCoordEcran(board.elements[i].connectionPoints[j].x, board.elements[i].connectionPoints[j].y, xCerc, yCerc, decalajTabla, zoomScale);

            if((xCerc - board.elements[i].connectionPoints[j].r*zoomScale > board.xa) and (xCerc + board.elements[i].connectionPoints[j].r*zoomScale < board.xb) and (yCerc - board.elements[i].connectionPoints[j].r*zoomScale > board.ya) and (yCerc + board.elements[i].connectionPoints[j].r*zoomScale < board.yb))
            {
                circle(xCerc, yCerc, board.elements[i].connectionPoints[j].r * zoomScale);
            }

            if (board.elements[i].connectionPoints[j].legatura != NULL)
            {
                setlinestyle(1,0,3);

                if (board.elements[i].connectionPoints[j].start)
                {
                    int xCercTarget, yCercTarget;
                    obtineCoordEcran(board.elements[i].connectionPoints[j].legatura -> x, board.elements[i].connectionPoints[j].legatura -> y, xCercTarget, yCercTarget, decalajTabla, zoomScale);

                    if(xCerc>board.xa and xCerc<board.xb and yCerc>board.ya and yCerc<board.yb && xCercTarget>board.xa and xCercTarget<board.xb and yCercTarget>board.ya and yCercTarget<board.yb)
                    {
                        line(xCerc, yCerc, xCercTarget, yCerc);
                        line(xCercTarget, yCerc, xCercTarget, yCercTarget);
                    }

                }
            }
        }
    }
    if(indexPiesaSelectata!=-1)
    {
        if(board.elements[indexPiesaSelectata].display_continut==true)
            displayContinutPiesa(board, indexPiesaSelectata, decalajTabla);
        else
            if(board.elements[indexPiesaSelectata].modifica_continut==true)
                modificaContinutPiesa(board, indexPiesaSelectata, decalajTabla);
    }

    if(board.dialogBox.afis==1)
        openDialogBox(board, decalajTabla);
}

void updateConnectionPointRotation(boardElement &element)
{
    int aux = 1;

    if (element.rotation % 2 == 0)
    {
        if (element.rotation == 2)
        {
            aux = -1;
        }

        element.width = 2;
        element.height = 1;

        element.connectionPoints[0].x = element.x + aux*2*laturaPatrat;
        element.connectionPoints[0].y = element.y;

        element.connectionPoints[1].x = element.x - aux*2*laturaPatrat;
        element.connectionPoints[1].y = element.y;
    }

    if (element.rotation % 2 == 1)
    {
        if (element.rotation == 3)
        {
            aux = -1;
        }

        element.width = 1;
        element.height = 2;

        element.connectionPoints[0].x = element.x;
        element.connectionPoints[0].y = element.y + aux*2*laturaPatrat;

        element.connectionPoints[1].x = element.x;
        element.connectionPoints[1].y = element.y - aux*2*laturaPatrat;
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

connectionPoint *getConnectionPoint(Board &board, POINT cursorPosition, decalaj decalajTabla)
{
    connectionPoint *punctGasit = NULL;

    int x1, y1;
    POINT P1; // punctul de pe tabla corspunzator lui P
    obtineCoordTabla(cursorPosition.x, cursorPosition.y, x1, y1, decalajTabla, zoomScale);
    P1.x=x1; P1.y=y1;

    for (int i = 0; i < board.elements_lg; i++)
    {
        for (int j = 0; j < board.elements[i].connectionPoints_nr; j++)
        {
            int x = board.elements[i].connectionPoints[j].x - P1.x;
            int y = board.elements[i].connectionPoints[j].y - P1.y;

            if (x*x + y*y <= (board.elements[i].connectionPoints[j].r)*(board.elements[i].connectionPoints[j].r))
            {
                punctGasit = &(board.elements[i].connectionPoints[j]);
                break;
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

    board.elements[board.elements_lg].connectionPoints[0].x = P.x + 2*laturaPatrat;
    board.elements[board.elements_lg].connectionPoints[0].y = P.y;
    board.elements[board.elements_lg].connectionPoints[0].r = 5;

    board.elements[board.elements_lg].connectionPoints[1].x = P.x - 2*laturaPatrat;
    board.elements[board.elements_lg].connectionPoints[1].y = P.y;
    board.elements[board.elements_lg].connectionPoints[1].r = 5;

    strcpy(board.elements[board.elements_lg].source, elementRuta);
    board.elements_lg++;
}

void modifyBoardPiesa (POINT P, Board &board, int indexCurrentDraggingPiesa)
{
    board.elements[indexCurrentDraggingPiesa].x = P.x;
    board.elements[indexCurrentDraggingPiesa].y = P.y;

    board.elements[indexCurrentDraggingPiesa].connectionPoints[0].x = P.x + 2*laturaPatrat;
    board.elements[indexCurrentDraggingPiesa].connectionPoints[0].y = P.y;
    board.elements[indexCurrentDraggingPiesa].connectionPoints[0].r = 5;

    board.elements[indexCurrentDraggingPiesa].connectionPoints[1].x = P.x - 2*laturaPatrat;
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

void puneSimbol(FILE *f, POINT c, Board &board, int i)
{
    setlinestyle(0,0,3);
    /*
    linesettingstype linfo;
    getlinesettings(&linfo);
    //cout<<linfo.thickness; */

    char text[20];
    fgets(text,100,f);
    if(i!=-1)
    {
        strcpy(board.elements[i].nume, text);
        setMF_UM(board, i);
    }


    int nrNoduri,j=0;
    fscanf(f, "%d", &nrNoduri);
    board.elements[i].connectionPoints_nr = nrNoduri;
    while(j<nrNoduri){
        /*POINT nod;
        fscanf(f, "%f", &nod.x);
        board.elements[i].connectionPoints[i].x = board.elements[i].x + nod.x*laturaPatrat;
        fscanf(f, "%f", &nod.y);
        board.elements[i].connectionPoints[i].y = board.elements[i].y + nod.y*laturaPatrat;
        board.elements[i].connectionPoints[i].r= 5*zoomScale;
        //asociazaNod(nod); */
        j++;
    }
    fseek(f,2,SEEK_CUR);
    fgets(text,20,f);
    text[0]=NULL;
    while(!feof(f)){
        setcolor(BLACK);
        char lit; int j;
        float cf[6];
        fscanf(f,"%c", &lit);

        if(i==-1)
            board.elements[i].rotation=0;
        if(lit=='l'){
            for(j=0;j<4;++j)
                fscanf(f,"%f", &cf[j]);

            rotatePoints(cf, board.elements[i].rotation);

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

void setMF_UM(Board &board, int i)
{
    if( strstr(board.elements[i].nume, "Condensator")){
        board.elements[i].nr_marimi_fizice=1;
        board.elements[i].marimeFizica[0]='C';

        board.elements[i].unitateMasura[0]='F';
    }
    else if(strstr(board.elements[i].nume, "Dioda")){
            board.elements[i].nr_marimi_fizice=4;
            board.elements[i].marimeFizica[0]='I';
            board.elements[i].marimeFizica[1]='R';
            board.elements[i].marimeFizica[2]='C';
            board.elements[i].marimeFizica[3]='U';

            board.elements[i].unitateMasura[0]='A';
            board.elements[i].unitateMasura[1]=213;  //omega
            board.elements[i].unitateMasura[2]='F';
            board.elements[i].unitateMasura[3]='V';
        }
        else if(strstr(board.elements[i].nume, "Dioda Zenner")){
                board.elements[i].nr_marimi_fizice=2;
                board.elements[i].marimeFizica[0]='U';
                board.elements[i].marimeFizica[1]='R';

                board.elements[i].unitateMasura[0]='V';
                board.elements[i].unitateMasura[1]=213;
        }
        else if(strstr(board.elements[i].nume, "Generator")){
            board.elements[i].nr_marimi_fizice=1;
            board.elements[i].marimeFizica[0]='I';

            board.elements[i].unitateMasura[0]='A';
        }
        else if(strstr(board.elements[i].nume, "Inductor")){
            board.elements[i].nr_marimi_fizice=1;
            board.elements[i].marimeFizica[0]='U';

            board.elements[i].unitateMasura[0]='V';
        }
        else if(strstr(board.elements[i].nume, "Rezistor")){
            board.elements[i].nr_marimi_fizice=1;
            board.elements[i].marimeFizica[0]='R';

            board.elements[i].unitateMasura[0]=213;
        }
        else if(strstr(board.elements[i].nume, "Sursa AC")){
            board.elements[i].nr_marimi_fizice=1;
            board.elements[i].marimeFizica[0]='U';

            board.elements[i].unitateMasura[0]='V';
        }
        else if(strstr(board.elements[i].nume, "Sursa de tensiune")){
            board.elements[i].nr_marimi_fizice=1;
            board.elements[i].marimeFizica[0]='U';
            board.elements[i].unitateMasura[0]='V';
        }

}


void displayContinutPiesa(Board &board, int i, decalaj decalajTabla)
{
    char text[50], s[50], s1[50], t[2], tasta, text2[50], sufix[3];
    int xEcran,yEcran;
    obtineCoordEcran(board.elements[i].connectionPoints[1].x,board.elements[i].connectionPoints[1].y+laturaPatrat, xEcran, yEcran, decalajTabla, zoomScale);

    text[0]=board.elements[i].marimeFizica[board.elements[i].indexMF] ;
    text[1]= '=';
    text[2]= '\0';

    itoa(board.elements[i].valoare[board.elements[i].indexMF], s, 10);

    sufix[0]=' ';
    sufix[1]= board.elements[i].unitateMasura[board.elements[i].indexMF];
    sufix[2]= '\0';

    t[0]=tasta; t[1]='\0';
    strcat(s,t);
    strcpy(s1,s); strcat(s1,sufix);
    setcolor(RED);
    strcpy(text2,text);
    strcat(text2,s1);
    outtextxy(xEcran, yEcran, text2);

    tasta=getch();
    if(tasta==13){  //enter
        board.elements[i].display_continut=false;
        board.elements[i].modifica_continut=true;
        drawBoard(board, true, decalajTabla, i);
    }
    else if(tasta==32){  //space
        board.elements[i].display_continut=false;
        board.elements[i].modifica_continut=false;
        drawBoard(board, true, decalajTabla,-1);
    }
    else if(tasta==39){  // ssageata dreapta
        board.elements[i].indexMF= (board.elements[i].indexMF + 1)% board.elements[i].nr_marimi_fizice;

        drawBoard(board, true, decalajTabla, i);
    }
    else if(tasta==37){ //sageata stanga
        board.elements[i].indexMF= (board.elements[i].indexMF - 1)% board.elements[i].nr_marimi_fizice;
        board.elements[i].display_continut=true;
        board.elements[i].modifica_continut=false;
        drawBoard(board, true, decalajTabla, i);
    }

}

void modificaContinutPiesa(Board &board, int i, decalaj decalajTabla)
{
    char text[50], s[50], s1[50], t[2], tasta, text2[50];
    int xEcran,yEcran;
    obtineCoordEcran(board.elements[i].connectionPoints[1].x,board.elements[i].connectionPoints[1].y+laturaPatrat, xEcran, yEcran, decalajTabla, zoomScale);

    text[0]=board.elements[i].marimeFizica[board.elements[i].indexMF] ;
    text[1]= '=';
    text[2]= '\0';

    strcpy(s,"");
    t[0]=tasta; t[1]='\0';
    strcat(s,t);
    strcpy(s1,s); strcat(s1,"_");
    setcolor(RED);
    strcpy(text2,text);
    strcat(text2,s1);
    outtextxy(xEcran,yEcran,text2);
    do {
        tasta=getch();
        if(tasta>=48 && tasta<=57)
        {
            t[0]=tasta; t[1]='\0';
            strcat(s,t);
            strcpy(s1,s); strcat(s1,"_");
            setcolor(RED);
            strcpy(text2,text);
            strcat(text2,s1);
            outtextxy(xEcran,yEcran,text2);
        }
    } while (tasta!=13);
    board.elements[i].valoare[board.elements[i].indexMF]=atoi(s);
    board.elements[i].modifica_continut=false;
    board.elements[i].display_continut=true;
    drawBoard(board, true, decalajTabla, i);

}

void rotatePoints(float points[], int rotation)
{
    for (int i = 0; i < rotation; i++)
    {
        float aux = points[0];

        points[0] = - points[1];
        points[1] = aux;

        aux = points[2];

        points[2] = - points[3];
        points[3] = aux;
    }
}
