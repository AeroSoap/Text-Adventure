#include <stdlib.h>
#include "combatant.c"
#include "location.c"

typedef struct Player {
	Combatant* combatant;
	Location* location;
} Player;

void freePlayer(Player* p) {
	/* Free the components of the player, then the player itself */
	freeCombatant(p->combatant);
	freeLocation(p->location);
	free(p);
}

Player* initPlayer(Location* location) {
	/* Give us space for a player */
	Player* p = malloc(sizeof(Player));
	
	p->combatant = initCombatant(100, 1);
	p->location = location;
	return p;
}
