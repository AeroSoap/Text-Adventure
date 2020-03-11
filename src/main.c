#include <stdio.h>
#include "player.c"

Player* p;

int main() {
	p = initPlayer();
	printf("Health: %i\n", p->combatant->health);
	return 0;
}
