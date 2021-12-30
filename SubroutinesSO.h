#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdbool.h>
#include <ncurses.h>

#define NEMICI 10 //Macro dedicata al numero dei nemici
#define MOVIMENTO 1 //Macro utilizzata pero lo spostamento diagonale dei proiettili

/* Struttura per la comunicazione tra figli e padre */
typedef struct pos {
char c; /* carattere del oggetto */
int x; /* coordinata x */
int y; /* coordinata y */
}pos;

//void NavicellaNemica(int pipeout);
void NavicellaGiocatore(int pipeout);
int Proiettili(char a , pos pos_Navicella , int pipeout);
void collision(int pipein);