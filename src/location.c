#include <stdlib.h>

typedef struct Location {
	char isValid;
	char* name;
	struct Location* near;
	int nearCount;
} Location;

Location* initLocation(char* name, int nearCount) {
	Location* l = malloc(sizeof(Location));
	l->name = name;
	l->near = calloc(sizeof(Location) * nearCount, 1);
	l->nearCount = nearCount;
	l->isValid = 1;
	return l;
}
