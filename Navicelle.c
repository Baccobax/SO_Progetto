#include "SubroutinesSO.h"

void NavicellaGiocatore(int pipeout)
{
    int MAXY , MAXX , c , dyG = MOVIMENTO , dyS = -MOVIMENTO , pidPro , pidProS , pidProG , statusPRO = 0 , statusPROS = 0 , statusPROG = 0;
    bool i = false , j = false;
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
            {
                if(pos_navicella.y > 2)
                {
                    pos_navicella.y -= 1;
                    write(pipeout , &pos_navicella , sizeof(pos_navicella));
                    break;
                }
            }        
            case KEY_DOWN:
            {
                if(pos_navicella.y < MAXY-3)
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
                                usleep(43000);
                                pos_proiettile_giu.y += dyG;
                                pos_proiettile_giu.x++;
                                write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
                            }
                            usleep(50000);
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
                                        usleep(43000);
                                        pos_proiettile_su.y += dyS;
                                        pos_proiettile_su.x++;
                                        write(pipeout , &pos_proiettile_su , sizeof(pos_proiettile_su));
                                    }
                                    usleep(50000);
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


/*momentaneamente ficchiamo la funzione qua per testing*/

void collision(int pipein)
{
    pos Nav, proiettile, proiettileGIU , proiettileSU , valore_letto , Nem;
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
            case('<'):  //Navicella nemica
            {
                switch (valore_letto.up_down)
                {
                    case true: //La navicella va verso giu
                    {
                        if(valore_letto.x >= 3)
                        {
                            mvaddch(valore_letto.y , valore_letto.x-1 , ' ');
                            mvaddch(valore_letto.y-1 , valore_letto.x , ' ');
                            mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
                        }
                        if(valore_letto.x <= 3)
                        {
                            mvaddch(valore_letto.y , valore_letto.x , ' ');                   
                        }
                        Nem = valore_letto;           
                    }
                    break;
                    
                    case false: //La navicella va su
                    {
                        if(valore_letto.x >= 3)
                        {
                            mvaddch(valore_letto.y , valore_letto.x-1 , ' ');
                            mvaddch(valore_letto.y , valore_letto.x-1 , ' ');
                            mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
                        }
                        if(valore_letto.x <= 3)
                        {
                            mvaddch(valore_letto.y , valore_letto.x , ' ');                   
                        }
                        Nem = valore_letto;  
                    }
                    break;
                }
                break;
            }
            case('#'):  //Proiettile nemico
            {
                if(valore_letto.x >= MAXX-3)
                    {
                        mvaddch(valore_letto.y , valore_letto.x+1, ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
                    }
                if(valore_letto.x <= 3)
                    {
                        mvaddch(valore_letto.y , valore_letto.x , ' ');                    
                    }
                break;
            }
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
    } while((Nav.x != Nem.x || Nav.y != Nem.y) || Nem.x >= 2);
    beep();
    flash();
    clear();
    refresh();
}