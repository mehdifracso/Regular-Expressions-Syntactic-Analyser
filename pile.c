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

void empiler(pile *stack, int value)
{
    if (stack->taille == 99)
    {
        puts("La pile est d�j� pleine, veuillez redimensionner votre pile, le programme s'arretera");
        exit(3);
    }
    else
    {
        stack->pile[stack->taille++] = value;
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
        stack->pile[stack->taille--] = 0;
    }
}

int sommetPile(pile *stack)
{
    return stack->pile[stack->taille];
}

void inverserPile(pile *stack)
{
    pile *tmpStack = NULL;
    tmpStack = initialiserPile();

    while (stack->taille != -1)
    {
        empiler(tmpStack, sommetPile(stack));
        depiler(stack);
    }

    while (tmpStack->taille != -1)
    {
        empiler(stack, sommetPile(tmpStack));
        depiler(tmpStack);
    }
}
