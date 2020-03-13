#include <stdio.h>
#include <stdlib.h>
#include "player.c"
#include "commandHandler.c"

Player* player;
Location* startLoc;

int main() {
	char input[64];
	startLoc = initLocation("Den", 3);
	startLoc->near[0] = initLocation("Office", 1);
	startLoc->near[1] = initLocation("Kitchen", 2);
	startLoc->near[2] = initLocation("My Room", 2);
	startLoc->near[0]->near[0] = startLoc;
	startLoc->near[1]->near[0] = startLoc;
	startLoc->near[1]->near[1] = startLoc->near[2];
	startLoc->near[2]->near[0] = startLoc;
	startLoc->near[2]->near[1] = startLoc->near[1];
	player = initPlayer(startLoc);
	setPlayer(player);
	do {
		gets(input);
		handleCommand(input);
	} while (!player->hasEnded);
	printf("Done!\n");
	/* It is not necessary to free locations from other structs containing pointers to them because they are all freed here */
	freeLocation(startLoc);
	freePlayer(player);
	printf("Freedom attained\n");
	return 0;
}
