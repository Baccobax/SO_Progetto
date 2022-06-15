#include "SubroutinesSO.h"
/**
 * @brief 
 * 
 * @param pipeout 
 */
void NavicellaGiocatore(int pipeout)
{
    int MAXY , MAXX , c , dyG = MOVIMENTO , dyS = -MOVIMENTO , pidPro , pidProS , pidProG , statusPRO = 0 , statusPROS = 0 , statusPROG = 0;
    bool i = false , j = false;
    getmaxyx(stdscr, MAXY, MAXX);
    keypad(stdscr , true);
    pos pos_navicella, pos_proiettile , pos_proiettile_giu , pos_proiettile_su;
    pos_navicella.status = Nav_Alleata;
    pos_proiettile.status = Proiettile;
    pos_proiettile_giu.status = Proiettile;
    pos_proiettile_su.status = Proiettile;
    pos_navicella.x = 1;
    pos_navicella.y = MAXY/2;
    pos_navicella.pidNav = getpid();
    pos_proiettile.cp = '+';
    pos_proiettile_giu.cp = '\\';
    pos_proiettile_su.cp = '/';
    write(pipeout , &pos_navicella , sizeof(pos_navicella));
    

    while(true)
    {
        c = getch();
        switch(c)
        {
            case KEY_UP:
            {
                if(pos_navicella.y > BRDDISTANCE)
                {
                    pos_navicella.y -= 1;
                    write(pipeout , &pos_navicella , sizeof(pos_navicella));
                    break;
                }
            }        
            case KEY_DOWN:
            {
                if(pos_navicella.y < MAXY-4)
                {
                    pos_navicella.y += 1;
                    write(pipeout , &pos_navicella , sizeof(pos_navicella));
                    break;
                }
            }
            case 'x':
            {
                if(i == false)
                {
                    i = true;
                    pidPro = fork();
                    switch(pidPro)
                    {
                        case -1:
                            perror("fork call");
                            _exit(2);
                            break;

                        case 0:
                        //Processo Proiettile
                        {
                            pos_proiettile.x = pos_navicella.x + 4;
                            pos_proiettile.y = pos_navicella.y;
                            pos_proiettile.pidNav = getpid();
                            write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
                            while(pos_proiettile.x < MAXX - 2) // il proiettile si ferma subito prima del bordo
                            {
                                usleep(BULLET_SPEED);
                                pos_proiettile.x++;
                                write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
                            }
                            usleep(35000);
                            _exit(SIGUSR1);
                        }
                    }
                }
            }
                    break;
            case ' ':
            {
                if(j == false)
                {
                    j = true;
                    pidProG = fork(); //Proiettile di giù
                    switch(pidProG)
                    {
                        case -1:
                                perror("fork call");
                                _exit(2);
                                break;
                        case 0:
                        {
                            pos_proiettile_giu.x = pos_navicella.x + 4;
                            pos_proiettile_giu.y = pos_navicella.y-1;
                            pos_proiettile_giu.pidNav = getpid();
                            write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
                            while(pos_proiettile_giu.x < MAXX - 2)
                            {
                                if(pos_proiettile_giu.y < 2) 
                                {
                                    dyG = MOVIMENTO;
                                    pos_proiettile_giu.cp = '\\';
                                }
                                if(pos_proiettile_giu.y >= MAXY - 2)
                                {
                                    dyG = -MOVIMENTO;
                                    pos_proiettile_giu.cp = '/';
                                }
                                usleep(BULLET_SPEED);
                                pos_proiettile_giu.y += dyG;
                                pos_proiettile_giu.x++;
                                write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
                            }
                            usleep(35000);
                            _exit(SIGUSR2);
                        }
                        default: //Proiettile di su 
                        {   
                            pidProS = fork();
                            switch(pidProS)
                            {
                                case -1:
                                    perror("fork call");
                                    _exit(2);
                                    break;
                                case 0:
                                {
                                    pos_proiettile_su.x = pos_navicella.x + 4;
                                    pos_proiettile_su.y = pos_navicella.y - 1;
                                    pos_proiettile_su.pidNav = getpid();
                                    write(pipeout , &pos_proiettile_su , sizeof(pos_proiettile_su));
                                    while(pos_proiettile_su.x < MAXX - 2)
                                    {
                                        if(pos_proiettile_su.y < 2) 
                                        {
                                            dyS = MOVIMENTO;
                                            pos_proiettile_su.cp = '\\';
                                        }
                                        if(pos_proiettile_su.y >= MAXY - 2)
                                        {
                                            dyS = -MOVIMENTO;
                                            pos_proiettile_su.cp = '/';
                                        }
                                        usleep(BULLET_SPEED);
                                        pos_proiettile_su.y += dyS;
                                        pos_proiettile_su.x++;
                                        write(pipeout , &pos_proiettile_su , sizeof(pos_proiettile_su));
                                    }
                                    usleep(35000);
                                    _exit(SIGUSR2);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        waitpid(pidPro , &statusPRO , WNOHANG);
        if(statusPRO != 0)
        {
            i = false;
            statusPRO = 0;
        }
        waitpid(pidProG , &statusPROG , WNOHANG);
        if(statusPROG != 0)
        {
            j = false;
            statusPROG = 0;
        }
        waitpid(pidProS , &statusPROS , WNOHANG);
        if(statusPROS != 0)
        {
            j = false;
            statusPROS = 0;
        }
    }
}
