#include "SubroutinesSO.h"


void main() 
{
    int tubo[2];
    int i = 0 , pidNav , status = 0 , column_nem , pidNem[NEMICI];
    srand((unsigned) time(NULL));
    
    
    initscr();
    noecho();
    curs_set(false);
    sfondo();

    refresh();
    column_nem = getmaxy(stdscr)* 5 / 23; //numero di nemici

    if(pipe(tubo) == -1) //pipe fallisce
    {
        perror("pipe call");
        _exit(1);
    }
    
    pidNav = fork();
    switch(pidNav)
    {
        case -1:
        {
            perror("fork call");
            _exit(2);
        }

        case 0: /*Processo Navicella*/
        {
            close(tubo[LETTURA]);
            NavicellaGiocatore(tubo[SCRITTURA]);
            _exit(SIGUSR1);
        }
        default:
        {    /* processo padre */
            for(i = 0; i < NEMICI ; i++) //ciclo per creare piu' navicelle: il numero di navicelle dipende dalla macro NEMICI
            {
                pidNem[i] = fork();
                
                switch (pidNem[i])
                {
                    case -1:
                        perror("fork call");
                        _exit(3);
                    case 0: //Processo singola Navicella nemica
                    {
                        close(tubo[LETTURA]);
                        Nemici(tubo[SCRITTURA] ,  i , column_nem);
                        break;
                    }
                }
            }
            close(tubo[SCRITTURA]);
            collision(tubo[LETTURA]);
        }
    }
    while(wait(0) > 0);
    endwin();
    exit(0);  
}
