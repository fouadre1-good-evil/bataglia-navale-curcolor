#include <iostream>
#include <conio.h>    //per il getch
#include "curcolor.h" //Per curcolor
#include <ctime>      //Per il random
#include <cstdlib>    //Per il random
#include <io.h>       //Per le caselle
#include <fcntl.h>    //PEr le caselle

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

int c;
int i = 9;
int z = 0;
int Portaerei = 2;           //5 caselle di lunghezza
int Corazzate = 3;           //4 caselle di lunghezza
int Sottomarini = 4;         //3 caselle di lunghezza
int Cacciatorpediniere = 5;  //2 caselle di lunghezza
int Pattugliatori =  6;      //1 caselle di lunghezza
int totnavi = 20;            //50 caselle di lunghezza

void displayMainLayout();
void INIZIO();
void stampacaselle();
void Gnavi();
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
    gotoXY(0, 0);
    cout << "Battaglia navale                                           - Data: ";
    displayToday();
    gotoXY(0, 1);
    cout << "================================================================================";
    if (z == 0)
    {
        gotoXY(31, i);
        cout << ">";
    }
    else
    {
        gotoXY(31,z);
        cout <<" ";
        gotoXY(31,i);
        cout <<">";
    }
    if(i == 9)
    {
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(32, 9);
        cout << "Inizia";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    else
    {
        gotoXY(32, 9);
        cout << "Inizia";
    }
    if(i == 10)
    {
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(32, 10);
        cout << "Gestione navi";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    else
    {
        gotoXY(32, 10);
        cout << "Gestione navi";
    }
    if(i == 11)
    {
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(32, 11);
        cout << "Esci";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    else
    {
        gotoXY(32, 11);
        cout << "Esci";
    }
    gotoXY(0,20);
    cout << "Premere ESC per uscire dal programma";
    gotoXY(0, 21);
    cout << "================================================================================";
    c = _getch();
    if (i == 9)
    {
        maxaltezza = true;
    }
    else if (i == 11)
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
            INIZIO();
            break;
        case 10:
            Gnavi();
            break;
        case 11:
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
    system("color BF");
    stampacaselle();

    Sleep(10000);

}

void stampacaselle()
{
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
    system ("cls");
    bool esc = false;
    i = 11;
    z = 11;
    while(!esc){
        gotoXY (0 ,0);
        cout << R"(
┌───────────────────────────────────┐
│ Le navi sono:                     │
│ -2 Portaerei          (5 caselle) │
│ -3 Corazzate          (4 caselle) │
│ -4 Sottomarini        (3 caselle) │
│ -5 Cacciatorpediniere (2 caselle) │
│ -6 Pattugliatori      (1 caselle) │
└───────────────────────────────────┘
)";
        cout<<endl;
        gotoXY(0,10);
        cout << "vuoi cambirle" <<endl;
            gotoXY(0 ,z);
            cout << " ";
            gotoXY(0 ,i);
            cout << ">";
        if (i == 11){
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(1,11);
            cout << " SI"<<endl;
            maxaltezza = true;
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }else{
            gotoXY(1,11);
            cout << " SI"<<endl;
        }
        if(i == 12){
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(1,12);
            cout << " No"<<endl;
            minaltezza = true;
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }else{
            gotoXY(1,12);
            cout << " No"<<endl;
        }
        z = i;
        c = _getch();
        if (c == SU && !maxaltezza){
            i -= 1;
            minaltezza = false;
        }else if (c == GIU && !minaltezza){
            i += 1;
            maxaltezza = false;
        }else if (c == ENTER){
            switch (i){
            case 11:

                break;
            case 12:
                system ("cls");
                esc = true;
                break;
            }
        }
    }
}

void USCITA ()
{
    clearScreen( 0, 15);
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
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
