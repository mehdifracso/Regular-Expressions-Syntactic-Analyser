#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pile.c"


int tableLL[8][7] =
{
    {1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 3, 2, 0, 3},
    {4, 4, 4, 0, 0, 0, 0},
    {7, 7, 7, 0, 0, 0, 0},
    {5, 5, 5, 6, 6, 0, 6},
    {9, 9, 9, 9, 9, 8, 9},
    {0, 0, 0, 0, 0, 10, 0},
    {11, 12, 13, 0, 0, 0, 0}
};



int retournerIndiceTerminal(char c)
{
    switch(c)
    {
    case 'a':
        return 0;
    case 'b':
        return 1;
    case '(':
        return 2;
    case ')':
        return 3;
    case '+':
        return 4;
    case '*':
        return 5;
    case '$':
        return 6;
    }
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
        puts(" A ");
        break;
    case 4:
        puts(" C ");
        break;
    case 5:
        puts(" B ");
        break;
    case 6:
        puts(" C' ");
        break;
    case 7:
        puts(" C\" ");
        break;
    case 8:
        puts(" F");
        break;
    }
}

void afficherProduction(int i)
{
    switch (i)
    {
    case 1:
        puts(" R --> AR' ");
        break;
    case 2:
        puts(" R' --> +R ");
        break;
    case 3:
        puts(" R' --> ε ");
        break;
    case 4:
        puts(" A --> CB ");
        break;
    case 5:
        puts(" B --> A ");
        break;
    case 6:
        puts(" B --> ε ");
        break;
    case 7:
        puts(" C --> FC' ");
        break;
    case 8:
        puts(" C' --> C\" ");
        break;
    case 9:
        puts(" C' --> ε ");
        break;
    case 10:
        puts(" C\" --> *C' ");
        break;
    case 11:
        puts(" F --> a ");
        break;
    case 12:
        puts(" F --> b ");
        break;
    case 13:
        puts(" F --> ( ");
        break;
    }
}

void empilerProd(pile* stack, int idProd)
{
    switch (idProd)
    {
    case 1:
        //puts(" R --> AR' ");
        empiler(stack,2);
        empiler(stack,3);
        break;
    case 2:
        //puts(" R' --> +R ");
        empiler(stack,1);
        empiler(stack,'+');
        break;
    case 3:
        //puts(" R' --> ε ");
        depiler(stack);
        break;
    case 4:
        //puts(" A --> CB ");
        empiler(stack,5);
        empiler(stack,4);
        break;
    case 5:
        //puts(" B --> A ");
        empiler(stack,3);
        break;
    case 6:
        //puts(" B --> ε ");
        depiler(stack);
        break;
    case 7:
        //puts(" C --> FC' ");
        empiler(stack,6);
        empiler(stack,8);
        break;
    case 8:
        //puts(" C' --> C\" ");
        empiler(stack,7);
        break;
    case 9:
        //puts(" C' --> ε ");
        depiler(stack);
        break;
    case 10:
        //puts(" C\" --> *C' ");
        empiler(stack,6);
        empiler(stack,'*');
        break;
    case 11:
        //puts(" F --> a ");
        empiler(stack,'a');
        break;
    case 12:
        //puts(" F --> b ");
        empiler(stack,'b');
        break;
    case 13:
        //puts(" F --> ( ");
        empiler(stack,'(');
        break;
    }
}

void analyseSyntaxiqueMot(pile* pProd, pile* pEntree)
{
    /// pile prod
    /// a pile entree
    while(1)
    {
        int X = pProd->pile[pProd->taille];
        int a = pEntree->pile[pEntree->taille];
        int idProd = tableLL[X-1,retournerIndiceTerminal(a)];
        if(X >= 1 && X <= 8)
        {

            if(idProd != 0)
            {
                depiler(pProd);
                empilerProd(pProd,X);
                afficherProduction(idProd);
            }
            else
            {
                puts("Erreur ! ");
                system("PAUSE");
                exit(4);
            }
        }
        else
        {
            if(X == '$')
            {
                if(a == '$')
                {
                    puts("Ce mot appartient à la grammaire des Regex du langage {a,b}");
                    system("PAUSE");
                    exit(0);
                }
                else
                {
                    puts("Erreur ! ");
                    system("PAUSE");
                    exit(5);
                }
            }
            else
            {
                if(X == a)
                {
                    depiler(pProd);
                    depiler(pEntree);
                }
                else
                {
                    puts("Erreur ! ");
                    system("PAUSE");
                    exit(6);
                }
            }
        }
    }
}

int main()
{
    FILE *tokensFile = NULL;

    tokensFile = fopen("tokens", "r");

    if (tokensFile != NULL)
    {
        pile *pileProd = NULL;
        pile *pileEntree = NULL;

        initialiserPile(pileProd);
        initialiserPile(pileEntree);

        char readCharacter;
        while(!feof(tokensFile))
        {
            readCharacter = fgetc(tokensFile);
            empiler(pileEntree,readCharacter);
        }

        //  Initialisation des deux piles
        empiler(pileEntree,'$');
        inverserPile(pileEntree);

        empiler(pileProd,'$');
        empiler(pileProd,1);

        //  Le traitement commence ici
        analyseSyntaxiqueMot(pileProd,pileEntree);

    }
    else
    {
        puts("Le fichier ne s'est pas ouvert correctement, le programme va s'arreter");
        exit(1);
    }

    return 0;
}
