#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdbool.h>
#include <ncurses.h>

#define NEMICI 10 //Macro dedicata al numero dei nemici
#define MOVIMENTO 1 //Macro utilizzata per lo spostamento diagonale dei proiettili
#define UNDEFINED -2 //Macro utilizzata per la definizione degli array di PID (vedi più in "Navicelle.c")

/* Struttura per la comunicazione tra figli e padre */
typedef struct pos {
    char c; /* carattere del oggetto */
    int x; /* coordinata x */
    int y; /* coordinata y */
}pos;

typedef enum AltoBasso {
    alto , 
    basso , 
    centro
}AltoBasso;


void sfondo();
void caricamento();
void Start();
void GameOver();
void NavicellaGiocatore();
void Nemici();
void InizializzazioneArrayPid();
void SparoNemici();
//int Proiettili();
void collision();
//void Vittoria();
//void GameOver();