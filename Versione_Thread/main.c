#include "SubroutinesSO.h"

/**
 * TODO
 * Sincronizzare l'intero programma
 * Dopo che un nemico viene ucciso, tutti si fermano. Psossbile bug in generazione coordinate dopo che il thread scomapre, oppure solito errore di sincronizzazione.
 * Potrebbe esssere causato da un controllo sull'indice dell'array, provare a implementare un controllo con lo status quando è morto. Possibile dover aggiungere un valore di enumerazione per tale stato.
 * 
 */

pthread_t threadNemici[NEMICI], threadNavEColl[NAVECOLL] , threadProiettili[PROIETTILI] , threadProiettiliNemici[NEMICI];
pthread_mutex_t mutex;
pos pos_navicella, pos_proiettile , pos_proiettile_giu , pos_proiettile_su , pos_nemico[NEMICI] , pos_pro_nem[NEMICI];
int cont;

void main()
{
    int i = 0 , *contatore = malloc(sizeof(int));
    srand((unsigned) time(NULL));
    pthread_mutex_init(&mutex, NULL);
    InizializzaProiettiliNemici();
    
    initscr();
    noecho();
    curs_set(false);
    //sfondo();

    //refresh();
    
    
    if(pthread_create(&threadNavEColl[NAV], NULL, NavicellaGiocatore, NULL) != 0)
    {
        
        perror("Failed to create ally spaceship thread");
        exit(5);
    }
    
    usleep(10000);

    for (i = 0; i < NEMICI ; i++) 
    {
        usleep(1000);
        *contatore = i;
        if (pthread_create(&threadNemici[i], NULL, Nemici, contatore) != 0) 
        {
            perror("Failed to create enemy thread");
            exit(5);
        }
    }

    collision();
    /*

    for (i = 0; i < NAV; i++) 
        {
            if (pthread_join(threadNavEColl[i], NULL) != 0) 
            {
                perror("Failed to join thread");
            }
        }
        for (i = 0; i < NEMICI; i++)
        {
            if (pthread_join(threadNemici[i], NULL) != 0) 
            {
                perror("Failed to join thread");
            }
        }
    */
    endwin();
    pthread_mutex_destroy(&mutex);
    exit(0);  
}


void *NavicellaGiocatore()
{
    int c , MAXX , MAXY;
    bool i = false , j = false;
    getmaxyx(stdscr, MAXY, MAXX);
    keypad(stdscr , true);
    pthread_mutex_lock(&mutex);
    pos_navicella.status = Nav_Alleata;
    pos_proiettile.status = Proiettile;
    pos_proiettile_giu.status = Proiettile;
    pos_proiettile_su.status = Proiettile;
    pos_navicella.x = 1;
    pos_navicella.y = MAXY/2;
    pos_proiettile.cp = '+';
    pos_proiettile_giu.cp = '\\';
    pos_proiettile_su.cp = '/';
    pthread_mutex_unlock(&mutex);

    while(true)
    {
        c = getch();
        timeout(100);
        switch(c)
        {
            case KEY_UP:
            {
                if(pos_navicella.y > BRDDISTANCE)
                {
                    pthread_mutex_lock(&mutex);
                    pos_navicella.y -= 1;
                    pthread_mutex_unlock(&mutex);
                    break;
                }
            }        
            case KEY_DOWN:
            {
                if(pos_navicella.y < MAXY-4)
                {
                    pthread_mutex_lock(&mutex);
                    pos_navicella.y += 1;
                    pthread_mutex_unlock(&mutex);
                    break;
                }
            }
            case 'x':
            {
                if(i == false)
                {
                    i = true;
                    if(pthread_create(&threadProiettili[PROIETTILE_DRITTO], NULL, &Proiettile_dritto, NULL) != 0)
                    {
                        perror("Failed to create straight projectile thread");
                        exit(5);
                    }
                }
            }
                    break;
            case ' ':
            {
                if(j == false)
                {
                    j = true;
                    if(pthread_create(&threadProiettili[PROIETTILE_IGIU], NULL, &Proiettili_giu, NULL) != 0)
                    {
                        perror("Failed to create downward projectile thread");
                        exit(5);
                    }
                    if(pthread_create(&threadProiettili[PROIETTILE_ISU], NULL, &Proiettili_su, NULL) != 0)
                    {
                        perror("Failed to create upward projectile thread");
                        exit(5);
                    }
                }
                break;
            }
        }


        if(i == true && (pos_proiettile.x >= MAXX - 2))
        {
            i = false;
            if (pthread_join(threadProiettili[PROIETTILE_DRITTO], NULL) != 0) 
            {
                exit(5);
            }
        }
        if(j == true && pos_proiettile_giu.x >= MAXX - 2 && pos_proiettile_su.x >= MAXX - 2)
        {
            j = false;
            if (pthread_join(threadProiettili[PROIETTILE_ISU], NULL) != 0) 
            {
                exit(5);
            }
            if (pthread_join(threadProiettili[PROIETTILE_IGIU], NULL) != 0) 
            {
                exit(5);
            }
        }
    }
}

void *Proiettile_dritto()
{
    int MAXX = getmaxx(stdscr);
    pthread_mutex_lock(&mutex);
    pos_proiettile.x = pos_navicella.x + 4;
    pos_proiettile.y = pos_navicella.y;
    pthread_mutex_unlock(&mutex);
    
    while(pos_proiettile.x < MAXX - 2) // il proiettile si ferma subito prima del bordo
    {
        pthread_mutex_lock(&mutex);
        pos_proiettile.x++;
        pthread_mutex_unlock(&mutex);
        usleep(BULLET_SPEED);
    }
    usleep(35000);
}

void *Proiettili_giu()
{
    int dyG = MOVIMENTO , MAXY , MAXX;
    getmaxyx(stdscr, MAXY, MAXX);
    pthread_mutex_lock(&mutex);
    pos_proiettile_giu.x = pos_navicella.x + 4;
    pos_proiettile_giu.y = pos_navicella.y-1;
    pthread_mutex_unlock(&mutex);
    
    while(pos_proiettile_giu.x < MAXX - 2)
    {
        if(pos_proiettile_giu.y < 2) 
        {
            dyG = MOVIMENTO;
            pthread_mutex_lock(&mutex);
            pos_proiettile_giu.cp = '\\';
            pthread_mutex_unlock(&mutex);
        }
        if(pos_proiettile_giu.y >= MAXY - 2)
        {
            dyG = -MOVIMENTO;
            pthread_mutex_lock(&mutex);
            pos_proiettile_giu.cp = '/';
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_lock(&mutex);
        pos_proiettile_giu.y += dyG;
        pos_proiettile_giu.x++;
        pthread_mutex_unlock(&mutex);
        usleep(BULLET_SPEED);
    }
    usleep(35000);
}

void *Proiettili_su()
{   
    int dyS = -MOVIMENTO, MAXY , MAXX;
    getmaxyx(stdscr, MAXY, MAXX);
    pthread_mutex_lock(&mutex);
    pos_proiettile_su.x = pos_navicella.x + 4;
    pos_proiettile_su.y = pos_navicella.y - 1;
    pthread_mutex_unlock(&mutex);

    while(pos_proiettile_su.x < MAXX - 2)
    {
        if(pos_proiettile_su.y < 2) 
        {
            dyS = MOVIMENTO;
            pthread_mutex_lock(&mutex);
            pos_proiettile_su.cp = '\\';
            pthread_mutex_unlock(&mutex);
        }
        if(pos_proiettile_su.y >= MAXY - 2)
        {
            dyS = -MOVIMENTO;
            pthread_mutex_lock(&mutex);
            pos_proiettile_su.cp = '/';
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_lock(&mutex);
        
        pos_proiettile_su.y += dyS;
        pos_proiettile_su.x++;
        pthread_mutex_unlock(&mutex);
        usleep(BULLET_SPEED);
    }
    usleep(35000);
}

///////////////////////////


//Da Modificare
void *Nemici(void *contatore)
{
    int MAXX , MAXY , MIDY , mx , my , randP , i , cont_nemici = *(int*)contatore , *indice_da_passare = malloc(sizeof(int));
    getmaxyx(stdscr , MAXY , MAXX);
    int column_nem = getmaxy(stdscr)* 5 / 23;
    pthread_mutex_lock(&mutex);
    *indice_da_passare = cont_nemici;

    

    pthread_mutex_unlock(&mutex);

    mx = cont_nemici/column_nem;
    my = cont_nemici % column_nem;

    pos_nemico[cont_nemici].indice_oggetto = cont_nemici;
    pos_nemico[cont_nemici].x = MAXX - BRDDISTANCE - ((BRDDISTANCE+1)*mx);

    pthread_mutex_lock(&mutex);
    if(my == 0)
    {
        pos_nemico[cont_nemici].y = MAXY/2;
    }
    if(my % 2 == 0)
    {
        pos_nemico[cont_nemici].y = (MAXY/2) - my*2;
    }
    else
    {
        pos_nemico[cont_nemici].y = (MAXY/2) + 2 + my*2;
    }

    pos_nemico[cont_nemici].status = Nav_Nemica;

    pos_nemico[cont_nemici].up_down = true;
    pthread_mutex_unlock(&mutex);
    while(pos_nemico[cont_nemici].x > BRDDISTANCE)
    {        
        usleep(ENEMY_SPEED);
        if((rand() + rand() ) % 11 == 0)
        {
            if((rand() + rand() ) % 19 == 0)
            {    
                if(pthread_create(&threadProiettiliNemici[cont_nemici], NULL, &SparoNemici, indice_da_passare) != 0)
                {
                    perror("Failed to create enemy projectile thread");
                    exit(5);
                }
            }
        }
        if(pos_nemico[cont_nemici].up_down == true)
        {
            pthread_mutex_lock(&mutex);
            pos_nemico[cont_nemici].y--;
            pos_nemico[cont_nemici].up_down = false;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_lock(&mutex);
            pos_nemico[cont_nemici].y++;
            pos_nemico[cont_nemici].up_down = true;
            pthread_mutex_unlock(&mutex);
        }
        
        usleep(ENEMY_SPEED);
        pthread_mutex_lock(&mutex);
        pos_nemico[cont_nemici].x--;
        pthread_mutex_unlock(&mutex);
    }
}

void InizializzaProiettiliNemici()
{
    int i;
    for(i = 0; i < NEMICI ; i++)
    {
        pthread_mutex_lock(&mutex);
        pos_pro_nem[i].status = Proiettile_Morto;
        pthread_mutex_unlock(&mutex);
    }
}

void *SparoNemici(void *arg)
{
    int i , indice_nemico = *(int*)arg;
    for(i = 0 ; i < NEMICI ; i++)
    {
        if(pos_pro_nem[i].status == Proiettile_Morto)
        {
            pthread_mutex_lock(&mutex);
            pos_pro_nem[i].status = Proiettile;
            pos_pro_nem[i].cp = '<';
            pos_pro_nem[i].x = pos_nemico[indice_nemico].x-3;
            pos_pro_nem[i].y = pos_nemico[indice_nemico].y;
            pthread_mutex_unlock(&mutex);
            while(pos_pro_nem[i].x >= BRDDISTANCE)
            {
                usleep(25000);
                pthread_mutex_lock(&mutex);
                pos_pro_nem[i].x--;
                pthread_mutex_unlock(&mutex);
            }
            pthread_mutex_lock(&mutex);
            pos_pro_nem[i].status = Proiettile_Morto;
            pthread_mutex_unlock(&mutex);
        }
    }
}


///////////////////////////


void collision()
{
    usleep(10000);
    pos Nav, proiettile, proiettileGIU , proiettileSU , Nem;
    int MAXY , MAXX, i, Nem_counter = 0, sy = -1 , nNav = 0 , Nem_life[NEMICI] , Nav_life = 99;
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
                exit(5);
            }
        }

        EliminaNemici(nNav , pos_nemico , Nem_life , MAXX , MAXY);

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
        
        nNav = pos_nemico[nNav].indice_oggetto;
        
        //Navicella Nemica
        usleep(1000);
        pthread_mutex_lock(&mutex);
        if(Nem_life[nNav] > DEATH)
        {
            for(i = 0 ; i < NEMICI ; i++)
            {
                mvprintw(3+i , 10 , "%d %d" , pos_nemico[i].x , pos_nemico[i].y);
                mvprintw(3+i , 16 , "%d" , Nem_life[i]);
                mvprintw(20 , 10 , "%d " , nNav);
            }
            if(Nem_life[nNav] == HITTED || Nem_life[nNav] == ALMOST_DEAD)
            {
                pos_nemico[nNav].status = Nav_Nemica_Rotta;
            }
            
            if(pos_nemico[nNav].x > BRDDISTANCE)
            {
                StampaNavicelle(pos_nemico[nNav] , sy , i , nNav);
            }
            if(pos_nemico[nNav].x <= BRDDISTANCE)
            {
                mvaddch(pos_nemico[nNav].y , pos_nemico[nNav].x , ' ');
                //game_over = true;
            }
            
            nNav++;
            
            if(nNav == NEMICI)
            {
                nNav = 0;
            }
        }
        pthread_mutex_unlock(&mutex);
         
        //Navicella giocatore
        pthread_mutex_lock(&mutex);
        Nav = pos_navicella;
        if(Nav.x >= 0 && Nav_life > DEATH)
        {
            StampaNavicelle(Nav , sy , i , nNav);
        }
        pthread_mutex_unlock(&mutex);
        
        //Proiettile nemico
        for(i=0; i<NEMICI; i++)
        {
            if (pos_pro_nem[i].x!=pos_nemico[i].x||pos_pro_nem[i].y!=pos_nemico[i].y)
            {
                if(pos_pro_nem[i].x <= MAXX-BRDDISTANCE)
                {
                    mvaddch(pos_pro_nem[i].y , pos_pro_nem[i].x+1 , ' ');
                    mvaddch(pos_pro_nem[i].y , pos_pro_nem[i].x , pos_pro_nem[i].cp);
                }
            }
        }
             
        for(i = 0 ; i < NEMICI ; i++)
        {
            if(pos_pro_nem[i].x <= BRDDISTANCE)
            {
                mvaddch(pos_pro_nem[i].y , pos_pro_nem[i].x , ' ');                    
            } 
        }           
        
        for(i = 0 ; i < NEMICI ; i++)
        {
            usleep(5000);
            if(pos_pro_nem[i].x == Nav.x+1 && (pos_pro_nem[i].y == Nav.y || pos_pro_nem[i].y == Nav.y+1 || pos_pro_nem[i].y == Nav.y-1))
            {

                flash();
                Nav_life--;
                if(Nav_life < DEATH)
                {
                    Nav_life = DEATH;
                }
            }
        }
        
        //Proiettile base
        usleep(1000);
        if(pos_proiettile.x >= BRDDISTANCE)
        {
            mvaddch(pos_proiettile.y , pos_proiettile.x-1, ' ');
            usleep(750);
            mvaddch(pos_proiettile.y , pos_proiettile.x , pos_proiettile.cp);
        }
        if(pos_proiettile.x >= MAXX-2)
        {
            mvaddch(pos_proiettile.y , pos_proiettile.x , ' ');                    
        }
            
        for(i=0; i<NEMICI; i++)
        {
            usleep(750);
            if (pos_proiettile.x == pos_nemico[i].x && (pos_proiettile.y == pos_nemico[i].y || pos_proiettile.y == pos_nemico[i].y+1 || pos_proiettile.y == pos_nemico[i].y-1))
            {
                usleep(750);
                Nem_life[i]--;
                pos_proiettile.x = MAXX;
                pos_proiettile.y = MAXY;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                pthread_cancel(threadProiettili[PROIETTILE_DRITTO]);
                Cancella3x4(pos_proiettile , sy , i);
            }
        }
        //Proiettile che va giù
        if(pos_proiettile_giu.x >= BRDDISTANCE)
            {
                mvaddch(pos_proiettile_giu.y-1 , pos_proiettile_giu.x-1, ' ');
                mvaddch(pos_proiettile_giu.y+1 , pos_proiettile_giu.x-1, ' ');
                usleep(750);
                mvaddch(pos_proiettile_giu.y , pos_proiettile_giu.x , pos_proiettile_giu.cp);
            }
        if(pos_proiettile_giu.x >= MAXX-2)
            {
                mvaddch(pos_proiettile_giu.y , pos_proiettile_giu.x , ' ');                    
            }

        for(i=0; i < NEMICI; i++)
        {
            if (pos_proiettile_giu.x == pos_nemico[i].x && (pos_proiettile_giu.y == pos_nemico[i].y || pos_proiettile_giu.y == pos_nemico[i].y+1 || pos_proiettile_giu.y == pos_nemico[i].y-1))
            {
                Nem_life[i]--;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                if(pthread_join(threadProiettili[PROIETTILE_IGIU] , NULL) != 0)
                {
                    exit(5);
                }
                Cancella3x4(pos_proiettile_giu , sy , i);
            }
        }   
        
        //Proiettile che va su
        if(pos_proiettile_su.x >= BRDDISTANCE)
        {
            mvaddch(pos_proiettile_su.y+1 , pos_proiettile_su.x-1, ' ');
            mvaddch(pos_proiettile_su.y-1 , pos_proiettile_su.x-1, ' ');
            usleep(750);
            mvaddch(pos_proiettile_su.y , pos_proiettile_su.x , pos_proiettile_su.cp);
        }
        if(pos_proiettile_su.x >= MAXX-2)
        {
            mvaddch(pos_proiettile_su.y , pos_proiettile_su.x , ' ');                    
        }
        for(i=0; i<NEMICI; i++)
        {
            if (pos_proiettile_su.x == pos_nemico[i].x && (pos_proiettile_su.y == pos_nemico[i].y || pos_proiettile_su.y == pos_nemico[i].y+1 || pos_proiettile_su.y == pos_nemico[i].y-1))
            {
                Nem_life[i]--;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                if(pthread_join(threadProiettili[PROIETTILE_ISU] , NULL) != 0)
                {
                    exit(5);
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
        EliminaNemici(nNav , pos_nemico, Nem_life , MAXX , MAXY);
        if(pthread_join(threadNavEColl[NAV] , NULL) != 0)
        {
            exit(5);
        }
        GameOver(MAXX , MAXY);
    }
    else
    {
        YouWin(MAXX, MAXY);
        if(pthread_join(threadNavEColl[NAV] , NULL) != 0)
        {
            exit(5);
        }
    }
    clear();
    refresh();
}

void EliminaNemici(int nNav , pos *coll_nem , int *Nem_life , int MAXX , int MAXY)
{
    for(nNav = 0 ; nNav < NEMICI ; nNav++)
    {
        usleep(1000);
        if(Nem_life[nNav] == DEATH)
        {
        /*if (pthread_join(threadNemici[nNav], NULL) != 0) 
        {
            exit(2);
        }*/
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
