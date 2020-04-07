#include "Header.h"

/******************************************************************************************
* Programmer: Calvin Herting                                                              *
* Class: CptS 122, Spring, 2019; Lab Section 2                                            *
* Programming Assignment: PA2                                                             *
* Date: February 6, 2020                                                                  *
* Description: Creating a basic video playlist manager.                                   *
*******************************************************************************************/

int main(void)
{
	int userChoice = 0;
	Node* head = NULL;
	Node* tail = NULL;

	while (userChoice != 11)
	{
		printf("*****Welcome to the basic video playlist manager... please select an option to get started!*****\n\n");
		userChoice = displayMenu();

		if (userChoice == 1)//Must read all records from a file and put them in a doubly linked list.
		{
			readFile(&head, &tail);
		}
		if (userChoice == 2)//Must write all records from linked list to .csv file and overwrite previous data.
		{
			writeFile(&tail);
		}
		if (userChoice == 3)//Need a Print menu. Must print records to the screen, depending on what the user wants to see.
		{
			printList(head);
		}
		if (userChoice == 4)//Must insert a video at the beginning of the playlist.
		{
			userInsert(&head, &tail);
		}
		if (userChoice == 5)//Must delete a video from the playlist.
		{
			system("cls");
			printf("This feature cannot be accessed yet...");
		}
		if (userChoice == 6)//Allows the user to search list by director and then prompts them which piece of information they want to edit.
		{
			editList(&head);
		}
		if (userChoice == 7)//Sorts playlist alphabetically
		{
			system("cls");
			printf("This feature cannot be accessed yet...");
		}
		if (userChoice == 8)//Allows user to rate whichever video they want.
		{
			rateFilm(&head);
		}
		if (userChoice == 9)//Allows user to select a video and then displays the contents
							//of that video for a short time, clears the screen, and plays
							//the rest of the videos in the playlist after that the same way.
		{
			playFilm(head);
		}
		if (userChoice == 10)//Shuffles the playlist, randomizing the order. 
		{
			system("cls");
			printf("This feature cannot be accessed yet...");
		}
		if (userChoice == 11)//Saves the most recent playlist to .csv file and exits program.
		{
			writeFile(&tail);
		}
		printf("\n\n*****Press any button to return to main menu*****");
		system("pause");
		system("cls");
	}
	

	return 0;
}