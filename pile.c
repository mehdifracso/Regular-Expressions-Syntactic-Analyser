#include "pile.h"

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


int sommetPile(pile* stack)
{
    return stack->pile[stack->taille];
}


void inverserPile(pile*stack)
{
    pile* tmpStack = NULL;
    initialiserPile(tmpStack);

    while(stack->taille != -1)
    {
        empiler(tmpStack,sommetPile(stack));
        depiler(stack);
    }

    while(tmpStack->taille != -1)
    {
        empiler(stack,sommetPile(tmpStack));
        depiler(tmpStack);
    }
}

