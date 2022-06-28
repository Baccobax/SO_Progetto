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

#define DEATH 0 // Macro utilizzata per definire la morte di un oggetto
#define PROIETTILE_DRITTO 0 // Macro utilizzata per definire il proiettile dritto
#define NAV 0 // Macro utilizzata per definire la funzione della navicella
#define COLL 1 // Macro utilizzata per definire la funzione delle collisioni
#define PROIETTILI 3 // Macro utilizzata per definire la dimensione dell'array di proiettili
#define PROIETTILE_ISU 1 // Macro utilizzata per definire il proiettile che parte verso l'alto
#define MOVIMENTO 1     //Macro utilizzata per lo spostamento diagonale dei proiettili
#define ALMOST_DEAD 1 // Macro utilizzata per definire la vita del nemico quando è quasi deceduto
#define NAVECOLL 2 //Macro utilizzata per l'indice dell'array di thread della navicella e della subroutine "collision"
#define HITTED 2 // Macro utilizzata per definire che il nemico è stato colpito
#define HEALTHY 3 // Macro utilizzata per definire la vita massima della navicella o di un nemico
#define PROIETTILE_IGIU 2 // Macro utilizzata per definire il proiettile che parte verso il basso
#define BRDDISTANCE 3   //Macro utilizzata per indicare la distanza minima dal bordo
#define NEMICI 10     //Macro dedicata al numero dei nemici
#define BULLET_SPEED 95000 //Macro dedicata alla velocita' dei proiettili
#define ENEMY_BULLET_SPEED 80000 //Macro dedicata alla velocita' dei proiettili dei nemici
#define ENEMY_SPEED 1500000 //Macro dedicata alla velocita' dei nemici
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
void AspettaProiettili();