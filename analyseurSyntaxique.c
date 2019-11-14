#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pile.c"

int tableLL[8][7] =
    {
        {1, 1, 0, 0, 1, 0, 0}, //R
        {0, 0, 2, 0, 0, 8, 8}, //R'
        {3, 3, 0, 0, 3, 0, 0}, //S
        {4, 4, 9, 0, 4, 9, 9}, //S'
        {5, 5, 0, 0, 5, 0, 0}, //T
        {10, 10, 10, 6, 10, 10, 10}, //T'
        {11, 12, 0, 0, 7, 0, 0} //U
    };

int retournerIndiceTerminal(char c)
{
    switch (c)
    {
    case 'a':
        return 0;
    case 'b':
        return 1;
    case '+':
        return 2;
    case '*':
        return 3;
    case '(':
        return 4;
    case ')':
        return 5;
    case '$':
        return 6;
    }

    return -1;
}

void afficherTerminal(int i)
{
    switch (i)
    {
    case 1:
        puts(" R ");
        break;
    case 2:
        puts(" R' ");
        break;
    case 3:
        puts(" S ");
        break;
    case 4:
        puts(" S' ");
        break;
    case 5:
        puts(" T ");
        break;
    case 6:
        puts(" T' ");
        break;
    case 7:
        puts(" U ");
        break;
    }
}

void afficherProduction(int i)
{
    switch (i)
    {
    case 1:
        puts(" R --> SR' ");
        break;
    case 2:
        puts(" R' --> +SR' ");
        break;
    case 3:
        puts(" S --> TS' ");
        break;
    case 4:
        puts(" S' --> TS' ");
        break;
    case 5:
        puts(" T --> UT' ");
        break;
    case 6:
        puts(" T' --> *T' ");
        break;
    case 7:
        puts(" U --> (R) ");
        break;
    case 8:
        puts(" R' --> epsilon ");
        break;
    case 9:
        puts(" S' --> epsilon ");
        break;
    case 10:
        puts(" T' --> epsilon ");
        break;
    case 11:
        puts(" U --> a ");
        break;
    case 12:
        puts(" U --> b ");
        break;
    default:
        puts("Pas de production dans ce cas");
    }
}

void empilerProd(pile *stack, int idProd)
{
    switch (idProd)
    {
    case 1:
        // R --> SR'
        empiler(stack, 2);
        empiler(stack, 3);
        break;
    case 2:
        // R' --> +SR'
        empiler(stack, 2);
        empiler(stack, 3);
        empiler(stack, '+');
        break;
    case 3:
        // S --> TS'
        empiler(stack, 4);
        empiler(stack, 5);
        break;
    case 4:
        // S' --> TS
        empiler(stack, 4);
        empiler(stack, 5);
        break;
    case 5:
        // T --> UT'
        empiler(stack, 6);
        empiler(stack, 7);
        break;
    case 6:
        //  T' --> *T'
        empiler(stack, 6);
        empiler(stack, '*');
        break;
    case 7:
        // U --> (R)
        empiler(stack, ')');
        empiler(stack, 1);
        empiler(stack, '(');
        break;
    case 8:
        // R' --> epsilon
        break;
    case 9:
        // S' --> epsilon
        break;
    case 10:
        // T' --> epsilon
        break;
    case 11:
        // U --> a
        empiler(stack, 'a');
        break;
    case 12:
        //  U --> b;
        empiler(stack, 'b');
        break;
    }
}

void analyseSyntaxiqueMot(pile *pProd, pile *pEntree)
{

    printf("Pile\t\t\tEntree\t\t\tSortie\n");
    while (1)
    {
        int X = pProd->pile[pProd->taille];
        int a = pEntree->pile[pEntree->taille];
        int idProd = tableLL[X - 1][retournerIndiceTerminal(a)];

        afficherPileProduction(pProd);
        printf("\t\t\t");
        afficherPileEntree(pEntree);
        printf("\t\t\t");
        afficherProduction(idProd);



        if (X >= 1 && X <= 7)
        {
            if (idProd != 0)
            {
                depiler(pProd);
                empilerProd(pProd, idProd);
            }
            else
            {
                puts("Erreur 0 !\n");
                //system("PAUSE");
                //break;
                if( sommetPile(pEntree) == (int)'$') break;
                depiler(pEntree);
            }
        }
        else
        {
            if (X == '$')
            {
                if (a == '$')
                {
                    puts("Ce mot appartient a la grammaire des Regex du langage {a,b}");
                    system("PAUSE");
                    system("CLS");
                    break;
                }
                else
                {
                    puts("Erreur 1 ! ");
                    //system("PAUSE");
                    break;
                }
            }
            else
            {
                if (X == a)
                {
                    depiler(pProd);
                    depiler(pEntree);
                }
                else
                {
                    puts("Erreur 2 ! ");
                    system("PAUSE");
                    break;
                }
            }
        }
    }
}

int main()
{
    FILE *tokensFile = NULL;

    tokensFile = fopen("tokens", "r+");

    if (tokensFile != NULL)
    {
        pile *pileProd = NULL;
        pile *pileEntree = NULL;

        pileEntree = initialiserPile();
        pileProd = initialiserPile();

        int eofReached = 0;
        int readCharacter;

        while(!eofReached)
        {
            viderPile(pileEntree);
            viderPile(pileProd);
            while (!(eofReached = feof(tokensFile)))
            {
                readCharacter = fgetc(tokensFile);
                if(readCharacter == '\n') break;
                empiler(pileEntree, readCharacter);
            }

            //  Initialisation des deux piles
            // $ba
            empiler(pileEntree, '$');
            pileEntree = inverserPile(pileEntree);

            empiler(pileProd, '$');
            empiler(pileProd, 1);

            //  Le traitement commence ici
            analyseSyntaxiqueMot(pileProd, pileEntree);
        }


        fclose(tokensFile);
    }
    else
    {
        puts("Le fichier ne s'est pas ouvert correctement, le programme va s'arreter");
        exit(1);
    }

    return 0;
}
