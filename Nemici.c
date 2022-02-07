#include "SubroutinesSO.h"
/**
 * @brief La funzione è atta alla generazione delle coordinate dei nemici e dei loro proiettili. La generazione
 * avviene in base al quante navicelle nemiche vengono richieste in chiamata
 * 
 * @param pipeout pipe utilizzata per la comunicazione tra processi
 * @param pidNem valore del pid collegato al processo del singolo nemico
 * @param cont indice dell'array dei nemici utilizzato per tener conto del singolo nemico e 
 */
void Nemici(int pipeout , int cont , int column , int *pid_nem)
{
    int MAXX , MAXY , MIDY , statusPRO = 0 , mx , my , status_nem[NEMICI];
    getmaxyx(stdscr , MAXY , MAXX);
    pos pos_nemico , pos_pro_nem;
    pos_nemico.life = 2;
    pos_nemico.indice_oggetto = cont;
    
    mx = cont/column;

    pos_nemico.x = MAXX - BRDDISTANCE - ((BRDDISTANCE+1)*mx);
    
    my = cont % column; 

    if(my == 0 )
    {
        pos_nemico.y = MAXY/2;
    }
    if(my % 2 == 0)
    {
        pos_nemico.y = (MAXY/2) - my*2;
    }
    else
    {
        pos_nemico.y = (MAXY/2) + 2 + my*2;
    }


    strcpy(pos_nemico.c[0], " | ");
    strcpy(pos_nemico.c[1], "-0-");
    strcpy(pos_nemico.c[2], " | ");

    write(pipeout , &pos_nemico , sizeof(pos_nemico));

    pos_nemico.up_down = true;
    while(pos_nemico.x > BRDDISTANCE)
    {
        /*while ( condition )
        {
            if(vite == 1)
            {
                modificamatrice();
                flagcondizionewhile = false;
            }
        }*/
        
        usleep(500000);
        if(pos_nemico.up_down == true)
        {
            pos_nemico.y--;
            pos_nemico.up_down = false;
        }
        else
        {
            pos_nemico.y++;
            pos_nemico.up_down = true;
        }
        write(pipeout , &pos_nemico , sizeof(pos_nemico));
        usleep(500000);
        pos_nemico.x--;
        write(pipeout , &pos_nemico , sizeof(pos_nemico));

        //read(pipein , &pos_nemico.life , sizeof(pos_nemico.life));
        if(pos_nemico.life <= 0)
        {
            _exit(SIGUSR1);
        }
        waitpid(pid_nem[cont] , status_nem[cont] , WNOHANG);
        /*if (/* condition )
        {
            /* code 
        }*/
    }
}

/**
 * @brief 
 * 
 * @param pipeout 
 * @param nemico 
 */
void SparoNemici(int pipeout , pos nemico)
{
    int pid_pro_nem , status_pro_nem;
    bool flag_pro = false;
    pos pro_nem;
    pro_nem.cp = '#';
    if(flag_pro == false)
    {
        flag_pro = true;
        pid_pro_nem = fork();
        switch(pid_pro_nem)
        {
            case -1:
                perror("fork call");
                _exit(2);
                break;
            case 0:
            {
                pro_nem.x = nemico.x-1;
                pro_nem.y = nemico.y;
                write(pipeout , &pro_nem , sizeof(pro_nem));
                while(pro_nem.x > 3)
                {
                    usleep(5000000);
                    pro_nem.x--;
                    write(pipeout , &pro_nem , sizeof(pro_nem));
                }
                usleep(5000000);
                _exit(SIGUSR1);
            }
            default:
            {
                break;
            }
        }
    }
    waitpid(pid_pro_nem , &status_pro_nem , WNOHANG);
    if(status_pro_nem != 0)
    {
        flag_pro = false;
        status_pro_nem = 0;
    }
}

