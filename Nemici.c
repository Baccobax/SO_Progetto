#include "SubroutinesSO.h"
/**
 * @brief La funzione è atta alla generazione delle coordinate dei nemici e dei loro proiettili. La generazione
 * avviene in base al quante navicelle nemiche vengono richieste in chiamata
 * 
 * @param pipeout pipe utilizzata per la comunicazione tra processi
 * @param pidNem valore del pid collegato al processo del singolo nemico
 * @param cont indice dell'array dei nemici utilizzato per tener conto del singolo nemico e 
 */
void Nemici(int pipeout , int cont)
{
    int MAXX , MAXY , MIDY , my = MOVIMENTO , statusPRO = 0;
    AltoBasso a;
    getmaxyx(stdscr , MAXY , MAXX);
    pos pos_nemico , pos_pro_nem;
    
    if(cont % 2 == 0)
    {
        pos_nemico.y = MAXY/2 + cont;
        a = alto;
    }
    else
    {
        pos_nemico.y = MAXY/2 - cont;
        a = basso;
    }
    pos_nemico.x = MAXX-3;
    pos_nemico.c = '<';
    write(pipeout , &pos_nemico , sizeof(pos_nemico));

    while(true)
    {
        refresh();
        switch(a)
        {
            case alto:
            {
                usleep(750000);
                pos_nemico.x--;
                pos_nemico.y++;
                write(pipeout , &pos_nemico , sizeof(pos_nemico));
                //SparoNemici(pipeout , pos_nemico);
                usleep(750000);
                /*if(pos_nemico.y < 2)
                {
                    my = MOVIMENTO;
                    pos_nemico.up_down = true;
                }
                if(pos_nemico.y > (MAXY/2)-1)
                {
                    my = -MOVIMENTO;
                    pos_nemico.up_down = false;
                }*/
                //pos_nemico.y += my;
                pos_nemico.x--;
                pos_nemico.y--;
                write(pipeout , &pos_nemico , sizeof(pos_nemico));
                break;
            }
            case basso:
            {
                usleep(500000);
                pos_nemico.x--;
                write(pipeout , &pos_nemico , sizeof(pos_nemico));
                //SparoNemici(pipeout , pos_nemico);
                usleep(500000);
                if(pos_nemico.y < (MAXY/2)+1)
                {
                    my = MOVIMENTO;
                    pos_nemico.up_down = true;
                }
                if(pos_nemico.y >= MAXY-2)
                {
                    my = -MOVIMENTO;
                    pos_nemico.up_down = false;
                }
                pos_nemico.y += my;
                write(pipeout , &pos_nemico , sizeof(pos_nemico));
                break;
            }
        }
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
    pro_nem.c = '#';
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