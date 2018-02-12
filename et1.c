/*
An ETL program to read in CSV data from an index of airstrips in Florida.
Michael Hollinger 2/11/2019
Written for Michael McAlpin's CS1 class at UCF
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airPdata.h"

//Size of a line of input
#define BUFFER_SIZE 1024

int CountLines(char * filename);
void PrintData(airPdata * airport);

int main(int argc, char* argv[])
{
	FILE * ifp = fopen(argv[1], "r");
	char buffer[BUFFER_SIZE];
	char * token;
	//Stores each lexeme on every line.
	char tokenList[15][50];
	
	if(ifp == NULL)
	{
		printf("etl ERROR: File %s not found.\n", argv[1]);
	}

	//File size.
	int numLines = CountLines(argv[1]);
	
	//List of data indices.
	struct airPdata airPorts[numLines];

	//Formatting.
	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s Tower\n",
"FAA Site", "Short Name", "Airport Name", "City", "ST",
"Latitude", "Longitude");

	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s =====\n",
"========", "==========", "============", "====", "==",
"========", "=========");

	int i; 

	//The real meat of the code.
	for(i = 0; i < numLines; i++)
	{
		int j = 0;

		fgets(buffer, BUFFER_SIZE, ifp);
		//This is a mutable line.
		char * temp = strdup(buffer);
		//Single character, Y or N.
		char * tower;

		while((token = strsep(&temp, ",")) != NULL)
		{
			//If it's an unnecessary value, get rid of it.
			if(!strcmp(token, "ASO") || (!strcmp(token, "ORL") && j != 1) || !strcmp(token, "PR") || !strcmp(token, "NON-NPIAS") || !strcmp(token, "PU") || !strcmp(token, "NONE"))
			{
				token == NULL;
				continue;
			}

			//If it's a tower, store it to the appropriate indice of the list.
			else if(!strcmp(token, "Y") || !strcmp(token, "N"))
			{
				strcpy(tokenList[7], token);
				j++;
			}

			//If not, good to go.
			else
			{
				strcpy(tokenList[j], token);				
				j++;
			}						
		}	
				//Assign each lexeme to the appropriate field of each indice of the list.
				airPorts[i].siteNumber = tokenList[0];
				airPorts[i].locID = tokenList[1];
				airPorts[i].fieldName = tokenList[2];
				airPorts[i].city = tokenList[3];
				airPorts[i].state = tokenList[4];
				airPorts[i].latitude = tokenList[5];
				airPorts[i].longitude = tokenList[6];
				airPorts[i].controlTower = tokenList[7];
				PrintData(&airPorts[i]);			
	}	

	fclose(ifp);
	return 0;
}

//Utility function to count the number of lines in any arbitrary CSV file.
int CountLines(char *filename)
{
	FILE * ifp = fopen(filename, "r");
	int ch = 0;
	int count = 0;

	if(ifp == NULL)
	{
		return 0;
	}

	count++;

	while((ch = fgetc(ifp)) != EOF)
	{
		if(ch == '\n')
		{
			count++;
		}
	}

	fclose(ifp);
	return count;
}

//Prints the data of a given indice of the list.
void PrintData(airPdata * airPort)
{
	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s %s\n", airPort->siteNumber, airPort->locID, airPort->fieldName, airPort->city, airPort->state, airPort->latitude, airPort->longitude, airPort->controlTower);	
}