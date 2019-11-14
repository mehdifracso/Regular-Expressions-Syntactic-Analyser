typedef struct Pile
{
    int pile[100];
    int taille;
} pile;

pile *initialiserPile();
void afficherPile(pile *stack);
void empiler(pile *stack, int value);
void depiler(pile *stack);
int sommetPile(pile *stack);
pile *inverserPile(pile *stack);
void afficherPileDansMemeLigneSommetVersBase(pile *stack);
void afficherPileDansMemeLigneBaseVersSommet(pile *stack);
void viderPile(pile* stack);
