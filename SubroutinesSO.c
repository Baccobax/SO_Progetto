#include "SubroutinesSO.h"

void Start()
{
    int i = 0;
    int g = 0;
    int ch , MAXX , MAXY;
    bool flag1;

    char menu[2][18] = {"Inizia partita", "Esci dal gioco"};
    char benvenuto[11][80] = {
    " ____                                  _   _                                 ",
    "| __ )  ___ _ ____   _____ _ __  _   _| |_(_)  ___ _   _                     ",
    "|  _ \\ / _ \\ '_ \\ \\ / / _ \\ '_ \\| | | | __| | / __| | | |              ",
    "| |_) |  __/ | | \\ V /  __/ | | | |_| | |_| | \\__ \\ |_| |                 ",
    "|____/ \\___|_| |_|\\_/ \\___|_| |_|\\__,_|\\__|_| |___/\\__,_|              ",
    " ____                         ___                     _                      ",
    "/ ___| _ __   __ _  ___ ___  |_ _|_ ____   ____ _  __| | ___ _ __ ___        ",
    "\\___ \\| '_ \\ / _` |/ __/ _ \\  | || '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __|",
    " ___) | |_) | (_| | (_|  __/  | || | | \\ V / (_| | (_| |  __/ |  \\__ \\    ",
    "|____/| .__/ \\__,_|\\___\\___| |___|_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/",
    "      |_|                                                                    "};

    //char item[18];
    //char item2[80];

    WINDOW *w1; //finestra per il menu iniziale di gioco

    initscr();
    noecho();
    curs_set(false);

    /* INIZIO MENU */ 
    getmaxyx(stdscr, MAXY, MAXX);

    w1 = newwin( MAXY - 2 , MAXX - 2 , 1 , 1);
    box(w1, ' ' , ' ');


    //STAMPO LA SCRITTA BENVENUTO
    for(g = 0; g < 11 ; g++)
    {
        //sprintf(item2, "%-79s", benvenuto[i]);
        mvwprintw( w1, g+1, (MAXX/2) - 40, "%s", benvenuto[g]); //la scritta verra' centrata sullo schermo a partire da altezza y=1
    }        

    //STAMPA LA PRIMA VOLTA IL MENU
    for ( i = 0; i < 2; i++)
    {
        if ( i == 0)
            wattron( w1, A_STANDOUT); // il primo elemento è illuminato
        else
            wattroff( w1, A_STANDOUT); // l'altro è "spento"
            //sprintf(item, "%-17s", menu[i]);
            mvwprintw( w1, i+2+(MAXY/2), 2, "%s", menu[i]);
    }
    wrefresh( w1 );
    i = 0;
    keypad( w1, TRUE );
    curs_set( 0 );
    
    
    while ((ch = wgetch(w1)) != 'q' && flag1 != false) //premendo q skippo tutto e parte il gioco
    {
        //sprintf(item, "%-17s", menu[i]);
        mvwprintw( w1, i+2+(MAXY/2), 2, "%s", menu[i]);

        switch (ch)
        {
        case KEY_UP:
            i--;
            if (i < 0) //porta all'ultimo della coda
                i = 1;
            break;
        
        case KEY_DOWN:
            i++;
            if (i > 1) //porta all'inizio della coda
                i = 0;
            break;
            
        case 10: // premendo il tasto invio...
            switch (i)
            {
            case 0: // se 0 esce dal ciclo e parte il gioco
                flag1 = false;   
                break;
            
            case 1: // se 1 termina il programma
                endwin();
                exit(0);
                break;
            }
        }
        wattron( w1 , A_STANDOUT );
        //sprintf(item, "%-17s", menu[i]);
        mvwprintw( w1, i+2+(MAXY/2), 2, "%s", menu[i]);
        wattroff( w1, A_STANDOUT );       
    }
    delwin(w1);
    endwin(); 
    
    return;
}

/*
void Vittoria()
{



    exit(0);
}
*/