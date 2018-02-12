//This header file just contains the struct definition.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct airPdata
{
	char *siteNumber;
	char *locID;
	char *fieldName;
	char *city;
	char *state;
	char *latitude;
	char *longitude;
	char *controlTower;
} airPdata;