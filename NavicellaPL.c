#include "SubroutinesSO.h"

void NavicellaGiocatore(int pipeout)
{
    int MAXY , MAXX;
    getmaxyx(stdscr, MAXY, MAXX);
    keypad(stdscr , true);
    pos pos_Navicella;
    pos_Navicella.c = '>';
    pos_Navicella.x = 1;
    pos_Navicella.y = MAXY/2;
    write(pipeout , &pos_Navicella , sizeof(pos_Navicella));
    while(true)
    {
        while(true)
        {
            int c = getch();
            switch(c)
            {
                case KEY_UP:
                    if(pos_Navicella.y > 2)
                    {
                        pos_Navicella.y -= 1;
                    }
                    break;
                case KEY_DOWN:
                    if(pos_Navicella.y < MAXY-2)
                    {
                        pos_Navicella.y += 1;
                        break;
                    }
                default:
                {
                    break;                
                }
            }
            write(pipeout , &pos_Navicella , sizeof(pos_Navicella));
        }
        Proiettili(getch() , pos_Navicella , pipeout);
    }

}


int Proiettili(char a , pos pos_Navicella , int pipeout)
{
    pos pos_proiettile , pos_proiettileGIU , pos_proiettileSU;
    int i , maxX , maxY , dyG , dyS;
    getmaxyx(stdscr , maxY ,maxX);
    
    switch(a)
    {
        case 'x':
        {
            pos_proiettile.x = pos_Navicella.x + 1;
            pos_proiettile.y = pos_Navicella.y;
            pos_proiettile.c = '+';
            write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
            for(i = 0 ; i < maxX , i++;)
            {
                pos_proiettile.x++; 
            }
            break;
        }
        case 'X':
        {
            pos_proiettile.x = pos_Navicella.x + 1;
            pos_proiettile.y = pos_Navicella.y;
            pos_proiettile.c = '+';
            write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
            for(i = 0 ; i < maxX , i++;)
            {
                pos_proiettile.x++; 
            }
            break;
        }
        case ' ':
        {
            pos_proiettileGIU.x = pos_Navicella.x + 1;
            pos_proiettileSU.x = pos_Navicella.x + 1;
            pos_proiettileGIU.y = pos_Navicella.y + 1;
            pos_proiettileSU.y = pos_Navicella.y - 1;
            pos_proiettileGIU.c = '\\';
            pos_proiettileSU.c = '/';
            write(pipeout , &pos_proiettileGIU , sizeof(pos_proiettileGIU));
            write(pipeout , &pos_proiettileSU , sizeof(pos_proiettileSU));

            
            while(pos_proiettileGIU.x != maxX && pos_proiettileSU.x != maxX)
            {
                /*Proiettile che parte andando verso*/
                if(pos_proiettileGIU.y + dyG < 0) //se va oltre, rimetti a posto
                {
                    pos_proiettileGIU.y = 0;
                }
                if(pos_proiettileGIU.y + dyG > maxY) //se va oltre rimetti a posto
                {
                    pos_proiettileGIU.y = maxY;
                }
                if(pos_proiettileGIU.y == 0) 
                {
                    dyG = MOVIMENTO;
                    pos_proiettileGIU.c = '\\';
                }
                if(pos_proiettileGIU.y == maxY)
                {
                    dyG = -MOVIMENTO;
                    pos_proiettileGIU.c = '/';
                }
                if(pos_proiettileGIU.y + dyG >= 0 || pos_proiettileGIU.y + dyG <= maxY)
                {
                    pos_proiettileGIU.y += dyG;
                    pos_proiettileGIU.x++;
                    if(pos_proiettileGIU.x >= maxX)
                    {
                        pos_proiettileGIU.x == maxX;
                    }
                }
                write(pipeout , &pos_proiettileGIU , sizeof(pos_proiettileGIU));
                /*Proiettile che parte andando verso l'alto*/
                if(pos_proiettileSU.y + dyS < 0) //se va oltre, rimetti a posto
                {
                    pos_proiettileSU.y = 0;
                }
                if(pos_proiettileSU.y + dyS > maxY) //se va oltre rimetti a posto
                {
                    pos_proiettileSU.y = maxY;
                }
                if(pos_proiettileSU.y == 0) 
                {
                    dyS = MOVIMENTO;
                    pos_proiettileSU.c = '\\';
                }
                if(pos_proiettileSU.y == maxY)
                {
                    dyS = -MOVIMENTO;
                    pos_proiettileSU.c = '/';
                }
                if(pos_proiettileSU.y + dyS >= 0 || pos_proiettileSU.y + dyS <= maxY)
                {
                    pos_proiettileSU.y += dyS;
                    pos_proiettileSU.x++;
                    if(pos_proiettileSU.x >= maxX)
                    {
                        pos_proiettileSU.x == maxX;
                    }
                }
                write(pipeout , &pos_proiettileSU , sizeof(pos_proiettileSU));
            }     
        }
    }
}

/*momentaneamente ficchiamo la funzione qua per testing*/

void collision(int pipein)
{
    pos Nav, proiettile, proiettileGIU , proiettileSU , valore_letto;
    Nav.x = -1;
    proiettile.x =- 1;

    do
    {
        read(pipein, &valore_letto, sizeof(valore_letto));
        if(valore_letto.c == '>')
        {
            if(Nav.x >= 0)
            {
                mvaddch(Nav.y, Nav.x , ' ');
            }
            Nav = valore_letto;
        }
        else
        {
            if(proiettile.x >= 0)
            {
                mvaddch(proiettile.y , proiettile.x , ' ');
            }
            proiettile = valore_letto;
        }
        mvaddch(valore_letto.y , valore_letto.x , valore_letto.c);
        curs_set(false);
        refresh();
    } while(true);
}