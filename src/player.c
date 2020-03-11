#include <stdlib.h>
#include "combatant.c"

typedef struct Player {
	Combatant* combatant;
} Player;

Player* initPlayer() {
	Player* p = malloc(sizeof(Player));
	p->combatant = initCombatant(100, 1);
	return p;
}
