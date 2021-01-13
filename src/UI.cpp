#include "../headers/UI.h"

using namespace std;


void setButtons(Buttons *ButtonsList, Board board)
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

        puneSimbol(f,P,board,-1);

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
    setlinestyle(0,0,5);
    rectangle(shape.x, shape.y, shape.x + shape.width, shape.y + shape.height);
}

void mouseUpdate(Mouse *mouse)
{
    mouse -> x = mousex();
    mouse -> y = mousey();

    mouse -> LMBClick = mouse -> RMBClick = mouse -> DClick = mouse -> justDropped = false;

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

    if(ismouseclick(WM_LBUTTONDBLCLK))
    {
        mouse -> DClick = true;
        clearmouseclick(WM_LBUTTONDBLCLK);
    }
}

void keyboardUpdate(Keyboard *keyboard)
{
    keyboard -> R_PRESS = false;

    if(GetAsyncKeyState(0x52) && keyboard -> R_CONTINUOUS == false)
    {
        keyboard -> R_PRESS = true;
    }

    keyboard -> R_CONTINUOUS = false;
    keyboard -> M_CONTINUOUS = false;

    if(GetAsyncKeyState(0x52))
    {
        keyboard -> R_CONTINUOUS = true;
    }

    if(GetAsyncKeyState(0x4D))
    {
        keyboard -> M_CONTINUOUS = true;
    }
}

void salvareCircuit(Board board, char nume[])
{
    char source[100];
    strcpy(source, "circuite\\");
    strcat(nume, ".txt");
    strcat(source,nume);

    //cout<<source<<' ';

    FILE *f;
    f = fopen(source, "w");

    int i,j;

    fprintf(f, "%d\n", board.elements_lg);  // nr piese
    for(i=0; i<board.elements_lg; i++)
    {
        fprintf(f, "%d %d\n", board.elements[i].x, board.elements[i].y); // coord piesa
        fprintf(f, "%d %d\n", board.elements[i].width , board.elements[i].height);  // latime, inaltime

        fprintf(f, "%d\n", board.elements[i].connectionPoints_nr);  // nr de noduri piesa
        for(j=0; j<board.elements[i].connectionPoints_nr; j++)
            fprintf(f, "%d %d %d %d %p\n", board.elements[i].connectionPoints[j].x, board.elements[i].connectionPoints[j].y, board.elements[i].connectionPoints[j].r, board.elements[i].connectionPoints[j].start, board.elements[i].connectionPoints[j].legatura);   // coord punct de leg

        fprintf(f, "%d\n", board.elements[i].rotation);

    /*
        fprintf(f, "%d\n", board.elements[i].nr_marimi_fizice);
        for(j=0; j<board.elements[i].nr_marimi_fizice; j++)
            fprintf(f, "%c %c\n", board.elements[i].marimeFizica[j], board.elements[i].unitateMasura[j] /*, board.elements[i].valoare[j] );
            */
        fprintf(f, "%d\n", board.elements[i].indexMF);
        /*fprintf(f, "%d %d\n", board.elements[i].display_continut, board.elements[i].modifica_continut);*/

        fprintf(f, "%s\n", board.elements[i].source);
        fprintf(f, "%s\n", board.elements[i].nume);

    }
    fclose(f);
}

void incarcareCircuit(Board &board, char nume[], decalaj decalajTabla)
{
    int i,j;

    char source[100];
    strcpy(source, "circuite\\");
    strcat(nume, ".txt");
    strcat(source,nume);

    FILE *f;
    if ((f = fopen(source ,"r")) == NULL){
        printf("Error! opening file2");
        exit(1);
    }

    fscanf(f, "%d", &board.elements_lg);
   // cout<<board.elements_lg<<'\n';

    for(i=0; i<board.elements_lg; i++)
    {
        fscanf(f, "%d", &board.elements[i].x);
        fscanf(f, "%d", &board.elements[i].y);
       // cout<<board.elements[i].x<<' '<<board.elements[i].y<<'\n';

        fscanf(f, "%d", &board.elements[i].width);
        fscanf(f, "%d", &board.elements[i].height);
        //cout<<board.elements[i].width<<' '<<board.elements[i].height<<'\n';

        fscanf(f, "%d", &board.elements[i].connectionPoints_nr);
       // cout<<board.elements[i].connectionPoints_nr<<'\n';

        for(j=0;j<board.elements[i].connectionPoints_nr; j++){
            fscanf(f, "%d", &board.elements[i].connectionPoints[j].x);
            fscanf(f, "%d", &board.elements[i].connectionPoints[j].y);
            fscanf(f, "%d", &board.elements[i].connectionPoints[j].r);
            fscanf(f, "%d", &board.elements[i].connectionPoints[j].start);
            fscanf(f, "%p", &board.elements[i].connectionPoints[j].legatura);
           // cout<<board.elements[i].connectionPoints[j].x<<' '<<board.elements[i].connectionPoints[j].y<<' '<<board.elements[i].connectionPoints[j].r<<' '<<board.elements[i].connectionPoints[j].start<<' '<<board.elements[i].connectionPoints[j].legatura<<'\n';
        }

        fscanf(f, "%d", &board.elements[i].rotation);
      //  cout<<board.elements[i].rotation<<'\n';
        /*
        fscanf(f, "%d", &board.elements[i].nr_marimi_fizice);
        cout<<board.elements[i].nr_marimi_fizice<<'\n';

         for(j=0; j<board.elements[i].nr_marimi_fizice; j++){
            fscanf(f, "%c", &board.elements[i].marimeFizica[j]);
            fscanf(f, "%c", &board.elements[i].unitateMasura[j]);
            //fscanf(f, "%d", &board.elements[i].valoare[j]);
            cout<<board.elements[i].marimeFizica[j]<<' '<<board.elements[i].unitateMasura[j]<<'\n';//<<board.elements[i].valoare[j]<<'\n';
        }
        */

        fscanf(f, "%d", &board.elements[i].indexMF);
        //cout<<board.elements[i].indexMF<<'\n';
        //cout<<board.elements[i].x<<'\n';
    /*
        fscanf(f, "%d", &board.elements[i].display_continut);
        fscanf(f, "%d", &board.elements[i].modifica_continut);
        // cout<<board.elements[i].display_continut<<' '<<board.elements[i].modifica_continut<<'\n';
    */
        fscanf(f, "%s", &board.elements[i].source);
       // cout<<board.elements[i].source<<'\n';

        fscanf(f, "%s", &board.elements[i].nume);
        //cout<<board.elements[i].nume<<'\n';
    }
    fclose(f);
    board.dialogBox.afis=false;
    drawBoard(board,true,decalajTabla,-1);
}

void openDialogBox(Board &board, decalaj decalajTabla)
{
    int x,y,x1,y1,L,l;
    L=(board.xb-board.xa)/4;
    l=(board.yb-board.ya)/11;
    x=(board.xb+board.xa)/2-L/2;
    x1=(board.xb+board.xa)/2+L/2;
    y=(board.yb+board.ya)/2-l/2;
    y1=(board.yb+board.ya)/2+l/2;

    setcolor(RGB(192,192,192));
    bar(x,y,x1,y1);
    setcolor(RED);
    setlinestyle(0,0,5);
    rectangle(x,y,x1,y1);
    setlinestyle(0,0,3);
    rectangle(x+3,y+3,x1-3,y1-3);

    if(board.dialogBox.mod==1)
        outtextxy(x+10,y+10,"SALVARE CIRCUIT");
    else outtextxy(x+10,y+10,"INCARCARE CIRCUIT");

    outtextxy(x+10,y+30,"introduceti nume circuit:");


    char tasta, t[3], s[50], nume[50];
    strcpy(s,"");
    t[0]=tasta; t[1]='\0';
    strcat(s,t);
    strcpy(nume,s); strcat(nume,"_");
    do {
        tasta=getch();
        if(isalnum(tasta))
        {
            t[0]=tasta; t[1]='\0';
            strcat(s,t);
            strcpy(nume,s); strcat(nume,"_");

            outtextxy(x+10,y+50,nume);
        }
    } while (tasta!=13);
    nume[strlen(nume)-1]=NULL;
    if(board.dialogBox.mod==1)
        salvareCircuit(board, nume);
    else{
        incarcareCircuit(board, nume, decalajTabla);
        cout<<board.elements[0].height;
    }
    board.dialogBox.afis=false;
    drawBoard(board,true,decalajTabla,-1);


}
