#include <iostream>
#include <conio.h>    //per il getch
#include "curcolor.h" //Per curcolor
#include <ctime>      //Per il random
#include <cstdlib>    //Per il random

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
int c;
int i = 9;
bool maxaltezza = true;
bool minaltezza = false;

void displayMainLayout();
void hideCursor();

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
    keybd_event(VK_MENU, 0x36,0,0);                  // ---------|
    keybd_event(VK_RETURN, 0x1c,0,0);                //          | ------> Per mettere lo
    keybd_event(VK_RETURN, 0x1c,KEYEVENTF_KEYUP,0);  //          | ------> schermo intero all'avvio
    keybd_event(VK_MENU, 0x38,KEYEVENTF_KEYUP,0);    // ---------|
    hideCursor();
    displayMainLayout();
    return 0;
}

void hideCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void displayMainLayout() {
    while(true){
        clearScreen(MAIN_BG, MAIN_FG);
        setColor(MAIN_BG, MAIN_FG);
        gotoXY (0, 0);
        cout << "Battaglia navale                                           - Data: ";
        displayToday();
        gotoXY(0, 1);
        cout << "================================================================================";
        gotoXY(31, i);
        cout << ">";
        if(i==9){
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(32, 9);
            cout << "Inizia";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }else{
            gotoXY(32, 9);
            cout << "Inizia";
        }
        if(i==10){
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(32, 10);
            cout << "Gestione navi";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }else{
            gotoXY(32, 10);
            cout << "Gestione navi";
        }
        if(i==11){
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            gotoXY(32, 11);
            cout << "Esci";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }else{
            gotoXY(32, 11);
            cout << "Esci";
        }
        gotoXY(0, 21);
        cout << "================================================================================";
        c = getch();
        if (i==9){
            maxaltezza = true;
        }else if (i==11){
            minaltezza = true;
        }
        if(c==SU && !maxaltezza){
            i-=1;
            minaltezza = false;
        }else if(c==GIU && !minaltezza){
            i+=1;
            maxaltezza = false;
        }
    }
}
