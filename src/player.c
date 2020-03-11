#include <stdlib.h>
#include "combatant.c"
#include "location.c"

typedef struct Player {
	Combatant* combatant;
	Location* location;
} Player;

Player* initPlayer(Location* location) {
	Player* p = malloc(sizeof(Player));
	p->combatant = initCombatant(100, 1);
	p->location = location;
	return p;
}
