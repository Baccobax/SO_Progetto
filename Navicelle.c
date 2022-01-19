#include "SubroutinesSO.h"

void NavicellaGiocatore(int pipeout , int pidPro)
{
    int MAXY , MAXX , c , dyG , dyS;
    getmaxyx(stdscr, MAXY, MAXX);
    keypad(stdscr , true);
    pos pos_navicella, pos_proiettile , pos_proiettile_giu , pos_proiettile_su;
    pos_navicella.c = '>';
    pos_navicella.x = 1;
    pos_navicella.y = MAXY/2;
    pos_proiettile.c = '+';
    pos_proiettile_giu.c = '\\';
    pos_proiettile_su.c = '/';
    write(pipeout , &pos_navicella , sizeof(pos_navicella));
    
    while(true)
    {
        c = getch();
        switch(c)
        {
            case KEY_UP:
                if(pos_navicella.y > 2)
                {
                    pos_navicella.y -= 1;
                    write(pipeout , &pos_navicella , sizeof(pos_navicella));
                    break;
                }        
            case KEY_DOWN:
                if(pos_navicella.y < MAXY-2)
                {
                    pos_navicella.y += 1;
                    write(pipeout , &pos_navicella , sizeof(pos_navicella));
                    break;
                }
            case 'x':
                {
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
                                    pos_proiettile.x = pos_navicella.x + 1;
                                    pos_proiettile.y = pos_navicella.y;
                                    write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
                                    while(pos_proiettile.x < MAXX - 2) // il proiettile si ferma subito prima del bordo
                                    {
                                        usleep(50000);
                                        pos_proiettile.x++;
                                        write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
                                    }
                                    usleep(50000);
                                    exit(EXIT_SUCCESS);
                                    kill(pidPro , 1);
                                }
                            default:
                                break;
                        }
                }
            case ' ':
                {
                    pidPro = fork();
                    switch(pidPro)
                    {
                        case -1:
                                perror("fork call");
                                _exit(2);
                                break;

                        case 0:
                            //Processo ProiettileGIU
                            {
                                pos_proiettile_giu.x = pos_navicella.x + 1;
                                pos_proiettile_giu.y = pos_navicella.y + 1;
                                
                                exit(EXIT_SUCCESS);
                                kill(pidPro , 1);
                            }

                        default:
                            //Processo ProiettileSU
                            {

                            }
                    }
                }
            default:
                {
                    break;
                }
            }
    }
}

/*
int Proiettili(pos pos_navicella, int pipeout)
{
        /*
        case ' ':
        {
            pos_proiettile_giu.x = pos_Navicella.x + 1;
            pos_proiettile_su.x = pos_Navicella.x + 1;
            pos_proiettile_giu.y = pos_Navicella.y + 1;
            pos_proiettile_su.y = pos_Navicella.y - 1;
            pos_proiettile_giu.c = '\\';
            pos_proiettile_su.c = '/';
            write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
            write(pipeout , &pos_proiettile_su , sizeof(pos_proiettile_su));

            
            while(pos_proiettile_giu.x != maxX && pos_proiettile_su.x != maxX)
            {
                Proiettile che parte andando verso il basso
                if(pos_proiettile_giu.y + dyG < 0) //se va oltre, rimetti a posto
                {
                    /*Proiettile che parte andando verso il basso
                    if(pos_proiettile_giu.y + dyG < 0) //se va oltre, rimetti a posto
                    {
                        pos_proiettile_giu.y = 0;
                    }
                }
                write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
                Proiettile che parte andando verso l'alto
                if(pos_proiettile_su.y + dyS < 0) //se va oltre, rimetti a posto
                {
                    pos_proiettile_su.y = 0;
                }
                if(pos_proiettile_su.y + dyS > maxY) //se va oltre rimetti a posto
                {
                    pos_proiettile_su.y = maxY;
                }
                if(pos_proiettile_su.y == 0) 
                {
                    dyS = MOVIMENTO;
                    pos_proiettile_su.c = '\\';
                }
                if(pos_proiettile_su.y == maxY)
                {
                    dyS = -MOVIMENTO;
                    pos_proiettile_su.c = '/';
                }
                if(pos_proiettile_su.y + dyS >= 0 || pos_proiettile_su.y + dyS <= maxY)
                {
                    pos_proiettile_su.y += dyS;
                    pos_proiettile_su.x++;
                    if(pos_proiettile_su.x >= maxX)
                    {
                        pos_proiettile_giu.y = maxY;
                    }
                }
                write(pipeout , &pos_proiettile_su , sizeof(pos_proiettile_su));
            }
         
    }
}/*

/*momentaneamente ficchiamo la funzione qua per testing*/

void collision(int pipein)
{
    pos Nav, proiettile, proiettileGIU , proiettileSU , valore_letto;
    int MAXY , MAXX;
    getmaxyx(stdscr, MAXY, MAXX);
    Nav.x = -1;
    proiettile.x =- 1;


    border(ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , '*' , '*' , '*' , '*');
    refresh();

    do
    {
        read(pipein, &valore_letto, sizeof(valore_letto));
        switch(valore_letto.c)
        {
            case('>'):
            {

                if(Nav.x >= 0)
                    {
                        mvaddch(Nav.y, Nav.x , ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
                    }
                Nav = valore_letto;
            }
            case('+'):
            {
                if(valore_letto.x >= 3)
                    {
                        mvaddch(valore_letto.y , valore_letto.x-1, ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
                    }
                if(valore_letto.x >= MAXX-2)
                    {
                        mvaddch(valore_letto.y , valore_letto.x , ' ');                    
                    }
                //proiettile = valore_letto;
            }
        }
        curs_set(false);
        refresh();
    } while(true);
}