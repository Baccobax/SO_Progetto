#include "SubroutinesSO.h"
/*
void *collision()
{
    usleep(69);
    pos Nav, proiettile, proiettileGIU , proiettileSU , Nem ,coll_nem[NEMICI];
    int MAXY , MAXX, i, Nem_counter = 0, sy = -1 , nNav = 0 , Nem_life[NEMICI] , Nav_life = HEALTHY;
    bool game_over = false, victory = false; 
    getmaxyx(stdscr, MAXY, MAXX);
    Nav.x = -1;
    proiettile.x = -1; 

    for(i = 0 ; i < NEMICI ; i++)
    {
        Nem_life[i] = HEALTHY; 
    }

    refresh();
    do
    {
        if(Nav_life == 0)
        {
            game_over = true;
            if(pthread_join(threadNavEColl[NAV], NULL) != 0) 
            {
                return 2;
            }
        }

        EliminaNemici(nNav , coll_nem , Nem_life , MAXX , MAXY);

        for(i = 0; i < NEMICI ; i++)
        {
            if(Nem_life[i] == DEATH)
            {
                Nem_counter++;                
            }
            if(Nem_counter == NEMICI)
            {
                victory = true;
            }
        }
        Nem_counter = 0;
        
        border(ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , '*' , '*' , '*' , '*');
        
        nNav = pos_nemico.indice_oggetto;
        
        //Navicella Nemica
        if(Nem_life[nNav] > DEATH)
        {
            if(Nem_life[nNav] == HITTED || Nem_life[nNav] == ALMOST_DEAD)
            {
                valore_letto.status = Nav_Nemica_Rotta;
            }
            coll_nem[nNav] = pos_nemico[nNav];
            
            if(coll_nem[nNav].x > BRDDISTANCE)
            {
                StampaNavicelle(coll_nem[nNav] , sy , i , nNav);
            }
            if(valore_letto.x <= BRDDISTANCE)
            {
                mvaddch(valore_letto.y , valore_letto.x , ' ');
                game_over = true;   
            }
            if((nNav+1) < NEMICI)
            {
                nNav++;
            }
        }
            
            
        //Navicella giocatore
        Nav = pos_navicella;
        if(Nav.x >= 0 && Nav_life > DEATH)
        {
            StampaNavicelle(Nav , sy , i , nNav);
        }
            

        //Proiettile nemico
        for(i=0; i<NEMICI; i++)
        {
            if (pos_pro_nem[i].x!=coll_nem[i].x||pos_pro_nem[i].y!=coll_nem[i].y)
            {
                if(pos_pro_nem.x <= MAXX-BRDDISTANCE)
                {
                    mvaddch(pos_pro_nem[i].y , pos_pro_nem[i].x+1 , ' ');
                    mvaddch(pos_pro_nem[i].y , pos_pro_nem[i].x , pos_pro_nem[i].cp);
                }
            }
        }     
        if(pos_pro_nem.x <= BRDDISTANCE)
        {
            mvaddch(pos_pro_nem[i].y , pos_pro_nem[i].x , ' ');                    
        }            
        
        if(pos_pro_nem[i].x == Nav.x+1 && (pos_pro_nem[i].y == Nav.y || pos_pro_nem[i].y == Nav.y+1 || pos_pro_nem[i].y == Nav.y-1))
        {
            flash();
            Nav_life--;
            if(Nav_life < DEATH)
            {
                Nav_life = DEATH;
            }
        }
        //Proiettile base
        if(pos_proiettile.x >= BRDDISTANCE)
        {
            mvaddch(pos_proiettile.y , pos_proiettile.x-1, ' ');
            mvaddch(pos_proiettile.y , pos_proiettile.x , pos_proiettile.cp);
        }
        if(pos_proiettile.x >= MAXX-2)
        {
            mvaddch(pos_proiettile.y , pos_proiettile.x , ' ');                    
        }
            
        for(i=0; i<NEMICI; i++)
        {
            if (pos_proiettile.x == coll_nem[i].x && (pos_proiettile.y == coll_nem[i].y || pos_proiettile.y == coll_nem[i].y+1 || pos_proiettile.y == coll_nem[i].y-1))
            {
                Nem_life[i]--;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                if(pthread_join(threadProiettili[PROIETTILE_DRITTO] , NULL) != 0)
                {
                    return 2;
                }
                Cancella3x4(pos_proiettile , sy , i);
            }
        }
        //Proiettile che va giù
        if(pos_proiettile_giu.x >= BRDDISTANCE)
            {
                mvaddch(pos_proiettile_giu.y-1 , pos_proiettile_giu.x-1, ' ');
                mvaddch(pos_proiettile_giu.y , pos_proiettile_giu.x , pos_proiettile_giu.cp);
            }
        if(pos_proiettile_giu.x >= MAXX-2)
            {
                mvaddch(pos_proiettile_giu.y , pos_proiettile_giu.x , ' ');                    
            }

        for(i=0; i < NEMICI; i++)
        {
            if (pos_proiettile_giu.x == coll_nem[i].x && (pos_proiettile_giu.y == coll_nem[i].y || pos_proiettile_giu.y == coll_nem[i].y+1 || pos_proiettile_giu.y == coll_nem[i].y-1))
            {
                Nem_life[i]--;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                if(pthread_join(threadProiettili[PROIETTILE_IGIU] , NULL) != 0)
                {
                    return 2;
                }
                Cancella3x4(pos_proiettile_giu , sy , i);
            }
        }   
        
        //Proiettile che va su
        if(pos_proiettile_su.x >= BRDDISTANCE)
        {
            mvaddch(pos_proiettile_su.y+1 , pos_proiettile_su.x-1, ' ');
            mvaddch(pos_proiettile_su.y , pos_proiettile_su.x , pos_proiettile_su.cp);
        }
        if(pos_proiettile_su.x >= MAXX-2)
        {
            mvaddch(pos_proiettile_su.y , pos_proiettile_su.x , ' ');                    
        }
        for(i=0; i<NEMICI; i++)
        {
            if (pos_proiettile_su.x == coll_nem[i].x && (pos_proiettile_su.y == coll_nem[i].y || pos_proiettile_su.y == coll_nem[i].y+1 || pos_proiettile_su.y == coll_nem[i].y-1))
            {
                Nem_life[i]--;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                if(pthread_join(threadProiettili[PROIETTILE_ISU] , NULL) != 0)
                {
                    return 2;
                }
                Cancella3x4(pos_proiettile_su , sy , i);
            }
        }
        refresh();
    } while(game_over == false && victory == false);
    beep();
    flash();
    clear();
    refresh();
    if(game_over == true)
    {
        for(i = 0 ; i < NEMICI ; i++)
        {
            Nem_life[i] = DEATH; 
        }
        EliminaNemici(nNav , coll_nem , Nem_status , Nem_life , MAXX , MAXY);
        if(pthread_join(threadNavEColl[NAV] , NULL) != 0)
        {
            return 2;
        }
        GameOver(MAXX , MAXY);
    }
    else
    {
        YouWin(MAXX, MAXY);
        if(pthread_join(threadNavEColl[NAV] , NULL) != 0)
        {
            return 2;
        }
    }
    clear();
    refresh();
}

void EliminaNemici(int nNav , pos *coll_nem , int *Nem_life , int MAXX , int MAXY)
{
    for(nNav = 0 ; nNav < NEMICI ; nNav++)
    {
        if(Nem_life[nNav] == DEATH)
        {

        if (pthread_join(threadNemici[nNav], NULL) != 0) 
        {
            return 2;
        }
        coll_nem[nNav].y = MAXY;
        coll_nem[nNav].x = MAXX;
        }
    }
}


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
*/