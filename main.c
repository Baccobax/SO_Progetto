#include "SubroutinesSO.h"


void main() 
{
    int tubo[2];
    int i = 0 , pidNav, pidPro;
    int MAXX, MAXY;

    char list[2][18] = {"Inizia partita", "Esci dal gioco"};
    char item[18];
    int ch, width = 18;

    //finestre per il menu iniziale di gioco
    WINDOW *w1;

    initscr();
    noecho();
    curs_set(false);

    /* INIZIO MENU */ 
    getmaxyx(stdscr, MAXY, MAXX);

    w1 = newwin( MAXY / 2 , MAXX - 2 , 1 , 1);
    box(w1, 0 , 0);
    //mvwprintw (w1 , 5 , 20 , "BENVENUTI SU SPACE INVADERS.");
    //mvwprintw (w1 , 6 , 18 , "premi un tasto per continuare...");
    for ( i = 0; i < 2; i++)
    {
        if ( i == 0)
            wattron( w1, A_STANDOUT);
        else
            wattroff( w1, A_STANDOUT);
            sprintf(item, "%-17s", list[i]);
            mvwprintw( w1, i+1, 2, "%s", item);
    }
    wrefresh( w1 );
    i = 0;
    //noecho();
    keypad( w1, TRUE );
    curs_set( 0 );
    
    while ((ch = wgetch(w1)) != 'q')
    {
        sprintf(item, "%-17s", list[i]);
        mvwprintw( w1, i+1, 2, "%s", item);

        switch (ch)
        {
        case KEY_UP:
            i--;
            if (i < 0)
                i = 1;
            break;
        
        case KEY_DOWN:
            i++;
            if (i > 1)
                i = 0;
            break;
            
        case KEY_ENTER:
            if (i = 0)
            {
                delwin( w1 );
                endwin();
                break;
            }
            else if ( i = 1 )
            {
                delwin ( w1 );
                endwin();
                exit(0);
                break;

            }
        }
        wattron( w1 , A_STANDOUT );
        sprintf(item, "%-17s", list[i]);
        mvwprintw( w1, i+1, 2, "%s", item);
        wattroff( w1, A_STANDOUT );
    }    


    //wgetch(w1);
    //delwin;

    /* FINE MENU   */


    wrefresh(stdscr);

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