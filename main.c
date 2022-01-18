#include "SubroutinesSO.h"


void main() 
{
    int tubo[2];
    int i = 0 , g = 0, pidNav, pidPro;
    int MAXX, MAXY;
    int ch;

    char menu[2][18] = {"Inizia partita", "Esci dal gioco"};
    char benvenuto[11][80] = {
    " ____                                  _   _                                 ",
    "| __ )  ___ _ ____   _____ _ __  _   _| |_(_)  ___ _   _                     ",
    "|  _ \\ / _ \\ '_ \\ \\ / / _ \\ '_ \\| | | | __| | / __| | | |              ",
    "| |_) |  __/ | | \\ V /  __/ | | | |_| | |_| | \\__ \\ |_| |                 ",
    "|____/ \\___|_| |_|\\_/ \\___|_| |_|\\__,_|\\__|_| |___/\\__,_|              ",
    " ____                         ___                     _                      ",
    "/ ___| _ __   __ _  ___ ___  |_ _|_ ____   ____ _  __| | ___ _ __ ___        ",
    "\\___ \\| '_ \\ / _` |/ __/ _ \\  | || '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __|",
    " ___) | |_) | (_| | (_|  __/  | || | | \\ V / (_| | (_| |  __/ |  \\__ \\    ",
    "|____/| .__/ \\__,_|\\___\\___| |___|_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/",
    "      |_|                                                                    "};

    //char item[18];
    //char item2[80];

    WINDOW *w1; //finestra per il menu iniziale di gioco

    initscr();
    noecho();
    curs_set(false);

    /* INIZIO MENU */ 
    getmaxyx(stdscr, MAXY, MAXX);

    w1 = newwin( MAXY - 2 , MAXX - 2 , 1 , 1);
    box(w1, ' ' , ' ');


    //STAMPO LA SCRITTA BENVENUTO
    for(g = 0; g < 11 ; g++)
    {
        //sprintf(item2, "%-79s", benvenuto[i]);
        mvwprintw( w1, g+1, 4, "%s", benvenuto[g]);
    }        

    //STAMPA LA PRIMA VOLTA IL MENU
    for ( i = 0; i < 2; i++)
    {
        if ( i == 0)
            wattron( w1, A_STANDOUT); // il primo elemento è illuminato
        else
            wattroff( w1, A_STANDOUT); // l'altro è "spento"
            //sprintf(item, "%-17s", menu[i]);
            mvwprintw( w1, i+2+(MAXY/2), 2, "%s", menu[i]);
    }
    wrefresh( w1 );
    i = 0;
    keypad( w1, TRUE );
    curs_set( 0 );
    
    
    while ((ch = wgetch(w1)) != 'q') //premendo q skippo tutto e parte il gioco
    {
        //sprintf(item, "%-17s", menu[i]);
        mvwprintw( w1, i+2+(MAXY/2), 2, "%s", menu[i]);

        switch (ch)
        {
        case KEY_UP:
            i--;
            if (i < 0) //porta all'ultimo della coda
                i = 1;
            break;
        
        case KEY_DOWN:
            i++;
            if (i > 1) //porta all'inizio della coda
                i = 0;
            break;
            
        case 10: // premendo il tasto invio...
            switch (i)
            {
            case 0: // se 0 termina il menu e inizia il gioco >> fa "segmentation fault ( core dumped )" )
                delwin(w1);
                endwin();    
                break;
            
            case 1: // se 1 termina il programma
                endwin();
                exit(0);
                break;
            }
        }
        wattron( w1 , A_STANDOUT );
        //sprintf(item, "%-17s", menu[i]);
        mvwprintw( w1, i+2+(MAXY/2), 2, "%s", menu[i]);
        wattroff( w1, A_STANDOUT );       
    }
    delwin(w1);
    endwin(); 
     

    /* FINE MENU   */


    refresh();

    if(pipe(tubo) == -1) //pipe fallisce
    {
        perror("pipe call");
        _exit(1);
    }
    
    //perror("diocane 1");
    pidNav = fork();
    switch(pidNav)
    {
        case -1:
            {
                perror("fork call");
                _exit(2);
            }

        case 0: /*Processo Navicella*/
            close(tubo[0]);
            NavicellaGiocatore(tubo[1] , pidPro, stdscr);

        default: /* processo padre */
            /*
            pidPro = fork();

            switch ( pidPro )
            {
            case -1:
                perror("fork call");
                _exit(2);
                break;

            case 0: /rocesso Proiettile
                close(tubo[0]);
                Proiettili(tubo[1]);
            
            default:
                close(tubo[1]);
                collision(tubo[0]);
            }

            
            for(i = 0; i < NEMICI ; i++) //ciclo per creare piu' navicella: il numero di navicelle dipende dalla macro NEMICI
            {
                pidNem[i] = fork();
            
                switch (pidNem[i])
                {
                    case -1:
                    perror("fork call");
                    _exit(i+3);
                    case 0: //Processo singola Navicella nemica
                    {
                        close(tubo[0]);
                        //NavicellaNemica(tubo[1]);
                        break;
                    }
                    default: /*Processo padre pt.2, il mio "main" in pratica
                    {
                        
                    }
                }
            } */
        close(tubo[1]);
        collision(tubo[0]);
        
         kill(pidNav , 1);
         /* ipotetico ciclo per uccidere le navicelle*/
         endwin();
         exit(666);  
    }
    exit(0);  
}