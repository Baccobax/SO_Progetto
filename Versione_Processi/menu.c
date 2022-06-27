#include "SubroutinesSO.h"

/**
 * @brief Funzione che si occupa della stampa e della navigazione all'interno del menù principale
 * 
 */
void sfondo(){
    int MAXX, MAXY;
    bool InizioGioco = false;
    getmaxyx(stdscr, MAXY, MAXX);
    keypad(stdscr,1);
    char stringa[4][30]={
            " _____ _____ _____ ____ ____ ",
            "|  ___|  _  |  _  | ___|  __|",
            "|____ | ____|  _  | |__|  __|",
            "|_____|_|   |_| |_|____|____|"};
    char stringa2[4][46]={
            " _____ ____ ____ ____ _   _ _____ ____ _____ ",
            "|  _  |  __|  __|  __| \\ | |  _  |  __|  _  |",
            "| |_| |  __|  __|  __| |\\  | |_| |  __|  _-- ",
            "|_____|____|__| |____|_| \\_|_____|____|_| \\_\\"
    };
    int frecciaMenu;
    freccia pointer;
    pointer.pos=(MAXY/2+2);
    while(InizioGioco == false) {

        clear();

        int g,y=1;
        for(g=0;g<4;g++){
            mvprintw(y,MAXX/2-15,"%s",stringa[g]);
            y++;
        }
        int z=5;
        for(g=0;g<4;g++){
            mvprintw(z,MAXX/2-22,"%s",stringa2[g]);
            z++;
        }
        int i;
        for (i = 0; i <= MAXY; i++){
            int x = rand()%MAXX;
            mvprintw(i, x, ".");
            usleep(1000);
        }
        
        char avvio[] = "Avvia gioco";
        char esci[] = "Esci";
        strcpy(pointer.stringa, "==>");
        mvprintw(MAXY/2+2, MAXX/2-sizeof(avvio)/2, avvio);
        mvprintw(MAXY/2+4, MAXX/2-sizeof(esci)/2, esci);
        mvprintw(pointer.pos, MAXX/2-10, pointer.stringa);
        timeout(1);

        pointer.input=getch();
        usleep(10000);
        switch(pointer.input){
            case KEY_UP:
                {
                    if(pointer.pos>MAXY/2+2)
                    pointer.pos-=2;
                    break;
                }
            case KEY_DOWN:
                {
                    if(pointer.pos<MAXY/2+4)
                    pointer.pos+=2;
                    break;
                }
            case ' ':
                {
                    if (pointer.pos==MAXY/2+2){
                        InizioGioco = true;
                        caricamento();
                    }
                    else{
                        endwin();
                        exit(0);
                    }
                    break;
                }
        }
        refresh();
    }
    clear();
}

/**
 * @brief Funzione che si occupa della stampa della schermata di Game over
 * 
 * @param MAXX dimensione massima x dello schermo
 * @param MAXY dimensione massima y dello schermo
 */
void GameOver(int MAXX , int MAXY)
{
char game_over[6][60]={
            "  ____                         ___                  ",
            " / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ ",
            "| |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|",
            "| |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |   ",
            " \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   ",
    };
    int g,y=1;
    clear();
    for(g=0;g<7;g++){
        mvprintw((MAXY/2-7)+y,MAXX/2-25,"%s",game_over[g]);
        y++;
        refresh();
        usleep(300000);
    }
    usleep(ENDGAMEWAIT);
}
/**
 * @brief Funzione che si occupa della stampa della schermata di vittoria
 * 
 * @param MAXX dimensione massima x dello schermo
 * @param MAXY dimensione massima y dello schermo
 */
void YouWin(int MAXX , int MAXY)
{
char you_win[6][45]={
            "__   __                     _            ",
            "\\ \\ / /__  _   _  __      _(_)_ __     ",
            " \\ V / _ \\| | | | \\ \\ /\\ / / | '_ \\",
            "  | | (_) | |_| |  \\ V  V /| | | | |   ",
            "  |_|\\___/ \\__,_|   \\_/\\_/ |_|_| |_|",
    };
    int g,y=1;
    clear();
    for(g=0;g<7;g++){
        mvprintw((MAXY/2-7)+y,MAXX/2-20,"%s",you_win[g]);
        y++;
        refresh();
        usleep(300000);
    }
    usleep(ENDGAMEWAIT);
}

/**
 * @brief Funzione che si occupa della stampa della schermata di caricamento
 * 
 */
void caricamento(){
    WINDOW *testo;

    int MAXX, MAXY , i;
    getmaxyx(stdscr, MAXY, MAXX);

    testo = newwin(5, 20, MAXY/2-2, MAXX/2-10);
    char amogus[5][13]={
            "    _______ ",
            " __|  ___  |",
            "|  | |___| |",
            "|__|       |",
            "   |___|___|"};
    int g;

    char caricamento[]="CARICAMENTO";
    for(i = 0 ; i < 3 ; i++) {

        int x=1;
        int y,z;

        while(x<MAXX-5) {
            clear();
            wclear(testo);
            box(testo, ACS_VLINE, ACS_HLINE);
            mvwprintw(testo, 2, 10-(sizeof (caricamento)/2), caricamento);
            y=MAXY-7;
            z=2;
            for (g = 0; g < 5; g++) {
                mvprintw(z, x, "%s", amogus[g]);
                z++;
                usleep(10000);
            }
            for (g = 0; g < 5; g++) {
                mvprintw(y, x, "%s", amogus[g]);
                y++;
                usleep(10000);
            }
            x+=5;
            refresh();
            wrefresh(testo);
        }
    }
    delwin(testo);
}
