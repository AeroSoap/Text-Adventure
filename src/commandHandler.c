#define CMD_AMT 4

Player* player;

char** cmdReg;
void (**cmds)(char*);

/* Returns 1 if the strings are equal, 0 if not */
int strEquals(char* str1, char* str2) {
	/* Check each character and make sure the strings haven't ended */
	while(*(str1++) == *(str2++) && *str1);
	/* Compare the last (non-'\0' if the strings are the same length) character to determine equality */
	return *(str1 - 1) == *(str2 - 1);
}

/* Returns the length of the string */
int lengthOf(char* str) {
	int i = 0;
	/* Iterate until we find '\0' */
	while(str[i++]);
	/* Go back one for the proper length */
	return i - 1;
}

void quit(char* args) {
	/* To get help on the command */
	if(strEquals(args, "GET_INFO")) {
		printf("Syntax: quit\n");
		printf("Ends the game after asking for confirmation.\n");
		return;
	}
	/* Error handling */
	if(lengthOf(args)) {
		printf("Command \"quit\" does not accept arguments.\n");
		return;
	}
	/* Confirm that we should quit */
	printf("To confirm that you want to quit, type \"confirm\". To continue playing, type anything else.\n");
	args = malloc(64);
	gets(args);
	if(strEquals(args, "confirm")) {
		free(args);
		player->hasEnded = 1;
		return;
	}
	free(args);
	printf("The game resumes.\n");
}

/* Moves the player to the given location if the location is valid and adjacent */
void look(char* args) {
	int i;
	/* To get help on the command */
	if(strEquals(args, "GET_INFO")) {
		printf("Syntax: look\n");
		printf("Gives information on the player's location and adjacent locations.\n");
		return;
	}
	/* Error handling */
	if(lengthOf(args) && !strEquals(args, "JUST_MOVED")) {
		printf("Command \"look\" does not accept arguments.\n");
		return;
	}
	/* Tell the player where they are now */
	if(!strEquals(args, "JUST_MOVED")) {
		printf("Current location: %s\n", player->location->name);
	}
	/* Use proper grammer... */
	/* Print case for one nearby location */
	if(player->location->nearCount == 1) {
		printf("Nearby location: %s.\n", player->location->near[0]->name);
	} else {
		/* Any more than one starts with this */
		printf("Nearby locations: ");
		/* Print case for two nearby locations */
		if(player->location->nearCount == 2) {
			printf("%s and %s.\n", player->location->near[0]->name, player->location->near[1]->name);
		} else {
			/* Print case for three or more nearby locations */
			for(i = 0 ; i < player->location->nearCount - 1; i++) {
				printf("%s, ", player->location->near[i]->name);
			}
			printf("and %s.\n", player->location->near[player->location->nearCount - 1]->name);
		}
	}
}

/* Moves the player to the location if it's allowed */
void move(char* args) {
	int i;
	/* To get help on the command */
	if(strEquals(args, "GET_INFO")) {
		printf("Syntax: move <location>\n");
		printf("Moves the player to the location name if the location is accessible from the player's current location.\n");
		return;
	}
	/* Error handling */
	if(!lengthOf(args)) {
		printf("Command \"move\" requires one argument.\n");
		return;
	}
	/* Find and move to the desired location */
	for(i = 0; i < player->location->nearCount; i++) {
		if(strEquals(args, player->location->near[i]->name)) {
			printf("You have moved from %s to %s.\n", player->location->name, player->location->near[i]->name);
			player->location = player->location->near[i];
			/* Generate what hasn't been generated */
			fillLocation(player->location);
			/* Show the new surroundings */
			look("JUST_MOVED");
			return;
		}
	}
	/* More error handling */
	printf("The location \"%s\" does not exist or is not nearby.\n", args);
}

	/* Prints a list of commands */
void help(char* args) {
	int i;
	/* Print info on a specific command */
	if(lengthOf(args)) {
		if(strEquals(args, "help")) {
			printf("Syntax: help [command]\n");
			printf("When no arguments are given, prints a list of commands.\nWhen the name of a command is given, prints info on that command.\n");
			return;
		}
		for(i = 0; i < CMD_AMT; i++) {
			if(strEquals(args, cmdReg[i])) {
				(cmds[i])("GET_INFO");
				return;
			}
		}
		printf("Command \"%s\" does not exist.\n", args);
		return;
	}
	/* Print the name of each command */
	printf("Commands: ");
	for(i = 0; i < CMD_AMT - 1; i++) {
		printf("%s, ", cmdReg[i]);
	}
	printf("and %s.\n", cmdReg[CMD_AMT - 1]);
}

/* Adds the command to the registry */
void addCommand(void (*func)(char*), char* cmd, int i) {
	int j;
	int len = lengthOf(cmd);
	cmds[i] = func;
	cmdReg[i] = malloc(len + 1);
	for(j = 0; j < len; j++) {
		cmdReg[i][j] = cmd[j];
	}
	cmdReg[i][len] = '\0';
	cmdReg[i][len + 1] = i;
}

/* Allows the command handler to handle commands involving the player (most of them lol).
Also runs setup for command association */
void setPlayer(Player* p) {
	int i = 0;
	player = p;
	/* Allocate space for the pointers to command strings */
	cmdReg = malloc(CMD_AMT * sizeof(char*));
	/* Allocate space for the commands */
	cmds = malloc(CMD_AMT * sizeof(void*));
	/* Add all the commands */
	addCommand(move, "move", i++);
	addCommand(look, "look", i++);
	addCommand(quit, "quit", i++);
	addCommand(help, "help", i++);
}

/* Returns the index of the first occurence of the given character, starting at the min value.
Returns -1 if character not found */
int indexOf(char c, char* str, int min) {
	/* Find the first occurence of c or the end of the string */
	while(str[min] != c && str[min] && ++min);
	/* Return -1 if str[min] is '\0', else return the correct index */
	return min * !!str[min] - 1 * !str[min];
}

/* Returns a new string with the content of the given string from start to end */
char* splice(char* str, int start, int end) {
	int i;
	/* Make a new string of the right length */
	char* out = malloc(end - start + 1);
	for(i = 0; i + start < end; i++) {
		out[i] = str[i + start];
	}
	out[end - start] = 0;
	return out;
}

void handleCommand(char* input) {
	int i;
	int found;
	/* Break the input into the command and arguments */
	int div = indexOf(' ', input, 0);
	char* cmd;
	char* args;
	if(div > 0) {
		cmd = splice(input, 0, div);
		args = splice(input, div + 1, lengthOf(input));
	} else {
		cmd = input;
		args = "";
	}
	found = 0;
	for(i = 0; i < CMD_AMT; i++) {
		if(strEquals(cmd, cmdReg[i])) {
			int index = cmdReg[i][lengthOf(cmdReg[i]) + 1];
			found = 1;
			(cmds[index])(args);
			break;
		}
	}
	if(!found) {
		printf("Command \"%s\" does not exist.\n", cmd);
	}
}
