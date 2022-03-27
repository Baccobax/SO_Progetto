#include "SubroutinesSO.h"

void collision(int pipein)
{
    pos Nav, proiettile, proiettileGIU , proiettileSU , valore_letto , Nem;
    int MAXY , MAXX, i, sy=-1 , lives_NavPl;
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
        if(Nav.life == 0)
        {
            game_over = true;
        }
        border(ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , '*' , '*' , '*' , '*');
        read(pipein, &valore_letto, sizeof(valore_letto));
        switch(valore_letto.c[1][1])
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
                
                //
                if(valore_letto.x == Nav.x+1 && (valore_letto.y == Nav.y || valore_letto.y == Nav.y+1 || valore_letto.y == Nav.y-1))
                {
                    flash();
                    Nav.life--;
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
                    
                for(i=0; i<NEMICI; i++){
                    
                    if (valore_letto.x == coll_nem[i].x && valore_letto.y == coll_nem[i].y){
                        coll_nem[i].life -= 1; 
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