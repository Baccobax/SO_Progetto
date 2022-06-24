#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdbool.h>
#include <ncurses.h>
#include <string.h>
#include <pthread.h>

#define DEATH 0
#define PROIETTILE_DRITTO 0
#define NAV 0
#define COLL 1
#define PROIETTILI 3
#define PROIETTILE_ISU 1
#define MOVIMENTO 1     //Macro utilizzata per lo spostamento diagonale dei proiettili
#define ALMOST_DEAD 1
#define NAVECOLL 2 //Macro utilizzata per l'indice dell'array di thread della navicella e della subroutine "collision"
#define HITTED 2
#define HEALTHY 3
#define PROIETTILE_IGIU 2
#define BRDDISTANCE 3   //Macro utilizzata per indicare la distanza minima dal bordo
#define NEMICI 3     //Macro dedicata al numero dei nemici
#define BULLET_SPEED 10000
#define ENEMY_SPEED 500000 //500000
#define ENDGAMEWAIT 5000000 //Macro utilizzata per definire la durata della schermata finale




typedef enum status_obj{
    Nav_Alleata,
    Nav_Nemica,
    Nav_Nemica_Rotta,
    Proiettile,
    Proiettile_Morto
}status_obj;

typedef struct freccia{
    char stringa[4];
    int pos;
    int input;
}freccia;

/* Struttura per la comunicazione tra figli e padre */
typedef struct pos {
    status_obj status;
    char cp;
    int x; /* coordinata x */
    int y; /* coordinata y */
    bool up_down;
    int indice_oggetto;
}pos;


void sfondo();
void caricamento();
void settings();
void *NavicellaGiocatore();
void *Nemici();
void *SparoNemici();
void collision();
void StampaNavicelle();
void Cancella3x4();
void GameOver();
void YouWin();
void EliminaNemici();
void *Proiettile_dritto();
void *Proiettili_giu();
void *Proiettili_su();
void InizializzaProiettiliNemici();