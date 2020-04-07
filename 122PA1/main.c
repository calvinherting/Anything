#include "Header.h"
/******************************************************************************************
* Programmer: Calvin Herting                                                              *
* Class: CptS 122, Spring, 2019; Lab Section 2                                            *
* Programming Assignment: PA1                                                             *
* Date: January 22, 2020                                                                  *
* Description: Analyze data that was generated from Fitbit devices.                     *
*******************************************************************************************/

int main(void)
{
	FitbitData* data = malloc(sizeof(FitbitData) * DAILYMIN);
	FILE* infile = NULL;
	FILE* outfile = NULL;


	infile = fopen("FitbitData.csv", "r");//Opens .csv file to read, uses if else statement to determine if the file was able to be opened or not.
	if (infile != NULL)
	{
		printf("File opened successfully successfully for reading.\n");
	}
	else
	{
		printf("File could not be opened... ending program.");
		return;
	}
	
	
	outfile = fopen("results.csv", "w");//Opens a result file to write, with another if else statement to ensure that the file either opened successfully or not. 
	if (outfile != NULL)
	{
		printf("File opened successfully for writing.\n\n\n");
	}
	else
	{
		printf("File could not be opened... ending program.");
		return;
	}
	
	//FUNCTION CALLS
	readData(infile, data);
	computeTotalCalories(data, outfile);
	computeDistanceWalked(data, outfile);
	computeFloorsWalked(data, outfile);
	computeHeartrate(data, outfile);
	computeStepsTaken(data, outfile);
	computeMaxSteps(data, outfile);
	
	//Closes both files
	fclose(infile);
	fclose(outfile);

	return 0;
}