#include <stdio.h>
#include <stdlib.h>

typedef struct Pile
{
    int pile[100];
    int taille;
} pile;

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

int tableLL[8][7] = {
    {1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 3, 2, 0, 3},
    {4, 4, 4, 0, 0, 0, 0},
    {7, 7, 7, 0, 0, 0, 0},
    {5, 5, 5, 6, 6, 0, 6},
    {9, 9, 9, 9, 9, 8, 9},
    {0, 0, 0, 0, 0, 10, 0},
    {11, 12, 13, 0, 0, 0, 0}};

void initialiserPile(pile *stack)
{
    stack = malloc(sizeof(pile));
    if (stack != NULL)
    {
        for (int i = 0; i < 100; stack->pile[i++] = 0)
            ;
        stack->taille = -1;
    }
    else
    {
        puts("La pile ne s'est pas initialisee correctement, le programme va s'arreter");
        exit(2);
    }
}

void empiler(pile *stack, int value)
{
    if(stack->taille == 99)
    {
        puts("La pile est déjà pleine, veuillez redimensionner votre pile, le programme s'arretera");
        exit(3);
    }
    else
    {
        stack->taille++;
        stack->pile[stack->taille] = value;
    }
}

void depiler(pile* stack)
{
    if(stack->taille == 0)
    {
        stack->pile[0] = 0;
        puts("La pile est déjà vide, aucun depilement n'est possible");
    }
    else
    {
        stack->pile[stack->taille] = 0;
        stack->taille--;
    }
}

void main()
{
    FILE *tokensFile = NULL;

    tokensFile = fopen("tokens", "r");

    if (tokensFile != NULL)
    {
        pile *pileProd;
        pile *pileEntree;

        initialiserPile(pileProd);
        initialiserPile(pileEntree);
    }
    else
    {
        puts("Le fichier ne s'est pas ouvert correctement, le programme va s'arreter");
        exit(1);
    }
}
