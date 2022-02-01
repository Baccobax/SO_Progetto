#include "SubroutinesSO.h"

void sfondo(){

    int MAXX, MAXY;
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
    int sy=(MAXY/2+2);
    while(true) {

        clear();

        int g,y=1;
        for(g=0;g<4;g++){
            mvprintw(y,MAXX/2-15,"%s",stringa[g]);
            y++;
        }
        int z=5;
        for(g=0;g<4;g++){
            mvwprintw(z,MAXX/2-22,"%s",stringa2[g]);
            z++;
        }
        int i;
        for (i = 0; i <= MAXY; i++){
            int x = rand()%MAXX;
            mvprintw(i, x, ".");
            usleep(1000);
        }

        char avvio[] = "Avvia gioco";
        char impostazioni[] = "Impostazioni";
        char esci[] = "Esci";
        char selezione[] = "==>";
        mvprintw(MAXY/2+2, MAXX/2-sizeof(avvio)/2, avvio);
        mvprintw(MAXY/2+4, MAXX/2-sizeof(impostazioni)/2, impostazioni);
        mvprintw(MAXY/2+6, MAXX/2-sizeof(esci)/2, esci);

        mvprintw(sy, MAXX/2-10, selezione);
        timeout(1);

        frecciaMenu=getch();
        switch(frecciaMenu){
            case KEY_UP:
                if(sy>MAXY/2+2)
                    sy-=2;
                break;
            case KEY_DOWN:
                if(sy<MAXY/2+6)
                    sy+=2;
                break;
            case 113:
               caricamento();
        }

        refresh();
        }
}

void caricamento(){
    WINDOW *testo;

    int MAXX, MAXY;
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
    while (true) {

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
}




