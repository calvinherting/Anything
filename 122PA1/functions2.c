#include "Header.h"
//readData gets all of the information from the csv file and stores it into an array of structs called data.
//Along the way, it "cleans" the data by checking to make sure it is the same user, no minutes are repeated,
//and it puts in non-valid numbers when there is an empty field. 
void readData(FILE* infile, FitbitData data[])
{
	char* ptr;
	char buffer[100];
	int i = -1;
	int flag;
	fgets(buffer, 100, infile);//Gets rid of the whole title line in infile so that I can start reading the data. 

	for (i = 0; i < 1440; i++)//Loops through 1440 times, which is how many minutes are in a day.
	{
		flag = 0;//Will use this flag variable to determine if there are any repeated minutes in the data.
		fgets(buffer, 100, infile);//Each time through for loop, it will read in a single line of data so that I can parse it and place it into individual fields within data array.
		ptr = strtok(buffer, ",");
		strcpy(data[i].patient, ptr);//Places the first piece of data (patient) from each lne into patient slot in the array of FitbitData structs.

		if (strcmp(data[i].patient, "12cx7") != 0)//This checks to see if there are any pieces of data from a user other than our target user "12cx7"
		{
			i--;//If the data is from a different user, this will simply allow that line of data to be forgotten and overwritten by the next iteration.
		}
		else
		{
			ptr = strtok(NULL, ",");
			if (i != 0)
			{
				if (strcmp(data[i - 1].minute, ptr) == 0)//Checks to see if the minute value on the current line is the same as the last minute which is already stored in the array.
				{
					flag = 1;
					i--;//If the minute is a repeat, it will cause this line of data to be forgotten and overwritten by the next. 
				}
			}
			if (flag != 1)
			{
				strcpy(data[i].minute, ptr);//Continues parsing data and placing it in data array in the corresponding fields. 
				ptr = strtok(NULL, ",");
				data[i].calories = atof(ptr);
				ptr = strtok(NULL, ",");
				data[i].distance = atof(ptr);
				ptr = strtok(NULL, ",");
				data[i].floors = atoi(ptr);
				ptr = strtok(NULL, ",");
				if (ptr == NULL)//If there is a missing data value for heartrate, I replaced NULL with 10000 which will make it easier to ignore when I write the average heartrate algorithm.
				{
					data[i].heartRate = 10000;
				}
				else
				{
					data[i].heartRate = atoi(ptr);
				}
				ptr = strtok(NULL, ",");
				data[i].steps = atoi(ptr);
				ptr = strtok(NULL, ",");
				if (ptr == NULL)//If there is a missing value for sleep level I set it to 0 which corresponds in the struct to "NONE"
				{
					data[i].sleepLevel = 0;
				}
				else
				{
					data[i].sleepLevel = atoi(ptr);
				}
			}
		}
	}
}

//computeTotalCalories takes in the data array and computes the total amount of calories that the user burnt in a
//24 hour span.
void computeTotalCalories(FitbitData data[], FILE* outfile)
{
	double totalCalories = 0.0;
	for (int i = 0; i < 1440; i++)
	{
		totalCalories += data[i].calories;//Adds up the calories from each index in the array.
	}
	printf("Total Calories Burnt: %.2lf\n", totalCalories);//Displays result to screen and also to results file!
	fprintf(outfile, "Total Calories Burnt: %.2lf\n", totalCalories);
}

//computeDistanceWalked takes in the data array and computes the total amount of miles the user walked in a
//24 hour span.
void computeDistanceWalked(FitbitData data[], FILE* outfile)
{
	double distance = 0.0;
	for (int i = 0; i < 1440; i++)
	{
		distance += data[i].distance;//Adds up distance from each index of array.
	}
	printf("Total Distance Walked in Miles: %.2lf\n", distance);
	fprintf(outfile, "Total Distance Walked in Miles: %.2lf\n", distance);//Display to screen and file. 
}

//computeFloorsWalked takes in the data array and computes the total amount of floors that the user walked in a
//24 hour span.
void computeFloorsWalked(FitbitData data[], FILE* outfile)
{
	int floors = 0;
	for (int i = 0; i < 1440; i++)
	{
		floors += data[i].floors;
	}
	printf("Total Floors Walked: %d\n", floors);
	fprintf(outfile, "Total Floors Walked: %d\n", floors);
}

//computeStepsTaken takes in the data array and computes the total amount of steps that the user took in a
//24 hour span.
void computeStepsTaken(FitbitData data[], FILE* outfile)
{
	int steps = 0;
	for (int i = 0; i < 1440; i++)
	{
		if (data[i].steps == 10000)//The missing values that I changed in readData function from NULL to 10000 are being ignored when finding average. 
		{
			data[i].steps = 0;
		}
		steps += data[i].steps;
	}
	printf("Total Steps Taken: %d\n", steps);
	fprintf(outfile, "Total Steps Taken: %d\n", steps);
}

//computeHeartrate takes in the data array and computes the AVERAGE heartrate per minute for the user in a
//24 hour span.
void computeHeartrate(FitbitData data[], FILE* outfile)
{
	double rate = 0.0;
	int count = 0;//To count how many data values were missing so they don't affect the average.
	for (int i = 0; i < 1440; i++)
	{
		if (data[i].heartRate == 10000)
		{
			data[i].heartRate = 0;
			count++;
		}
		rate += data[i].heartRate;
	}
	rate = rate / 1440 - count;//Takes total heartrate and divides it by the minutes that were logged on fitbit to find an average heartbeat per minute. 
	printf("Average Heart Rate: %.2lf beats per minute\n", rate);
	fprintf(outfile, "Average Heart Rate: %.2lf beats per minute\n", rate);
}

//computeMaxSteps decides the most amount of steps that the user took in a single minute. 
void computeMaxSteps(FitbitData data[], FILE* outfile)
{
	int max = 0;
	int minute = 0;//Will keep track of which minute has the max amount of steps.
	for (int i = 0; i < 1440; i++)//Traverses the array and decides which minute has the most steps.
	{
		if (data[i].steps >= max)//If there are multiple maxes, I will display the later minute values max. 
		{
			max = data[i].steps;
			minute = i + 1;
		}
	}
	printf("Max Steps in a Minute: %d steps during minute %d\n", max, minute);
	fprintf(outfile, "Max Steps in a Minute: %d steps during minute %d\n", max, minute);
}