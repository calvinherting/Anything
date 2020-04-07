#include "Header.h"

int isEmpty(Node* head)//Checks to see if the list is empty.
{
	int status = 0;
	if (head == NULL)
	{
		status = TRUE;
	}
	return status;
}



int displayMenu(void)//Displays menu and returns user choice.
{
	int choice = -1;
	while (choice == -1)
	{
		printf("\n\n* 1.) Load Videos\n* 2.) Store Videos\n* 3.) Display Videos\n* 4.) Insert Videos\n* 5.) Delete Videos\n* 6.) Edit Videos\n* 7.) Sort Videos\n* 8.) Rate Videos\n* 9.) Play Videos\n* 10.) Shuffle Videos\n* 11.) Exit Playlist Manager\n\nUser Option: ");
		scanf("%d", &choice);//Has problem when user inputs any other character other than an int.

		if (choice < 1 || choice > 11)//Checks to make sure user input is valid.
		{
			choice = -1;
			system("cls");
		}
	}
	return choice;
}



int insertFront(Node* newNode, Node** head, Node** tail)
{
	int status = 0;

	if (newNode != NULL)//Checks to see if memory was allocated for Node. 
	{
		status = 1;
	}

	Node* current = *head;

	if (isEmpty(*head))
	{
		
		newNode->Next = NULL;
		newNode->Prev = NULL;
		*head = newNode;
		*tail = newNode;
	}
	else
	{
		current->Prev = newNode;
		newNode->Next = *head;
		*head = newNode;
		newNode->Prev = NULL;
	}
	return status;
}



void readFile(Node** head, Node** tail)
{
	FILE* infile = fopen("PlayList.csv", "r");
	char* ptr;
	char buffer[300];
	Node* newNode = NULL;

	//This determines if the file opened successfully.

	if (infile != NULL)
	{
		printf("***Video file opened successfully.\n");
	}
	else
	{
		printf("Video file could not be opened... \n");
		return;
	}



	//Read data from file and stores it into Nodes

	fgets(buffer, 200, infile);
	while (!feof(infile))
	{
		Node* newNode = (Node*)malloc(sizeof(Node));
		fgets(buffer, 300, infile);//Each time through for loop, it will read in a single line of data so that I can parse it and place it into individual fields within data part of node.

		//Reads all data from line into newNode
		ptr = strtok(buffer, ",");
		strcpy(newNode->Data.title, ptr);
		ptr = strtok(NULL, ",");
		strcpy(newNode->Data.director, ptr);
		ptr = strtok(NULL, ",");
		strcpy(newNode->Data.description, ptr);
		ptr = strtok(NULL, ",");
		strcpy(newNode->Data.genre, ptr);
		ptr = strtok(NULL, ":");
		newNode->Data.runtime.hours = atoi(ptr);
		ptr = strtok(NULL, ",");
		newNode->Data.runtime.minutes= atoi(ptr);
		ptr = strtok(NULL, ",");
		newNode->Data.year = atoi(ptr);
		ptr = strtok(NULL, ",");
		newNode->Data.timesPlayed = atoi(ptr);
		ptr = strtok(NULL, ",");
		newNode->Data.rating = atoi(ptr);
		insertFront(newNode, head, tail);
	}
		printf("***Videos were successfully loaded!\n");
		fclose(infile);
		printf("***Videos file closed successfully!\n");
}



void printList(Node* head)
{
	system("cls");
	Node* current = head;
	if (isEmpty(head))
	{
		printf("\n***The list is empty!");
	}
	else
	{
		printf("***The videos you have in your playlist are...\n\n\n");
		while (current != NULL)
		{
			printf("Title: %s\n", current->Data.title);
			printf("Director: %s\n", current->Data.director);
			printf("Description: %s\n", current->Data.description);
			printf("Genre: %s\n", current->Data.genre);
			printf("Runtime: %d hours and %d minutes\n", current->Data.runtime.hours, current->Data.runtime.minutes);
			printf("Year: %d\n", current->Data.year);
			printf("Times Played: %d\n", current->Data.timesPlayed);
			printf("Rating: %d\n\n\n\n", current->Data.rating);
			
			
			current = current->Next;
		}
	}
}



void writeFile(Node** tail)
{
	Node* current = *tail;

	FILE* outfile = NULL;
	outfile = fopen("PlayList.csv", "w");
	if (outfile != NULL)
	{
		printf("***File opened successfully for writing!\n");
	}
	else
	{
		printf("***File failed to open for writing...");
		return;
	}

	fprintf(outfile, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating\n");
	while (current != NULL)
	{
		fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d,%d", current->Data.title, current->Data.director, current->Data.description, current->Data.genre, current->Data.runtime.hours, current->Data.runtime.minutes, current->Data.year, current->Data.timesPlayed, current->Data.rating);
		
		if (current->Prev != NULL)
		{
			fprintf(outfile, "\n");
		}

		current = current->Prev;
	}
	printf("***Videos successfully recorded on file\n");

	fclose(outfile);
	printf("***File closed successfully!\n");
}



void userInsert(Node** head, Node** tail)
{
	system("cls");//Clears the menu screen before prompting user for video information.
	Node* newNode = (Node*)malloc(sizeof(Node));//Allocates space for a node that will be added to front of list. 
	Node* current = *head;

	printf("***Please enter the information of the video you would like to add to the front of the playlist...\n\n");
	printf("\nTitle: ");
	scanf("%s", &newNode->Data.title);
	printf("\nDirector: ");
	scanf(" ");
	scanf("%s", &newNode->Data.director);
	
	printf("\nDescription: ");scanf(" ");
	scanf("%s", &newNode->Data.description);
	
	printf("\nGenre: ");
	scanf("%s", &newNode->Data.genre);
	printf("\nRuntime... hours: ");
	scanf("%d", &newNode->Data.runtime.hours);
	printf("\n... minutes: ");
	scanf("%d", &newNode->Data.runtime.minutes);
	printf("\nYear: ");
	scanf("%d", &newNode->Data.year);
	printf("\nTimes Played: ");
	scanf("%d", &newNode->Data.timesPlayed);
	printf("\nRating (1-5): ");
	scanf("%d", &newNode->Data.rating);

	if (isEmpty(*head))
	{
		
		newNode->Next = NULL;
		newNode->Prev = NULL;
		*head = newNode;
		*tail = newNode;
	}
	else
	{
		current->Prev = newNode;
		newNode->Next = *head;
		*head = newNode;
		newNode->Prev = NULL;
	}
}



void editList(Node** head)
{
	Node* edit;
	char director[50];
	char ndata[200];
	int data = 0;
	int choice = 0;
	system("cls");
	printf("***Enter the director of the video that you would like to edit...");
	scanf(" ");
	gets(director);
	
	edit = findDirector(head, director);
	while (choice == 0 && edit != NULL)
	{
		printf("\n\nWhat aspects of this video would you like to edit?...\n1.) Title\n2.) Director\n3.) Description\n4.) Genre\n5.) Runtime\n6.) Years\n7.) Times Played\n8.) Rating\n\nChoice:  ");
		scanf("%d", &choice);
		if (choice == 1)
		{
			
			printf("What would you like the new title to be?\nTitle: ");
			scanf(" ");
			gets(ndata);
			strcpy(edit->Data.title, ndata);
		}
		else if (choice == 2)
		{
			printf("What would you like the new Director to be?\nDirector: ");
			scanf(" ");
			gets(ndata);
			strcpy(edit->Data.director, ndata);
		}
		else if (choice == 3)
		{
			printf("What would you like the new Description to be?\nDescription: ");
			scanf(" ");
			gets(ndata);
			strcpy(edit->Data.description, ndata);
		}
		else if (choice == 4)
		{
			printf("What would you like the new genre to be?\nGenre: ");
			scanf(" ");
			gets(ndata);
			strcpy(edit->Data.genre, ndata);
		}
		else if (choice == 5)
		{
			printf("What would you like the new runtime to be?\nHours: ");
			scanf("%d", &data);
			edit->Data.runtime.hours = data;
			printf("\nMinutes: ");
			scanf("%d", &data);
			edit->Data.runtime.minutes = data;
			
		}
		else if (choice == 6)
		{
			printf("What would you like the new year to be?\nYear: ");
			scanf("%d", &data);
			edit->Data.year = data;
		}
		else if (choice == 7)
		{
			printf("What would you like the new Times Played to be?\nTimes Played: ");
			scanf("%d", &data);
			edit->Data.timesPlayed = data;
		}
		else if (choice == 8)
		{
			printf("What would you like the new Rating to be?\nRating: ");
			scanf("%d", &data);
			if (data < 6 && data >0)
			{
				edit->Data.rating = data;
			}
			else
			{
				printf("\n****Invalid rating entered (Enter a rating between 1 and 5");
				choice = 0;
			}
		}
		else//Sends back to while loop for invalid input
		{
			choice = 0;
		}
	}
}



Node* findDirector(Node** head, char* director)
{
	Node* current = *head;
	int choice = 0;

	while (current->Next != NULL && strcmp(current->Data.director, director) != 0)
	{
		current = current->Next;
	}

	if (strcmp(current->Data.director, director) == 0)
	{
		printf("\n\n***Successfully found a video.");
		return current;
	}
	else
	{
		printf("\n\nVideo with the director %s is not in the list.", director);
		return NULL;
	}
}



void rateFilm(Node** head)
{
	Node* current = *head;
	int choice = 0;
	system("cls");
	printf("Give a rating between 1 and 5 to each of the films\n\n");
	while (current != NULL)
	{
		while (choice < 1 || choice > 5)
		{
			printf("%s: ", current->Data.title);
			scanf("%d", &choice);
		}
		current->Data.rating = choice;
		current = current->Next;
		choice = 0;
	}
}



void playFilm(Node* head)
{
	int choice = 0;
	Node* current = head;
	while (current != NULL && choice != 1)
	{
		printf("Would you like to start playing playlist from '%s'? Type 1 for yes and 0 for no...\nChoice: ", current->Data.title);
		scanf("%d", &choice);
		if (choice != 1)
		{
			current = current->Next;
		}
	}
	printList(current);
}