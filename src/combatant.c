#include <stdlib.h>

typedef struct Combatant {
	int health;
	int armor;
} Combatant;

Combatant* initCombatant(int health, int armor) {
	Combatant* c = malloc(sizeof(Combatant));
	c->health = health;
	c->armor = armor;
	return c;
}
