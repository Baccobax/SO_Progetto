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

/* Scritte di Benvenuto e GameOver
char benvenuto[11][71] = {
" ____                                  _   _                          ",       
"| __ )  ___ _ ____   _____ _ __  _   _| |_(_)  ___ _   _              ", 
"|  _ \\ / _ \\ '_ \\ \\ / / _ \\ '_ \\| | | | __| | / __| | | |             ",  
"| |_) |  __/ | | \\ V /  __/ | | | |_| | |_| | \\__ \\ |_| |             ", 
"|____/ \\___|_| |_|\\_/ \\___|_| |_|\\__,_|\\__|_| |___/\\__,_|             ", 
" ____                         ___                     _               ",
"/ ___| _ __   __ _  ___ ___  |_ _|_ ____   ____ _  __| | ___ _ __ ___ ",
"\\___ \\| '_ \\ / _` |/ __/ _ \\  | || '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __|",
" ___) | |_) | (_| | (_|  __/  | || | | \\ V / (_| | (_| |  __/ |  \\__ \",
"|____/| .__/ \__,_|\___\___| |___|_| |_|\_/ \__,_|\__,_|\___|_|  |___/",
"      |_|                                                             "};
*/

//void NavicellaNemica(int pipeout);
void NavicellaGiocatore();
int Proiettili();
void collision();