#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pile.c"


int tableLL[8][7] = {
    {1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 3, 2, 0, 3},
    {4, 4, 4, 0, 0, 0, 0},
    {7, 7, 7, 0, 0, 0, 0},
    {5, 5, 5, 6, 6, 0, 6},
    {9, 9, 9, 9, 9, 8, 9},
    {0, 0, 0, 0, 0, 10, 0},
    {11, 12, 13, 0, 0, 0, 0}};


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
        puts(" F --> (R) (ou F --> C, ask ihssane) ");
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
        puts(" R' --> +R ");
        empiler(stack,1);
        empiler(stack,3);
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
        puts(" F --> (R) (ou F --> C, ask ihssane) ");
        break;
    }
}

void analyseSyntaxiqueMot(pile* pProd, pile* pEntree)
{
    /// pile prod
    /// a pile entree
    while(1)
    {
        if(pProd->pile[pProd->taille] >= 1 && pProd->pile[pProd->taille] <= 8)
        {
            if(tableLL[pProd->pile[pProd->taille],pProd->pile[pEntree->taille]] != 0)
            {
                depiler(pProd);

            }
        }
        else{

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

    }
    else
    {
        puts("Le fichier ne s'est pas ouvert correctement, le programme va s'arreter");
        exit(1);
    }

    return 0;
}
