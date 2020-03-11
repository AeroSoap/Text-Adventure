#include <stdio.h>
#include "player.c"

Player* player;
Location* startLoc;

int main() {
	int i;
	Location** near;
	startLoc = initLocation("Base", 5);
	player = initPlayer(startLoc);
	near = &(startLoc->near);
	*near = initLocation("Zero", 1);
	*(near + 1) = initLocation("One", 1);
	printf("Start near: %i\n", startLoc->nearCount);
	printf("Health: %i\n", player->combatant->health);
	printf("Location: %s\n", player->location->name);
	printf("Valid: %i\n", player->location->isValid);
	printf("Nearby locations(%i max)\n", player->location->nearCount);
	for(i = 0; i < player->location->nearCount; i++) {
		if(player->location->near[i].isValid) {
			printf("\t%s\n", player->location->near[i].name);
		} else {
			printf("%i\n", i);
		}
	}
	printf("Done!");
	free(player);
	free(startLoc);
	return 0;
}
