#include "SubroutinesSO.h"

void NavicellaGiocatore(int pipeout)
{
    int MAXY , MAXX , c , dyG = MOVIMENTO , dyS = -MOVIMENTO , pidPro[10] , pidProS[10] , pidProG[10] , status , i = 0 , g = 0 , s = 0 ;
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

    InizializzazioneArrayPid(pidPro , pidProG , pidProS);

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
                if(pos_navicella.y < MAXY-3)
                {
                    pos_navicella.y += 1;
                    write(pipeout , &pos_navicella , sizeof(pos_navicella));
                    break;
                }
            case 'x':
                {
                    i++;
                    pidPro[i] = fork();
                    switch(pidPro[i])
                    {
                        case -1:
                            perror("fork call");
                            _exit(2);\
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
                                _exit(SIGUSR1);
                            }
                        }
                    break;
                }
            case ' ':
                {
                    g++;
                    pidProG[g] = fork(); //Proiettile di giù
                    switch(pidProG[g])
                    {
                        case -1:
                                perror("fork call");
                                _exit(2);
                                break;
                        case 0:
                            {
                                pos_proiettile_giu.x = pos_navicella.x + 1;
                                pos_proiettile_giu.y = pos_navicella.y + 1;
                                write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
                                while(pos_proiettile_giu.x < MAXX - 2)
                                {
                                    if(pos_proiettile_giu.y < 2) 
                                    {
                                        dyG = MOVIMENTO;
                                        pos_proiettile_giu.c = '\\';
                                    }
                                    if(pos_proiettile_giu.y >= MAXY - 2)
                                    {
                                        dyG = -MOVIMENTO;
                                        pos_proiettile_giu.c = '/';
                                    }
                                    usleep(50000);
                                    pos_proiettile_giu.y += dyG;
                                    pos_proiettile_giu.x++;
                                    write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
                                }
                                usleep(50000);
                                _exit(SIGUSR1);
                            }
                        default: //Proiettile di su 
                            {   
                                s++;
                                pidProS[s] = fork();
                                switch(pidProS[s])
                                {
                                    case -1:
                                        perror("fork call");
                                        _exit(2);
                                        break;
                                    case 0:
                                    {
                                        pos_proiettile_su.x = pos_navicella.x + 1;
                                        pos_proiettile_su.y = pos_navicella.y - 1;
                                        write(pipeout , &pos_proiettile_su , sizeof(pos_proiettile_su));
                                        while(pos_proiettile_su.x < MAXX - 2)
                                        {
                                            if(pos_proiettile_su.y < 2) 
                                            {
                                                dyS = MOVIMENTO;
                                                pos_proiettile_su.c = '\\';
                                            }
                                            if(pos_proiettile_su.y >= MAXY - 2)
                                            {
                                                dyS = -MOVIMENTO;
                                                pos_proiettile_su.c = '/';
                                            }
                                            usleep(50000);
                                            pos_proiettile_su.y += dyS;
                                            pos_proiettile_su.x++;
                                            write(pipeout , &pos_proiettile_su , sizeof(pos_proiettile_su));
                                        }
                                        usleep(50000);
                                        _exit(SIGUSR1);
                                    }
                                }
                                break;
                            }
                    }
                }
        }
        i = 0;
        g = 0;
        s = 0;
        while(i < 10 && g < 10 && s < 10)
        {
            if(pidPro[i] != UNDEFINED)
            {
                waitpid(pidPro[i] , &status , WNOHANG);
            }
            if(pidProG[g] != UNDEFINED)
            {
                waitpid(pidPro[i] , &status , WNOHANG);    
            }
            if(pidProS[s] != UNDEFINED)
            {
                waitpid(pidProS[s] , &status , WNOHANG);   
            }
            i++;
            g++;
            s++;
        }
        i = 0;
        g = 0;
        s = 0;
    }
}

void InizializzazioneArrayPid(int *PrimoPid , int *SecondoPid , int *TerzoPid)
{
    int i;
    for(i = 0 ; i < 10 ; i++)
    {
        PrimoPid[i] = UNDEFINED;
        SecondoPid[i] = UNDEFINED;
        TerzoPid[i] = UNDEFINED;
    }
}

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
            case('>'):  //Navicella
            {

                if(Nav.x >= 0)
                    {
                        mvaddch(Nav.y, Nav.x , ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
                    }
                Nav = valore_letto;
                break;
            }
            case('+'):  //Proiettile base
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
                break;
            }
            case('\\'):  //Proiettile che va giù
            {
                if(valore_letto.x >= 3)
                    {
                        mvaddch(valore_letto.y-1 , valore_letto.x-1, ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
                    }
                if(valore_letto.x >= MAXX-2)
                    {
                        mvaddch(valore_letto.y , valore_letto.x , ' ');                    
                    }
                break;    
            }
            case('/'):   //Proiettile che va su
            {
                if(valore_letto.x >= 3)
                    {
                        mvaddch(valore_letto.y+1 , valore_letto.x-1, ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
                    }
                if(valore_letto.x >= MAXX-2)
                    {
                        mvaddch(valore_letto.y , valore_letto.x , ' ');                    
                    }
                break;
            }
        }
        curs_set(false);
        refresh();
    } while(true);
    refresh();
}