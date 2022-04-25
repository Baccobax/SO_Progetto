#include "SubroutinesSO.h"

void collision(int pipein)
{
    pos Nav, proiettile, proiettileGIU , proiettileSU , valore_letto , Nem ,coll_nem[NEMICI];
    int MAXY , MAXX, i, sy=-1 , nNav=0 , Nem_life[NEMICI] , Nav_life = 3 , Nem_status = 0;
    bool game_over = false, victory = false; 
    getmaxyx(stdscr, MAXY, MAXX);
    Nav.x = -1;
    proiettile.x = -1; 

    for(i = 0 ; i < NEMICI ; i++)
    {
        Nem_life[i] = 2; 
    }

    refresh();
    do
    {  
        if(nNav==NEMICI){
            nNav=0;
        }
        if(Nav_life == 0)
        {
            game_over = true;
        }
        border(ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , '*' , '*' , '*' , '*');
        for(i = 0; i < NEMICI ; i++)
        {
            mvprintw(20, 20+(i) , "%d", Nem_life[i]);
        }
        read(pipein, &valore_letto, sizeof(valore_letto));
        switch(valore_letto.c[1][1])
        {
            case('0'):  //Navicella nemica
            {
                if(Nem_life[nNav] == 1)
                {
                    strcpy(valore_letto.c[0], "* *");
                    strcpy(valore_letto.c[1], "   ");
                    strcpy(valore_letto.c[2], "* *");
                }
                
                coll_nem[nNav]=valore_letto;

                if(valore_letto.x > BRDDISTANCE)
                {
                    for(i=0; i < 5; i++){
                        mvprintw(valore_letto.y+sy-1, valore_letto.x, "   ");
                        sy+=1;
                        if(Nem_life[nNav] == 1)
                        {
                            mvprintw(valore_letto.y+2, valore_letto.x-1, "   ");
                            mvprintw(valore_letto.y-2, valore_letto.x-1, "   ");
                        }
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
                //Nem = valore_letto;
                nNav++;
                Nem_status = 0;
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
                    
                    if (valore_letto.x!=coll_nem[i].x||valore_letto.y!=coll_nem[i].y){
                        if(valore_letto.x <= MAXX-BRDDISTANCE)
                        {
                            mvaddch(valore_letto.y , valore_letto.x+1 , ' ');
                            mvaddch(valore_letto.y , valore_letto.x , valore_letto.cp);
                        }
                    }
                    if (valore_letto.x == coll_nem[i].x || valore_letto.y == coll_nem[i].y){
                        mvprintw(coll_nem[i].y, coll_nem[i].x-1, coll_nem[i].c[1]);
                    }
                }
                            
                if(valore_letto.x <= BRDDISTANCE)
                {
                    mvaddch(valore_letto.y , valore_letto.x , ' ');                    
                }            
                
                if(valore_letto.x == Nav.x+1 && (valore_letto.y == Nav.y || valore_letto.y == Nav.y+1 || valore_letto.y == Nav.y-1))
                {
                    //flash();
                    //Nav_life--;
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
                    
                for(i=0; i<NEMICI; i++)
                {
                    if (valore_letto.x == coll_nem[i].x && (valore_letto.y == coll_nem[i].y || valore_letto.y == coll_nem[i].y+1 || valore_letto.y == coll_nem[i].y-1))
                    {
                        Nem_life[i]--; 
                    }
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

                for(i=0; i<NEMICI; i++)
                {
                    if (valore_letto.x == coll_nem[i].x && (valore_letto.y == coll_nem[i].y || valore_letto.y == coll_nem[i].y+1 || valore_letto.y == coll_nem[i].y-1))
                    {
                        Nem_life[i]--; 
                    }
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

                for(i=0; i<NEMICI; i++)
                {
                    if (valore_letto.x == coll_nem[i].x && (valore_letto.y == coll_nem[i].y || valore_letto.y == coll_nem[i].y+1 || valore_letto.y == coll_nem[i].y-1))
                    {
                        Nem_life[i]--; 
                    }
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