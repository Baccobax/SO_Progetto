#include "SubroutinesSO.h"
/*
void *Nemici(int pipeout , int cont , int column)
{
    int MAXX , MAXY , MIDY , statusPRO = 0 , mx , my , status_pro_nem[PROIETTILI] , randP , pid_pro_nem[PROIETTILI] , i;
    getmaxyx(stdscr , MAXY , MAXX);
    pos pos_nemico , pos_pro_nem, valore_letto;
    pos_nemico.indice_oggetto = cont;
    
    for(i=0 ; i < (PROIETTILI) ; i++)
    {
        pid_pro_nem[i] = 0;
    }

    for(i=0 ; i < (PROIETTILI) ; i++)
    {
        status_pro_nem[i] = 0;
    }

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

    pos_nemico.pidNav = (int)getpid();

    pos_nemico.status = Nav_Nemica;

    write(pipeout , &pos_nemico , sizeof(pos_nemico));

    pos_nemico.up_down = true;
    while(pos_nemico.x > BRDDISTANCE)
    {        
        usleep(ENEMY_SPEED);
        if((rand() + (int)getpid() ) % 4 == 0)
        {
            for(i = 0 ; i < PROIETTILI ; i++)
            {
                if(pid_pro_nem[i] == 0)
                {   
                    if((rand() + (int)getpid() ) % 2 == 0)
                    {    
                        pid_pro_nem[i] = SparoNemici(pipeout , pos_nemico, column);   
                    }
                }
            }
        }
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
        usleep(ENEMY_SPEED);
        pos_nemico.x--;
        write(pipeout , &pos_nemico , sizeof(pos_nemico));
        for(i = 0 ; i < PROIETTILI ; i++)
        {
            if(pid_pro_nem[i] != 0)
            {
                waitpid(pid_pro_nem[i] , &status_pro_nem[i] , WNOHANG);
                if(status_pro_nem[i] != 0)
                {
                    pid_pro_nem[i] = 0;
                    status_pro_nem[i] = 0;
                }
            }
        }
    }
} 
*/
/**
 * @brief 
 * 
 * @param pipeout 
 * @param nemico 

int SparoNemici(int pipeout , pos nemico , int column)
{
    int pid_pro_nem , status_pro_nem = 0 , uhm = 0;
    bool flag_pro = false;
    pos pro_nem;
    pro_nem.cp = '<';
    pro_nem.status = Proiettile;
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
            pro_nem.x = nemico.x-3;
            pro_nem.y = nemico.y;
            write(pipeout , &pro_nem , sizeof(pro_nem));
            while(pro_nem.x >= BRDDISTANCE)
            {
                usleep(25000);
                pro_nem.x--;
                write(pipeout , &pro_nem , sizeof(pro_nem));
            }
            _exit(SIGUSR1);
            return pid_pro_nem;
        }
    }
}

*/