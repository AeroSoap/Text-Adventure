#include <stdio.h>
#include "player.c"

Player* player;
Location* startLoc;

int main() {
	startLoc = initLocation("Home", 3);
	startLoc->near[0] = initLocation("Store", 1);
	startLoc->near[1] = initLocation("School", 2);
	startLoc->near[2] = initLocation("Hell", 2);
	startLoc->near[0]->near[0] = startLoc;
	startLoc->near[1]->near[0] = startLoc;
	startLoc->near[1]->near[1] = startLoc->near[2];
	startLoc->near[2]->near[0] = startLoc;
	startLoc->near[2]->near[1] = startLoc->near[1];
	player = initPlayer(startLoc);
	printf("Start near: %i\n", startLoc->nearCount);
	printf("Health: %i\n", player->combatant->health);
	printf("Location: %s\n", player->location->name);
	printf("Valid: %i\n", player->location->isValid);
	printNear(player->location);
	printNear(player->location->near[0]);
	printNear(player->location->near[1]);
	printNear(player->location->near[2]);
	printf("Done!\n");
	freePlayer(player);
	printf("Freedom attained\n");
	return 0;
}
