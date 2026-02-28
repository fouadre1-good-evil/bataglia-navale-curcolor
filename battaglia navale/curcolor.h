#include <iostream>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <string.h>

#ifndef CURCOLOR_H_INCLUDED
#define CURCOLOR_H_INCLUDED

/* Posizione il cursore a colonna x e riga y
   Il monitor è una matrice 25x80. La 25^ riga è riservata al Sistema Operativo
   per cui per l'applicazione è disponibile una matrice 24x80
*/
void gotoXY(int x, int y) {
        COORD CursorPos = {(short)x, (short)y};
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsole, CursorPos);
}
/* Imposta il colore di background (sfondo) e foreground (rilievo)
   bg tra 0 e 7
   fg tra 0 e 15
   Legenda dei colori in fondo a questo file
*/
void setColor(int bg, int fg) {
    int val;
    if (bg<0) bg=0;
    if (fg>15) fg=15;
    val=bg*16+fg;
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        val);
}
// ritorna l'attributo dei colori correnti
unsigned short getCurrentColor() {
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    return csbiInfo.wAttributes;
}
// ripristina i colori con un attributo
void setCurrentColor(unsigned short colorAttr) {
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute ( h, colorAttr);
}
// =
// ================ Funzioni di Utilità ======================
// =

// Pulisce lo schermo
void clearScreen() {
    for (int i=0; i<24; i++) {
        gotoXY(0, i);
        for (int j=0; j<80; j++) {
            std::cout << " ";
        }
    }
    gotoXY(0, 0);
}
// Colora l'intero schermo con sfondo e rilievo
void clearScreen(int bg, int fg) {
 unsigned short curColor = getCurrentColor();
 setColor(bg,fg);
 clearScreen();
 setCurrentColor(curColor );
}
/* Pulisce una riga a partire dal una colonna sino a 80
   y riga
   x da colonna
*/
void clearMessage(int x, int y) {
    gotoXY(x,y);
    for (int j=0; j<80-x; j++) {
        std::cout << " ";
    }
}

/* Pulisce una riga a partire dal una colonna sino a 80 con sfondo e rilievo
   y riga
   x da colonna
   bg sfondo
   fg rilievo
*/
void clearMessage(int x, int y, int bg, int fg) {
 unsigned short oldColor = getCurrentColor();
 setColor(bg,fg);
 clearMessage(x,y);
 setCurrentColor(oldColor );
}
/* Visualizza messaggio da riga e colonna
   y riga
   x da colonna
*/
void displayMessage(char msg[], int x, int y) {
    gotoXY(x, y);
    std::cout << msg;
    clearMessage(x+strlen(msg),y);
}
/* Visualizza messaggio da riga e colonna con colori
   y riga
   x da colonna
   bg sfondo
   fg rilievo
*/
void displayMessage(char msg[], int x, int y, int bg, int fg) {
 unsigned short oldColor = getCurrentColor();
 setColor(bg,fg);
 displayMessage(msg,x,y);
 setCurrentColor(oldColor );
}

void displayToday() {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  std::cout << std::setfill('0') << std::setw(2) << tm.tm_mday << "/"
       << std::setfill('0') << std::setw(2) << (tm.tm_mon + 1) << "/"
       <<  (tm.tm_year + 1900);
  /*
  printf("now: %d-%02d-%02d %02d:%02d:%02d\n",
          tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
          tm.tm_hour, tm.tm_min, tm.tm_sec);
  */
}


#endif // CURCOLOR_H_INCLUDED

/*
0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/
