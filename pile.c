#include "pile.h"

pile *initialiserPile()
{
    pile *stack = malloc(sizeof(pile));

    if (stack != NULL)
    {
        int i;
        for (i = 0; i < 100; stack->pile[i++] = 0)
            ;
        stack->taille = -1;
        return stack;
    }
    else
    {
        puts("La pile ne s'est pas initialisee correctement, le programme va s'arreter");
        exit(2);
    }
}

void afficherNTSansEspace(int i)
{
    switch (i)
    {
    case 1:
        printf("R");
        break;
    case 2:
        printf("R'");
        break;
    case 3:
        printf("S");
        break;
    case 4:
        printf("S'");
        break;
    case 5:
        printf("T");
        break;
    case 6:
        printf("T'");
        break;
    case 7:
        printf("U");
        break;
    default:
        printf("%c", i);
    }
}
void afficherPile(pile *stack)
{
    int i;
    printf("Affichage pile : \n taille pile : %d\n", stack->taille);
    for (i = stack->taille; i != -1; i--)
        printf("Contenu : %c Position dans la pile : %d\n", stack->pile[i], i);
    puts("Fin affichage");
}

void afficherPileProduction(pile *stack)
{
    int i;
    for (i = 0; i < stack->taille + 1; i++)
        afficherNTSansEspace(stack->pile[i]);

}

void afficherPileEntree(pile *stack)
{
    int i;
    for (i = stack->taille; i != -1; i--)
        printf("%c", stack->pile[i]);

}

void empiler(pile *stack, int value)
{
    if (stack->taille == 99)
    {
        puts("La pile est déjà pleine, veuillez redimensionner votre pile, le programme s'arretera");
        exit(3);
    }
    else
    {
        if (value != -1)
        {
            stack->pile[++stack->taille] = value;
            //  printf("Entrain d'empiler : nouvelle taille : %d\n", stack->taille);
        }
    }
}

void depiler(pile *stack)
{
    if (stack->taille == -1)
    {
        puts("La pile est déjà vide, aucun depilement n'est possible");
    }
    else
    {
        stack->pile[stack->taille] = 0;
        stack->taille -= 1;
    }
}

int sommetPile(pile *stack)
{
    return stack->pile[stack->taille];
}

pile *inverserPile(pile *stack)
{
    pile *newStack = NULL;
    newStack = initialiserPile();

    while (stack->taille != -1)
    {
        empiler(newStack, sommetPile(stack));
        depiler(stack);
    }

    //free(stack);
    return newStack;
}


void viderPile(pile* stack)
{
    if(stack->taille != -1)
    {
        int i;
        for(i=0; i<stack->taille; i++)
        {
            depiler(stack);
        }
        stack->taille = -1;
    }
}
