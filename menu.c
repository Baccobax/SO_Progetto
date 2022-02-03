#include "SubroutinesSO.h"


void sfondo(){
    //push
    start_color();
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
    freccia pointer;
    pointer.pos=(MAXY/2+2);
    while(true) {

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
        char impostazioni[] = "Impostazioni";
        char esci[] = "Esci";
        strcpy(pointer.stringa, "==>");
        mvprintw(MAXY/2+2, MAXX/2-sizeof(avvio)/2, avvio);
        mvprintw(MAXY/2+4, MAXX/2-sizeof(impostazioni)/2, impostazioni);
        mvprintw(MAXY/2+6, MAXX/2-sizeof(esci)/2, esci);

        mvprintw(pointer.pos, MAXX/2-10, pointer.stringa);
        timeout(1);

        pointer.input=getch();
        usleep(10000);
        switch(pointer.input){
            case KEY_UP:
                if(pointer.pos>MAXY/2+2)
                    pointer.pos-=2;
                break;
            case KEY_DOWN:
                if(pointer.pos<MAXY/2+6)
                    pointer.pos+=2;
                break;
            case 113:
                if (pointer.pos==MAXY/2+2){
                   caricamento();
                }else if(pointer.pos==MAXY/2+4){
                    timeout(-1);
                    settings();
                }
                else{
                    endwin();
                    exit(0);
                }
        }

        refresh();
    }
}



void settings(){
    int MAXX, MAXY;
    getmaxyx(stdscr, MAXY, MAXX);
    freccia pointer;
    pointer.pos=(MAXY/2+2);
    while(true){
        clear();
        int i=0;
        int j;
        char impostazioni[] = "Impostazioni";
        char scolore[] = "Cambia colori";
        char snav[] = "Cambia navicella";
        char back[] = "Torna al menu";
        char scegliScritta[] = "Scegli il colore della scritta";
        char scegliSfondo[] = "Scegli il colore dello sfondo";
        char scegliNavicella[] = "Scegli la navicella";
        char colori[8][8]={"Nero   ", "Rosso  ", "Verde  ", "Giallo ", "Blu    ", "Magenta", "Ciano  ", "Bianco "};
        int asciiColori[8]={COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};
        int coloreSfondo, coloreScritta;

        strcpy(pointer.stringa, "==>");
        char nav1[4][7]={
            " ____ ",
            "|  . |",
            "|    |",
            "|__|_|"
        };
        char nav2[4][6]={
            " _   ",
            "| |_ ",
            "|  _|",
            "|_|  "
        };
        char nav3[4][7]={
            "   ^  ",
            "// _ \\",
            "\\   //",
            "   v  "
        };
        mvprintw(MAXY/2+2, MAXX/2-sizeof(scolore)/2, scolore);
        mvprintw(MAXY/2+4, MAXX/2-sizeof(snav)/2, snav);
        mvprintw(MAXY/2+6, MAXX/2-sizeof(back)/2, back);

        mvprintw(pointer.pos, MAXX/2-18, pointer.stringa);

        pointer.input=getch();
        switch(pointer.input){
            case KEY_UP:
                if(pointer.pos>MAXY/2+2)
                    pointer.pos-=2;
                break;
            case KEY_DOWN:
                if(pointer.pos<MAXY/2+6)
                    pointer.pos+=2;
                break;
            case 113:
                if (pointer.pos==MAXY/2+2){
                        while(i==0){
                            clear();
                            int c=-8;
                            for(j=0; j<8; j++){
                                mvprintw(MAXY/2+c, MAXX/2-sizeof(colori[j])/2, colori[j]);
                                c+=2;
                            }
                            
                            mvprintw(MAXY/2-10, MAXX/2-sizeof(scegliScritta)/2, scegliScritta);
                            mvprintw(pointer.pos, MAXX/2-10, pointer.stringa);

                            pointer.input=getch();

                            switch(pointer.input){
                                case KEY_UP:
                                    if(pointer.pos>MAXY/2-8)
                                        pointer.pos-=2;
                                    break;
                                case KEY_DOWN:
                                    if(pointer.pos<MAXY/2+6)
                                        pointer.pos+=2;
                                    break;
                                case 'q': 
                                    c=-8;
                                    for(j=0; j<8; j++){
                                        if(pointer.pos==MAXY/2+c){
                                            coloreScritta=asciiColori[j];
                                        }
                                        c+=2;
                                    }
                                    while(true){
                                        clear();
                                        int c=-8;
                                        for(j=0; j<8; j++){
                                            mvprintw(MAXY/2+c, MAXX/2-sizeof(colori[j])/2, colori[j]);
                                            c+=2;
                                        }
                                        
                                        mvprintw(MAXY/2-10, MAXX/2-sizeof(scegliSfondo)/2, scegliSfondo);
                                        mvprintw(pointer.pos, MAXX/2-10, pointer.stringa);

                                        pointer.input=getch();

                                        switch(pointer.input){
                                            case KEY_UP:
                                                if(pointer.pos>MAXY/2-8)
                                                    pointer.pos-=2;
                                                break;
                                            case KEY_DOWN:
                                                if(pointer.pos<MAXY/2+6)
                                                    pointer.pos+=2;
                                                break;
                                            case 'q': 
                                                c=-8;
                                                for(j=0; j<8; j++){
                                                    if(pointer.pos==MAXY/2+c){
                                                        coloreSfondo=asciiColori[j];
                                                    }
                                                    c+=2;
                                                }
                                                init_pair(1, coloreScritta, coloreSfondo);
                                                attron(COLOR_PAIR(1));
                                                bkgd(COLOR_PAIR(1));
                                                settings();
                                            }
                                    }
                            }                
                            refresh();        
                        };
                }else if(pointer.pos==MAXY/2+4){
                    pointer.pos=MAXY/2-7;
                        while(true){
                            clear();
                            mvprintw(MAXY/2-10, MAXX/2-sizeof(scegliNavicella)/2, scegliNavicella);
                            int c=-8;
                            
                            for (j=0; j<4; j++){
                                mvprintw(MAXY/2+c, MAXX/2, nav1[j]);
                                c+=1;
                            }
                            c+=2;
                            for (j=0; j<4; j++){
                                mvprintw(MAXY/2+c, MAXX/2, nav2[j]);
                                c+=1;
                            }
                            c+=2;
                            for (j=0; j<4; j++){
                                mvprintw(MAXY/2+c, MAXX/2, nav3[j]);
                                c+=1;
                            }
                            
                            mvprintw(pointer.pos, MAXX/2-10, pointer.stringa);
                            
                            pointer.input=getch();

                            switch(pointer.input){
                                case KEY_UP:
                                    if(pointer.pos>MAXY/2-7)
                                        pointer.pos-=6;
                                    break;
                                case KEY_DOWN:
                                    if(pointer.pos<MAXY/2+5)
                                        pointer.pos+=6;
                                    break;
                                case 'q':
                                    settings();
                            }    
                            refresh();
                        }
                }else{
                        sfondo();
                    }

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




