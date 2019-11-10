typedef struct Pile
{
    int pile[100];
    int taille;
} pile;


pile* initialiserPile();
void empiler(pile *stack, int value);
void depiler(pile* stack);
int sommetPile(pile* stack);
void inverserPile(pile*stack);
