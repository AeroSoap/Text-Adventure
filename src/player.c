#include "combatant.c"
#include "location.c"
#include "inventory.c"

typedef struct Player {
	Combatant* combatant;
	Location* location;
	Inventory* inventory;
	int hasEnded;
} Player;

void freePlayer(Player* p) {
	/* Free the components of the player, then the player itself */
	freeCombatant(p->combatant);
	freeInventory(p->inventory);
	free(p);
}

Player* initPlayer(Location* location) {
	/* Give us space for a player */
	Player* p = malloc(sizeof(Player));

	p->combatant = initCombatant(100, 1);
	p->location = location;
	p->inventory = initInventory();
	p->hasEnded = 0;
	return p;
}
