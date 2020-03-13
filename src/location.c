#include <stdlib.h>

int locationCount = 0;

typedef struct Location {
	char isValid;
	char* name;
	struct Location** near;
	int nearCount;
} Location;

/* Prints out the location given and the locations near that location */
void printNear(Location* l) {
	int i;
	printf("Nearby locations to %s:\n", l->name);
	for(i = 0; i < l->nearCount; i++) {
		if(l->near[i]->isValid) {
			printf("\t%s\n", l->near[i]->name);
		}
	}
}

/* Helper function that grabs all the locations reachable from the given location */
void getLocations(Location* l, Location** locs, int* amt) {
	int i;
	/* Mark the location as invalid so it's not visited again */
	l->isValid = 0;
	/* Go through all near locations and recursively repeat the search */
	for(i = 0; i < l->nearCount; i++) {
		if(l->near[i]->isValid) {
			getLocations(l->near[i], locs, amt);
		}
	}
	/* Add the location to the array of locations to be deleted */
	locs[*amt] = l;
	(*amt)++;
}

/* Unlike other free functions, this will free all locations reachable by the given location as well */
void freeLocation(Location* l) {
	/* Make sure the array can hold the maximum amount of locations if needed */
	Location** locs = malloc(locationCount * sizeof(Location*));

	int amt = 0;
	int i;
	/* Grab and delete all necessary locations */
	getLocations(l, locs, &amt);
	for(i = 0; i < amt; i++) {
		free(locs[i]->near);
		free(locs[i]);
	}
	/* Update the counter of the amount of existing locations */
	locationCount -= amt;
}

Location* initLocation(char* name, int nearCount) {
	/* Give us space for the new location */
	Location* l = malloc(sizeof(Location));

	l->name = name;
	/* Allocate space for the nearby locations */
	l->near = malloc(nearCount * sizeof(Location*));
	l->nearCount = nearCount;

	l->isValid = 1;
	locationCount++;
	return l;
}
