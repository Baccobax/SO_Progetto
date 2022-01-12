#include "SubroutinesSO.h"


void main() 
{
    int tubo[2];
    int i = 0 , pidNav, pidPro;

    initscr();
    noecho();
    curs_set(false);

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