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
    int i , maxX;
    getmaxx(stdscr , maxX)
    switch(a)
        case 'x':
        {
            pos_proiettile.x = pos_Navicella.x + 1;
            pos_proiettile.y = pos_Navicella.y;
            pos_proiettile.c = '+';
            write(pipeout , &pos_proiettile , sizeof(pos_proiettile));
            for(i = 0 ; i < maxX , i++)
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
            for(i = 0 ; i < maxX , i++)
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
            pos_proiettileSU.y = pos_Navicella.y + 1
            
            ///////////////
            /*Sistema di rimbalzo preso da vespa e contadino, da adattare ai proiettili*/
                if(pos_hornet.y + dy < 2)
                {
                    pos_hornet.y = 2;
                }
                if(pos_hornet.y + dy >= MAXY)
                {
                    pos_hornet.y = MAXY-3;
                }
                if(pos_hornet.y == 2)
                {
                    dy = PASSO; 
                }
                if(pos_hornet.y == (MAXY-3))
                {
                    dy = -PASSO;
                }
                if(pos_hornet.y + dy >= 2 || pos_hornet.y + dy <= MAXY-3)
                {
                    pos_hornet.y += dy;
        }
            ///////////////
            /*proiettili come rimbalzono cambiano carattere es. / *tocca bordo* \ */
        }
}