#include "SubroutinesSO.h"

void NavicellaGiocatore(int pipeout)
{
    int MAXY , MAXX , c , dyG = MOVIMENTO , dyS = -MOVIMENTO , pidPro , pidProS , pidProG , statusPRO = 0 , statusPROS = 0 , statusPROG = 0;
    bool i = false , j = false;
    getmaxyx(stdscr, MAXY, MAXX);
    keypad(stdscr , true);
    pos pos_navicella, pos_proiettile , pos_proiettile_giu , pos_proiettile_su;
    strcpy(pos_navicella.c[0], "XX ");
    strcpy(pos_navicella.c[1], "XXX");
    strcpy(pos_navicella.c[2], "XX ");

    pos_navicella.x = 1;
    pos_navicella.y = MAXY/2;
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
                            pos_proiettile_giu.x = pos_navicella.x + 4;
                            pos_proiettile_giu.y = pos_navicella.y-1;
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
                                    pos_proiettile_su.x = pos_navicella.x + 4;
                                    pos_proiettile_su.y = pos_navicella.y - 1;
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
    int MAXY , MAXX, i, sy=-1;
    bool game_over = false, victory = false; 
    getmaxyx(stdscr, MAXY, MAXX);
    Nav.x = -1;
    proiettile.x =- 1;
    pos coll_nem[NEMICI];
    int nNav=0;
    refresh();
    do
    {
        if(nNav==NEMICI){
            nNav=0;
        }
        border(ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , '*' , '*' , '*' , '*');
        read(pipein, &valore_letto, sizeof(valore_letto));
        switch(valore_letto.c[1][1]) //da correggere in modo da far controllare il carattere centrale
        {
            case('0'):  //Navicella nemica
            {
                coll_nem[nNav]=valore_letto;
                if(valore_letto.x > BRDDISTANCE)
                {
                    for(i=0; i < 5; i++){
                        mvprintw(valore_letto.y+sy-1, valore_letto.x, "   ");
                        sy+=1;
                    }
                    
                    sy = -1;
                    for(i=0; i < BRDDISTANCE; i++)
                    {
                        mvprintw(valore_letto.y+sy, valore_letto.x-1, valore_letto.c[i]);
                        sy += 1;
                    }
                    sy = -1;
                    
                
                }   
                if(valore_letto.x <= BRDDISTANCE)
                {
                    mvaddch(valore_letto.y , valore_letto.x , ' ');
                    game_over = true;                   
                }
                Nem = valore_letto;
                nNav++;
                break;
            }
            
            
            case('X'):  //Navicella
            {
                if(Nav.x >= 0)
                    {
                        for(i=0; i < 5; i++)
                        {
                            mvprintw(valore_letto.y+sy-1, valore_letto.x, "   ");
                            sy += 1;
                        }
                        sy=-1;
                        for(i=0; i < BRDDISTANCE; i++)
                        {
                            mvprintw(valore_letto.y+sy, valore_letto.x, valore_letto.c[i]);
                            sy += 1;
                        }
                        sy = -1;
                    }
                Nav = valore_letto;
                break;
            }
            
        }

        switch(valore_letto.cp){
            case('<'):  //Proiettile nemico
            {
                for(i=0; i<NEMICI; i++){
                    if(valore_letto.x!=coll_nem[i].x){
                        mvprintw(15,15,"%d %d %d", coll_nem[i].y, coll_nem[i].x, i);
                        if(valore_letto.x <= MAXX-BRDDISTANCE)
                            {
                                mvaddch(valore_letto.y , valore_letto.x+1 , ' ');
                                mvaddch(valore_letto.y , valore_letto.x , valore_letto.cp);
                            }
                        if(valore_letto.x <= BRDDISTANCE)
                            {
                                mvaddch(valore_letto.y , valore_letto.x , ' ');                    
                            }
                    }
                }  
                break;
            }
            case('+'):  //Proiettile base
            {
                if(valore_letto.x >= BRDDISTANCE)
                    {
                        mvaddch(valore_letto.y , valore_letto.x-1, ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.cp);
                    }
                if(valore_letto.x >= MAXX-2)
                    {
                        mvaddch(valore_letto.y , valore_letto.x , ' ');                    
                    }
                    
                break;
            }
            case('\\'):  //Proiettile che va giù
            {
                if(valore_letto.x >= BRDDISTANCE)
                    {
                        mvaddch(valore_letto.y-1 , valore_letto.x-1, ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.cp);
                    }
                if(valore_letto.x >= MAXX-2)
                    {
                        mvaddch(valore_letto.y , valore_letto.x , ' ');                    
                    }
                break;    
            }
            case('/'):   //Proiettile che va su
            {
                if(valore_letto.x >= BRDDISTANCE)
                    {
                        mvaddch(valore_letto.y+1 , valore_letto.x-1, ' ');
                        mvaddch(valore_letto.y , valore_letto.x , valore_letto.cp);
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
    } while(game_over == false && victory == false);
    beep();
    flash();
    clear();
    refresh();
}