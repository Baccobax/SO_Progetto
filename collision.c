#include "SubroutinesSO.h"

/**
 * @brief TODO
 * 
 * 
 */


/**
 * @brief 
 * 
 * @param pipein 
 */
void collision(int pipein)
{
    pos Nav, proiettile, proiettileGIU , proiettileSU , valore_letto , Nem ,coll_nem[NEMICI];
    int MAXY , MAXX, i, sy=-1 , nNav=0 , Nem_life[NEMICI] , Nav_life = 3 , Nem_status[NEMICI] , Pro_Status[3];
    bool game_over = false, victory = false; 
    getmaxyx(stdscr, MAXY, MAXX);
    Nav.x = -1;
    proiettile.x = -1; 

    for(i = 0 ; i < NEMICI ; i++)
    {
        Nem_life[i] = HEALTHY; 
    }

    for(i = 0 ; i < 3 ; i++)
    {
        Pro_Status[i] = 0;
    }

    refresh();
    do
    {  
        if(Nav_life == 0)
        {
            game_over = true;
        }
        border(ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , '*' , '*' , '*' , '*');
        //
        for(i = 0; i < NEMICI ; i++)
        {
            mvprintw(20, 20+(i) , "%d", Nem_life[i]); //vite
        }
        //
        read(pipein, &valore_letto, sizeof(valore_letto));
        nNav = valore_letto.indice_oggetto;
        switch(valore_letto.status)
        {
            case(Nav_Nemica):  //Navicella nemica 
            {
                if(Nem_life[nNav] > DEATH)
                {
                    if(Nem_life[nNav] == HITTED)
                    {
                        valore_letto.status = Nav_Nemica_Rotta;
                    }
                    coll_nem[nNav] = valore_letto;
                    
                    if(coll_nem[nNav].x > BRDDISTANCE)
                    {
                        StampaNavicelle(valore_letto , sy , i , nNav);
                    }
                    if(valore_letto.x <= BRDDISTANCE)
                    {
                        mvaddch(valore_letto.y , valore_letto.x , ' ');
                        game_over = true;   
                    }
                    nNav++;
                }
                if(Nem_life[nNav] <= DEATH)
                {
                    kill(coll_nem[nNav].pidNav , SIGUSR2);
                    waitpid(coll_nem[nNav].pidNav , &Nem_status[nNav] , WNOHANG);
                    coll_nem[nNav].y = MAXY;
                    coll_nem[nNav].x = MAXX;
                }
                break;
            }
            
            
            case(Nav_Alleata):  //Navicella
            {
                if(Nav.x >= 0)
                {
                    StampaNavicelle(valore_letto , sy , i , nNav);
                }
                Nav = valore_letto;
                break;
            }
            
            case(Proiettile): //Proiettili
            {
                switch(valore_letto.cp){
                    case('<'):  //Proiettile nemico
                    { 
                        for(i=0; i<NEMICI; i++){
                            
                            if (valore_letto.x!=coll_nem[i].x||valore_letto.y!=coll_nem[i].y)
                            {
                                if(valore_letto.x <= MAXX-BRDDISTANCE)
                                {
                                    mvaddch(valore_letto.y , valore_letto.x+1 , ' ');
                                    mvaddch(valore_letto.y , valore_letto.x , valore_letto.cp);
                                }
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
                                kill(valore_letto.pidNav , SIGUSR2);
                                waitpid(valore_letto.pidNav , Pro_Status[PROIETTILE_DRITTO] , WNOHANG);
                                if(Pro_Status[PROIETTILE_DRITTO] != 0)
                                {
                                    Pro_Status[PROIETTILE_DRITTO] = 0;
                                }
                                Cancella3x4(valore_letto , sy , i);
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

                        for(i=0; i < NEMICI; i++)
                        {
                            if (valore_letto.x == coll_nem[i].x && (valore_letto.y == coll_nem[i].y || valore_letto.y == coll_nem[i].y+1 || valore_letto.y == coll_nem[i].y-1))
                            {
                                Nem_life[i]--;
                                kill(valore_letto.pidNav , SIGUSR1);
                                waitpid(valore_letto.pidNav , Pro_Status[PROIETTILE_IGIU] , WNOHANG);
                                if(Pro_Status[PROIETTILE_IGIU] != 0)
                                {
                                    Pro_Status[PROIETTILE_IGIU] = 0;
                                }
                                Cancella3x4(valore_letto , sy , i);
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
                                kill(valore_letto.pidNav , SIGUSR2);
                                waitpid(valore_letto.pidNav , Pro_Status[PROIETTILE_ISU] , WNOHANG);
                                if(Pro_Status[PROIETTILE_ISU] != 0)
                                {
                                    Pro_Status[PROIETTILE_ISU] = 0;
                                }
                                Cancella3x4(valore_letto , sy , i);
                            }
                        }
                        break;
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

/**
 * @brief Semplice subroutine che esegue un'operazione di cancellamento dei caratteri in un'area 3x4
 * 
 * @param Nav Variabile posizione dell'oggetto. Viene utilizzato per ottenere le coordinate del suddetto.
 * @param sy 
 * @param i Contatore i utilizzato nel ciclo.
 */
void Cancella3x4(pos Nav , int sy , int i)
{
    for(i=0; i < 5; i++)
        {
            mvprintw(Nav.y+sy-1, Nav.x-1, "    ");
            mvprintw(Nav.y+2, Nav.x-1, "   ");
            mvprintw(Nav.y-2, Nav.x-1, "   ");
            sy+=1;
        }
}

/**
 * @brief 
 * 
 * @param Nav 
 * @param sy 
 * @param i 
 * @param nNav 
 */
void StampaNavicelle(pos Nav , int sy , int i, int nNav)
{
    char Sprite[3][4];
    switch(Nav.status)
    {
        case(Nav_Alleata):
        {
            strcpy(Sprite[0], "XX ");
            strcpy(Sprite[1], "XXX");
            strcpy(Sprite[2], "XX ");

            for(i=0; i < 5; i++)
                {
                    mvprintw(Nav.y+sy-1, Nav.x, "   ");
                    sy += 1;
                }
                sy=-1;
                for(i=0; i < BRDDISTANCE; i++)
                {
                    mvprintw(Nav.y+sy, Nav.x, Sprite[i]);
                    sy += 1;
                }
                sy = -1;
            break;
        }
        case(Nav_Nemica):
        {
            strcpy(Sprite[0], " | ");
            strcpy(Sprite[1], "-0-");
            strcpy(Sprite[2], " | ");

            for(i=0; i < 5; i++)
            {
                mvprintw(Nav.y+sy-1, Nav.x, "   ");
                sy+=1;
            }
            sy = -1;
            for(i = 0; i < BRDDISTANCE; i++)
            {
                mvprintw(Nav.y+sy, Nav.x-1, Sprite[i]);
                sy += 1;
            }
            sy = -1;
            break;
        }
        case(Nav_Nemica_Rotta):
        {
            strcpy(Sprite[0], "* *");
            strcpy(Sprite[1], "   ");
            strcpy(Sprite[2], "* *");

            Cancella3x4(Nav , sy , i);

            for(i = 0; i < BRDDISTANCE; i++)
            {
                mvprintw(Nav.y+sy, Nav.x-1, Sprite[i]);
                sy += 1;
            }
            sy = -1;
            break;
        }
        default:
        {
            mvprintw((getmaxy(stdscr)/2) , (getmaxx(stdscr)/2) , "Questo non dovrebbe mai essere stampato");
        }
    }
}
