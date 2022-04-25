#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdbool.h>
#include <ncurses.h>
#include <string.h>

#define NEMICI 6       //Macro dedicata al numero dei nemici
#define MOVIMENTO 1     //Macro utilizzata per lo spostamento diagonale dei proiettili
#define BRDDISTANCE 3   //Macro utilizzata per indicare la distanza minima dal bordo
#define UNDEFINED -2    //Macro utilizzata per la definizione degli array di PID (vedi più in "Navicelle.c")
#define PROIETTILI 40

/* Struttura per la comunicazione tra figli e padre */
typedef struct pos {
    char c[3][4]; /* carattere del oggetto */
    char cp;
    int x; /* coordinata x */
    int y; /* coordinata y */
    bool up_down;
    int indice_oggetto;
    int pidNav;
}pos;


typedef struct freccia{
    char stringa[4];
    int pos;
    int input;
}freccia;


void sfondo();
void caricamento();
void settings();
void NavicellaGiocatore();
void Nemici();
int SparoNemici();
void collision();
