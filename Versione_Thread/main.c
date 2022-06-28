#include "SubroutinesSO.h"



pthread_t threadNemici[NEMICI], threadNavEColl[NAVECOLL] , threadProiettili[PROIETTILI] , threadProiettiliNemici[NEMICI];
pthread_mutex_t mutex;
pos pos_navicella, pos_proiettile , pos_proiettile_giu , pos_proiettile_su , pos_nemico[NEMICI] , pos_pro_nem[NEMICI/2] , buffer_pro_nem[NEMICI/2];
int cont = 0;
bool j_pro = false , i_pro = false;

void main()
{
    int i = 0 , *contatore = malloc(sizeof(int));
    srand((unsigned) time(NULL));
    pthread_mutex_init(&mutex, NULL);
    InizializzaProiettiliNemici();
    
    initscr();
    noecho();
    curs_set(false);
    sfondo();

    
    
    if(pthread_create(&threadNavEColl[NAV], NULL, NavicellaGiocatore, NULL) != 0)
    {
        
        perror("Failed to create ally spaceship thread");
        exit(5);
    }
    
    usleep(10000);

    for (i = 0; i < NEMICI ; i++) 
    {
        usleep(100);
        *contatore = i;
        cont = i;
        if (pthread_create(&threadNemici[i], NULL, Nemici, contatore) != 0) 
        {
            perror("Failed to create enemy thread");
            exit(5);
        }
    }

    collision();


    endwin();
    pthread_mutex_destroy(&mutex);
    exit(0);  
}

/**
 * @brief Funzione che si occupa della generazione e modifica delle coordinate delle navicella. Si occupa anche generazione dei proiettili
 * 
 * @return void* 
 */
void *NavicellaGiocatore()
{
    int c , MAXX , MAXY;
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
                if(i_pro == false)
                {
                    i_pro = true;
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
                if(j_pro == false)
                {
                    j_pro = true;
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


        if(i_pro == true && (pos_proiettile.x >= MAXX - 2))
        {
            i_pro = false;
            pthread_cancel(threadProiettili[PROIETTILE_DRITTO]);
            pthread_mutex_lock(&mutex);
            pos_proiettile.x = -1;
            pthread_mutex_unlock(&mutex);
        }
        if(j_pro == true && pos_proiettile_giu.x >= MAXX - 2 && pos_proiettile_su.x >= MAXX - 2)
        {
            j_pro = false;
            pthread_mutex_lock(&mutex);
            pos_proiettile_giu.y = -1;
            pos_proiettile_giu.x = -1;
            pos_proiettile_su.y = -1;
            pos_proiettile_su.x = -1;
            pthread_mutex_unlock(&mutex);
            pthread_cancel(threadProiettili[PROIETTILE_ISU]);
            pthread_cancel(threadProiettili[PROIETTILE_IGIU]);
        }
    }
}

/**
 * @brief Funzione che si occupa della generazione dei proiettili in senso orizzontale
 * 
 * @return void* 
 */
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

/**
 * @brief Funzione che si occupa della generazione dei proiettili in senso diagonale che partono verso il basso
 * 
 * @return void* 
 */
void *Proiettili_giu()
{
    int dyG = MOVIMENTO , MAXY , MAXX;
    getmaxyx(stdscr, MAXY, MAXX);
    pthread_mutex_lock(&mutex);
    pos_proiettile_giu.x = pos_navicella.x + 4;
    pos_proiettile_giu.y = pos_navicella.y-1;
    pos_proiettile_giu.cp = '\\';
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
    pthread_mutex_lock(&mutex);
    pos_proiettile_giu.y = -1;
    pos_proiettile_giu.x = -1;
    pthread_mutex_unlock(&mutex);
    usleep(35000);
}

/**
 * @brief Funzione che si occupa della generazione dei proiettili in senso diagonale che partono verso l'alto
 * 
 * @return void* 
 */
void *Proiettili_su()
{   
    int dyS = -MOVIMENTO, MAXY , MAXX;
    getmaxyx(stdscr, MAXY, MAXX);
    pthread_mutex_lock(&mutex);
    pos_proiettile_su.cp = '/';
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
    pthread_mutex_lock(&mutex);
    pos_proiettile_su.y = -1;
    pos_proiettile_su.x = -1;
    pthread_mutex_unlock(&mutex);
    usleep(35000);
}


/**
 * @brief Funzione che si occupa della generazione e modifica delle coordinate dei nemici. Inoltre si occupa della generazione dei proiettili nemici
 * 
 * @param contatore contatore che indica l'indice dei nemici generati. Viene incrementato ogni volta che viene generato un nuovo nemico e viene usato per la generazione dei proiettili nemici.
 * @return void* 
 */
void *Nemici(void *contatore)
{
    int MAXX , MAXY , MIDY , mx , my , randP , i , cont_nemici = *(int*)contatore , *indice_da_passare = malloc(sizeof(int));
    getmaxyx(stdscr , MAXY , MAXX);
    int column_nem = getmaxy(stdscr)* 5 / 23; //column_nem = numero di colonne in cui dividere i nemici. questo calcolo permette di adattare le colonne in base alla grandezza dello schermo

    pthread_mutex_lock(&mutex);
    *indice_da_passare = cont_nemici;
    pthread_mutex_unlock(&mutex);

    mx = cont_nemici/column_nem; //variabile utilizzata per impostare di volta in volta in base al loro indice la posizione x dei nemici
    my = cont_nemici % column_nem; //variabile utilizzata per impostare di volta in volta in base al loro indice la posizione y dei nemici

    pos_nemico[cont_nemici].indice_oggetto = cont_nemici;
    pos_nemico[cont_nemici].x = MAXX - BRDDISTANCE-1 - ((BRDDISTANCE+1)*mx);

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

    while(cont != NEMICI-1)
    {usleep(500);}

    while(pos_nemico[cont_nemici].x > BRDDISTANCE && cont == NEMICI-1)
    {        
        usleep(ENEMY_SPEED);
        if((rand() + rand() ) % 2 == 0)
        {
            if((rand() + rand() ) % 2 == 0)
            {    
                AspettaProiettili();
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

/**
 * @brief Funzione che si occupa di inizializzare lo status dei proiettili nemici.
 * 
 */
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


/**
 * @brief Funzione che si occupa di generare i proiettili nemici e di modificare le sue coordinate.
 * 
 * @param arg indice del nemico utilizzato per identificare il nemico che spara il proiettile.
 * @return void* 
 */
void *SparoNemici(void *arg)
{
    int i , indice_nemico = *(int*)arg;
    for(i = 0 ; i < NEMICI/2 ; i++)
    {
        if(pos_pro_nem[i].status == Proiettile_Morto)
        {
            pthread_mutex_lock(&mutex);
            pos_pro_nem[i].status = Proiettile;
            pos_pro_nem[i].cp = '<';
            pos_pro_nem[i].x = pos_nemico[indice_nemico].x-3;
            pos_pro_nem[i].y = pos_nemico[indice_nemico].y;
            pthread_mutex_unlock(&mutex);
            while(pos_pro_nem[i].x >= BRDDISTANCE-1)
            {
                usleep(ENEMY_BULLET_SPEED);
                pthread_mutex_lock(&mutex);
                pos_pro_nem[i].x--;
                pthread_mutex_unlock(&mutex);
            }
            pthread_mutex_lock(&mutex);
            pos_pro_nem[i].status = Proiettile_Morto;
            pos_pro_nem[i].x = -2;
            pthread_mutex_unlock(&mutex);
            usleep(ENEMY_BULLET_SPEED);
        }
    }
}

/**
 * @brief Funzione che impone un'attesa nella generazione dei proiettili in base a quanti proiettili sono vivi al momento della chiamata
 * 
 */
void AspettaProiettili()
{
    int i;
    for(i = 0; i < (NEMICI/2)-1 ; i++)
    {
        if(pos_pro_nem[i].status == Proiettile)
        {
            usleep(ENEMY_BULLET_SPEED);
        }
    }
}

/**
 * @brief Funzione che si occupa delle varie stampe e gestisce le collisioni tra oggetti. Inoltre si occupa di eliminare determinati thread in caso di collisione.
 * 
 */
void collision()
{
    usleep(1500000);
    curs_set(false);
    pos Nav, proiettile, proiettileGIU , proiettileSU , Nem;
    int MAXY , MAXX, i, Nem_counter = 0, sy = -1 , nNav = 0 , Nem_life[NEMICI] , Nav_life = 3;
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
        border(ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , '*' , '*' , '*' , '*');
        refresh();
        if(Nav_life == DEATH)
        {
            game_over = true;
            pthread_cancel(threadNavEColl[NAV]);
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
        
        
        //Navicella Nemica
        usleep(1000);
        for(nNav = 0 ; nNav < NEMICI ; nNav++)
        {
            if(Nem_life[nNav] >= DEATH)
            {
                if(Nem_life[nNav] == HITTED || Nem_life[nNav] == ALMOST_DEAD)
                {
                    pos_nemico[nNav].status = Nav_Nemica_Rotta;
                }
                
                if(pos_nemico[nNav].x > BRDDISTANCE)
                {
                    StampaNavicelle(pos_nemico[nNav] , sy , i);
                }
                if(pos_nemico[nNav].x <= BRDDISTANCE)
                {
                    mvaddch(pos_nemico[nNav].y , pos_nemico[nNav].x , ' ');
                    game_over = true;
                }
            }
        }

         
        //Navicella giocatore
        Nav = pos_navicella;
        if(Nav.x >= 0 && Nav_life > DEATH)
        {
            StampaNavicelle(Nav , sy , i);
        }

        
        //Proiettile nemico
        usleep(1000);
        for(i = 0 ; i < NEMICI/2 ; i++)
        {
            if (pos_pro_nem[i].x != pos_nemico[i].x || pos_pro_nem[i].y != pos_nemico[i].y)
            {
                if(pos_pro_nem[i].x <= MAXX-BRDDISTANCE)
                {
                    usleep(1000);
                    mvprintw(pos_pro_nem[i].y , pos_pro_nem[i].x+1 , "     ");
                    mvaddch(pos_pro_nem[i].y , pos_pro_nem[i].x , pos_pro_nem[i].cp);
                }
            }
        }
        
        for(i = 0 ; i < NEMICI ; i++)
        {
            if(pos_pro_nem[i].x <= BRDDISTANCE)
            {
                mvprintw(pos_pro_nem[i].y , pos_pro_nem[i].x-1 , "      ");                    
            }
        }           
        
        for(i = 0 ; i < NEMICI ; i++)
        {
            usleep(5000);
            if(pos_pro_nem[i].x == Nav.x+1 && (pos_pro_nem[i].y == Nav.y || pos_pro_nem[i].y == Nav.y+1 || pos_pro_nem[i].y == Nav.y-1))
            {
                clear();
                flash();
                refresh();
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
            usleep(750);
            mvprintw(pos_proiettile.y , pos_proiettile.x-3, "   ");
            mvaddch(pos_proiettile.y , pos_proiettile.x , pos_proiettile.cp);
        }
        if(pos_proiettile.x >= MAXX-BRDDISTANCE)
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
                pos_proiettile.x = -1;
                pos_proiettile.y = -1;
                i_pro = false;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                pthread_cancel(threadProiettili[PROIETTILE_DRITTO]);
                Cancella3x4(pos_proiettile , sy , i);
            }
        }
        //Proiettile che va giù
        usleep(1000);
        if(pos_proiettile_giu.x >= BRDDISTANCE)
        {
            usleep(750);
            for(i = 1 ; i < BRDDISTANCE ; i++)
            {
                mvaddch(pos_proiettile_giu.y+i , pos_proiettile_giu.x-i, ' ');
                mvaddch(pos_proiettile_giu.y-i , pos_proiettile_giu.x-i, ' ');
            }
            mvaddch(pos_proiettile_giu.y , pos_proiettile_giu.x , pos_proiettile_giu.cp);
        }
        if(pos_proiettile_giu.x >= MAXX-BRDDISTANCE)
            {
                mvaddch(pos_proiettile_giu.y , pos_proiettile_giu.x , ' ');                    
            }

        for(i=0; i < NEMICI; i++)
        {
            if (pos_proiettile_giu.x == pos_nemico[i].x && (pos_proiettile_giu.y == pos_nemico[i].y || pos_proiettile_giu.y == pos_nemico[i].y+1 || pos_proiettile_giu.y == pos_nemico[i].y-1))
            {
                usleep(750);
                Nem_life[i]--;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                pthread_cancel(threadProiettili[PROIETTILE_IGIU]);
                Cancella3x4(pos_proiettile_giu , sy , i);
                pos_proiettile_giu.y = -1;
                pos_proiettile_giu.x = -1;
            }
        }   
        
        //Proiettile che va su
        usleep(1000);
        if(pos_proiettile_su.x >= BRDDISTANCE)
        {
            usleep(750);
            for(i = 1 ; i < BRDDISTANCE ; i++)
            {
                mvaddch(pos_proiettile_su.y+i , pos_proiettile_su.x-i, ' ');
                mvaddch(pos_proiettile_su.y-i , pos_proiettile_su.x-i, ' ');
            }
            mvaddch(pos_proiettile_su.y , pos_proiettile_su.x , pos_proiettile_su.cp);
        }
        if(pos_proiettile_su.x >= MAXX-BRDDISTANCE)
        {
            mvaddch(pos_proiettile_su.y , pos_proiettile_su.x , ' ');                    
        }
        for(i=0; i<NEMICI; i++)
        {
            if (pos_proiettile_su.x == pos_nemico[i].x && (pos_proiettile_su.y == pos_nemico[i].y || pos_proiettile_su.y == pos_nemico[i].y+1 || pos_proiettile_su.y == pos_nemico[i].y-1))
            {
                usleep(750);
                Nem_life[i]--;
                if(Nem_life[i] < DEATH)
                {
                    Nem_life[i] = DEATH;
                }
                pthread_cancel(threadProiettili[PROIETTILE_ISU]);
                Cancella3x4(pos_proiettile_su , sy , i);
                pos_proiettile_su.y = -1;
                pos_proiettile_su.x = -1;
            }
        }
        if(pos_proiettile_su.x == -1 && pos_proiettile_giu.x == -1)
        {
            j_pro = false;
        }
        border(ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , '*' , '*' , '*' , '*');
        refresh();
    } while(game_over == false && victory == false);
    beep();
    flash();
    clear();
    refresh();
    if(game_over == true)
    {
        GameOver(MAXX , MAXY);
        for(i = 0 ; i < NEMICI ; i++)
        {
            Nem_life[i] = DEATH; 
        }
        EliminaNemici(nNav , pos_nemico, Nem_life , MAXX , MAXY);
        pthread_cancel(threadNavEColl[NAV]);
    }
    else
    {
        YouWin(MAXX, MAXY);
        pthread_cancel(threadNavEColl[NAV]);
    }
    clear();
    refresh();
}


/**
 * @brief Funzione che si occupa dell'eliminazione dei thread dei nemici e della loro cancellazione dallo schermo
 * 
 * @param nNav Variabile utilizzata come contatore
 * @param coll_nem puntatore che contiene l'array dei nemici eventualmente da eliminare
 * @param Nem_life puntatore che contiene l'array della vita dei nemici per sapere quali nemici eliminare
 * @param MAXX dimensione massima dello schermo in base ai valori di x
 * @param MAXY dimensione massima dello schermo in base ai valori di y
 */
void EliminaNemici(int nNav , pos *coll_nem , int *Nem_life , int MAXX , int MAXY)
{
    for(nNav = 0 ; nNav < NEMICI ; nNav++)
    {
        usleep(1000);
        if(Nem_life[nNav] == DEATH)
        {
        pthread_cancel(threadNemici[nNav]);
        Cancella3x4(coll_nem[nNav] , MAXY , nNav);
        coll_nem[nNav].y = MAXY;
        coll_nem[nNav].x = MAXX;
        }
    }
}

/**
 * @brief Semplice funzione che cancella in uno spazio di 3x4.
 * 
 * @param Nav variabile di tipo pos che contiene le coordinate dove effettuare la cancellazione
 * @param sy variabile utilizzata per indicare una traslazione sull'asse y in cui effettuare la cancellazione
 * @param i variabile contatore per il ciclo for
 */
void Cancella3x4(pos Nav , int sy , int i)
{
    sy = -1;
    for(i = 0; i < 5; i++)
        {
            mvprintw(Nav.y+sy-1, Nav.x-1, "    ");
            mvprintw(Nav.y+2, Nav.x-1, "   ");
            mvprintw(Nav.y-2, Nav.x-1, "   ");
            sy+=1;
        }
}

/**
 * @brief Funzione atta alla stampa degli oggetti Navicella e Navicella nemica in base al loro status
 * 
 * @param Nav variabile di tipo pos che contiene le coordinate dove effettuare la stampa
 * @param sy variabile utilizzata per indicare una traslazione sull'asse y in cui effettuare la stampa
 * @param i contatore per il ciclo for
 */
void StampaNavicelle(pos Nav , int sy , int i)
{
    char Sprite[3][4];
    int maxy = getmaxy(stdscr);
    switch(Nav.status)
    {
        case(Nav_Alleata):
        {
            strcpy(Sprite[0], "XX ");
            strcpy(Sprite[1], "XXX");
            strcpy(Sprite[2], "XX ");

            for(i = 2 ; i < maxy; i++)
            {
                mvprintw(i, Nav.x, "   ");
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
