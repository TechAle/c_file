//
//  main.c
//  maze 1.0.2
//
//  Created by alessandro on 27/11/2018.
//  Copyright © 2018 alessandro. All rights reserved.
//
//  features:
//  -comment
//  -costum (program)frrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
ùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùù
//  -tidy

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
#include <string.h>
#define CURSEIN 0
#define LUNGMAXALTEZZA 15
#define LUNGMAXLARGHEZZA 50
#ifdef  WINDOWS
int os=0;
#else
int os = 1;
#endif
int main(int argc, const char * argv[])
{
    /*variabili file*/
    char    righe[LUNGMAXALTEZZA][LUNGMAXLARGHEZZA],
            labirinto[LUNGMAXALTEZZA-1][LUNGMAXLARGHEZZA],
            movimento[2];
    /*variabili generale*/
    int i,
        j,
        xinizio = 0,
        xbackup = 0,
        yinizio = 0,
        ybackup = 0,
        xfine = 0,
        yfine = 0,
        fine = 0,
        flag = 0,
        xnontrovata = 0,
        ynontrovata = 0,
        lungstring = 0,
        cont = 0,
        cont2 = 0,
        altezza = 0,
        xins = 0,
        oins = 0,
        mins,
        cins,
        xmod,
        ymod,
        xmodback,
        ymodback,
        cex,
        ceo;
    /*apertura file labirinto*/
    FILE *labirintofile;
    labirintofile = fopen("labirinto", "r");
    if(labirintofile == NULL)   /*se non lo trova*/
    {
        if(CURSEIN==0)
            printf("file labirinto non trovato");   /*stdio*/
        else
        {
            printw("file labirinto non trovato");   /*curses*/
        }
        exit(0);
    }
    for(i=0;i<LUNGMAXALTEZZA;i++)   /*trasportare il labirinto in un vettore*/
    {
        fgets(righe[i], LUNGMAXLARGHEZZA, labirintofile);
        
            if(i==0)    /*inizio*/
            {
                labirinto[i][j]=righe[i][j];
                for(j=0;j<50;j++)
                {
                    labirinto[i][j]=righe[i][j];
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
                if(i==1)    /*dopo 1 giro*/
                {
                    labirinto[i][1]=righe[i][j];
                    lungstring=strlen(righe[0])-2;
                }
        cont = 0;
        for(j=0;j<lungstring;j++)   /*inizio con la lunghezza*/
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
    
    /*verifica se ci stà tutto*/
    }
    /*variabili curses + inizio*/
    if(CURSEIN==1) {initscr();}
    int x,
    y,
    startx = 0,
    starty = 0;
    if(CURSEIN==1)  /*inizio di curses*/
    {
        noecho();
        cbreak();
        printw("labirinto prova 1.0");
        getmaxyx(stdscr, y, x);
        startx=x/3;
        starty=y/4;
        mvprintw(y/4-y/20, x/2-x/6, "inserire un movimento");
    }
    WINDOW * scatola = newwin(altezza, lungstring, starty, startx);
    if(CURSEIN==1)  /*creazione scatola*/
    {
        box(scatola,0,0);
        refresh();
        wrefresh(scatola);
    }
    /*modifiche*/
    char modifiche[1];
    printf("vuoi giocare(0) oppure modificare il labirinto(1) ");
    scanf("%s",modifiche);
    if(modifiche[0]=='1')
    {
        /*inizio a resettare*/
        xmodback=xmod=1;
        ymod=ymodback=1;
        mins=cins=ceo=cex=0;
        char mod_string[altezza][lungstring];
        /*trasmuto righe in mod_string*/
        for(i=0;i<altezza;i++)
        {
            for(j=0;j<lungstring;j++)
            {
                mod_string[i][j]=labirinto[i][j];
            }
        }
        printf("\nwasd per muoverti\nX per mettere lo spawn\nO per mettere una fine\nm per i muri (per disattivare, premere dinuovo m)\nc per cancellare (per disattivare, premere dinuovo c)\nq per finire\n");
        do
        {
            mod_string[ymod][xmod]='W';
            /*labirinto stampta*/
            for(i=0;i<altezza;i++)
            {
                for(j=0;j<lungstring;j++)
                {
                    if(CURSEIN==0)
                        printf("%c",mod_string[i][j]);   /*stdio*/
                    else
                    {
                        mvwprintw(scatola, i, j, "%c",mod_string[i][j]); /*curses*/
                    }
                }
                if(CURSEIN==0){printf("\n");}
                
            }
            if(CURSEIN==1)  /*refresh*/
            {
                refresh();
                wrefresh(scatola);
            }
            /*inizio modifiche*/
            scanf("%s",modifiche);              /*ricerca*/
            switch (tolower(modifiche[0]))
            {
                case 'w':
                    ymod--;
                    break;
                case 'a':
                    xmod--;
                    break;
                case 's':
                    ymod++;
                    break;
                case 'd':
                    xmod++;
                    break;
                case 'm':
                    mins++;
                    break;
                case 'x':
                    xins=1;
                    break;
                case 'o':
                    oins=1;
                    break;
                case 'c':
                    cins++;
                    break;
                
                case 'q':
                    printf("vuoi salvare(1) o no(0)\n");
                    scanf("%d",&flag);
                    if(flag==1)
                    {
                        
                    }
                    fine=1;
                    break;
                    
                default:
                    printf("carattere inserito non valido\n");
                    break;
            }                   /*controllo se è ai contorni*/
            if(ymod==0 || ymod==altezza-1 || xmod==0 || xmod==lungstring-1)
            {
                mod_string[ymod][xmod]=labirinto[ymod][xmod];
                ymod=ymodback;
                xmod=xmodback;
            }else               /*inserimenti*/
            {
                mod_string[ymodback][xmodback]=labirinto[ymodback][xmodback];
                if(xins==1) /* X */
                {
                    if(mod_string[ymod][xmod]=='O')
                    {
                        cex=1;
                    }
                    if(ceo==0) {printf("c'e gia una x\n");}
                    else
                    {
                    mod_string[ymod][xmod]=labirinto[ymod][xmod]='X';
                        ceo=0;
                        yinizio=ymod;
                        xinizio=xmod;
                    }
                }else
                    if(oins==1) /* O */
                    {
                        if(mod_string[ymod][xmod]=='O')
                        {
                            cex=1;
                        }
                        if(mod_string[ymod][xmod]=='X')
                        {
                            ceo=1;
                        }
                        if(cex==0) {printf("c'e gia una o\n");}
                        else
                        {
                            mod_string[ymod][xmod]=labirinto[ymod][xmod]='O';
                            cex=0;
                            yfine=ymod;
                            xfine=xmod;
                        }
                    }else
                if(mins==1)     /* # */
                {
                    if(mod_string[ymod][xmod]=='O')
                    {
                        cex=1;
                    }
                    if(mod_string[ymod][xmod]=='X')
                    {
                        ceo=1;
                    }
                   mod_string[ymod][xmod]=labirinto[ymod][xmod]='#';
                }else
                if(mins>1)  /* reset # */
                {
                    mins=0;
                }else
                if(cins==1) /*cancel*/
                {
                    if(mod_string[ymod][xmod]=='O')
                    {
                        cex=1;
                    }
                    if(mod_string[ymod][xmod]=='X')
                    {
                        ceo=1;
                    }
                    mod_string[ymod][xmod]=labirinto[ymod][xmod]=' ';
                }else
                    if(cins>1)  /*reset cancel*/
                    {
                        cins=0;
                    }
            }
            /*inizializzazione*/
            
            xins=0;
            oins=0;
            ymodback=ymod;
            xmodback=xmod;
        } while (fine!=1);
        fine=0;
        
    }
    if(os==1)
    {
        system("clear");
    }else
    {
        system("cls");
    }
    /*fine modifiche*/
    if(xnontrovata>1)   /*se trova più di 2 spawn*/
    {
        if(CURSEIN==0)
            printf("non ci possono essere 2 spawn");    /*stdio*/
        else
        {
            printw("non ci possono essere 2 spawn");    /*curses*/
            endwin();
        }
        
        exit(0);                                /*d'ora in poi non dirò più se è curses o stdio*/
    }
    if(xnontrovata==0)          /*se non trova lo spawn*/
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
    if(ynontrovata==0)      /*se non trova la fine*/
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
    
    do      /*inizio ciclo*/
    {
        
        flag = 0;
        /*labirinto stampta*/
        for(i=0;i<altezza;i++)
        {
            for(j=0;j<lungstring;j++)
            {
                if(CURSEIN==0)
                    printf("%c",labirinto[i][j]);   /*stdio*/
                else
                {
                    mvwprintw(scatola, i, j, "%c",labirinto[i][j]); /*curses*/
                }
            }
            if(CURSEIN==0){printf("\n");}

        }
        if(CURSEIN==1)  /*refresh*/
        {
            refresh();
            wrefresh(scatola);
        }
        if(CURSEIN==0)  /*prendere movimenti*/
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
        labirinto[yinizio][xinizio] = ' ';      /*elaborazione movimenti*/
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
                endwin();
                exit(0);
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
        if(xinizio==xfine && yinizio == yfine)  /*se raggiunge la fine*/
        {
            fine=1;
            if(CURSEIN==0)
                printf("gioco finito\n");
            
            else
            {
                
            }
            labirinto[yinizio][xinizio] = 'V';
        }
        if(os==1)
        {
            system("clear");
        }else
        {
            system("cls");
        }
    } while (fine!=1);  /*fine ciclo*/
    mvprintw(1, 0, "vittoria");
    for(i=0;i<altezza;i++)
    {
        for(j=0;j<lungstring;j++)   /*ultima stampa*/
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
        else
        {
            wrefresh(scatola);
        }
    }
            /*uscita*/
    if(CURSEIN==1) {getch();endwin();}
    exit(0);
}
