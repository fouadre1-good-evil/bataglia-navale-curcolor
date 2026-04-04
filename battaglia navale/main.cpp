#include <iostream>
#include <conio.h>    //per il getch
#include "curcolor.h" //Per curcolor
#include <ctime>      //Per il random
#include <cstdlib>    //Per il random
#include <io.h>       //Per le caselle
#include <fcntl.h>    //PEr le caselle
#include <strings.h>

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define SU  72
#define DX  77
#define GIU  80
#define SX 75

using namespace std;

const int MAIN_BG = 11;
const int MAIN_FG = 0;
const int INPUT_FG = 15;
const int INFO_FG = 5;
const int ERROR_FG = 4;
const int qcaselle_navi = 50;

bool maxaltezza = true;
bool minaltezza = false;
bool uscire = false;
bool scelta = true;
bool winplayer1 = false;
bool winplayer2 = false;
bool partitainiziata = false;
bool direzione = true;
bool postoc = false;

int c;
int i = 9;
int z = 0;
int x = 4;
int y = 2;
int Vx = 4;
int Vy = 2;
int Mx = 0;
int My = 0;
int Portaerei = 2;           //5 caselle di lunghezza  (nella matrice = 1)
int Corazzate = 3;           //4 caselle di lunghezza  (nella matrice = 2)
int Sottomarini = 4;         //3 caselle di lunghezza  (nella matrice = 3)
int Cacciatorpediniere = 5;  //2 caselle di lunghezza  (nella matrice = 4)
int Pattugliatori =  6;      //1 casella di lunghezza  (nella matrice = 5)
int totcaselle = 50;         //50 caselle di lunghezza
int PortaereiP = 0;
int CorazzateP = 0;
int SottomariniP = 0;
int CacciatorpediniereP = 0;
int PattugliatoriP = 0;
int player1 = 0;
int player2 = 0;


struct giocatore
{
    char nome [20] = {0};
    int punti;
    int tempo;
};

giocatore giocatori[99];


int mappaP1[10][30];
int mappaP2[10][30];
int mappaPC[10][30] = {{0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,1,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,1,0,0},
    {0,2,0,0,0,0,0,0,0,1,0,0,0,3,3,3,0,0,2,0,0,0,0,4,0,0,0,1,0,0},
    {0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,0,0,0,3,0,0,0,0,1,0,0},
    {0,0,4,0,0,4,4,0,0,0,0,0,0,5,0,0,0,0,2,0,0,0,3,0,0,5,0,1,0,0},
    {0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},
    {0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,4,4,0,0,0,5,0}
};

void displayMainLayout();
void INIZIO();
void Sposizionenavi();
void Sposizionenavi2();
void P_PC();
void stampacaselle();
void Gnavi();
void Classifica();
void USCITA();
void hideCursor();

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
    keybd_event(VK_MENU, 0x36,0,0);                  // ---------|
    keybd_event(VK_RETURN, 0x1c,0,0);                //          | ------> Per mettere lo
    keybd_event(VK_RETURN, 0x1c,KEYEVENTF_KEYUP,0);  //          | ------> schermo intero all'avvio
    keybd_event(VK_MENU, 0x38,KEYEVENTF_KEYUP,0);    // ---------|
    hideCursor();
    clearScreen(MAIN_BG, MAIN_FG);
    strcpy(giocatori[99].nome,"The Big Yahu");
    while (!uscire)
    {
        displayMainLayout();
    }
    USCITA ();
    Sleep(4000);
    return 0;
}

void displayMainLayout()
{
    setColor(MAIN_BG, MAIN_FG);
    gotoXY(0,0);
    cout << "Battaglia navale                                           - Data: ";
    displayToday();
    gotoXY(0,1);
    cout << "================================================================================";
    if (z == 0)
    {
        gotoXY(31,i);
        cout << ">";
    }
    else
    {
        gotoXY(31,z);
        cout <<" ";
        gotoXY(31,i);
        cout <<">";
    }
    if (i == 9)
    {
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(32,9);
        cout << "Inizia";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    else
    {
        gotoXY(32,9);
        cout << "Inizia";
    }
    if (i == 10)
    {
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(32,10);
        cout << "Gestione navi";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    else
    {
        gotoXY(32,10);
        cout << "Gestione navi";
    }
    if (i == 11)
    {
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(32,11);
        cout << "Classifica";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    else
    {
        gotoXY(32,11);
        cout << "Classifica";
    }
    if (i == 12)
    {
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(32,12);
        cout << "Esci";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    else
    {
        gotoXY(32,12);
        cout << "Esci";
    }
    gotoXY(0,20);
    cout << "Premere ESC per uscire dal programma";
    gotoXY(0,21);
    cout << "================================================================================";
    c = _getch();
    if (i == 9)
    {
        maxaltezza = true;
    }
    else if (i == 12)
    {
        minaltezza = true;
    }
    if (c == SU && !maxaltezza)
    {
        z = i;
        i -= 1;
        minaltezza = false;
    }
    else if (c == GIU && !minaltezza)
    {
        z = i;
        i +=1 ;
        maxaltezza = false;
    }
    if (c == ENTER)
    {
        switch (i)
        {
        case 9:
            partitainiziata = true;
            INIZIO();
            partitainiziata = false;
            break;
        case 10:
            Gnavi();
            break;
        case 11:
            Classifica();
            break;
        case 12:
            uscire = true;
            break;
        }
    }
    if (c == ESC)
    {
        uscire = true;
    }
}

void INIZIO ()
{
    clearScreen(MAIN_BG, MAIN_FG);
    system("color B0");
    P_PC();
    clearScreen(MAIN_BG, MAIN_FG);
    char nome [20];
    bool messo = false;
    if (!uscire)
    {
        while (!uscire)
        {
            if (!scelta)  //2Player
            {
                i = 1;
                z = i;
                bool p = false;
dinuovo:
                if (p == false)
                {
                    cout << "Inserisci il nome del primo giocatore:" <<endl;
                }
                else
                {
                    cout << "Inserisci il nome del secondo giocatore :" <<endl;
                }
                cin.getline(nome,20);
                for (int Cnomi = 0; Cnomi < 100; Cnomi++)
                {
                    if (strcmp(nome ,giocatori[Cnomi].nome) == 0 )
                    {

                        while (c != ESC)
                        {
                            clearScreen(MAIN_BG, MAIN_FG);
                            cout << "Questo nome è gia in uso vuoi continuare con le statistiche di questo nome?" <<endl;
                            gotoXY(1,1);
                            if (i == 1)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                cout << " Si";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            else
                            {
                                cout << " Si";
                            }
                            gotoXY(1,2);
                            if(i == 2)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                cout << " No";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            else
                            {
                                cout << " No";
                            }
                            gotoXY(0,z);
                            cout << " ";
                            gotoXY(0,i);
                            cout << ">";
                            z = i;
                            c = _getch();
                            if (c == SU && i != 1)
                                i -= 1;

                            else if (c == SU && i == 1)
                            {
                                i = 2;
                            }
                            if (c == GIU && i != 2)
                            {
                                i += 1;
                            }
                            else if (c == GIU && i == 2)
                            {
                                i = 1;
                            }
                            if (c == ENTER)
                            {
                                if(i == 1 && p == false)
                                {
                                    player1 = Cnomi;
                                    clearScreen(MAIN_BG, MAIN_FG);
                                    Sposizionenavi();
                                    p = true;
                                    messo = true;
                                    cout << "Debug";
                                    Sleep(2000);
                                    goto dinuovo;
                                }
                                else if(i == 1 && p == true)
                                {
                                    player2 = Cnomi;
                                    clearScreen(MAIN_BG, MAIN_FG);
                                    Sposizionenavi2();
                                    messo = true;
                                    p = false;
                                }
                                else
                                {
                                    clearScreen(MAIN_BG, MAIN_FG);
                                    cout << "Debug";
                                    Sleep(2000);
                                    goto dinuovo;
                                }
                            }
                        }
                    }
                }
                if(messo == false){
                    for (int Cnomi = 0; Cnomi < 100; Cnomi++){
                        if(giocatori[Cnomi].nome[0] == '\0'){
                           strcpy(giocatori[Cnomi].nome ,nome);
                           if (p = true){
                                player1 = Cnomi;
                                Sposizionenavi();
                           }else{
                               player2 = Cnomi;
                               Sposizionenavi2();
                           }
                           p = true;
                        }
                    }
                }
            }
            else          //PC
            {
                i = 1;
                z = i;
dinuovo2:
                cout << "Inserisci il tuo nome:" <<endl;
                gotoXY(21,0);
                cin.getline(nome,20);
                for (int Cnomi = 0; Cnomi < 100; Cnomi++)
                {
                    if (nome == giocatori[Cnomi].nome)
                    {
                        while (c != ESC)
                        {
                            clearScreen(MAIN_BG, MAIN_FG);
                            cout << "Questo nome è gia in uso vuoi continuare con le statistiche di questo nome?" <<endl;
                            gotoXY(1,1);
                            if (i == 1)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                cout << " Si";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            else
                            {
                                cout << " Si";
                            }
                            gotoXY(1,2);
                            if(i == 2)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                cout << " No";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            else
                            {
                                cout << " No";
                            }
                            gotoXY(0,z);
                            cout << " ";
                            gotoXY(0,i);
                            cout << ">";
                            z = i;
                            c = _getch();
                            if (c == SU && i != 1)
                                i -= 1;

                            else if (c == SU && i == 1)
                            {
                                i = 2;
                            }
                            if (c == GIU && i != 2)
                            {
                                i += 1;
                            }
                            else if (c == GIU && i == 2)
                            {
                                i = 1;
                            }
                            if (c == ENTER)
                            {
                                if(i == 1)
                                {
                                    player1 = Cnomi;
                                    clearScreen(MAIN_BG, MAIN_FG);
                                    Sposizionenavi();
                                }
                                else
                                {
                                    clearScreen(MAIN_BG, MAIN_FG);
                                    goto dinuovo2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Sposizionenavi()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    clearScreen(MAIN_BG, MAIN_FG);
    int x1;
    int y1;
    i = 2;
    z = 2;
    maxaltezza = true;
    minaltezza = false;
    do
    {
        gotoXY(1,2);
        if (i == 2)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Portaerei";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Portaerei";
        }
        cout << " (" << Portaerei << " rimaste)";
        gotoXY(1,5);
        if ( i == 5)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Corazzate";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Corazzate";
        }
        cout << " (" << Corazzate << " rimaste) ";
        gotoXY(1,8);
        if (i == 8)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Sottomarini";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Sottomarini";
        }
        cout << " (" << Sottomarini << " rimaste)";
        gotoXY(1,11);
        if (i == 11)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Cacciatorpediniere";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Cacciatorpediniere";
        }
        cout << " (" << Cacciatorpediniere << " rimaste)";
        gotoXY(1,14);
        if (i == 14)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Pattugliatori";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Pattugliatori";
        }
        cout << " (" << Pattugliatori << " rimaste)";
        gotoXY(0,z);
        cout << " ";
        gotoXY(0,i);
        cout << ">";
        z = i;
        c = _getch();
        if (i == 2)
        {
            maxaltezza = true;
        }
        else if (i == 14)
        {
            minaltezza = true;
        }
        if (c == SU && !maxaltezza)
        {
            i -= 3;
            minaltezza = false;
        }
        if (c == GIU && !minaltezza)
        {
            i += 3;
            maxaltezza = false;
        }
        if (c == ENTER)
        {
            if(i == 2 && Portaerei != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Portaerei != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 134)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐┌───┐┌───┐┌───┐┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   ││   ││   ││   ││   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘└───┘└───┘└───┘└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐┌───┐┌───┐┌───┐┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   ││   ││   ││   ││   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘└───┘└───┘└───┘└───┘";
                    }
                    if(y <= 17)
                    {
                        for(int k = 0; k < 15; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP1[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐┌───┐┌───┐┌───┐┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   ││   ││   ││   ││   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘└───┘└───┘└───┘└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 20)
                        {
                            for(int k = 0; k < 15; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 129)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 17)
                        {
                            y += 3;
                            My += 1;
                        }
                    }

                    if (c == BACKSPACE && direzione == true && y < 20)
                    {
                        direzione = false;
                    }
                    else if (c == BACKSPACE && direzione == false && x < 134)
                    {
                        direzione = true;
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 5; k++)
                    {
                        if (mappaP1[y1][x1 + k] != 0 || mappaP1[y1 - 1][x1 + k] == 1 || mappaP1[y1][x1 + k - 1] == 1 || mappaP1[y1 - 1][x1 + k - 1] == 1 || mappaP1[y1 - 1][x1 + k + 1] == 1 || mappaP1[y1 + 1][x1 + k - 1] == 1 || mappaP1[y1 + 1][x1 + k + 1] == 1 || mappaP1[y1 + 1][x1 + k] == 1 || mappaP1[y1][x1 + k + 1] == 1 || mappaP1[y1][x1 + k] == 1)
                        {
                            postoc = true;
                        }
                        if (mappaP1[y1 + k][x1] != 0 || mappaP1[y1 + k- 1][x1] == 1 || mappaP1[y1 + k][x1 - 1] == 1 || mappaP1[y1 + k - 1][x1 - 1] == 1 || mappaP1[y1 + k - 1][x1 + 1] == 1 || mappaP1[y1 + k + 1][x1 - 1] == 1 || mappaP1[y1 + k + 1][x1 + 1] == 1 || mappaP1[y1 + k + 1][x1] == 1 || mappaP1[y1 + k][x1 + 1] == 1 || mappaP1[y1 + k][x1] == 1)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Portaerei--;
                        for (int k = 0; k < 5; k++)
                        {
                            if (direzione)
                            {
                                mappaP1[y1][x1 + k] = 1;
                            }
                            else
                            {
                                mappaP1[y1 + k][x1] = 1;
                            }
                        }
                    }
                }
            }
            if(i == 5 && Corazzate != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Corazzate != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 139)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐┌───┐┌───┐┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   ││   ││   ││   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘└───┘└───┘└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐┌───┐┌───┐┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   ││   ││   ││   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘└───┘└───┘└───┘";
                    }
                    if(y <= 20)
                    {
                        for(int k = 0; k < 12; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP1[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐┌───┐┌───┐┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   ││   ││   ││   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘└───┘└───┘└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 23)
                        {
                            for(int k = 0; k < 12; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 134)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 20)
                        {
                            y += 3;
                            My += 1;
                        }
                    }

                    if (c == BACKSPACE && direzione == true && y < 23)
                    {
                        direzione = false;
                    }
                    else if (c == BACKSPACE && direzione == false && x < 139)
                    {
                        direzione = true;
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 5; k++)
                    {
                        if (mappaP1[y1][x1 + k] != 0 || mappaP1[y1 - 1][x1 + k] == 2 || mappaP1[y1][x1 + k - 1] == 2 || mappaP1[y1 - 1][x1 + k - 1] == 2 || mappaP1[y1 - 1][x1 + k + 1] == 2 || mappaP1[y1 + 1][x1 + k - 1] == 2 || mappaP1[y1 + 1][x1 + k + 1] == 2 || mappaP1[y1 + 1][x1 + k] == 2 || mappaP1[y1][x1 + k + 1] == 2 || mappaP1[y1][x1 + k] == 2)
                        {
                            postoc = true;
                        }
                        if (mappaP1[y1 + k][x1] != 0 || mappaP1[y1 + k- 1][x1] == 2 || mappaP1[y1 + k][x1 - 1] == 2 || mappaP1[y1 + k - 1][x1 - 1] == 2 || mappaP1[y1 + k - 1][x1 + 1] == 2 || mappaP1[y1 + k + 1][x1 - 1] == 2 || mappaP1[y1 + k + 1][x1 + 1] == 2 || mappaP1[y1 + k + 1][x1] == 2 || mappaP1[y1 + k][x1 + 1] == 2 || mappaP1[y1 + k][x1] == 2)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Corazzate--;
                        for (int k = 0; k < 4; k++)
                        {
                            if (direzione)
                            {
                                mappaP1[y1][x1 + k] = 2;
                            }
                            else
                            {
                                mappaP1[y1 + k][x1] = 2;
                            }
                        }
                    }
                }
            }
            if(i == 8 && Sottomarini != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Sottomarini != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 144)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐┌───┐┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   ││   ││   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘└───┘└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐┌───┐┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   ││   ││   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘└───┘└───┘";
                    }
                    if(y <= 23)
                    {
                        for(int k = 0; k < 9; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP1[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐┌───┐┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   ││   ││   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘└───┘└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 26)
                        {
                            for(int k = 0; k < 9; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 139)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 23)
                        {
                            y += 3;
                            My += 1;
                        }
                    }

                    if (c == BACKSPACE && direzione == true && y < 26)
                    {
                        direzione = false;
                    }
                    else if (c == BACKSPACE && direzione == false && x < 144)
                    {
                        direzione = true;
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 5; k++)
                    {
                        if (mappaP1[y1][x1 + k] != 0 || mappaP1[y1 - 1][x1 + k] == 3 || mappaP1[y1][x1 + k - 1] == 3 || mappaP1[y1 - 1][x1 + k - 1] == 3 || mappaP1[y1 - 1][x1 + k + 1] == 3 || mappaP1[y1 + 1][x1 + k - 1] == 3 || mappaP1[y1 + 1][x1 + k + 1] == 3 || mappaP1[y1 + 1][x1 + k] == 3 || mappaP1[y1][x1 + k + 1] == 3 || mappaP1[y1][x1 + k] == 3)
                        {
                            postoc = true;
                        }
                        if (mappaP1[y1 + k][x1] != 0 || mappaP1[y1 + k- 1][x1] == 3 || mappaP1[y1 + k][x1 - 1] == 3 || mappaP1[y1 + k - 1][x1 - 1] == 3 || mappaP1[y1 + k - 1][x1 + 1] == 3 || mappaP1[y1 + k + 1][x1 - 1] == 3 || mappaP1[y1 + k + 1][x1 + 1] == 3 || mappaP1[y1 + k + 1][x1] == 3 || mappaP1[y1 + k][x1 + 1] == 3 || mappaP1[y1 + k][x1] == 3)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Sottomarini--;
                        for (int k = 0; k < 3; k++)
                        {
                            if (direzione)
                            {
                                mappaP1[y1][x1 + k] = 3;
                            }
                            else
                            {
                                mappaP1[y1 + k][x1] = 3;
                            }
                        }
                    }
                }
            }
            if(i == 11 && Cacciatorpediniere != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Cacciatorpediniere != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 144)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   ││   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   ││   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘└───┘";
                    }
                    if(y <= 26)
                    {
                        for(int k = 0; k < 6; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP1[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   ││   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 29)
                        {
                            for(int k = 0; k < 6; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 144)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 26)
                        {
                            y += 3;
                            My += 1;
                        }
                    }

                    if (c == BACKSPACE && direzione == true && y < 29)
                    {
                        direzione = false;
                    }
                    else if (c == BACKSPACE && direzione == false && x < 149)
                    {
                        direzione = true;
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 5; k++)
                    {
                        if (mappaP1[y1][x1 + k] != 0 || mappaP1[y1 - 1][x1 + k] == 4 || mappaP1[y1][x1 + k - 1] == 4 || mappaP1[y1 - 1][x1 + k - 1] == 4 || mappaP1[y1 - 1][x1 + k + 1] == 4 || mappaP1[y1 + 1][x1 + k - 1] == 4 || mappaP1[y1 + 1][x1 + k + 1] == 4 || mappaP1[y1 + 1][x1 + k] == 4 || mappaP1[y1][x1 + k + 1] == 4 || mappaP1[y1][x1 + k] == 4)
                        {
                            postoc = true;
                        }
                        if (mappaP1[y1 + k][x1] != 0 || mappaP1[y1 + k- 1][x1] == 4 || mappaP1[y1 + k][x1 - 1] == 4 || mappaP1[y1 + k - 1][x1 - 1] == 4 || mappaP1[y1 + k - 1][x1 + 1] == 4 || mappaP1[y1 + k + 1][x1 - 1] == 4 || mappaP1[y1 + k + 1][x1 + 1] == 4 || mappaP1[y1 + k + 1][x1] == 4 || mappaP1[y1 + k][x1 + 1] == 4 || mappaP1[y1 + k][x1] == 4)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Cacciatorpediniere--;
                        for (int k = 0; k < 2; k++)
                        {
                            if (direzione)
                            {
                                mappaP1[y1][x1 + k] = 4;
                            }
                            else
                            {
                                mappaP1[y1 + k][x1] = 4;
                            }
                        }
                    }
                }
            }
            if(i == 14 && Pattugliatori != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Pattugliatori != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 144)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘";
                    }
                    if(y <= 26)
                    {
                        for(int k = 0; k < 3; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP1[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP1[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 29)
                        {
                            for(int k = 0; k < 3; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                            My += 1;
                        }
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 1; k++)
                    {
                        if (mappaP1[y1][x1 + k] != 0 || mappaP1[y1 - 1][x1 + k] == 5 || mappaP1[y1][x1 + k - 1] == 5 || mappaP1[y1 - 1][x1 + k - 1] == 5 || mappaP1[y1 - 1][x1 + k + 1] == 5 || mappaP1[y1 + 1][x1 + k - 1] == 5 || mappaP1[y1 + 1][x1 + k + 1] == 5 || mappaP1[y1 + 1][x1 + k] == 5 || mappaP1[y1][x1 + k + 1] == 5 || mappaP1[y1][x1 + k] == 5)
                        {
                            postoc = true;
                        }
                        if (mappaP1[y1 + k][x1] != 0 || mappaP1[y1 + k- 1][x1] == 5 || mappaP1[y1 + k][x1 - 1] == 5 || mappaP1[y1 + k - 1][x1 - 1] == 5 || mappaP1[y1 + k - 1][x1 + 1] == 5 || mappaP1[y1 + k + 1][x1 - 1] == 5 || mappaP1[y1 + k + 1][x1 + 1] == 5 || mappaP1[y1 + k + 1][x1] == 5 || mappaP1[y1 + k][x1 + 1] == 5 || mappaP1[y1 + k][x1] == 5)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Pattugliatori--;
                        for (int k = 0; k < 1; k++)
                        {
                            if (direzione)
                            {
                                mappaP1[y1][x1 + k] = 5;
                            }
                            else
                            {
                                mappaP1[y1 + k][x1] = 5;
                            }
                        }
                    }
                }
            }
            system("cls");
        }
        if (Portaerei != 0 && Corazzate != 0 && Sottomarini != 0 && Cacciatorpediniere != 0 && Pattugliatori != 0){
            c = ESC;
        }
    }
    while(c != ESC );
    Portaerei = PortaereiP;
    Corazzate = CorazzateP;
    Sottomarini = SottomariniP;
    Cacciatorpediniere = CacciatorpediniereP;
    Pattugliatori = PattugliatoriP;
}

void Sposizionenavi2()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    clearScreen(MAIN_BG, MAIN_FG);
    int x1;
    int y1;
    i = 2;
    z = 2;
    maxaltezza = true;
    minaltezza = false;
    do
    {
        gotoXY(1,2);
        if (i == 2)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Portaerei";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Portaerei";
        }
        cout << " (" << Portaerei << " rimaste)";
        gotoXY(1,5);
        if ( i == 5)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Corazzate";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Corazzate";
        }
        cout << " (" << Corazzate << " rimaste) ";
        gotoXY(1,8);
        if (i == 8)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Sottomarini";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Sottomarini";
        }
        cout << " (" << Sottomarini << " rimaste)";
        gotoXY(1,11);
        if (i == 11)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Cacciatorpediniere";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Cacciatorpediniere";
        }
        cout << " (" << Cacciatorpediniere << " rimaste)";
        gotoXY(1,14);
        if (i == 14)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "Pattugliatori";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            cout << "Pattugliatori";
        }
        cout << " (" << Pattugliatori << " rimaste)";
        gotoXY(0,z);
        cout << " ";
        gotoXY(0,i);
        cout << ">";
        z = i;
        c = _getch();
        if (i == 2)
        {
            maxaltezza = true;
        }
        else if (i == 14)
        {
            minaltezza = true;
        }
        if (c == SU && !maxaltezza)
        {
            i -= 3;
            minaltezza = false;
        }
        if (c == GIU && !minaltezza)
        {
            i += 3;
            maxaltezza = false;
        }
        if (c == ENTER)
        {
            if(i == 2 && Portaerei != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Portaerei != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 134)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐┌───┐┌───┐┌───┐┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   ││   ││   ││   ││   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘└───┘└───┘└───┘└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐┌───┐┌───┐┌───┐┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   ││   ││   ││   ││   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘└───┘└───┘└───┘└───┘";
                    }
                    if(y <= 17)
                    {
                        for(int k = 0; k < 15; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP2[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐┌───┐┌───┐┌───┐┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   ││   ││   ││   ││   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘└───┘└───┘└───┘└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 20)
                        {
                            for(int k = 0; k < 15; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 129)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 17)
                        {
                            y += 3;
                            My += 1;
                        }
                    }

                    if (c == BACKSPACE && direzione == true && y < 20)
                    {
                        direzione = false;
                    }
                    else if (c == BACKSPACE && direzione == false && x < 134)
                    {
                        direzione = true;
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 5; k++)
                    {
                        if (mappaP2[y1][x1 + k] != 0 || mappaP2[y1 - 1][x1 + k] == 1 || mappaP2[y1][x1 + k - 1] == 1 || mappaP2[y1 - 1][x1 + k - 1] == 1 || mappaP2[y1 - 1][x1 + k + 1] == 1 || mappaP2[y1 + 1][x1 + k - 1] == 1 || mappaP2[y1 + 1][x1 + k + 1] == 1 || mappaP2[y1 + 1][x1 + k] == 1 || mappaP2[y1][x1 + k + 1] == 1 || mappaP2[y1][x1 + k] == 1)
                        {
                            postoc = true;
                        }
                        if (mappaP2[y1 + k][x1] != 0 || mappaP2[y1 + k- 1][x1] == 1 || mappaP2[y1 + k][x1 - 1] == 1 || mappaP2[y1 + k - 1][x1 - 1] == 1 || mappaP2[y1 + k - 1][x1 + 1] == 1 || mappaP2[y1 + k + 1][x1 - 1] == 1 || mappaP2[y1 + k + 1][x1 + 1] == 1 || mappaP2[y1 + k + 1][x1] == 1 || mappaP2[y1 + k][x1 + 1] == 1 || mappaP2[y1 + k][x1] == 1)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Portaerei--;
                        for (int k = 0; k < 5; k++)
                        {
                            if (direzione)
                            {
                                mappaP2[y1][x1 + k] = 1;
                            }
                            else
                            {
                                mappaP2[y1 + k][x1] = 1;
                            }
                        }
                    }
                }
            }
            if(i == 5 && Corazzate != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Corazzate != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 139)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐┌───┐┌───┐┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   ││   ││   ││   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘└───┘└───┘└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐┌───┐┌───┐┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   ││   ││   ││   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘└───┘└───┘└───┘";
                    }
                    if(y <= 20)
                    {
                        for(int k = 0; k < 12; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP2[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐┌───┐┌───┐┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   ││   ││   ││   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘└───┘└───┘└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 23)
                        {
                            for(int k = 0; k < 12; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 134)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 20)
                        {
                            y += 3;
                            My += 1;
                        }
                    }

                    if (c == BACKSPACE && direzione == true && y < 23)
                    {
                        direzione = false;
                    }
                    else if (c == BACKSPACE && direzione == false && x < 139)
                    {
                        direzione = true;
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 5; k++)
                    {
                        if (mappaP2[y1][x1 + k] != 0 || mappaP2[y1 - 1][x1 + k] == 2 || mappaP2[y1][x1 + k - 1] == 2 || mappaP2[y1 - 1][x1 + k - 1] == 2 || mappaP2[y1 - 1][x1 + k + 1] == 2 || mappaP2[y1 + 1][x1 + k - 1] == 2 || mappaP2[y1 + 1][x1 + k + 1] == 2 || mappaP2[y1 + 1][x1 + k] == 2 || mappaP2[y1][x1 + k + 1] == 2 || mappaP2[y1][x1 + k] == 2)
                        {
                            postoc = true;
                        }
                        if (mappaP2[y1 + k][x1] != 0 || mappaP2[y1 + k- 1][x1] == 2 || mappaP2[y1 + k][x1 - 1] == 2 || mappaP2[y1 + k - 1][x1 - 1] == 2 || mappaP2[y1 + k - 1][x1 + 1] == 2 || mappaP2[y1 + k + 1][x1 - 1] == 2 || mappaP2[y1 + k + 1][x1 + 1] == 2 || mappaP2[y1 + k + 1][x1] == 2 || mappaP2[y1 + k][x1 + 1] == 2 || mappaP2[y1 + k][x1] == 2)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Corazzate--;
                        for (int k = 0; k < 4; k++)
                        {
                            if (direzione)
                            {
                                mappaP2[y1][x1 + k] = 2;
                            }
                            else
                            {
                                mappaP2[y1 + k][x1] = 2;
                            }
                        }
                    }
                }
            }
            if(i == 8 && Sottomarini != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Sottomarini != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 144)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐┌───┐┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   ││   ││   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘└───┘└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐┌───┐┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   ││   ││   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘└───┘└───┘";
                    }
                    if(y <= 23)
                    {
                        for(int k = 0; k < 9; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP2[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐┌───┐┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   ││   ││   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘└───┘└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 26)
                        {
                            for(int k = 0; k < 9; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 139)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 23)
                        {
                            y += 3;
                            My += 1;
                        }
                    }

                    if (c == BACKSPACE && direzione == true && y < 26)
                    {
                        direzione = false;
                    }
                    else if (c == BACKSPACE && direzione == false && x < 144)
                    {
                        direzione = true;
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 5; k++)
                    {
                        if (mappaP2[y1][x1 + k] != 0 || mappaP2[y1 - 1][x1 + k] == 3 || mappaP2[y1][x1 + k - 1] == 3 || mappaP2[y1 - 1][x1 + k - 1] == 3 || mappaP2[y1 - 1][x1 + k + 1] == 3 || mappaP2[y1 + 1][x1 + k - 1] == 3 || mappaP2[y1 + 1][x1 + k + 1] == 3 || mappaP2[y1 + 1][x1 + k] == 3 || mappaP2[y1][x1 + k + 1] == 3 || mappaP2[y1][x1 + k] == 3)
                        {
                            postoc = true;
                        }
                        if (mappaP2[y1 + k][x1] != 0 || mappaP2[y1 + k- 1][x1] == 3 || mappaP2[y1 + k][x1 - 1] == 3 || mappaP2[y1 + k - 1][x1 - 1] == 3 || mappaP2[y1 + k - 1][x1 + 1] == 3 || mappaP2[y1 + k + 1][x1 - 1] == 3 || mappaP2[y1 + k + 1][x1 + 1] == 3 || mappaP2[y1 + k + 1][x1] == 3 || mappaP2[y1 + k][x1 + 1] == 3 || mappaP2[y1 + k][x1] == 3)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Sottomarini--;
                        for (int k = 0; k < 3; k++)
                        {
                            if (direzione)
                            {
                                mappaP2[y1][x1 + k] = 3;
                            }
                            else
                            {
                                mappaP2[y1 + k][x1] = 3;
                            }
                        }
                    }
                }
            }
            if(i == 11 && Cacciatorpediniere != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Cacciatorpediniere != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 144)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   ││   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   ││   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘└───┘";
                    }
                    if(y <= 26)
                    {
                        for(int k = 0; k < 6; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP2[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   ││   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 29)
                        {
                            for(int k = 0; k < 6; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 144)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 26)
                        {
                            y += 3;
                            My += 1;
                        }
                    }

                    if (c == BACKSPACE && direzione == true && y < 29)
                    {
                        direzione = false;
                    }
                    else if (c == BACKSPACE && direzione == false && x < 149)
                    {
                        direzione = true;
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 5; k++)
                    {
                        if (mappaP2[y1][x1 + k] != 0 || mappaP2[y1 - 1][x1 + k] == 4 || mappaP2[y1][x1 + k - 1] == 4 || mappaP2[y1 - 1][x1 + k - 1] == 4 || mappaP2[y1 - 1][x1 + k + 1] == 4 || mappaP2[y1 + 1][x1 + k - 1] == 4 || mappaP2[y1 + 1][x1 + k + 1] == 4 || mappaP2[y1 + 1][x1 + k] == 4 || mappaP2[y1][x1 + k + 1] == 4 || mappaP2[y1][x1 + k] == 4)
                        {
                            postoc = true;
                        }
                        if (mappaP2[y1 + k][x1] != 0 || mappaP2[y1 + k- 1][x1] == 4 || mappaP2[y1 + k][x1 - 1] == 4 || mappaP2[y1 + k - 1][x1 - 1] == 4 || mappaP2[y1 + k - 1][x1 + 1] == 4 || mappaP2[y1 + k + 1][x1 - 1] == 4 || mappaP2[y1 + k + 1][x1 + 1] == 4 || mappaP2[y1 + k + 1][x1] == 4 || mappaP2[y1 + k][x1 + 1] == 4 || mappaP2[y1 + k][x1] == 4)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Cacciatorpediniere--;
                        for (int k = 0; k < 2; k++)
                        {
                            if (direzione)
                            {
                                mappaP2[y1][x1 + k] = 4;
                            }
                            else
                            {
                                mappaP2[y1 + k][x1] = 4;
                            }
                        }
                    }
                }
            }
            if(i == 14 && Pattugliatori != 0)
            {
                system("cls");
                stampacaselle();
                x = 4;
                y = 2;
                while(Pattugliatori != 0)
                {
                    if(direzione == false)
                    {
                        if (x < 144)
                        {
                            gotoXY(Vx,Vy);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2);
                            cout << "└───┘";
                        }
                    }
                    else
                    {
                        gotoXY(Vx,Vy);
                        cout << "┌───┐";
                        gotoXY(Vx,Vy + 1);
                        cout << "│   │";
                        gotoXY(Vx,Vy + 2);
                        cout << "└───┘";
                    }
                    if(y <= 26)
                    {
                        for(int k = 0; k < 3; k += 3)
                        {
                            gotoXY(Vx,Vy + k);
                            cout << "┌───┐";
                            gotoXY(Vx,Vy + 1 + k);
                            cout << "│   │";
                            gotoXY(Vx,Vy + 2 + k);
                            cout << "└───┘";
                        }
                    }
                    gotoXY(0,32);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,33);
                    cout << "                                                                                                                                                                                                              ";
                    gotoXY(0,34);
                    cout << "                                                                                                                                                                                                              ";
                    for (int j = 0; j < 30 ; j++)
                    {
                        gotoXY(154,2 + j);
                        cout <<"     ";
                        gotoXY(154,3 + j);
                        cout <<"     ";
                        gotoXY(154,4 + j);
                        cout <<"     ";
                    }
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 30; c++)
                        {
                            if (mappaP2[r][c] == 1)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 2)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 3)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_RED  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 4)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            if (mappaP2[r][c] == 5)
                            {
                                int posX = c * 5 + 4;
                                int posY = r * 3 + 2;
                                SetConsoleTextAttribute(h, BACKGROUND_BLUE  | BACKGROUND_RED | BACKGROUND_INTENSITY);
                                gotoXY(posX, posY);
                                cout << "┌───┐";
                                gotoXY(posX, posY + 1);
                                cout << "│   │";
                                gotoXY(posX, posY + 2);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    if (direzione == true)
                    {
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(x,y);
                        cout << "┌───┐";
                        gotoXY(x,y + 1);
                        cout << "│   │";
                        gotoXY(x,y + 2);
                        cout << "└───┘";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else
                    {
                        if (y < 29)
                        {
                            for(int k = 0; k < 3; k += 3)
                            {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                gotoXY(x,y + k);
                                cout << "┌───┐";
                                gotoXY(x,y + 1 + k);
                                cout << "│   │";
                                gotoXY(x,y + 2 + k);
                                cout << "└───┘";
                                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                        }
                    }
                    Vx = x;
                    Vy = y;
                    c = _getch();
                    if (direzione)
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                        }
                    }
                    else
                    {
                        if (c == DX && x != 149)
                        {
                            x += 5;
                            Mx += 1;
                        }
                        if (c == SX && x != 4)
                        {
                            x -= 5;
                            Mx -= 1;
                        }
                        if (c == SU && y != 2)
                        {
                            y -= 3;
                            My -= 1;
                        }
                        if (c == GIU && y != 29)
                        {
                            y += 3;
                            My += 1;
                        }
                    }
                    postoc = false;
                    x1 = x / 5;
                    y1 = y / 3;
                    for (int k = 0; k < 1; k++)
                    {
                        if (mappaP2[y1][x1 + k] != 0 || mappaP2[y1 - 1][x1 + k] == 5 || mappaP2[y1][x1 + k - 1] == 5 || mappaP2[y1 - 1][x1 + k - 1] == 5 || mappaP2[y1 - 1][x1 + k + 1] == 5 || mappaP2[y1 + 1][x1 + k - 1] == 5 || mappaP1[y1 + 1][x1 + k + 1] == 5 || mappaP2[y1 + 1][x1 + k] == 5 || mappaP2[y1][x1 + k + 1] == 5 || mappaP2[y1][x1 + k] == 5)
                        {
                            postoc = true;
                        }
                        if (mappaP2[y1 + k][x1] != 0 || mappaP2[y1 + k- 1][x1] == 5 || mappaP2[y1 + k][x1 - 1] == 5 || mappaP2[y1 + k - 1][x1 - 1] == 5 || mappaP2[y1 + k - 1][x1 + 1] == 5 || mappaP2[y1 + k + 1][x1 - 1] == 5 || mappaP1[y1 + k + 1][x1 + 1] == 5 || mappaP2[y1 + k + 1][x1] == 5 || mappaP2[y1 + k][x1 + 1] == 5 || mappaP2[y1 + k][x1] == 5)
                        {
                            postoc = true;
                        }
                    }
                    if (c == ENTER && !postoc)
                    {
                        Pattugliatori--;
                        for (int k = 0; k < 1; k++)
                        {
                            if (direzione)
                            {
                                mappaP2[y1][x1 + k] = 5;
                            }
                            else
                            {
                                mappaP2[y1 + k][x1] = 5;
                            }
                        }
                    }
                }
            }
            system("cls");
        }
        if (Portaerei != 0 && Corazzate != 0 && Sottomarini != 0 && Cacciatorpediniere != 0 && Pattugliatori != 0){
            c = ESC;
        }
    }
    while(c != ESC );
    Portaerei = PortaereiP;
    Corazzate = CorazzateP;
    Sottomarini = SottomariniP;
    Cacciatorpediniere = CacciatorpediniereP    ;
    Pattugliatori = PattugliatoriP;
}

void P_PC ()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int i = 1,z = 1;
    bool v = false;
    while (!uscire && !v)
    {
        gotoXY(1,0);
        cout << "┌─────────────────┐" <<endl;
        if ( i == 1 )
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(1,1);
            cout << "│-2 Player";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "        │" <<endl;
        }
        else
        {
            gotoXY(1,1);
            cout << "│-2 Player        │" <<endl;
        }
        if (i == 2)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(1,2);
            cout << "│-VS PC";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "           │" <<endl;
        }
        else
        {
            gotoXY(1,2);
            cout << "│-VS PC           │" <<endl;
        }
        if (i == 3)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(1,3);
            cout << "│-ESC per uscire";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            cout << "  │"<<endl;
        }
        else
        {
            gotoXY(1,3);
            cout << "│-ESC per uscire  │" <<endl;
        }
        gotoXY(1,4);
        cout << "└─────────────────┘" <<endl;
        gotoXY(0,z);
        cout << " ";
        gotoXY(0,i);
        cout << ">";
        c = _getch();
        if (i == 1)
        {
            maxaltezza = true;
        }
        else if (i == 3)
        {
            minaltezza = true;
        }
        if (c == SU && maxaltezza == false)
        {
            minaltezza = false;
            z = i;
            i -= 1;
        }
        else if (c== GIU && minaltezza == false)
        {
            maxaltezza = false;
            z = i;
            i += 1;
        }
        if (c == ENTER)
        {
            switch (i)
            {
            case 1:
                scelta = false;
                v = true;
                break;
            case 2:
                scelta = true;
                v = true;
                break;
            case 3:
                uscire = true;
                break;
            }
        }
        if (c == ESC)
        {
            uscire = true;
        }
    }
}

void stampacaselle()
{
    clearScreen(MAIN_BG, MAIN_FG);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout << R"(
      1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  A │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  B │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  C │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  D │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  E │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  F │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  G │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  H │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  I │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
    ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐
  J │   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   ││   │
    └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘
)";
    cout <<endl;
}

void Gnavi()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    clearScreen(MAIN_BG, MAIN_FG);
    bool esc = false;

    i = 9;
    z = 9;

    while(!esc){
rinizia:
        gotoXY (0 ,0);
        cout << "┌────────────────────────────────────┐"<<endl;
        gotoXY (0 ,1);
        cout << "│ Le navi sono:                      │"<<endl;
        gotoXY (0 ,2);
        cout << "│ -";
        if (Portaerei >= 10) {
            cout << Portaerei << " Portaerei          (5 caselle) │" <<endl;
        }
        else
        {
            cout << Portaerei << " Portaerei           (5 caselle) │" <<endl;
        }
        gotoXY (0 ,3);
        cout << "│ -";
        if (Corazzate >= 10)
        {
            cout << Corazzate << " Corazzate          (4 caselle) │" <<endl;
        }
        else
        {
            cout << Corazzate << " Corazzate           (4 caselle) │" <<endl;
        }
        gotoXY (0 ,4);
        cout << "│ -";
        if (Sottomarini >= 10)
        {
            cout << Sottomarini << " Sottomarini        (3 caselle) │" <<endl;
        }
        else
        {
            cout << Sottomarini << " Sottomarini         (3 caselle) │" <<endl;
        }
        gotoXY (0,5);
        cout << "│ -";
        if (Cacciatorpediniere >= 10)
        {
            cout << Cacciatorpediniere << " Cacciatorpediniere (2 caselle) │" <<endl;
        }
        else
        {
            cout << Cacciatorpediniere << " Cacciatorpediniere  (2 caselle) │" <<endl;
        }
        gotoXY (0,6);
        cout << "│ -";
        if (Pattugliatori >= 10)
        {
            cout << Pattugliatori << " Pattugliatori     (1 casella)  │" <<endl;
        }
        else
        {
            cout << Pattugliatori << " Pattugliatori       (1 casella) │ "<<endl;
        }
        gotoXY (0,7);
        cout << "└────────────────────────────────────┘" <<endl;
        gotoXY(0,8);
        cout << "vuoi cambiarle" <<endl;
        gotoXY(0,z);
        cout << " ";
        gotoXY(0,i);
        cout << ">";
        if (i == 9)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(1,9);
            cout << " SI"<<endl;
            maxaltezza = true;
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            gotoXY(1,9);
            cout << " SI"<<endl;
        }
        if(i == 10)
        {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(1,10);
            cout << " No"<<endl;
            minaltezza = true;
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        else
        {
            gotoXY(1,10);
            cout << " No"<<endl;
        }
        z = i;
        c = _getch();
        if (c == SU && !maxaltezza)
        {
            i -= 1;
            minaltezza = false;
        }
        else if (c == GIU && !minaltezza)
        {
            i += 1;
            maxaltezza = false;
        }
        else if (c == ENTER)
        {
            switch (i)
            {
            case 9:
                i = 3;
                totcaselle = 50;
                PortaereiP = Portaerei;
                CorazzateP = Corazzate;
                SottomariniP = Sottomarini;
                CacciatorpediniereP = Cacciatorpediniere;
                PattugliatoriP = Pattugliatori;
                clearScreen(MAIN_BG, MAIN_FG);
                while (true)
                {
                    if (i == 2){
                        gotoXY(1 ,1);
                        cout << "│ ";
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "Il numero di caselle int utilizzo e'--->";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "│";
                    }else{
                        gotoXY(1 ,1);
                        cout << "│ Il numero di caselle in utilizzo e'--->│";
                    }
                    if (i == 3){
                        gotoXY(1 ,3);
                        cout << "│ ";
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "I Portaerei valgono 5 caselle";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "          │";
                    }else{
                        gotoXY(1 ,3);
                        cout << "│ I Portaerei valgono 5 caselle          │";
                    }
                    if (i == 5){
                        gotoXY(1 ,5);
                        cout << "│ ";
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "Le Corazzate valgono 4 caselle";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "         │";
                    }else{
                        gotoXY(1 ,5);
                        cout << "│ Le Corazzate valgono 4 caselle         │";
                    }
                    if ( i == 7){
                        gotoXY(1, 7);
                        cout << "│ ";
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "I Sottomarini valgono 3 caselle";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "        │";
                    }else{
                        gotoXY(1, 7);
                        cout << "│ I Sottomarini valgono 3 caselle        │";
                    }
                    if (i == 9){
                        gotoXY(1 ,9);
                        cout << "│ ";
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "IL Cacciatorpediniere vale 2 caselle";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "   │";
                    }else{
                        gotoXY(1 ,9);
                        cout << "│ IL Cacciatorpediniere vale 2 caselle   │";
                    }
                    if (i == 11){
                        gotoXY(1 ,11);
                        cout << "│ ";
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "I Pattugliatori valgono 1 casella";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        cout << "      │";
                    }else{
                        gotoXY(1 ,11);
                        cout << "│ I Pattugliatori valgono 1 casella      │";
                    }
                    gotoXY(2 ,13);
                    cout << "Premere ENTER per andare confermare";

                    gotoXY(2 ,14);
                    cout << "Premere ESC per tornare indietro";

                    gotoXY(1 ,0);
                    cout << "┌────────────────────────────────────────┐";
                    gotoXY(1 ,2);
                    cout << "│                                        │";
                    gotoXY(1 ,4);
                    cout << "│                                        │";
                    gotoXY(1 ,6);
                    cout << "│                                        │";
                    gotoXY(1 ,8);
                    cout << "│                                        │";
                    gotoXY(1 ,10);
                    cout << "│                                        │";
                    gotoXY(1 ,12);
                    cout << "└────────────────────────────────────────┘";
                    if (totcaselle >= 10){
                        gotoXY(46 ,1);
                        cout << totcaselle;
                    }else{
                        gotoXY(46 ,1);
                        cout << "  ";
                        gotoXY(46 ,1);
                        cout << totcaselle;
                    }
                    gotoXY(44 ,3);
                    cout << "<";
                    gotoXY(0 ,z);
                    cout << " ";
                    gotoXY(0 ,i);
                    cout << ">";
                    if(Portaerei >= 10){
                        gotoXY(46 ,3);
                        cout << "  ";
                        gotoXY(45 ,3);
                        cout << " " << Portaerei << " ";
                        gotoXY(49 ,3);
                        cout << ">";
                    }else{
                        gotoXY(46 ,3);
                        cout << " ";
                        gotoXY(45 ,3);
                        cout << " " << Portaerei << " " ;
                        gotoXY(48 ,3);
                        cout << ">";
                    }
                    gotoXY(44 ,5);
                    cout << "<";
                    if(Corazzate >= 10){
                        gotoXY(46 ,5);
                        cout << "  ";
                        gotoXY(45 ,5);
                        cout << " " << Corazzate << " ";
                        gotoXY(49 ,5);
                        cout << ">";
                    }else{
                        gotoXY(46 ,5);
                        cout << " ";
                        gotoXY(45 ,5);
                        cout << " " << Corazzate << " " ;
                        gotoXY(48 ,5);
                        cout << ">";
                    }
                    gotoXY(44 ,7);
                    cout << "<";
                    if(Sottomarini >= 10){
                        gotoXY(46 ,7);
                        cout << "  ";
                        gotoXY(45 ,7);
                        cout << " " << Sottomarini << " ";
                        gotoXY(49 ,7);
                        cout << ">";
                    }else{
                        gotoXY(46 ,7);
                        cout << " ";
                        gotoXY(45 ,7);
                        cout << " " << Sottomarini << " " ;
                        gotoXY(48 ,7);
                        cout << ">";
                    }
                    gotoXY(44 ,9);
                    cout << "<";
                    if(Cacciatorpediniere >= 10){
                        gotoXY(46 ,9);
                        cout << "  ";
                        gotoXY(45 ,9);
                        cout << " " << Cacciatorpediniere << " ";
                        gotoXY(49 ,9);
                        cout << ">";
                    }else{
                        gotoXY(46 ,9);
                        cout << " ";
                        gotoXY(45 ,9);
                        cout << " " << Cacciatorpediniere << " " ;
                        gotoXY(48 ,9);
                        cout << ">";
                    }
                    gotoXY(44 ,11);
                    cout << "<";
                    if(Pattugliatori >= 10){
                        gotoXY(46 ,11);
                        cout << "  ";
                        gotoXY(45 ,11);
                        cout << " " << Pattugliatori << " ";
                        gotoXY(49 ,11);
                        cout << ">";
                    }else{
                        gotoXY(46 ,11);
                        cout << "  ";
                        gotoXY(45 ,11);
                        cout << " " << Pattugliatori << " " ;
                        gotoXY(48 ,11);
                        cout << ">";
                    }
                    c = _getch();
                    if (c == DX && (totcaselle + 5) <= 50 && i == 3 && (Portaerei + 1) >= 10){
                        Portaerei++;
                        gotoXY(48 ,3);
                        cout << " ";
                        gotoXY(46 ,3);
                        cout << Portaerei;
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(49 ,3);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        totcaselle += 5;
                    }else if (c == DX && (totcaselle + 5) <= 50 && i == 3 && (Portaerei + 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(48 ,3);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Portaerei++;
                        totcaselle += 5;
                    }else if (c == SX && (totcaselle - 5) >= 0 && i == 3 && (Portaerei - 1) >= 0 && (Portaerei - 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,3);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        gotoXY(49 ,3);
                        cout << " ";
                        gotoXY(48 ,3);
                        cout << ">";
                        Portaerei--;
                        totcaselle -= 5;
                    }else if (c == SX && (totcaselle - 5) >= 0 && i == 3 && (Portaerei - 1) >= 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,3);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Portaerei--;
                        totcaselle -= 5;
                    }
                    if(c == DX && (totcaselle + 4) <= 50 && i == 5 && (Corazzate + 1) >= 10){
                        Corazzate++;
                        gotoXY(48 ,5);
                        cout << " ";
                        gotoXY(46 ,5);
                        cout << Corazzate;
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(49 ,5);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        totcaselle += 4;
                    }else if (c == DX && (totcaselle + 4) <= 50 && i == 5 && (Corazzate + 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(48 ,5);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Corazzate++;
                        totcaselle += 4;
                    }else if (c == SX && (totcaselle - 4) >= 0 && i == 5 && (Corazzate - 1) >= 0 && (Corazzate - 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,5);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        gotoXY(49 ,5);
                        cout << " ";
                        gotoXY(48 ,5);
                        cout << ">";
                        Corazzate--;
                        totcaselle -= 4;
                    }else if (c == SX && (totcaselle - 4) >= 0 && i == 5 && (Corazzate - 1) >= 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,5);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Corazzate--;
                        totcaselle -= 4;
                    }
                    if(c == DX && (totcaselle + 3) <= 50 && i == 7 && (Sottomarini + 1) >= 10){
                        Sottomarini++;
                        gotoXY(48 ,7);
                        cout << " ";
                        gotoXY(46 ,7);
                        cout << Sottomarini;
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(49 ,7);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        totcaselle += 3;
                    }else if (c == DX && (totcaselle + 3) <= 50 && i == 7 && (Sottomarini + 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(48 ,7);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Sottomarini++;
                        totcaselle += 3;
                    }else if (c == SX && (totcaselle - 3) >= 0 && i == 7 && (Sottomarini - 1) >= 0 && (Sottomarini - 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,7);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        gotoXY(49 ,7);
                        cout << " ";
                        gotoXY(48 ,7);
                        cout << ">";
                        Sottomarini--;
                        totcaselle -= 3;
                    }else if (c == SX && (totcaselle - 3) >= 0 && i == 7 && (Sottomarini - 1) >= 0 && (Sottomarini - 1) >= 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,7);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Sottomarini--;
                        totcaselle -= 3;

                    }
                    if(c == DX && (totcaselle + 2) <= 50 && i == 9 && (Cacciatorpediniere + 1) >= 10){
                        Cacciatorpediniere++;
                        gotoXY(48 ,9);
                        cout << " ";
                        gotoXY(46 ,9);
                        cout << Cacciatorpediniere;
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(49 ,9);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        totcaselle += 2;
                    }else if (c == DX && (totcaselle + 2) <= 50 && i == 9 && (Cacciatorpediniere + 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(48 ,9);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Cacciatorpediniere++;
                        totcaselle += 2;
                    }else if (c == SX && (totcaselle - 2) >= 0 && i == 9 && (Cacciatorpediniere - 1) >= 0 && (Cacciatorpediniere - 1) <10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,9);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        gotoXY(49 ,9);
                        cout << " ";
                        gotoXY(48 ,9);
                        cout << ">";
                        Cacciatorpediniere--;
                        totcaselle -= 2;
                    }else if (c == SX && (totcaselle - 2) >= 0 && i == 9 && (Cacciatorpediniere - 1) >=10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,9);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        gotoXY(49 ,9);
                        cout << ">";
                        Cacciatorpediniere--;
                        totcaselle -= 2;
                    }
                    if(c == DX && (totcaselle + 1) <= 50 && i == 11 && (Pattugliatori + 1) >= 10){
                        Pattugliatori++;
                        gotoXY(48 ,11);
                        cout << " ";
                        gotoXY(46 ,11);
                        cout << Pattugliatori;
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(49 ,11);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        totcaselle += 1;
                    }else if (c == DX && (totcaselle + 1) <= 50 && i == 11 && (Pattugliatori + 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(48 ,11);
                        cout << ">";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Pattugliatori++;
                        totcaselle += 1;
                    }else if (c == SX && (totcaselle - 1) >= 0 && i == 11 && (Pattugliatori - 1) >= 0 && (Pattugliatori - 1) < 10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,11);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        gotoXY(49 ,11);
                        cout << " ";
                        gotoXY(48 ,11);
                        cout << ">";
                        Pattugliatori--;
                        totcaselle -= 1;
                    }else if (c == SX && (totcaselle - 1) >= 0 && i == 11 && (Pattugliatori - 1) >=10){
                        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        gotoXY(44 ,11);
                        cout << "<";
                        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        Sleep(500);
                        Pattugliatori--;
                        totcaselle -= 1;
                    }
                    if (c == ENTER && totcaselle == 50){
                        clearScreen(MAIN_BG, MAIN_FG);
                        i = 9;
                        goto rinizia;
                    }else if (c == ENTER && totcaselle !=50){
                        gotoXY(0 ,14);
                        cout << R"(
 ___  _____   _____   ___    _   ___  ___ ___ _   _ _  _  ___ ___ ___ ___
|   \| __\ \ / /_ _| | _ \  /_\ / __|/ __|_ _| | | | \| |/ __| __| _ \ __|
| |) | _| \ V / | |  |   / / _ \ (_ | (_ || || |_| | .` | (_ | _||   / _|
|___/|___| \_/ |___| |_|_\/_/ \_\___|\___|___|\___/|_|\_|\___|___|_|_\___|
             ___  __       ___   _   ___ ___ _    _    ___
            | __|/  \     / __| /_\ / __| __| |  | |  | __|
            |__ \ () |   | (__ / _ \\__ \ _|| |__| |__| _|
            |___/\__/     \___/_/ \_\___/___|____|____|___|
)";
                        Sleep(3000);
                        gotoXY(0 ,14);
                        cout << "                                                                           ";
                        gotoXY(0 ,15);
                        cout << "                                                                           ";
                        gotoXY(0 ,16);
                        cout << "                                                                           ";
                        gotoXY(0 ,17);
                        cout << "                                                                           ";
                        gotoXY(0 ,18);
                        cout << "                                                                           ";
                        gotoXY(0 ,19);
                        cout << "                                                                           ";
                        gotoXY(0 ,20);
                        cout << "                                                                           ";
                        gotoXY(0 ,21);
                        cout << "                                                                           ";
                        gotoXY(0 ,22);
                        cout << "                                                                           ";
                    }
                    if (c == ESC){
                        totcaselle = 50;
                        Portaerei = PortaereiP;
                        Corazzate = CorazzateP;
                        Sottomarini = SottomariniP;
                        Cacciatorpediniere = CacciatorpediniereP;
                        Pattugliatori = PattugliatoriP;
                        clearScreen(MAIN_BG, MAIN_FG);
                        i = 9;
                        goto rinizia;
                    }
                    z = i;
                    if (i == 3){
                        maxaltezza = true;
                    }else if (i == 11){
                        minaltezza = true;
                    }
                    if (c == SU && !maxaltezza){
                        i -= 2;
                        minaltezza = false;
                    }else if (c == GIU && !minaltezza){
                        i += 2;
                        maxaltezza = false;
                    }
                }
            case 10:
                clearScreen(MAIN_BG, MAIN_FG);
                esc = true;
                break;
            }
        }
    }
    PortaereiP = Portaerei;
    CorazzateP = Corazzate;
    SottomariniP = Sottomarini;
    CacciatorpediniereP = Cacciatorpediniere;
    PattugliatoriP = Pattugliatori;
}

void Classifica()
{















    Sleep(10000);
}

void USCITA ()
{
    system("cls");
    system("color 0F");
    cout << R"(
 _____ ______  ___   ___________ _____     ______ ___________       ___  _   _ ___________
|  __ \| ___ \/ _ \ |___  /_   _|  ___|    | ___ \  ___| ___ \     / _ \| | | |  ___| ___ \
| |  \/| |_/ / /_\ \   / /  | | | |__      | |_/ / |__ | |_/ /    / /_\ \ | | | |__ | |_/ /
| | __ |    /|  _  |  / /   | | |  __|     |  __/|  __||    /     |  _  | | | |  __||    /
| |_\ \| |\ \| | | |./ /____| |_| |___     | |   | |___| |\ \     | | | \ \_/ / |___| |\ \
 \____/\_| \_\_| |_/\_____/\___/\____/     \_|   \____/\_| \_|    \_| |_/\___/\____/\_| \_|


 _____ _____ _____ _____   ___ _____ _____        ___     ______  ___ _____ _____ ___  _____  _     _____  ___        _   _   ___  _   _  ___   _      _____
|  __ \_   _|  _  /  __ \ / _ \_   _|  _  |      / _ \    | ___ \/ _ \_   _|_   _/ _ \|  __ \| |   |_   _|/ _ \      | \ | | / _ \| | | |/ _ \ | |    |  ___|
| |  \/ | | | | | | /  \// /_\ \| | | | | |     / /_\ \   | |_/ / /_\ \| |   | |/ /_\ \ |  \/| |     | | / /_\ \     |  \| |/ /_\ \ | | / /_\ \| |    | |__
| | __  | | | | | | |    |  _  || | | | | |     |  _  |   | ___ \  _  || |   | ||  _  | | __ | |     | | |  _  |     | . ` ||  _  | | | |  _  || |    |  __|
| |_\ \_| |_\ \_/ / \__/\| | | || | \ \_/ /     | | | |   | |_/ / | | || |   | || | | | |_\ \| |_____| |_| | | |     | |\  || | | \ \_/ / | | || |____| |___
 \____/\___/ \___/ \____/\_| |_/\_/  \___/      \_| |_/   \____/\_| |_/\_/   \_/\_| |_/\____/\_____/\___/\_| |_/     \_| \_/\_| |_/\___/\_| |_/\_____/\____/


)";
}

void hideCursor()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void bubbleSort(){
    bool siScambi;
    int z;
    int z1;
    char z2 [20];
    while(siScambi){
        siScambi = false;
        for (int i = 0; i < 98 ; i++){
            if(giocatori[i].punti > giocatori[i+1].punti){
                z = giocatori[i].punti;
                z1 = giocatori[i].tempo;
                strcpy(z2,giocatori[i].nome);
                giocatori[i].punti = giocatori[i+1].punti;
                giocatori[i].tempo = giocatori[i+1].tempo;
                strcpy(giocatori[i].nome,giocatori[i+1].nome);
                giocatori[i+1].punti = z;
                giocatori[i+1].tempo = z1;
                strcpy(giocatori[i+1].nome,z2);
                siScambi = true;
            }
        }
    }
}
