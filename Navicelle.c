#include "SubroutinesSO.h"

void NavicellaGiocatore(int pipeout , int pidPro)
{
    int MAXY , MAXX , c , dyG = MOVIMENTO , dyS = -MOVIMENTO , pidProS , pidProG;
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
                                //mvprintw(10 , 10 , "%d , %d" , pos_navicella.x , pos_navicella.y);
                                refresh();
                                pos_proiettile.x = pos_navicella.x + 1;
                                pos_proiettile.y = pos_navicella.y;
                                write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
                                while(pos_proiettile.x < MAXX - 2) // il proiettile si ferma subito prima del bordo
                                {
                                    usleep(50000);
                                    pos_proiettile.x++;
                                    write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
                                    //mvprintw(20 , 20 , "%d , %d" , pos_proiettile.x , pos_proiettile.y);
                                    refresh();
                                }
                                usleep(50000);
                                exit(EXIT_SUCCESS);
                                kill(pidPro , 1);
                            }
                        default:
                            break;
                    }
                    break;
                }
            case ' ':
                {
                    //mvprintw(20,20, "AAAAAAAAH");
                    pidProG = fork(); //Proiettile di giù
                    int a = getpid();
                    if(getpid() == 0)
                    {
                        mvprintw(20 , 20 , "processo figlio");
                        refresh();
                    }
                    else
                    {
                        mvprintw(25 , 20 , "processo padre");
                        refresh();
                    }
                    refresh();
                    switch(pidProG)
                    {
                        case -1:
                                perror("fork call");
                                _exit(2);
                                break;
                        case 0:
                            {   mvprintw(25 , 20 , "%d , %d" , pos_navicella.x , pos_navicella.y);
                                refresh();
                                pos_proiettile_giu.x = pos_navicella.x + 1;
                                pos_proiettile_giu.y = pos_navicella.y + 1;
                                write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
                                //mvprintw(25 , 20 , "%d , %d" , pos_proiettile_giu.x , pos_proiettile_giu.y);
                                refresh();
                                while(pos_proiettile_giu.x < MAXX - 2)
                                {
                                    if(pos_proiettile_giu.y <= 2) 
                                    {
                                        dyG = MOVIMENTO;
                                        pos_proiettile_giu.c = '/';
                                    }
                                    if(pos_proiettile_giu.y >= MAXY - 2)
                                    {
                                        dyG = -MOVIMENTO;
                                        pos_proiettile_giu.c = '\\';
                                    }
                                    usleep(50000);
                                    pos_proiettile_giu.y += dyG;
                                    pos_proiettile_giu.x++;
                                    write(pipeout , &pos_proiettile_giu , sizeof(pos_proiettile_giu));
                                }
                                usleep(50000);
                                exit(EXIT_SUCCESS);
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
                                        //mvprintw(10 , 10 , "%d , %d" , pos_proiettile.x , pos_proiettile.y);
                                        pos_proiettile_su.x = pos_navicella.x + 1;
                                        pos_proiettile_su.y = pos_navicella.y - 1;
                                        write(pipeout , &pos_proiettile_su , sizeof(pos_proiettile_su));
                                        refresh();
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
                                            //mvprintw(20 , 20 , "%d , %d" , pos_proiettile_su.x , pos_proiettile_su.y);
                                            refresh();
                                        }
                                        usleep(50000);
                                        exit(EXIT_SUCCESS);
                                        kill(pidProS , 1);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                                break;
                            }
                    }
                    kill(pidProG , 1);
                    break;
                }
            default:
                {
                    break;
                }
            }
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
}