#include "SubroutinesSO.h"


void main() 
{
    int tubo[2];
    int i = 0 , pidNav , pidNem[NEMICI] ,status = 0;
    
    //Start();
    initscr();
    noecho();
    curs_set(false);

    refresh();

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
            close(tubo[0]);
            NavicellaGiocatore(tubo[1]);
            _exit(SIGUSR1);

        default: /* processo padre */
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
                        Nemici(tubo[1] , pidNem , i);
                        break;
                    }
                }
            }
            close(tubo[1]);
            collision(tubo[0]);
            /* ipotetico ciclo per uccidere le navicelle*/
    }
    while(wait(0) > 0);
    endwin();
    exit(0);  
}