//
//  main.c
//  maze 1.0.1
//
//  Created by alessandro on 27/11/2018.
//  Copyright © 2018 alessandro. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
#include <string.h>
#define CURSEIN 0
#define LUNGMAXALTEZZA 15
#define LUNGMAXLARGHEZZA 50
int main(int argc, const char * argv[])
{
    
    /*variabili curses + inizio*/
    if(CURSEIN==1) {initscr();}
    int x,
    y,
    startx = 0,
    starty = 0;
    if(CURSEIN==1)
    {
        noecho();
        cbreak();
        printw("labirinto prova 1.0");
        getmaxyx(stdscr, y, x);
        startx=x/3;
        starty=y/4;
        mvprintw(y/4-y/20, x/2-x/6, "inserire un movimento");
    }
    WINDOW * scatola = newwin(11, 24, starty, startx);
    if(CURSEIN==1)
    {
        box(scatola,0,0);
        refresh();
        wrefresh(scatola);
    }
    /*variabili file*/
    char    righe[LUNGMAXALTEZZA][LUNGMAXLARGHEZZA],
    labirinto[LUNGMAXALTEZZA-1][LUNGMAXLARGHEZZA],
    movimento[2];
    
    int i,
        j,
        xinizio = 0,
        xbackup,
        yinizio = 0,
        ybackup,
        xfine = 0,
        yfine = 0,
        fine = 0,
        flag = 0,
        xnontrovata = 0,
        ynontrovata = 0,
        lungstring = 0,
        cont = 0,
        cont2 = 0,
        altezza = 0;
    FILE *labirintofile;
    labirintofile = fopen("labirinto", "r");
    if(labirintofile == NULL)
    {
        if(CURSEIN==0)
            printf("file labirinto non trovato");
        else
        {
            printw("file labirinto non trovato");
        }
        exit(0);
    }
    for(i=0;i<LUNGMAXALTEZZA;i++)
    {
        fgets(righe[i], LUNGMAXLARGHEZZA, labirintofile);
        
            if(i==0)
            {
                labirinto[i][0]=righe[i][0+1];
                for(j=0;j<50;j++)
                {
                    labirinto[i][j]=righe[i][j+1];
                    if(labirinto[i][j]=='X')
                    {
                        yinizio=i;
                        xinizio=j;
                        xnontrovata++;
                    }
                    if(labirinto[i][j]=='O')
                    {
                        yfine=i;
                        xfine=j;
                        ynontrovata++;
                    }
                }
            }else
                if(i==1)
                {
                    labirinto[i][1]=righe[i][1+1];
                    lungstring=strlen(righe[0])-2;
                    printf("%d\n",lungstring);
                }
        cont = 0;
        for(j=0;j<lungstring;j++)
        {
            labirinto[i][j]=righe[i][j+1];
            if(i>2)
            {
                if(labirinto[i][j]=='#')
                    cont++;
            }
            if(labirinto[i][j]=='X')
            {
                yinizio=i;
                xinizio=j;
                xnontrovata++;
            }
            if(labirinto[i][j]=='O')
            {
                yfine=i;
                xfine=j;
                ynontrovata++;
            }
        }
        if(cont==lungstring)
        {
            cont2++;
        }
        if(cont2==2)
        {
            altezza=i+1;
            i=LUNGMAXALTEZZA;
        }
        
        
        
        
    }
    if(xnontrovata>1)
    {
        if(CURSEIN==0)
            printf("non ci possono essere 2 spawn");
        else
        {
            printw("non ci possono essere 2 spawn");
            endwin();
        }
        
        exit(0);
    }
    if(xnontrovata==0)
    {
        if(CURSEIN==0)
            printf("\nspawn non trovato!");
        else
        {
            printw("spawn non trovato");
            endwin();
        }
        exit(0);
    }
    if(ynontrovata==0)
    {
        if(CURSEIN==0)
            printf("\nFine non è stata trovata!");
        else
        {
            printw("la fine non è stata trovata");
            endwin();
        }
        return 0;
    }
    do
    {
        flag = 0;
        /*labirinto stampta*/
        for(i=0;i<altezza;i++)
        {
            for(j=0;j<lungstring;j++)
            {
                if(CURSEIN==0)
                    printf("%c",labirinto[i][j]);
                else
                {
                    mvwprintw(scatola, i, j, "%c",labirinto[i][j]);
                }
            }
            printf("\n");

        }
        if(CURSEIN==1)
        {
            refresh();
            wrefresh(scatola);
        }
        if(CURSEIN==0)
        {
            printf("inserire un movimento (wasd) ");
            scanf("%s",movimento);
            printf("\n");
            getchar();
        }else
        {
            movimento[0]=getch();
        }
        
        
        xbackup=xinizio;
        ybackup=yinizio;
        labirinto[yinizio][xinizio] = ' ';
        switch (tolower(movimento[0]))
        {
            case 'w':
                yinizio--;
                break;
            case 'a':
                xinizio--;
                break;
            case 's':
                yinizio++;
                break;
            case 'd':
                xinizio++;
                break;
            case 'q':
                fine=1;
                break;
                
            default:
                if(CURSEIN==0)
                    printf("scelta non disponibile\n");
                else
                {
                    
                }
                flag=1;
                break;
        }
        movimento[0]=' ';
        if(labirinto[yinizio][xinizio] == '#')
        {
            flag = 1;
        }
        if(flag==1)
        {
            xinizio=xbackup;
            yinizio=ybackup;
        }
        labirinto[yinizio][xinizio] = 'X';
        if(xinizio==xfine && yinizio == yfine)
        {
            fine=1;
            if(CURSEIN==0)
                printf("gioco finito\n");
            else
            {
                
            }
            labirinto[yinizio][xinizio] = 'V';
        }
    } while (fine!=1);
    mvprintw(1, 0, "vittoria");
    for(i=0;i<altezza;i++)
    {
        for(j=0;j<lungstring;j++)
        {
            if(CURSEIN==0)
                printf("%c",labirinto[i][j]);
            else
            {
                mvwprintw(scatola, i, j, "%c",labirinto[i][j]);
            }
        }
        if(CURSEIN==0)
            printf("\n");
    }
    getch();
    if(CURSEIN==1) {endwin();}
    exit(0);
}
