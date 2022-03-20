#include "SubroutinesSO.h"


void main() 
{
    int tubo[2];
    int i = 0 , pidNav , status = 0 , column_nem , pidNem[NEMICI];
    
    
    
    initscr();
    noecho();
    curs_set(false);
    //sfondo();
    refresh();
    column_nem = getmaxy(stdscr)*5 / 23; //numero di nemici

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
            close(tubo[0]);
            NavicellaGiocatore(tubo[1]);
            _exit(SIGUSR1);
        }
        default:
        {    /* processo padre */
            for(i = 0; i < NEMICI ; i++) //ciclo per creare piu' navicella: il numero di navicelle dipende dalla macro NEMICI
            {
                pidNem[i] = fork();
                
                switch (pidNem[i])
                {
                    case -1:
                        perror("fork call");
                        _exit(3);
                    case 0: //Processo singola Navicella nemica
                    {
                        close(tubo[0]);
                        Nemici(tubo[1] , tubo[0],  i , column_nem , pidNem);
                        break;
                    }
                }
            }
            collision(tubo[0], tubo[1]);
        }
    }
    while(wait(0) > 0);
    endwin();
    exit(0);  
}
