#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define DAILYMIN 1440//Amount of minutes in 24 hours. Will be used when allocating memory for an array that is to hold 24 hours of minute data.

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;


//This struct stores all the minute data collected on the fitbit. An array type FitbitData of 1440 is declared in main.
typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

//Accepts in an array type FitbitData, reads all data in from .csv file and stores it into the array of structs.
//Also this function "cleans" the data by getting rid of any data entries from a different patient as well as 
//making sure there is no empty fields remaining in the data.
void readData(FILE* infile, FitbitData data[]);

//Accepts in data array and results file, adds the users calories together from the array and prints the total to the screen.
void computeTotalCalories(FitbitData data[], FILE* outfile);

//Adds total distance and displays it to screen and results file. 
void computeDistanceWalked(FitbitData data[], FILE* outfile);

//Adds total floors walked and displays it to screen and results file. 
void computeFloorsWalked(FitbitData data[], FILE* outfile);

//Adds total steps taken and displays them to the screen and to the results file. 
void computeStepsTaken(FitbitData data[], FILE* outfile);

//Takes all of the valid heartrate data and finds the average heartrate per minute. 
void computeHeartrate(FitbitData data[], FILE* outfile);

//This function traverses through an array to find the max amount of steps that the user took in a single minute.
void computeMaxSteps(FitbitData data[], FILE* outfile);



