#include <stdlib.h>

typedef struct Combatant {
	int health;
	int armor;
} Combatant;

void freeCombatant(Combatant* c) {
	free(c);
}

Combatant* initCombatant(int health, int armor) {
	/* Give us space for a combatant */
	Combatant* c = malloc(sizeof(Combatant));

	c->health = health;
	c->armor = armor;
	return c;
}
