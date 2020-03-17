#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOC_NAME_COUNT 9

int locationCount = 0;
char** names;

typedef struct Location {
	char isValid;
	char* name;
	struct Location** near;
	int nearCount;
} Location;

Location* initLocation(char* name, int nearCount);
int lengthOf(char* str);
int strEquals(char* str1, char* str2);

/* Grabs the location type data from the file */
void grabLocationData() {
	int i;
	/* Open file */
	FILE* f = fopen("locations.txt", "r");
	/* Allocate needed space */
	names = malloc(sizeof(char*) * LOC_NAME_COUNT);
	/* Read in and store each name */
	for(i = 0; i < LOC_NAME_COUNT; i++) {
		char* s = malloc(16);
		fgets(s, 16, f);
		s[lengthOf(s) - 1] = '\0';
		names[i] = s;
	}
	/* Close file */
	fclose(f);
	/* Seed the RNG for later */
	srand(time(NULL));
}

/* Populates the location's unpopulated nearby locations */
void fillLocation(Location* l) {
	int i;
	int j;
	int badName;
	char* name;
	for(i = 0; i < l->nearCount; i++) {
		if(!l->near[i]->isValid) {
			free(l->near[i]);
			badName = 1;
			while(badName) {
				name = names[rand() % LOC_NAME_COUNT];
				badName = 0;
				for(j = 0; j < i; j++) {
					if(strEquals(name, l->near[j]->name)) {
						badName = 1;
					}
				}
			}
			l->near[i] = initLocation(name, rand() % 3 + 2);
			l->near[i]->near[0] = l;
		}
	}
}

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
	int i;
	/* Give us space for the new location */
	Location* l = malloc(sizeof(Location));

	l->name = name;
	/* Allocate space for the nearby locations */
	l->near = malloc(nearCount * sizeof(Location*));
	for(i = 0; i < nearCount; i++) {
		l->near[i] = calloc(1, sizeof(Location));
	}
	l->nearCount = nearCount;

	l->isValid = 1;
	locationCount++;
	return l;
}
