#include <stdio.h>
#include <stdlib.h>
#include "player.c"
#include "commandHandler.c"

Player* player;
Location* startLoc;

int main() {
	char input[64];
	printf("You find yourself at the entrance of an immense, non-euclidian castle fractured in time and space.\n");
	printf("You hear lightning strike somewhere behind the castle, but not even the faintest glow is visible.\n");
	printf("For reasons baffling to philosophers and psychologists alike, you push open the doors and walk inside.\n");
	grabLocationData();
	startLoc = initLocation("Entrance", 2);
	fillLocation(startLoc);
	player = initPlayer(startLoc);
	setPlayer(player);
	do {
		gets(input);
		handleCommand(input);
	} while (!player->hasEnded);
	/* It is not necessary to free locations from other structs containing pointers to them because they are all freed here */
	freeLocation(startLoc);
	freePlayer(player);
	free(names);
	printf("Thanks for playing!\n");
	return 0;
}
